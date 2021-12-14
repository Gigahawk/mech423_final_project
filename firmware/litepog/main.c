#include <msp430.h> 
#include <stdbool.h>
#include <stdint.h>
#include "init.h"
#include "ws2812.h"
#include "config.h"
#include "color.h"
#include "util.h"


typedef enum {
    GAME_PONG = 0,     // Rev 1 firmware game with improvements
    GAME_PINGPONG = 1, // Ping Pong game from promo video
    GAME_TUGOWAR = 2,  // Tug o' War game from promo video

    // Placeholder names for detecting when the end of the game list is reached
    _GAME_FIRST = GAME_PONG,
    _GAME_LAST = GAME_TUGOWAR,
} GameType;

volatile uint64_t counter;

// Store game type selection in FRAM
#pragma DATA_SECTION(game_type, ".infoB")
GameType game_type;

void drawCountDown(uint8_t state) {
    uint8_t i, j;
    uint8_t pos_left, pos_right;

    clearStrip();
    if(state < COUNTDOWN_NUMBER) {
        // Show countdown going up (red lights)
        for(i=0; i<=state; i++) {
            pos_left = NPX_MID_IDX - NPX_EVEN_LEDS - i*COUNTDOWN_LED_WIDTH;
            pos_right = NPX_MID_IDX - NPX_EVEN_LEDS + i*COUNTDOWN_LED_WIDTH;
            for(j=0; j<COUNTDOWN_LED_WIDTH; j++) {
                setLEDColor(pos_left + j, 255, 0, 0);
                setLEDColor(pos_right + j, 255, 0, 0);
            }
        }
    } else {
        // Show countdown finishing (green light)
        for(i=COUNTDOWN_MIN_IDX; i<=COUNTDOWN_MAX_IDX; i++)
            setLEDColor(i, 0, 255, 0);
    }
    showStrip();
}

void drawDemoPong(bool show) {
    static uint64_t last_frame = 0;
    static uint8_t pos = NPX_MID_IDX;
    static int8_t dir = 1;
    static uint8_t frame_div = DEMO_PONG_INTERVAL_DIV;
    if (counter > last_frame + DEMO_INTERVAL) {
        last_frame = counter;
        frame_div--;
        if(frame_div == 0) {
            frame_div = DEMO_PONG_INTERVAL_DIV;
            clearStrip();
            setLEDColor(DEMO_MIN_IDX, 0, 0, RETURN_ZONE_BRIGHTNESS);
            setLEDColor(DEMO_MAX_IDX, 0, 0, RETURN_ZONE_BRIGHTNESS);
            setLEDColor(pos, 0, 0, 255);
            pos += dir;
            if(pos <= DEMO_MIN_IDX)
                dir = 1;
            else if(pos >= DEMO_MAX_IDX)
                dir = -1;
            if(show)
                showStrip();
        }
    }
}

int8_t pingPongIdx(uint8_t pos) {
    if(NPX_EVEN_LEDS) {
        if(pos >= NPX_MID_IDX)
            return (int8_t)pos - NPX_MID_IDX;
        else
            return (int8_t)pos - NPX_MID_IDX + 1;
    } else {
        return (int8_t)pos - NPX_MID_IDX;
    }
}

void drawDemoPingPong(bool show) {
    static uint64_t last_frame = 0;
    static uint8_t pos = NPX_MID_IDX;
    int8_t side;
    static int8_t dir = 1;
    static uint8_t frame_div = DEMO_PINGPONG_INTERVAL_DIV;
    uint8_t i;
    if (counter > last_frame + DEMO_INTERVAL) {
        last_frame = counter;
        frame_div--;
        if(frame_div == 0) {
            frame_div = DEMO_PINGPONG_INTERVAL_DIV;
            clearStrip();
            for(i=DEMO_MIN_IDX; i<=DEMO_MAX_IDX; i++) {
                if(pingPongIdx(i))
                    setLEDColor(i, 0, 0, RETURN_ZONE_BRIGHTNESS);
            }
            pos += dir;
            side = pingPongIdx(pos);
            if(!(counter % DEMO_PINGPONG_RETURN_RATE)) {
                if(side > 0)
                    dir = -1;
                else if (side < 0)
                    dir = 1;
            }
            if(pos <= DEMO_MIN_IDX)
                dir = 1;
            else if(pos >= DEMO_MAX_IDX)
                dir = -1;

            setLEDColor(pos, 0, 0, 255);
            if(show)
                showStrip();
        }
    }
}

void drawDemoTugOWar(bool show) {
    static uint64_t last_frame = 0;
    static uint8_t pos = NPX_MID_IDX;
    static uint8_t frame_div = DEMO_TUGOWAR_INTERVAL_DIV;
    if (counter > last_frame + DEMO_INTERVAL) {
        last_frame = counter;
        frame_div--;
        if(frame_div == 0) {
            frame_div = DEMO_TUGOWAR_INTERVAL_DIV;
            pos += ((int32_t)fast_rand() % 3) - 1;
            clearStrip();
            setLEDColor(pos, 0, 0, 255);
            if(pos <= DEMO_MIN_IDX)
                pos += 1;
            else if(pos >= DEMO_MAX_IDX)
                pos -= 1;
            if(show)
                showStrip();
        }
    }
}

