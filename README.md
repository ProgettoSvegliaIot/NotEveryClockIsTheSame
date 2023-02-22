# **NotEveryClockIsTheSame** - *a smart alarm project*

## What is this documentation about?

This documentation details the realization of a smart alarm, equipped with IoT features.
In addition to basic operation as clock and alarm, the user has two other possibilities:

- view in real time the weaher of a specific location, with its temperature and the percentage of humidity;

- check how many minutes the buses of a certain line arrive at a specific stop, and in which direction they are going

Below is an easy summary outline of screeshots viewable by a user using the product:

<br>
<img src="https://user-images.githubusercontent.com/108399870/220087728-0e4a8eb1-bb53-4262-890c-56db32b15b78.png" alt="What I can see as User" height="250">

## Instructions for use

After an inizialization phase, during which the device connects to the network, the time is displayed on the screen. Here you can also see if the alarm clock is enable or not.

To enter main menu you can press any button, except the return one.

Once here you can navigate through the variuos options using the right and left buttons.

Press *OK* button to make your choice.

- Set alarm: first of all you set the hours, then the minutes. Press *OK* to enable the alarm. Once enabled, it still be active until disabled.

- Show weather: the operation may take a few seconds. You will see the weather in Trento.

- Show arriving buses: the operation may take a few seconds. You will see the arriving buses.

When the alarm rings, press *RETURN* button to snooze alarm of 10 minutes, any other button to turn of the alarm. In this last case the alarm is already active for the following day.

To disable an alarm go to home screen, then press *RETURN* button. You will be asked if you are sure to perform the operation: press *OK* to confirm or *RETURN* to undo.

<br />

## Hardware components

-	MSP432-P401R with its RTC Module
-	ESP32-WROVER-E with its LILYGO T5 E-paper 4.7 INCH
-	Buzzer
-	Buttons
-	Cables for connection

<br />

## How does the entire project work?

#### Software structure

```
MSP
├── RTC 
│   └── implementation of module usage features, including customizing the calendar and turning on and off the alarm clock
├── Time_Management
│   └── defines a struct to keep the starting calendar and a function to fill the struct with timestamp conversions
├── Timer
│   └── code to configure the timer, enable and disable it, and managing the buttons whose interrupts activation depend 
│       on the timer
├── transport_base
│   └── functions for serializing and deserializing data before transmission and after reception using the UART protocol
├── transport_timestamp
│   └── functions for serializing and deserializating timestamp
├── uart_comunication
│   └── definition of the UART protocol and its functionalities
├── state_machine
│   └── definition of the system's overall control flow via FSM, as well as the definition of the interrupts that cause 
│       events on the basis of which, depending on the current state, various actions are taken as a result
├── main.c
    └── definition of the program's flow

ESP
├── api
│   └── webConnection
│           └── it describes the procedures for connecting to different APIs and interpreting the incoming data,  
│               making it a crucial file for Internet connections
├── fonts
│   ├── firasans
│   ├── roboto_all_small
│   ├── roboto_all_very_small
│   ├── roboto_numbers_medium
│   └── roboto_numbers
│           └── font used for writing on the screen
├── gui
│   ├── alarm_interface
│   ├── bus_interface
│   ├── interface_elements
│   ├── iot_clock
│   ├── menu_interface
│   ├── meteo_interface
│   └── set_interface
│           └── the multiple interfaces' definition and implementation of the features to display them on the screen
├── images
│   └── directory containing all the images used in the project as arrays of uint8_t
├── uart
│   ├── trasport_base
│   ├── transport_timestamp
│   └── uart_communication
│           └── files that correspond to those specified in the MSP for managing the UART protocol
├── main.c
│   └── definition of the program's flow
└── utils
    └── functions of general utility such as manipulating strings and expanding images
```

The communication between the two boards via the UART Protocol is what makes the smart alarm work. The MSP serves as the overall command center. It handles time and alarms through its integrated RTC module, and elaborate inputs, transmitting signals to the ESP.

### Let's examine the process in detail...

*Inizialization phase*

As seen in the ESP32 `main.c` code, the crucial operations are:
- `WifiConnection()` : allows the alarm clock to connect to the Internet
- `timestampAPIconnection(uint32 t * tStamp)` : inserts the timestamp's real-time value into the variable passed as a parameter, after making a request to the API for doing so
- `uart_send(int8_t  *  send_buf, size_t  len_toSend)` : the prepared timestamp is sent to the other board after a serialization process

