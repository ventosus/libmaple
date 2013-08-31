/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
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
 * @file   wirish/boards/maple_mini/board.cpp
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @author Hanspeter Portner <agenthp@users.sf.net>
 * @brief  Orone Mini board file.
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

    /* Top header */

    [PB11]= {GPIOB, TIMER2, NULL, 11, 4, ADCx}, /* D0/PB11 */
    [PB10]= {GPIOB, TIMER2, NULL, 10, 3, ADCx}, /* D1/PB10 */
    [PB2] = {GPIOB,   NULL, ADC2,  2, 0,   12}, /* D2/PB2 */
    [PB0] = {GPIOB, TIMER3, ADC3,  0, 3,   12}, /* D3/PB0 */
    [PA7] = {GPIOA, TIMER3, ADC2,  7, 2,    4}, /* D4/PA7 */			/* also TIMER17 CH1 */
    [PA6] = {GPIOA, TIMER3, ADC2,  6, 1,    3}, /* D5/PA6 */			/* also TIMER16 CH1 */
    [PA5] = {GPIOA,   NULL, ADC2,  5, 0,    2}, /* D6/PA5 */
    [PA4] = {GPIOA, TIMER3, ADC2,  4, 2,    1}, /* D7/PA4 */
    [PA3] = {GPIOA, TIMER2, ADC1,  3, 4,    4}, /* D8/PA3 */			/* also TIMER15 CH2 */
    [PA2] = {GPIOA, TIMER2, ADC1,  2, 3,    3}, /* D9/PA2 */			/* also TIMER15 CH1 */
    [PA1] = {GPIOA, TIMER2, ADC1,  1, 2,    2}, /* D10/PA1 */
    [PA0] = {GPIOA, TIMER2, ADC1,  0, 1,    1}, /* D11/PA0 */
    [PC15]= {GPIOC,   NULL, NULL, 15, 0, ADCx}, /* D12/PC15 */
    [PC14]= {GPIOC,   NULL, NULL, 14, 0, ADCx}, /* D13/PC14 */
    [PC13]= {GPIOC,   NULL, NULL, 13, 0, ADCx}, /* D14/PC13 */

    /* Bottom header */

    [PB7] = {GPIOB, TIMER4, NULL,  7, 2, ADCx}, /* D15/PB7 */			/* also TIMER3 CH4 */
    [PB6] = {GPIOB, TIMER4, NULL,  6, 1, ADCx}, /* D16/PB6 */			/* also TIMER8 CH1 */
    [PB5] = {GPIOB, TIMER3, NULL,  5, 2, ADCx}, /* D17/PB5 */			/* also TIMER17 CH1 */
    [PB4] = {GPIOB, TIMER3, NULL,  4, 1, ADCx}, /* D18/PB4 */			/* also TIMER16 CH1 */
    [PB3] = {GPIOB, TIMER2, NULL,  3, 2, ADCx}, /* D19/PB3 */
    [PA15]= {GPIOA, TIMER8, NULL, 15, 1, ADCx}, /* D20/PA15 */
    [PA14]= {GPIOA, TIMER8, NULL, 14, 2, ADCx}, /* D21/PA14 */
    [PA13]= {GPIOA, TIMER4, NULL, 13, 3, ADCx}, /* D22/PA13 */
    [PA12]= {GPIOA, TIMER4, NULL, 12, 2, ADCx}, /* D23/PA12 */		/* also TIMER16 CH1 */
    [PA11]= {GPIOA, TIMER4, NULL, 11, 1, ADCx}, /* D24/PA11 */		/* also TIMER1 CH4 */
    [PA10]= {GPIOA, TIMER1, NULL, 10, 3, ADCx}, /* D25/PA10 */		/* also TIMER2 CH4 */
    [PA9] = {GPIOA, TIMER1, NULL,  9, 2, ADCx}, /* D26/PA9 */			/* also TIMER2_CH3 */
    [PA8] = {GPIOA, TIMER1, NULL,  8, 1, ADCx}, /* D27/PA8 */
    [PB15]= {GPIOB, TIMER15,ADC4, 15, 2,    5}, /* D28/PB15 */
    [PB14]= {GPIOB, TIMER15,ADC4, 14, 1,    4}, /* D29/PB14 */
    [PB13]= {GPIOB,   NULL, ADC3, 13, 0,    5}, /* D30/PB13 */
    [PB12]= {GPIOB,   NULL, ADC4, 12, 0,    3}, /* D31/PB12 */
    [PB8] = {GPIOB, TIMER4, NULL,  8, 3, ADCx}, /* D32/PB8 */			/* also TIMER16 CH1 */
    [PB1] = {GPIOB, TIMER3, ADC3,  1, 4,    1}, /* D33/PB1 */
};

extern const uint8 boardPWMPins[BOARD_NR_PWM_PINS] __FLASH__ = {
		PB11, PB10,
		PB0,
		PA7, PA6,
		PA4, PA3, PA2, PA1, PA0,
		PB7, PB6, PB5, PB4, PB3,
		PA15, PA14, PA13, PA12, PA11, PA10, PA9, PA8,
		PB15, PB14,
		PB8,
		PB1
};

extern const uint8 boardADCPins[BOARD_NR_ADC_PINS] __FLASH__ = {
		PB2, PB0,
		PA7, PA6, PA5, PA4, PA3, PA2, PA1, PA0,
		PB15, PB14, PB13, PB12,
		PB1
};

#define USB_DP 23
#define USB_DM 24

extern const uint8 boardUsedPins[BOARD_NR_USED_PINS] __FLASH__ = {
    BOARD_LED_PIN, BOARD_BUTTON_PIN, USB_DP, USB_DM
};
