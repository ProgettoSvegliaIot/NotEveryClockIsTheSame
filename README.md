# ***NotEveryClockIsTheSame** - a smart alarm project*

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

<br>

## Hardware components
-	MSP432-P401R with its RTC Module
-	ESP32-WROVER-E with its LILYGO T5 E-paper 4.7 INCH
-	Buzzer
-	Buttons
-	Cables for connection

<br>

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
Also, a parameter that denotes the lenght of the message sent is defined, along with a few constants that indicate control or error codes.

Data processing involves two crucial procedures for sharing information:
- `void serialize(base * b, volatile int8_t *)` : the data must be serialized before being transferred, and the sending vector must then be correctly established - executed by the master
- `base * deserialize(int8_t * serialized)` : once the vector containing the serialized data is received, it will be deserialized inside of an appropriate data collection structure that is returned from the function - executed by the slave

>Note: actually, rather than being 8 bits, the integers provided are 6 bits. This is so that control and error codes can be used only with more bits.



---

*CRC mechanism*



To better understand the message exchange between master and slave, refer to a few simple diagrams:

---




Spiegare un attimo il  discorso delle interrupt uart

 

How does the e-Ink screen work?
---
This technology simulates the appearance of ink on a piece of paper, the fact that electrophoresis is utilized here sets them apart from LCD panels, which use a back light to illuminate the pixels and display the image. This kind of screen is internally composed of tiny electrically charged spheres, each of which is separated into two hemispheres: the black hemisphere is positively charged, and the white one is negatively charged. The spheres can be oriented to create the desired image by taking advantage of the electric fields.
In terms of software, we've utilized some of the screen's primitives in order to make use of its capabilities, here some examples:

- `writeln` : to type text into the screen
> Note: choosing the appropriate font type before beginning to write a text is necessary.
> We developed Pyhton scripts to generate the appropriate fonts for our purposes.

- `write_mode` : used in our case to remove some elements; the term *white on white* describes our technique in which an element is covered by printing it on the screen in white

- `epd_clear_area_cycles` : utilized to control the amount of cleaning cycles and the area of the screen to be cleaned

- `epd_draw_grayscale_image` :  used to print a buffer containing elements on the screen. For instance, the time displayed in the *HOME* screen is made up of a collection of numbers that were collected inside of a structure, just like all the other components of various screens.

Every function we built to enable the GUI's representation of the various states starts with the word *draw_*.


## Project development environments

We used Code Composer Studio, an IDE designed exclusively for Texas Instruments embedded processors, to create the software that runs on the MSP.
The introduction of the DriverLib allows us to benefit from a greater level of abstraction when interacting with the hardware.

The code that runs on the ESP, on the other hand, was developed using PlatformIO:  https://platformio.org/

The internet connection to the following APIs provides the information required to get the timestamp, weather, and arriving buses:
- timestamp - https://www.ntppool.org/it/
- weather - https://openweathermap.org/
- buses - https://github.com/matteocontrini/traquantopassa