After a sequence of basic hardware settings, the MSP is currently waiting for data:

- `Uart_Receive( )` : function designed to receive the timestamp over the UART protocol, returns its value after the data have been retrieved
- `configureRTC(uint32_t timesec)` : the RTC module's calendar registers are initialized with the timestamp value provided as a parameter, and they will now track the passage of time. The function also enables the module's interrupts

As a result, the `CURRENT_STATE` is set to *HOME*.

At this point, the initialization phase concludes with the transmission of the updated data to the ESP, which displays everything on the screen.
- ---
*General functioning*

> Note: from this point forward, all the ESP does is receive data from the MSP, show the current status on the screen, and maybe connect to the adequate APIs in the case of weather or transport.

The MSP, which was already defined as the primary control point, sends data to the ESP whenever a user pushes a button. The communication starts each time the minute, the current status, the alarm clock's enable status, or the time for which it has to be set changes.

The following two functions - which are part of the UART protocol - are involved in the information exchange:

- `Uart_Communicate(base * to_send)` : used by the MSP to transmit data each time an update occurs
- `uart_receive(uint8_t*  recv, size_t, uint8_t*  act_recv)` : ESP's method of receiving

The state machine definition, which can be seen in the code of the files `state machine.h` and `state machine.c` of MSP, is what controls the system's overall behavior. It consists of a series of pairings *{state, state function pointer}*. The implementation of the functions associated with each state determines how the device will behave in response to various events.

---
*Interrupt handlers*

Let's now focus on the management of interrupts, which define the event generated and the device's subsequent behavior:

>Note: this handlers are defined and implemented in MSP code

<br> `void RtcIsrHandler(void)`
The RTC's interruptions take place:

- every second: we use these interrupts to increase a counter variable, as you can see from the code. The counter is reset via the *TIMEOUT* event to return to the main state if it reaches the value of 30, unless we are in the *HOME* or *DRINN* states. In this manner, when the predetermined amount of time (30 sec) has passed on a certain screen, you will automatically return to *HOME*

- every minute: used to increase the minutes of the current time, with the hours being updated properly as needed

- when the alarm should sound: a *DRIN* event is generated, so the alarm clock switches into the *DRINN* state and sounds the buzzer.

<br>`void PORT5_IRQHandler()`
This is the buttons handler, which, generates the respective event based on the button that the user presses.
As you can see in the function code, here, there is a particularity: in order to prevent unintended state changes, a 1 second timer in compare mode is employed to temporarily disable the buttons interrupts. This decision was made to give the electrical signal time to stabilize. It functions like a debouncer.

How does the UART protocol work?
---
This component is both an important and challenging part of the project, and it is made to exchange data as a *vector of 8 bit integers*. 
It is a master-slave protocol, meaning that the roles of the actors utilizing it are predetermined.
Also, a parameter that denotes the lenght of the entire message to sent is defined, along with a few constants that indicate control or error codes.

Data processing involves two crucial procedures for sharing information:

- `void serialize(base * b, volatile int8_t *)` : the data must be serialized before being transferred, and the sending vector must then be put into the send buffer - executed by the master
- `base * deserialize(int8_t * serialized)` : once the vector containing the serialized data is received, it will be deserialized to an appropriate data structure that is returned from the function - executed by the slave

>Note: actually, rather than being 8 bits, the integers provided are 6 bits. This is the length of the *real* message. Control and error codes uses the remaining combinations. Negative numbers are also ignored as cause of problems on the receiver end.

A sample comunication works like this:

<img src='https://user-images.githubusercontent.com/47862158/220392502-2303ff63-4dc8-48ed-abda-2cec214a6958.png' style='width: 30%; margin: 0 auto; display: block;' />

## Error situations handled by the protocol 

- Desyncronization of the sender and the receiver
- One or many unit of data sent but never received
- The received data is incorrect

>Fun note: Every problem occurred multiple times even on wires that are less than 10 centimeters long.

### Desyncronization of the sender and the receiver

The protocol is based on **two arrays**, one on the Master (sender) and one on the slave (receiver).
If everything goes well, the two will be on the same *0 index* at the beginning

