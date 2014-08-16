/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2014 OpenMusicKontrollers.
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
 * @file   wirish/boards/F301xx/board.c
 * @author F3-port: Hanspeter Portner <dev@open-music-kontrollers.ch>
 * @brief  F301xx board file (F301K6, F301K8, F301C6, F301C8, F301R6, F301R8).
 */

#include <board/board.h>

#include <libmaple/gpio.h>
#include <libmaple/timer.h>

#include <wirish/wirish_debug.h>
#include <wirish/wirish_types.h>

/* Since we want the Serial Wire/JTAG pins as GPIOs, disable both SW
 * and JTAG debug support on the packages with low pin-count (e.g. MEDIUM_DENSITY),
 * unless configured otherwise. */
void boardInit(void) {
#if defined(STM32_LOW_DENSITY) || defined(STM32_MEDIUM_DENSITY)
    disableDebugPorts();
#endif
}

extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {
    [PA0] = {GPIOA, TIMER2, ADC1,  0, 1,    1},	/* PA0 */ 
    [PA1] = {GPIOA, TIMER2, ADC1,  1, 2,    2},	/* PA1 */ 
    [PA2] = {GPIOA, TIMER2, ADC1,  2, 3,    3},	/* PA2 */ 			/* also TIMER15 CH1 */
    [PA3] = {GPIOA, TIMER2, ADC1,  3, 4,    4},	/* PA3 */ 			/* also TIMER15 CH2 */
    [PA4] = {GPIOA,   NULL, ADC1,  4, 0,    5},	/* PA4 */ 
    [PA5] = {GPIOA, TIMER2, NULL,  5, 1, ADCx},	/* PA5 */ 
    [PA6] = {GPIOA,   NULL, ADC1,  6, 0,   10},	/* PA6 */ 			/* also TIMER16 CH1 */
    [PA7] = {GPIOA,   NULL, ADC1,  7, 0,   15},	/* PA7 */ 			/* also TIMER17 CH1 */

    [PB0] = {GPIOB,   NULL, ADC1,  0, 0,   11},	/* PB0 */ 

    [PA8] = {GPIOA, TIMER1, NULL,  8, 1, ADCx},	/* PA8 */ 
    [PA9] = {GPIOA, TIMER1, NULL,  9, 2, ADCx},	/* PA9 */ 			/* also TIMER2_CH3 */
    [PA10]= {GPIOA, TIMER1, NULL, 10, 3, ADCx},	/* PA10 */ 			/* also TIMER2 CH4 */
    [PA11]= {GPIOA, TIMER1, NULL, 11, 4, ADCx},	/* PA11 */ 			/* also TIMER1 CH4 */
    [PA12]= {GPIOA,   NULL, NULL, 12, 0, ADCx},	/* PA12 */ 			/* also TIMER16 CH1 */
    [PA13]= {GPIOA,   NULL, NULL, 13, 0, ADCx},	/* PA13 */ 
    [PA14]= {GPIOA,   NULL, NULL, 14, 0, ADCx},	/* PA14 */ 
    [PA15]= {GPIOA,   NULL, NULL, 15, 0, ADCx},	/* PA15 */ 

    [PB3] = {GPIOB,   NULL, NULL,  3, 0, ADCx},	/* PB3 */ 
    [PB4] = {GPIOB,   NULL, NULL,  4, 0, ADCx},	/* PB4 */ 			/* also TIMER16 CH1 */
    [PB5] = {GPIOB,   NULL, NULL,  5, 0, ADCx},	/* PB5 */ 			/* also TIMER17 CH1 */
    [PB6] = {GPIOB,   NULL, NULL,  6, 0, ADCx},	/* PB6 */
    [PB7] = {GPIOB,   NULL, NULL,  7, 0, ADCx},	/* PB7 */ 			/* also   NULL CH4 */

#if defined(STM32_MEDIUM_DENSITY) || defined(STM32_HIGH_DENSITY)
    [PC13]= {GPIOC,   NULL, NULL, 13, 0, ADCx},	/* PC13 */  
    [PC14]= {GPIOC,   NULL, NULL, 14, 0, ADCx},	/* PC14 */ 			/* OSC32_IN */
    [PC15]= {GPIOC,   NULL, NULL, 15, 0, ADCx},	/* PC15 */ 			/* OSC32_OUT */

    [PF0] = {GPIOF,   NULL, NULL,  0, 0, ADCx},	/* PF0 */ 			/* OSC_IN */
    [PF1] = {GPIOF,   NULL, NULL,  1, 0, ADCx},	/* PF1 */ 			/* OSC_OUT */
    [PB1] = {GPIOB,   NULL, ADC1,  1, 0,   12},	/* PB1 */ 
    [PB2] = {GPIOB,   NULL, NULL,  2, 0, ADCx},	/* PB2 */ 

    [PB10]= {GPIOB, TIMER2, NULL, 10, 3, ADCx},	/* PB10 */ 
    [PB11]= {GPIOB, TIMER2, ADC1, 11, 4,   14},	/* PB11 */ 
    [PB12]= {GPIOB,   NULL, NULL, 12, 0, ADCx},	/* PB12 */ 
    [PB13]= {GPIOB,   NULL, ADC1, 13, 0,   13},	/* PB13 */ 
    [PB14]= {GPIOB, TIMER15,NULL, 14, 1, ADCx},	/* PB14 */ 
    [PB15]= {GPIOB, TIMER15,NULL, 15, 2, ADCx},	/* PB15 */ 

    [PB8] = {GPIOB,   NULL, NULL,  8, 0, ADCx},	/* PB8 */ 			/* also TIMER16 CH1 */
    [PB9] = {GPIOB,   NULL, NULL,  9, 0, ADCx},	/* PB9 */ 			/* also TIMER17 CH1 */

# if defined(STM32_HIGH_DENSITY)
    [PC0] = {GPIOC, TIMER1, ADC1,  0, 1,   6},	/* PC0 */  
    [PC1] = {GPIOC, TIMER1, ADC1,  1, 2,   7},	/* PC1 */  
    [PC2] = {GPIOC, TIMER1, ADC1,  2, 3,   8},	/* PC2 */  
    [PC3] = {GPIOC, TIMER1, ADC1,  3, 4,   9},	/* PC3 */  

    [PF4] = {GPIOF,   NULL, NULL,  4, 0, ADCx},	/* PF4 */  

    [PC4] = {GPIOC,   NULL, NULL,  4, 0, ADCx},	/* PC4 */  
    [PC5] = {GPIOC,   NULL, NULL,  5, 0, ADCx},	/* PC5 */  
    [PC6] = {GPIOC,   NULL, NULL,  6, 0, ADCx},	/* PC6 */
    [PC7] = {GPIOC,   NULL, NULL,  7, 0, ADCx},	/* PC7 */
    [PC8] = {GPIOC,   NULL, NULL,  8, 0, ADCx},	/* PC8 */
    [PC9] = {GPIOC,   NULL, NULL,  9, 0, ADCx},	/* PC9 */
    [PC10]= {GPIOC,   NULL, NULL, 10, 0, ADCx},	/* PC10 */  
    [PC11]= {GPIOC,   NULL, NULL, 11, 0, ADCx},	/* PC11 */  
    [PC12]= {GPIOC,   NULL, NULL, 12, 0, ADCx},	/* PC12 */  

    [PD2] = {GPIOD,   NULL, NULL,  2, 0, ADCx},	/* PD2 */  
#	endif
#endif
};

extern const uint8 boardPWMPins[BOARD_NR_PWM_PINS] __FLASH__ = {
		PA0, PA1, PA2, PA3, PA5, PA8, PA9, PA10, PA11,
#if defined(STM32_MEDIUM_DENSITY) || defined(STM32_HIGH_DENSITY)
		PB10, PB11, PB14, PB15,
# if defined(STM32_HIGH_DENSITY)
		PC0, PC1, PC2, PC3
# endif
#endif
};

extern const uint8 boardADCPins[BOARD_NR_ADC_PINS] __FLASH__ = {
		PA0, PA1, PA2, PA3, PA4, PA6, PA7, PB0, 
#if defined(STM22_MEDIUM_DENSITY) || defined(STM32_HIGH_DENSITY)
		PB1, PB11, PB13,
# if defined(STM32_HIGH_DENSITY)
		PC0, PC1, PC2, PC3
# endif
#endif
};

#define OSC_IN PF0
#define OSC_OUT PF1

#define USB_DM PA11
#define USB_DP PA12

extern const uint8 boardUsedPins[BOARD_NR_USED_PINS] __FLASH__ = {
    OSC_IN, OSC_OUT, USB_DP, USB_DM
};
