#pragma once
const uint32_t humidity_width = 60;
const uint32_t humidity_height = 60;
const uint8_t humidity_data[(60*60)/2] = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x2A, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0x11, 0xF4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x4E, 0xC5, 0x82, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x27, 0xFD, 0x19, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0xA1, 0xFF, 0x4F, 0xF4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0xF6, 0xFF, 0xDF, 0x82, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x36, 0xFE, 0xFF, 0xFF, 0x1A, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0xA1, 0xFF, 0xFF, 0xFF, 0x5F, 0xE3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0xF6, 0xFF, 0xFF, 0xFF, 0xDF, 0x72, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x27, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x1A, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0xA1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x5F, 0xF4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0xF5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0x91, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x19, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x28, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0x82, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x4F, 0xF5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x5F, 0xE3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0B, 0xFA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x36, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x54, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x2D, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAF, 0xD1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xE2, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x72, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x19, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x2A, 0xFD, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDE, 0xFF, 0xFF, 0xFF, 0xEF, 0x82, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x2F, 0xF7, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x17, 0xFC, 0xFF, 0xFF, 0x9F, 0xD2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAF, 0xE1, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0x31, 0xE3, 0xFF, 0xFF, 0x2F, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x73, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0xD6, 0x62, 0xFF, 0xFF, 0x2A, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x29, 0xFE, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x25, 0xFE, 0x0A, 0xFB, 0xFF, 0x63, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1E, 0xFB, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAF, 0xB1, 0xFF, 0x5F, 0xE2, 0xCF, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xF3, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1D, 0xF8, 0xFF, 0xFF, 0x63, 0x7F, 0xF3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xFE, 0xCF, 0xC1, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x45, 0xFE, 0xFF, 0xFF, 0x1B, 0x2A, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x5F, 0xF7, 0xEF, 0x73, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAF, 0xB1, 0xFF, 0xFF, 0xFF, 0x6F, 0x12, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8F, 0xE2, 0xFF, 0x46, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x2E, 0xF7, 0xFF, 0xFF, 0xFF, 0xEF, 0x22, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xD0, 0xFF, 0x2B, 0xFE, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x27, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x1A, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA2, 0xFF, 0x0E, 0xFE, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0xA1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x5F, 0xF4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x84, 0xFF, 0x0F, 0xFE, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x4E, 0xF5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0x91, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x85, 0xFF, 0x0F, 0xFE, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x19, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x28, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA2, 0xFF, 0x0E, 0xFE, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xEF, 0x72, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x2F, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0xFF, 0x1B, 0xFE, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x8F, 0xE2, 0xFF, 0xDF, 0x69, 0x44, 0x75, 0xEB, 0xFF, 0xAF, 0xD1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8F, 0xF2, 0xFF, 0x47, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x2E, 0xF9, 0xDF, 0x16, 0x62, 0x97, 0x47, 0x21, 0xF9, 0xFF, 0x63, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x2E, 0xF7, 0xFF, 0x73, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x38, 0xFF, 0x2B, 0xA3, 0xFE, 0xFF, 0xFF, 0x7D, 0x52, 0xFE, 0x1A, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x19, 0xFD, 0xCF, 0xC1, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xEF, 0x91, 0xBF, 0x61, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x2C, 0xE3, 0x4F, 0xF6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0x91, 0xFF, 0x7F, 0xF3, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x9F, 0xE2, 0x2D, 0xF6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0x52, 0xAF, 0xD2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x2C, 0xF5, 0xFF, 0x1D, 0xFB, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x3F, 0xF8, 0x35, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1C, 0xFC, 0x82, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0x52, 0xFE, 0xEF, 0x44, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x1B, 0xCE, 0xC1, 0xFF, 0xCF, 0x44, 0xFC, 0xFF, 0xD8, 0xFF, 0x6F, 0xF4, 0x18, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x4F, 0xF8, 0xFF, 0x7F, 0xD2, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x45, 0x7F, 0xE2, 0xFF, 0x4F, 0x55, 0xF3, 0x5F, 0xD1, 0xFF, 0xBF, 0xD1, 0x1D, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x19, 0xFA, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xEF, 0x92, 0x4F, 0xF5, 0xFF, 0x2F, 0x78, 0xD2, 0x15, 0xFB, 0xFF, 0xEF, 0xA1, 0x3F, 0xF6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8F, 0x91, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xDF, 0xD0, 0x3E, 0xF8, 0xFF, 0xAF, 0x11, 0x69, 0xC1, 0xFF, 0xFF, 0xFF, 0x91, 0x7F, 0xF4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0x14, 0xFA, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xCF, 0xF0, 0x2E, 0xF9, 0xFF, 0xFF, 0xEF, 0x26, 0xCA, 0xFE, 0xFF, 0xFF, 0x82, 0xAF, 0x40, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0x28, 0xC4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xBF, 0xF0, 0x3F, 0xF8, 0xFF, 0xFF, 0x6F, 0xB2, 0x14, 0xD2, 0xFF, 0xFF, 0x91, 0xBF, 0x51, 0x21, 0xD8, 0xFE, 0xFF, 0xEF, 0xBE, 0x16, 0x92, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xCF, 0xF0, 0x5F, 0xF5, 0xFF, 0xFF, 0x15, 0xBC, 0xB2, 0x83, 0xFF, 0xEF, 0xB1, 0xAF, 0xE3, 0x7C, 0x03, 0x42, 0x54, 0x34, 0x11, 0xA5, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xDF, 0xD1, 0x8F, 0xE2, 0xFF, 0x7F, 0xC1, 0xCF, 0x51, 0xA1, 0xFF, 0xAF, 0xD1, 0x7F, 0xF4, 0xFF, 0xDF, 0x8A, 0x56, 0x96, 0xEC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xEF, 0x92, 0xDF, 0xA0, 0xFF, 0xCF, 0xFD, 0xFF, 0x6B, 0xFA, 0xFF, 0x5F, 0xF5, 0x3F, 0xF6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x55, 0xFF, 0x27, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1A, 0xFC, 0x1D, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x1C, 0xFD, 0x3E, 0xE4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0x81, 0xFF, 0x38, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x5F, 0xF6, 0xDF, 0x43, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x2A, 0xF6, 0xDF, 0xA2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xCF, 0xB2, 0xFF, 0x4D, 0x81, 0xFD, 0xFF, 0xEF, 0x5B, 0x81, 0xFF, 0x5F, 0xF4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x29, 0xFE, 0xEF, 0x29, 0x21, 0x43, 0x23, 0x40, 0xFC, 0xFF, 0x28, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x7F, 0xC2, 0xFF, 0xFF, 0x7B, 0x55, 0x86, 0xFD, 0xFF, 0x9F, 0xB2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x18, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0x35, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0x43, 0xFA, 0xFF, 0xFF, 0xFF, 0xDF, 0x28, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0x23, 0x95, 0xBB, 0x8A, 0x24, 0xC5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0x7A, 0x45, 0x85, 0xDB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	};