void drawGameSelectIndicator(void) {
    static uint64_t last_frame = 0;
    static HsvColor hsv = {0, 255, 100};
    RgbColor rgb;
    uint8_t i;
    if (counter > last_frame + DEMO_INTERVAL) {
        last_frame = counter;
        rgb = HsvToRgb(hsv);
        for(i=0; i<GAME_SELECT_WIDTH; i++)
            setLEDColor(
                    NPX_NUM_LEDS - 1 - i, rgb.r, rgb.g, rgb.b);

        showStrip();
        hsv.h++;
    }
}

void demoLoop(void) {
    bool countdown_started = false;
    void (*demo_anim)(bool);
    uint64_t countdown_start;
    uint8_t countdown_state = 0;

    switch(game_type) {
    case GAME_PONG:
        demo_anim = &drawDemoPong;
        break;
    case GAME_PINGPONG:
        demo_anim = &drawDemoPingPong;
        break;
    case GAME_TUGOWAR:
        demo_anim = &drawDemoTugOWar;
        break;
    }

    clearStrip();
    showStrip();

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
            (*demo_anim)(true);
        }
    }
}

// Returns 0 if Player 1  wins, 1 if Player 2 wins
uint8_t gameLoopPong(void) {
    int8_t dir;
    int32_t pos = NPX_NUM_LEDS / 2;
    uint64_t ball_counter = 0;
    int32_t ball_interval = PONG_BALL_INTERVAL_START;
    uint8_t i;
    ButtonState btn1, btn2;


    // Ball should move away from player that releases button first
    while(1) {
        if(BTN_PxIN & BTN1_PIN) {
            dir = 1;
            break;
        }

        if(BTN_PxIN & BTN2_PIN) {
            dir = -1;
            break;
        }
    }

    clearStrip();
    showStrip();

    while(1) {
        if(ball_counter + ball_interval <= counter) {
            ball_counter = counter;
            pos += dir;
            if(pos < 0)
                return 1;
            else if(pos >= NPX_NUM_LEDS)
                return 0;
            clearStrip();
            for(i=0; i<PONG_RETURN_ZONE_WIDTH; i++)
                setLEDColor(i, 0, 0, RETURN_ZONE_BRIGHTNESS);
            for(i=NPX_NUM_LEDS-1; i>=NPX_NUM_LEDS-PONG_RETURN_ZONE_WIDTH; i--)
                setLEDColor(i, 0, 0, RETURN_ZONE_BRIGHTNESS);
            setLEDColor(pos, 0, 0, 255);
            showStrip();
        }

        if(pos < PONG_RETURN_ZONE_WIDTH && dir < 0) {
            LED_PxOUT |= LED1_PIN;
            if(btnPressed(&btn1, BTN1_PIN)) {
                dir *= -1;
                ball_interval -= PONG_BALL_INTERVAL_SPEEDUP;
            }
        } else {
            LED_PxOUT &= ~(LED1_PIN);
            btn1 = BTN_WAIT;
        }

        if(pos >= NPX_NUM_LEDS - PONG_RETURN_ZONE_WIDTH && dir > 0) {
            LED_PxOUT |= LED2_PIN;
            if(btnPressed(&btn2, BTN2_PIN)) {
                dir *= -1;
                ball_interval -= PONG_BALL_INTERVAL_SPEEDUP;
            }
        } else {
            LED_PxOUT &= ~(LED2_PIN);
            btn2 = BTN_WAIT;
        }

        if(ball_interval < PONG_BALL_INTERVAL_MIN)
            ball_interval = PONG_BALL_INTERVAL_MIN;
    }
}

