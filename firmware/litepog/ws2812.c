#include <msp430.h>
#include "ws2812.h"

#define ENABLE_SPI_PIN P1DIR &= ~(OUTPUT_PIN); P1SEL0 &= ~(OUTPUT_PIN); P1SEL1 |= (OUTPUT_PIN);
#define DISABLE_SPI_PIN P1SEL0 &= ~(OUTPUT_PIN); P1SEL1 &= ~(OUTPUT_PIN); P1DIR |= (OUTPUT_PIN); P1OUT &= ~(OUTPUT_PIN)

// WS2812 takes GRB format
typedef struct {
    u_char green;
    u_char red;
    u_char blue;
} LED;

static LED leds[NUM_LEDS] = { { 0, 0, 0 } };

// Initializes everything needed to use this library. This clears the strip.
void initStrip() {
    DISABLE_SPI_PIN;

    // Hold UCB0 in reset
    UCB0CTLW0 |= UCSWRST;

    // Set mode to 3-pin SPI
    UCB0CTLW0 &= ~(UCMODE0 | UCMODE1);
    UCB0CTLW0 |= (UCMODE_0);

    // Clock phase 1
    UCB0CTLW0 |= UCCKPH;

    // Clock polarity inactive low
    UCB0CTLW0 &= ~(UCCKPL);

    // Data is MSB first
    UCB0CTLW0 |= UCMSB;

    // UCB0 is SPI master
    UCB0CTLW0 |= UCMST;

    // Enable synchronous mode
    UCB0CTLW0 |= UCSYNC;

    // Clock source: SMCLK
    UCB0CTLW0 &= ~(UCSSEL0 | UCSSEL1);
    UCB0CTLW0 |= (UCSSEL__SMCLK);

    // Divide BRCLK by 11
    UCB0BR0 = 11;

    // Bring UCB0 out of reset
    UCB0CTLW0 &= ~(UCSWRST);

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
    _disable_interrupts();
    ENABLE_SPI_PIN;

    // send RGB color for every LED
    unsigned int i, j;
    for (i = 0; i < NUM_LEDS; i++) {
        u_char *rgb = (u_char *)&leds[i]; // get GRB color for this LED

        // send green, then red, then blue
        for (j = 0; j < 3; j++) {
            u_char mask = 0x80;    // b1000000

            // check each of the 8 bits
            while (mask != 0) {
                while (!(UCB0IFG & UCTXIFG));    // wait to transmit
                if (rgb[j] & mask) {        // most significant bit first
                    UCB0TXBUF = HIGH_CODE;  // send 1
                } else {
                    UCB0TXBUF = LOW_CODE;   // send 0
                }

                mask >>= 1;  // check next bit
            }
        }
    }


    while (!(UCB0IFG & UCTXIFG));
    // Hack cause CPOL setting doesn't seem to work
    DISABLE_SPI_PIN;
    // send RES code for at least 50 us (800 cycles at 16 MHz)
    _delay_cycles(10000);

    _enable_interrupts();
}

// Clear the color of all LEDs (make them black/off)
void clearStrip() {
    fillStrip(0x00, 0x00, 0x00);  // black
}

// Fill the strip with a solid color. This will update the strip.
void fillStrip(u_char r, u_char g, u_char b) {
    int i;
    for (i = 0; i < NUM_LEDS; i++) {
        setLEDColor(i, r, g, b);  // set all LEDs to specified color
    }
}
