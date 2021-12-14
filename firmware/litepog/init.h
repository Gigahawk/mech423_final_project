/*
 * init.h
 *
 *  Created on: Dec 13, 2021
 *      Author: Jasper
 */

#ifndef INIT_H_
#define INIT_H_
#include <msp430.h>
#include "config.h"

volatile extern uint64_t counter;

// Set DCO == SMCLK == MCLK == 24 MHz
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

void initGpio(void) {
    // Configure buttons as input
    BTN_PxDIR &= ~(BTN1_PIN | BTN2_PIN);

#ifdef BTN_PULLUP_EN
    // Enable pullups if required
    BTN_PxREN |= (BTN1_PIN | BTN2_PIN);
    BTN_PxOUT |= (BTN1_PIN | BTN2_PIN);
#endif

    // Configure LEDs as output
    LED_PxDIR |= (LED1_PIN | LED2_PIN);
    LED_PxOUT &= ~(LED1_PIN | LED2_PIN);

}

void initTimer(void) {
    counter = 0;

    // Stop TB1
    TB1CTL &= ~(MC0 | MC1);
    TB1CTL |= MC__STOP;

    // Set TB1 source to SMCLK (24 MHz)
    TB1CTL |= TBSSEL__SMCLK;

    // Set clock division to 8*3==24 (1 MHz timer tick)
    TB1CTL |= ID__8;
    TB1EX0 |= TBIDEX_3;

    // Enable TBIFG interrupt
    TB1CTL |= TBIE;

    // TB1 overflows every 1000 ticks (1 MHz / 1000 == 1 kHz, counter iterates every 1 ms)
    TB1CCR0 =  1000;

    // Start TB1
    TB1CTL|= MC__UP;
}



#endif /* INIT_H_ */
