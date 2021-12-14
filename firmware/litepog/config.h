/*
 * config.h
 *
 *  Created on: Nov 16, 2021
 *      Author: Jasper
 */

#ifndef CONFIG_H_
#define CONFIG_H_

// Number of LEDs in Neopixel strip
#define NPX_NUM_LEDS 30

// Index of middle LED
#define NPX_MID_IDX (NPX_NUM_LEDS/2)

// True if even number of LEDs
#define NPX_EVEN_LEDS (!(NPX_NUM_LEDS % 2))

// Seed for pseudo-random number generator
#define PRNG_SEED 0xB00B

// Time to wait between allowing button edges during game select
#define GAME_SELECT_DEBOUNCE_TIME 20

// Width of game selection menu indicator
#define GAME_SELECT_WIDTH 6

// Time between demo animation frames
#define DEMO_INTERVAL 10

// Frame divisor for pong demo animation
#define DEMO_PONG_INTERVAL_DIV 4

// Frame divisor for ping pong demo animation
#define DEMO_PINGPONG_INTERVAL_DIV 4

// Frame divisor for tug o' war demo animation
#define DEMO_TUGOWAR_INTERVAL_DIV 2

// Chance of ball being returned each frame of ping pong demo animation (1/N)
#define DEMO_PINGPONG_RETURN_RATE 9

// Width of the demo animation
#define DEMO_WIDTH 8

#define DEMO_MIN_IDX (NPX_MID_IDX - DEMO_WIDTH/2)
#define DEMO_MAX_IDX (NPX_MID_IDX + DEMO_WIDTH/2 - ((DEMO_WIDTH + 1) % 2))

// Time between countdown ticks
#define COUNTDOWN_INTERVAL 700

// Number of LEDs lit up for each countdown tick
#define COUNTDOWN_LED_WIDTH (1 + NPX_EVEN_LEDS)

// Number of countdown ticks before game start
#define COUNTDOWN_NUMBER 3

#define COUNTDOWN_MIN_IDX (NPX_MID_IDX - ((COUNTDOWN_NUMBER - 1)*COUNTDOWN_LED_WIDTH + NPX_EVEN_LEDS))
#define COUNTDOWN_MAX_IDX (NPX_MID_IDX + (COUNTDOWN_NUMBER - 1)*COUNTDOWN_LED_WIDTH)

// Brightness of ball return zones
#define RETURN_ZONE_BRIGHTNESS 15

// Initial time between ball events for pong
#define PONG_BALL_INTERVAL_START 70

// Amount of speedup after each rally for pong
#define PONG_BALL_INTERVAL_SPEEDUP 5

// Minimum interval time (max ball speed) for pong
#define PONG_BALL_INTERVAL_MIN 40

// Size of return zone for pong
#define PONG_RETURN_ZONE_WIDTH 3

// Initial time between ball events for pong
#define PINGPONG_BALL_INTERVAL_START 70

// Amount of speedup after each rally for pong
#define PINGPONG_BALL_INTERVAL_SPEEDUP 5

// Minimum interval time (max ball speed) for pong
#define PINGPONG_BALL_INTERVAL_MIN 10

// Size of return zone for pong
#define PINGPONG_RETURN_ZONE_WIDTH (NPX_MID_IDX - NPX_EVEN_LEDS)

// Debounce time for ping pong button reads
#define PINGPONG_DEBOUNCE_TIME 3

// Debounce time for tug o' war button reads
#define TUGOWAR_DEBOUNCE_TIME 3

// Time between winner animation frames
#define WINNER_INTERVAL 300

// Number of LEDs to flash per side
#define WINNER_LED_WIDTH 3

// Number of times the winner animation flashes
#define WINNER_NUMBER 5


// Hardware specific config
#if defined(LITEPOG_EXP430)  // MSP-EXP430FR5739

// Neopixel is driven by UCB0
#define NPX_UCxCTLW0 UCB0CTLW0
#define NPX_UCxBR0   UCB0BR0
#define NPX_UCxTXBUF UCB0TXBUF
#define NPX_UCxSTATW UCB0STATW
#define NPX_UCxIFG   UCB0IFG

// Neopixel data pin is P1.6 (UCB0SIMO)
#define NPX_PxDIR  P1DIR
#define NPX_PxSEL0 P1SEL0
#define NPX_PxSEL1 P1SEL1
#define NPX_PIN    BIT6

