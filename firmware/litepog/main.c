#include <msp430.h> 
#include "ws2812.h"

#define DELAY_COUNT 1000000;

void initClock(void) {
    // Unlock Clock System Control Registers
    CSCTL0_H = CSKEY_H;

    // Configure DCO to run at 24MHz
    CSCTL1 |= (DCORSEL);
    CSCTL1 &= ~(DCOFSEL0 | DCOFSEL1);
    CSCTL1 |= DCOFSEL_3;

    // Set SMCLK source to DCO
    CSCTL2 &= ~(SELS0 | SELS1 | SELS2);
    CSCTL2 |= SELS__DCOCLK;

    // Set SMCLK divider to 1
    CSCTL3 &= ~(DIVS0 | DIVS1 | DIVS2);
    CSCTL3 |= DIVS__1;

    // Set MCLK source to DCO
    //CSCTL2 &= ~(SELM0 | SELM1 | SELM2);
    CSCTL2 |= SELM__DCOCLK;

    // Set MCLK divider to 1
    CSCTL3 &= ~(DIVM0 | DIVM1 | DIVM2);
    CSCTL3 |= DIVM__1;
}

int main(void)
{
    volatile long i;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	initClock();

	initStrip();

	while(1) {
	    for(i = 0; i < NUM_LEDS; i++) {
	        clearStrip();
	        setLEDColor(i, 0, 0, 255);
	        showStrip();
	        _delay_cycles(1000000);
	    }
	    for(i = NUM_LEDS - 1; i >= 0; i--) {
	        clearStrip();
	        setLEDColor(i, 0, 0, 255);
	        showStrip();
	        _delay_cycles(1000000);
	    }
	}

	return 0;
}
