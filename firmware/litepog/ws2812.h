#ifndef __WS2812_H__
#define __WS2812_H__
#include <msp430.h>
#include "config.h"

// Useful typedefs
typedef unsigned char u_char;	// 8 bit
typedef unsigned int u_int;     // 16 bit

// Transmit codes
#define HIGH_CODE   (0b11000000)
#define LOW_CODE    (0b10000000)

// Configure processor to output to data strip
void initStrip(void);

// Send colors to the strip and show them. Disables interrupts while processing.
void showStrip(void);

// Set the color of a certain LED
void setLEDColor(u_int p, u_char r, u_char g, u_char b);

// Clear the color of all LEDs (make them black/off)
void clearStrip(void);

// Fill the strip with a solid color. This will update the strip.
void fillStrip(u_char r, u_char g, u_char b);

#endif // __WS2812_H__
