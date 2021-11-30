#include <msp430.h> 
#include <stdbool.h>
#include <stdint.h>
#include "ws2812.h"
#include "config.h"

unsigned volatile long long counter;


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

void drawCountDown(uint8_t state) {
    const uint8_t middle_idx = NPX_NUM_LEDS/2;
    const uint8_t max_left = middle_idx - (COUNTDOWN_NUMBER - 1)*PIXEL_WIDTH;
    const uint8_t max_right = middle_idx + (COUNTDOWN_NUMBER - 1)*PIXEL_WIDTH + (PIXEL_WIDTH - 1);
    uint8_t i, j;
    uint8_t pos_left, pos_right;

    clearStrip();
    if(state < COUNTDOWN_NUMBER) {
        // Show countdown going up (red lights)
        for(i=0; i<=state; i++) {
            pos_left = middle_idx - i*PIXEL_WIDTH;
            pos_right = middle_idx + i*PIXEL_WIDTH;
            for(j=0; j<PIXEL_WIDTH; j++) {
                setLEDColor(pos_left + j, 255, 0, 0);
                setLEDColor(pos_right + j, 255, 0, 0);
            }
        }
    } else {
        // Show countdown finishing (green light)
        for(i=max_left; i<=max_right; i++)
            setLEDColor(i, 0, 255, 0);
    }
    showStrip();
}

void demoLoop(void) {
    int npx_idx = 0;
    bool countdown_started = false;
    unsigned long long countdown_start;
    unsigned long long demo_counter = 0;
    uint8_t countdown_state;
    while(1) {
        if(BTN_PxIN & BTN1_PIN)
            LED_PxOUT &= ~(LED1_PIN);
        else
            LED_PxOUT |= LED1_PIN;

        if(BTN_PxIN & BTN2_PIN)
            LED_PxOUT &= ~(LED2_PIN);
        else
            LED_PxOUT |= LED2_PIN;

        if(!(BTN_PxIN & (BTN1_PIN | BTN2_PIN))) {
            if(!countdown_started) {
                countdown_started = true;
                countdown_start = counter;
            }
            if(
                    counter >=
                    countdown_start + countdown_state*COUNTDOWN_INTERVAL) {
                drawCountDown(countdown_state++);

                if(countdown_state > COUNTDOWN_NUMBER) {
                    LED_PxOUT &= ~(LED1_PIN | LED2_PIN);
                    return;
                }
            }

        } else {
            // Reset countdown, show demo loop
            countdown_started = false;
            countdown_state = 0;
            if(counter > demo_counter + DEMO_INTERVAL) {
                demo_counter = counter;
                clearStrip();
                setLEDColor(npx_idx, 0, 0, 255);
                showStrip();
                if(++npx_idx >= NPX_NUM_LEDS)
                    npx_idx = 0;
            }
        }
    }
}

uint8_t gameLoop(void) {
    // TODO: Implement game logic
    while(1) {
        if(BTN_PxIN & BTN1_PIN)
            return 0;

        if(BTN_PxIN & BTN2_PIN)
            return 1;
    }
}

void winnerLoop(uint8_t winner) {
    uint8_t i = 0;
    uint8_t j;
    uint8_t winner_idx, loser_idx, idx1, idx2;
    unsigned long long anim_start = counter;

    clearStrip();
    while(i<WINNER_NUMBER*2) {
        if (counter >= anim_start + i*WINNER_INTERVAL) {
            if(i%2) {
                clearStrip();
            } else {
                for(j=0; j < WINNER_LED_WIDTH; j++) {
                    idx1 = j;
                    idx2 = NPX_NUM_LEDS - 1 - j;
                    if(winner) {
                        loser_idx = idx1;
                        winner_idx = idx2;
                    } else {
                        loser_idx = idx2;
                        winner_idx = idx1;
                    }
                    setLEDColor(winner_idx, 0, 255, 0);
                    setLEDColor(loser_idx, 255, 0, 0);
                }
            }
            showStrip();
            i++;
        }
    }
}

int main(void)
{
    uint8_t winner;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	initGpio();

	initClock();

	initStrip();

	initTimer();

	__enable_interrupt();

	while(1) {
        demoLoop();
        winner = gameLoop();
        winnerLoop(winner);
	}

	return 0;
}

// TB1 Interrupt Vector handler
#pragma vector=TIMER1_B1_VECTOR
__interrupt void TIMER1_B1_ISR(void) {
  switch(__even_in_range(TB1IV,14))
  {
    case  0: break;                          // No interrupt
    case  2: break;
    case  4: break;
    case  6: break;                          // reserved
    case  8: break;                          // reserved
    case 10: break;                          // reserved
    case 12: break;                          // reserved
    case 14:
        //overflow
        counter++;
        break;
    default: break;
  }
}


