/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2013 OpenMusicKontrollers.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file   wirish/boards/48F3/board.c
 * @author F3-port: Hanspeter Portner <dev@open-music-kontrollers.ch>
 * @brief  48pin F3 board file.
 */

#include <board/board.h>

#include <libmaple/gpio.h>
#include <libmaple/timer.h>

#include <wirish/wirish_debug.h>
#include <wirish/wirish_types.h>

/* Since we want the Serial Wire/JTAG pins as GPIOs, disable both SW
 * and JTAG debug support, unless configured otherwise. */
void boardInit(void) {
    disableDebugPorts();
}

extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {
    {GPIOC,   NULL, NULL, 13, 0, ADCx},	/* PC13 */  
    {GPIOC,   NULL, NULL, 14, 0, ADCx},	/* PC14 */ 			/* OSC32_IN */
    {GPIOC,   NULL, NULL, 15, 0, ADCx},	/* PC15 */ 			/* OSC32_OUT */

    {GPIOF,   NULL, NULL,  0, 0, ADCx},	/* PF0 */ 			/* OSC_IN */
    {GPIOF,   NULL, NULL,  1, 0, ADCx},	/* PF1 */ 			/* OSC_OUT */

    {GPIOA, TIMER2, ADC1,  0, 1,    1},	/* PA0 */ 
    {GPIOA, TIMER2, ADC1,  1, 2,    2},	/* PA1 */ 
    {GPIOA, TIMER2, ADC1,  2, 3,    3},	/* PA2 */ 			/* also TIMER15 CH1 */
    {GPIOA, TIMER2, ADC1,  3, 4,    4},	/* PA3 */ 			/* also TIMER15 CH2 */
    {GPIOA, TIMER3, ADC2,  4, 2,    1},	/* PA4 */ 
    {GPIOA,   NULL, ADC2,  5, 0,    2},	/* PA5 */ 
    {GPIOA, TIMER3, ADC2,  6, 1,    3},	/* PA6 */ 			/* also TIMER16 CH1 */
    {GPIOA, TIMER3, ADC2,  7, 2,    4},	/* PA7 */ 			/* also TIMER17 CH1 */

    {GPIOB, TIMER3, ADC3,  0, 3,   12},	/* PB0 */ 
    {GPIOB, TIMER3, ADC3,  1, 4,    1},	/* PB1 */ 
    {GPIOB,   NULL, ADC2,  2, 0,   12},	/* PB2 */ 

    {GPIOB, TIMER2, NULL, 10, 3, ADCx},	/* PB10 */ 
    {GPIOB, TIMER2, NULL, 11, 4, ADCx},	/* PB11 */ 
    {GPIOB,   NULL, ADC4, 12, 0,    3},	/* PB12 */ 
    {GPIOB,   NULL, ADC3, 13, 0,    5},	/* PB13 */ 
    {GPIOB, TIMER15,ADC4, 14, 1,    4},	/* PB14 */ 
    {GPIOB, TIMER15,ADC4, 15, 2,    5},	/* PB15 */ 

    {GPIOA, TIMER1, NULL,  8, 1, ADCx},	/* PA8 */ 
    {GPIOA, TIMER1, NULL,  9, 2, ADCx},	/* PA9 */ 			/* also TIMER2_CH3 */
    {GPIOA, TIMER1, NULL, 10, 3, ADCx},	/* PA10 */ 			/* also TIMER2 CH4 */
    {GPIOA, TIMER4, NULL, 11, 1, ADCx},	/* PA11 */ 			/* also TIMER1 CH4 */
    {GPIOA, TIMER4, NULL, 12, 2, ADCx},	/* PA12 */ 			/* also TIMER16 CH1 */
    {GPIOA, TIMER4, NULL, 13, 3, ADCx},	/* PA13 */ 
    {GPIOA, TIMER8, NULL, 14, 2, ADCx},	/* PA14 */ 
    {GPIOA, TIMER8, NULL, 15, 1, ADCx},	/* PA15 */ 

    {GPIOB, TIMER2, NULL,  3, 2, ADCx},	/* PB3 */ 
    {GPIOB, TIMER3, NULL,  4, 1, ADCx},	/* PB4 */ 			/* also TIMER16 CH1 */
    {GPIOB, TIMER3, NULL,  5, 2, ADCx},	/* PB5 */ 			/* also TIMER17 CH1 */
    {GPIOB, TIMER4, NULL,  6, 1, ADCx},	/* PB6 */ 			/* also TIMER8 CH1 */
    {GPIOB, TIMER4, NULL,  7, 2, ADCx},	/* PB7 */ 			/* also TIMER3 CH4 */
    {GPIOB, TIMER4, NULL,  8, 3, ADCx},	/* PB8 */ 			/* also TIMER16 CH1 */
    {GPIOB, TIMER4, NULL,  9, 4, ADCx},	/* PB9 */ 			/* also TIMER17 CH1 */
};

extern const uint8 boardPWMPins[BOARD_NR_PWM_PINS] __FLASH__ = {
		PA0, PA1, PA2, PA3, PA4, PA6, PA7, PB0, PB1, PB10, PB11, PB14, PB15, PA8, PA9, PA10, PA11, PA12, PA13, PA14, PA15, PB3, PB4, PB5, PB6, PB7, PB8, PB9,
};

extern const uint8 boardADCPins[BOARD_NR_ADC_PINS] __FLASH__ = {
		PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PB0, PB1, PB2, PB12, PB13, PB14, PB15
};

#define OSC_IN PF0
#define OSC_OUT PF1

#define USB_DM PA11
#define USB_DP PA12

extern const uint8 boardUsedPins[BOARD_NR_USED_PINS] __FLASH__ = {
    OSC_IN, OSC_OUT, USB_DP, USB_DM
};
