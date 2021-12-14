/*
 * util.h
 *
 *  Created on: Dec 13, 2021
 *      Author: Jasper
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"

typedef enum {
    BTN_WAIT,
    BTN_HIGH,
    BTN_LOW
} ButtonState;

static uint32_t g_seed;

// Call in a loop to detect falling edge
bool btnPressed(ButtonState *state, uint8_t pin) {
    switch(*state) {
    case BTN_WAIT:
        if(BTN_PxIN & pin)
            *state = BTN_HIGH;
        break;
    case BTN_HIGH:
        if(!(BTN_PxIN & pin)) {
            *state = BTN_LOW;
            return true;
        }
        break;
    }
    return false;
}


// Fast random number generator from https://stackoverflow.com/a/26237777
inline void fast_srand(int seed) {
    g_seed = seed;
}

inline uint32_t fast_rand(void) {
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}


#endif /* UTIL_H_ */