// Returns 0 if Player 1  wins, 1 if Player 2 wins
uint8_t gameLoopPingPong(void) {
    int8_t dir;
    int32_t pos = NPX_NUM_LEDS / 2;
    uint64_t ball_counter = 0;
    uint64_t cooldown = 0;
    int32_t ball_interval = PINGPONG_BALL_INTERVAL_START;
    uint8_t i;
    ButtonState btn1 = BTN_WAIT;
    ButtonState btn2 = BTN_WAIT;


    // Ball should move away from player that releases button first
    while(1) {
        if(BTN_PxIN & BTN1_PIN) {
            dir = 1;
            break;
        }

        if(BTN_PxIN & BTN2_PIN) {
            dir = -1;
            break;
        }
    }

    clearStrip();
    showStrip();

    while(1) {
        if(ball_counter + ball_interval <= counter) {
            ball_counter = counter;
            pos += dir;
            if(pos < 0)
                return 1;
            else if(pos >= NPX_NUM_LEDS)
                return 0;
            clearStrip();
            for(i=0; i<PINGPONG_RETURN_ZONE_WIDTH; i++)
                setLEDColor(i, 0, 0, RETURN_ZONE_BRIGHTNESS);
            for(i=NPX_NUM_LEDS-1; i>=NPX_NUM_LEDS-PINGPONG_RETURN_ZONE_WIDTH; i--)
                setLEDColor(i, 0, 0, RETURN_ZONE_BRIGHTNESS);
            setLEDColor(pos, 0, 0, 255);
            showStrip();
        }

        if(counter > cooldown) {
            cooldown = counter + PINGPONG_DEBOUNCE_TIME;
            if(btnPressed(&btn1, BTN1_PIN)) {
                btn1 = BTN_WAIT;
                if(pos < PINGPONG_RETURN_ZONE_WIDTH && dir < 0) {
                    dir *= -1;
                    ball_interval -= PINGPONG_BALL_INTERVAL_SPEEDUP;
                } else {
                    return 1;
                }
            }
            if(btnPressed(&btn2, BTN2_PIN)) {
                btn2 = BTN_WAIT;
                if(pos >= NPX_NUM_LEDS - PINGPONG_RETURN_ZONE_WIDTH && dir > 0) {
                    dir *= -1;
                    ball_interval -= PINGPONG_BALL_INTERVAL_SPEEDUP;
                } else {
                    return 0;
                }
            }
        }

        if(pos < PINGPONG_RETURN_ZONE_WIDTH && dir < 0) {
            LED_PxOUT |= LED1_PIN;
        } else {
            LED_PxOUT &= ~(LED1_PIN);
        }

        if(pos >= NPX_NUM_LEDS - PINGPONG_RETURN_ZONE_WIDTH && dir > 0) {
            LED_PxOUT |= LED2_PIN;
        } else {
            LED_PxOUT &= ~(LED2_PIN);
        }

        if(ball_interval < PINGPONG_BALL_INTERVAL_MIN)
            ball_interval = PINGPONG_BALL_INTERVAL_MIN;
    }
}

// Returns 0 if Player 1  wins, 1 if Player 2 wins
uint8_t gameLoopTugOWar(void) {
    int32_t pos = NPX_NUM_LEDS / 2;
    uint64_t cooldown = 0;
    ButtonState btn1 = BTN_WAIT;
    ButtonState btn2 = BTN_WAIT;

    clearStrip();
    showStrip();

    while(1) {
        if(pos < 0)
            return 1;
        else if(pos >= NPX_NUM_LEDS)
            return 0;
        clearStrip();
        setLEDColor(pos, 0, 0, 255);
        showStrip();
        if(counter > cooldown) {
            cooldown = counter + TUGOWAR_DEBOUNCE_TIME;
            if(btnPressed(&btn1, BTN1_PIN)) {
                btn1 = BTN_WAIT;
                pos++;
            }
            if(btnPressed(&btn2, BTN2_PIN)) {
                btn2 = BTN_WAIT;
                pos--;
            }
        }
    }
}

void winnerLoop(uint8_t winner) {
    uint8_t i = 0;
    uint8_t j;
    uint8_t winner_idx, loser_idx, idx1, idx2;
    uint64_t anim_start = counter;

    LED_PxOUT &= 0;
    clearStrip();
    showStrip();
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

void nextGame(void) {
    if(game_type == _GAME_LAST)
        game_type =_GAME_FIRST;
    else
        game_type++;
}

void prevGame(void) {
    if(game_type == _GAME_FIRST)
        game_type =_GAME_LAST;
    else
        game_type--;
}


void gameSelectLoop(void) {
    ButtonState btn1 = BTN_WAIT;
    ButtonState btn2 = BTN_WAIT;
    uint64_t cooldown = 0;
    while(1) {
        if(counter > cooldown) {
            cooldown = counter + GAME_SELECT_DEBOUNCE_TIME;
            if(btnPressed(&btn1, BTN1_PIN)) {
                btn1 = BTN_WAIT;
                nextGame();
                continue;
            }
            if(btnPressed(&btn2, BTN2_PIN)) {
                btn2 = BTN_WAIT;
                prevGame();
                continue;
            }
        }
        switch(game_type) {
        case GAME_PONG:
            drawDemoPong(false);
            break;
        case GAME_PINGPONG:
            drawDemoPingPong(false);
            break;
        case GAME_TUGOWAR:
            drawDemoTugOWar(false);
            break;
        }
        drawGameSelectIndicator();
    }
}


int main(void)
{
    uint8_t winner;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	fast_srand(PRNG_SEED);

	initGpio();

	initClock();

	initStrip();

	initTimer();

	__enable_interrupt();

	if(!(BTN_PxIN & BTN2_PIN)) {
	    // Activate game selection if button 2 (power handle side)
	    // is held down when turning on
	    gameSelectLoop();
	} else {
        while(1) {
            demoLoop();
            switch(game_type) {
            case GAME_PONG:
                winner = gameLoopPong();
                break;
            case GAME_PINGPONG:
                winner = gameLoopPingPong();
                break;
            case GAME_TUGOWAR:
                winner = gameLoopTugOWar();
                break;
            }
            winnerLoop(winner);
        }
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