// UCB0 SPI clock pin is P2.2 (used for timing debug)
#define NPX_DBG_CLK_PxDIR  P2DIR
#define NPX_DBG_CLK_PxSEL0 P2SEL0
#define NPX_DBG_CLK_PxSEL1 P2SEL1
#define NPX_DBG_CLK_PIN    BIT2

// Buttons are connected to P4
#define BTN_PxDIR P4DIR
#define BTN_PxIN  P4IN
// Button 1 (connected to logic handle) is on P4.0
#define BTN1_PIN BIT0
// Button 2 (connected to power handle) is on P4.1
#define BTN2_PIN BIT1

// EXP430 board requires internal pullups
#define BTN_PULLUP_EN
#define BTN_PxREN P4REN
#define BTN_PxOUT P4OUT

// LEDs are connected to PJ
#define LED_PxDIR PJDIR
#define LED_PxOUT PJOUT
// LED 1 (connected to logic handle) is on PJ.0
#define LED1_PIN BIT0
// LED 2 (connected to power handle) is on PJ.1
#define LED2_PIN BIT1

#elif defined(LITEPOG_MAIN)  // LitePog mainboard (default config)

// Neopixel is driven by UCB0
#define NPX_UCxCTLW0 UCB0CTLW0
#define NPX_UCxBR0   UCB0BR0
#define NPX_UCxTXBUF UCB0TXBUF
#define NPX_UCxSTATW UCB0STATW
#define NPX_UCxIFG   UCB0IFG

// Neopixel data pin is P1.6 (UCB0SIMO)
#define NPX_PxDIR  P1DIR
#define NPX_PxSEL0 P1SEL0
#define NPX_PxSEL1 P1SEL1
#define NPX_PIN    BIT6

// UCB0 SPI clock pin is P2.2 (used for timing debug)
#define NPX_DBG_CLK_PxDIR  P2DIR
#define NPX_DBG_CLK_PxSEL0 P2SEL0
#define NPX_DBG_CLK_PxSEL1 P2SEL1
#define NPX_DBG_CLK_PIN    BIT2

// Buttons are connected to P3
#define BTN_PxDIR P3DIR
#define BTN_PxIN  P3IN
// Button 1 (connected to logic handle) is on P3.0
#define BTN1_PIN BIT0
// Button 2 (connected to power handle) is on P3.1
#define BTN2_PIN BIT1

// LEDs are connected to PJ
#define LED_PxDIR PJDIR
#define LED_PxOUT PJOUT
// LED 1 (connected to logic handle) is on PJ.0
#define LED1_PIN BIT0
// LED 2 (connected to power handle) is on PJ.1
#define LED2_PIN BIT1

#elif defined(LITEPOG_ALT)  // LitePog mainboard (alt config)

// Neopixel is driven by UCA0
#define NPX_UCxCTLW0 UCA0CTLW0
#define NPX_UCxBR0   UCA0BR0
#define NPX_UCxTXBUF UCA0TXBUF
#define NPX_UCxSTATW UCA0STATW
#define NPX_UCxIFG   UCA0IFG

// Neopixel data pin is P2.0 (UCA0SIMO)
#define NPX_PxDIR  P2DIR
#define NPX_PxSEL0 P2SEL0
#define NPX_PxSEL1 P2SEL1
#define NPX_PIN    BIT0

// UCA0 SPI clock pin is P1.5 (used for timing debug)
#define NPX_DBG_CLK_PxDIR  P1DIR
#define NPX_DBG_CLK_PxSEL0 P1SEL0
#define NPX_DBG_CLK_PxSEL1 P1SEL1
#define NPX_DBG_CLK_PIN    BIT5

// Buttons are connected to P3
#define BTN_PxDIR P3DIR
#define BTN_PxIN  P3IN
// Button 1 (connected to logic handle) is on P3.2
#define BTN1_PIN BIT2
// Button 2 (connected to power handle) is on P3.3
#define BTN2_PIN BIT3

// LEDs are connected to PJ
#define LED_PxDIR PJDIR
#define LED_PxOUT PJOUT
// LED 1 (connected to logic handle) is on PJ.2
#define LED1_PIN BIT2
// LED 2 (connected to power handle) is on PJ.3
#define LED2_PIN BIT3

#else

#error A proper configuration must be defined

#endif


#endif /* CONFIG_H_ */