![image](https://user-images.githubusercontent.com/47862158/220388059-8b21cc91-a3a0-43b2-9fd6-f639536d78a9.png)

IF that's not the case, the situation will be, for example:
![image](https://user-images.githubusercontent.com/47862158/220393311-6847e01a-76c9-4782-aec9-2837eb25fc49.png)

When a value is received on the Slave end, the array index on which the value was saved is returned to the Master.
So it's easy to know when the desynchronization happends.
The master will send a `ERROR_NUM`, so that the slave can move it's index in the *0 position*, responding with a `ERROR_ACK`.
When this value is received on the Master end, it will start again sending the data from the beginning.

![image](https://user-images.githubusercontent.com/47862158/220393707-e7d5c4bb-cceb-471b-8639-1050f8d867f1.png)

The beginning situation has so been restored successfully on both ends.

### One or many unit of data sent but never received

This is done by implementing a Timeout strategy.
The timeout is calculated as a fixed `~3x` the time it normally takes to receive a response after sending the data.
It is done always on the Master end, that will send again the same data when the timeout occurs.

### The received data is incorrect

This is resolved using a 3-way handshake with a "*CRC*" check. 
The CRC value is requested from the Master and calculated on both ends. The slave will then send it's value, that is checked by the master, that will:

- Accept it, sending an *ACK* . If it's the same as the one Master calculated. 
- Refuse it, sending an *ERROR_NUM*. The flow continues as described earlier in the *Desyncronization* section, essentially starting over.

It is common knowledge between the two ends of **when** the handshake should begin.
If the master requests the CRC too early, it's the Slave who responds with a *ERROR_ACK*.
The handing is the usual, both the cards will reset their indexes to 0 and start over.

But how it's the CRC calulated?

Two constant values are needed: *CRC_START* and *CRC_SIZE*, that are known in advance by both cards.
The sum of all the received values is used to calculate it:

`CRC_START - ( sum(recv_buf) % CRC_SIZE )`

With the CRC_START set as 121 and CRC_SIZE as 55, the values between 66 and 121 are *used* / *reserved* for CRC, leaving the values from 0 to *actually* 65 for the user data. 6 bits are used for convenience

### Protocol implementation

The biggest challenge implementing has been figuring out that the right way to do it was to use polling instead of an interrupt-based approach.
To do that we used a `global volatile` variable to costantly check whenever a new value was received by UART.

The rest is just a switch that works based on the value received.

How does the e-Ink screen work?
---

This technology simulates the appearance of ink on a piece of paper, the fact that electrophoresis is utilized here sets them apart from LCD panels, which use a back light to illuminate the pixels and display the image. This kind of screen is internally composed of tiny electrically charged spheres, each of which is separated into two hemispheres: the black hemisphere is positively charged, and the white one is negatively charged. The spheres can be oriented to create the desired image by taking advantage of the electric fields.
In terms of software, we've utilized some of the screen's primitives in order to make use of its capabilities, here some examples:

- `writeln` : to type text into the screen

> Note: choosing the appropriate font type before beginning to write a text is necessary.
> We developed Python scripts to generate the appropriate fonts for our purposes.

- `write_mode` : used in our case to remove some elements; the term *white on white* describes our technique in which an element is covered by printing it on the screen in white

- `epd_clear_area_cycles` : utilized to control the amount of cleaning cycles and the area of the screen to be cleaned

- `epd_draw_grayscale_image` :  used to print a buffer containing elements on the screen. For instance, the time displayed in the *HOME* screen is made up of a collection of numbers that were collected inside of a structure, just like all the other components of various screens.

Every function we built to enable the GUI's representation of the various states starts with the word *draw_*.

## Project development environments

We used Code Composer Studio, an IDE designed exclusively for Texas Instruments embedded processors, to create the software that runs on the MSP.
In order to load the project into the board, just import the code into the IDE (making sure the folder name is *ProgettoSvegliaMSP* to import it correctly)

The DriverLib allows us to benefit from a greater level of abstraction when interacting with the hardware, so it's also needed to import it into the project.

The code that runs on the ESP, on the other hand, was developed using ![PlatformIO](https://platformio.org/), that basically enabled us to use the Arduino IDE inside Visual Studio Code.
To load the code is needed to open the folder as a project, and just click on the build button, to use the default configuration.

The internet connection to the following APIs provides the information required to get the timestamp, weather, and arriving buses:

- timestamp - ![ntppool.org](https://www.ntppool.org/it/)
- weather - ![openweathermap.org](https://openweathermap.org/)
- buses - ![traquantopassa.in](https://github.com/matteocontrini/traquantopassa)
