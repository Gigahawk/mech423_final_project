#include <msp430.h>
#include "ws2812.h"

// WS2812 takes GRB format
typedef struct {
    u_char green;
    u_char red;
    u_char blue;
} LED;

static LED leds[NPX_NUM_LEDS] = { { 0, 0, 0 } };

// Initializes everything needed to use this library. This clears the strip.
void initStrip() {
    NPX_PxDIR &= ~(NPX_PIN);

    NPX_PxSEL0 &= ~(NPX_PIN);
    NPX_PxSEL1 |= (NPX_PIN);

#ifdef NPX_DEBUG
    // enable SPI CLK for timing debug
    NPX_DBG_CLK_PxSEL0 &= ~(NPX_DBG_CLK_PIN);
    NPX_DBG_CLK_PxSEL1 |= NPX_DBG_CLK_PIN;
#endif

    // Hold SPI peripheral in reset
    NPX_UCxCTLW0 |= UCSWRST;

    // Set mode to 3-pin SPI
    NPX_UCxCTLW0 &= ~(UCMODE0 | UCMODE1);
    NPX_UCxCTLW0 |= (UCMODE_0);

    // Clock phase 1
    NPX_UCxCTLW0 |= UCCKPH;

    // Clock polarity inactive low
    NPX_UCxCTLW0 &= ~(UCCKPL);

    // Data is MSB first
    NPX_UCxCTLW0 |= UCMSB;

    // Act as SPI master
    NPX_UCxCTLW0 |= UCMST;

    // Enable synchronous mode
    NPX_UCxCTLW0 |= UCSYNC;

    // Clock source: SMCLK
    NPX_UCxCTLW0 &= ~(UCSSEL0 | UCSSEL1);
    NPX_UCxCTLW0 |= (UCSSEL__SMCLK);

    // Divide BRCLK by 11
    NPX_UCxBR0 = 11;

    // Bring UCB0 out of reset
    NPX_UCxCTLW0 &= ~(UCSWRST);

    clearStrip();
    showStrip();
}

// Sets the color of a certain LED (0 indexed)
void setLEDColor(u_int p, u_char r, u_char g, u_char b) {
	leds[p].green = g;
    leds[p].red = r;
    leds[p].blue = b;
}

// Send colors to the strip and show them. Disables interrupts while processing.
void showStrip() {
    __disable_interrupt();

    // send RGB color for every LED
    unsigned int i, j;
    for (i = 0; i < NPX_NUM_LEDS; i++) {
        u_char *rgb = (u_char *)&leds[i]; // get GRB color for this LED

        // send green, then red, then blue
        for (j = 0; j < 3; j++) {
            u_char mask = 0x80;    // b1000000

            // check each of the 8 bits
            while (mask != 0) {
                while (!(NPX_UCxIFG & UCTXIFG));  // wait to transmit
                if (rgb[j] & mask) {              // most significant bit first
                    UCB0TXBUF = HIGH_CODE;        // send 1
                } else {
                    UCB0TXBUF = LOW_CODE;         // send 0
                }

                mask >>= 1;  // check next bit
            }
        }
    }

    // Wait for transfer to finish
    while(NPX_UCxSTATW & UCBUSY);

    // Reset SPI bus, SIMO only seems to idle low while/after reset
    NPX_UCxCTLW0 |= UCSWRST;

    // Hold SIMO low to latch values
    _delay_cycles(10000);

    // Release UCB0 from reset
    NPX_UCxCTLW0 &= ~(UCSWRST);

    __enable_interrupt();
}

// Clear the color of all LEDs (make them black/off)
void clearStrip() {
    fillStrip(0x00, 0x00, 0x00);  // black
}

// Fill the strip with a solid color. This will update the strip.
void fillStrip(u_char r, u_char g, u_char b) {
    int i;
    for (i = 0; i < NPX_NUM_LEDS; i++) {
        setLEDColor(i, r, g, b);  // set all LEDs to specified color
    }
}
