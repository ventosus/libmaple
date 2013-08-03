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
 * @brief  F302xx board file (F302CB, F302CC, F302RB, F302RC, F302VB, F302VC).
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
#if defined(STM32_MEDIUM_DENSITY)
    disableDebugPorts();
#endif
}

extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {
#if defined(STM32_XL_DENSITY)
    {GPIOE, TIMER3, NULL,  2, 1, ADCx},	/* PE2 */  
    {GPIOE, TIMER3, NULL,  3, 2, ADCx},	/* PE3 */  
    {GPIOE, TIMER3, NULL,  4, 3, ADCx},	/* PE4 */  
    {GPIOE, TIMER3, NULL,  5, 4, ADCx},	/* PE5 */  
    {GPIOE,   NULL, NULL,  6, 0, ADCx},	/* PE6 */  
#endif

/* on all density devices */
    {GPIOC,   NULL, NULL, 13, 0, ADCx},	/* PC13 */  
    {GPIOC,   NULL, NULL, 14, 0, ADCx},	/* PC14 */ 			/* OSC32_IN */
    {GPIOC,   NULL, NULL, 15, 0, ADCx},	/* PC15 */ 			/* OSC32_OUT */

#if defined(STM32_XL_DENSITY)
    {GPIOF,TIMER15, NULL,  9, 1, ADCx},	/* PF9 */  
    {GPIOF,TIMER15, NULL, 10, 2, ADCx},	/* PF10 */  
#endif

/* on all density devices */
    {GPIOF,   NULL, NULL,  0, 0, ADCx},	/* PF0 */ 			/* OSC_IN */
    {GPIOF,   NULL, NULL,  1, 0, ADCx},	/* PF1 */ 			/* OSC_OUT */

#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
    {GPIOC,   NULL, ADC1,  0, 0,    6},	/* PC0 */  
    {GPIOC,   NULL, ADC1,  1, 0,    7},	/* PC1 */  
    {GPIOC,   NULL, ADC1,  2, 0,    8},	/* PC2 */  
    {GPIOC,   NULL, ADC1,  3, 0,    9},	/* PC3 */  
#	if defined(STM32_XL_DENSITY)
    {GPIOF,   NULL, ADC1,  2, 0,   10},	/* PF2 */  
#	endif
#endif

/* on all density devices */
    {GPIOA, TIMER2, ADC1,  0, 1,    1},	/* PA0 */ 
    {GPIOA, TIMER2, ADC1,  1, 2,    2},	/* PA1 */ 
    {GPIOA, TIMER2, ADC1,  2, 3,    3},	/* PA2 */ 			/* also TIMER15 CH1 */
    {GPIOA, TIMER2, ADC1,  3, 4,    4},	/* PA3 */ 			/* also TIMER15 CH2 */

#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
    {GPIOF,   NULL, ADC1,  4, 0,    5},	/* PF4 */  
#endif

/* on all density devices */
    {GPIOA, TIMER3, ADC2,  4, 2,    1},	/* PA4 */ 
    {GPIOA,   NULL, ADC2,  5, 0,    2},	/* PA5 */ 
    {GPIOA, TIMER3, ADC2,  6, 1,    3},	/* PA6 */ 			/* also TIMER16 CH1 */
    {GPIOA, TIMER3, ADC2,  7, 2,    4},	/* PA7 */ 			/* also TIMER17 CH1 */

#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
    {GPIOC,   NULL, ADC2,  4, 0,    5},	/* PC4 */  
    {GPIOC,   NULL, ADC2,  5, 0,   11},	/* PC5 */  
#endif

/* on all density devices */
    {GPIOB, TIMER3, NULL,  0, 3, ADCx},	/* PB0 */ 
    {GPIOB, TIMER3, NULL,  1, 4, ADCx},	/* PB1 */ 
    {GPIOB,   NULL, ADC2,  2, 0,   12},	/* PB2 */ 

#if defined(STM32_XL_DENSITY)
    {GPIOE,   NULL, NULL,  7, 0, ADCx},	/* PE7 */  
    {GPIOE,   NULL, NULL,  8, 0, ADCx},	/* PE8 */  
    {GPIOE, TIMER1, NULL,  9, 1, ADCx},	/* PE9 */  
    {GPIOE,   NULL, NULL, 10, 0, ADCx},	/* PE10 */  
    {GPIOE, TIMER1, NULL, 11, 2, ADCx},	/* PE11 */  
    {GPIOE,   NULL, NULL, 12, 0, ADCx},	/* PE12 */  
    {GPIOE, TIMER1, NULL, 13, 3, ADCx},	/* PE13 */  
    {GPIOE, TIMER1, NULL, 14, 4, ADCx},	/* PE14 */  
    {GPIOE,   NULL, NULL, 15, 0, ADCx},	/* PE15 */  
#endif

/* on all density devices */
    {GPIOB, TIMER2, NULL, 10, 3, ADCx},	/* PB10 */ 
    {GPIOB, TIMER2, NULL, 11, 4, ADCx},	/* PB11 */ 
    {GPIOB,   NULL, NULL, 12, 0, ADCx},	/* PB12 */ 
    {GPIOB,   NULL, NULL, 13, 0, ADCx},	/* PB13 */ 
    {GPIOB, TIMER15,NULL, 14, 1, ADCx},	/* PB14 */ 
    {GPIOB, TIMER15,NULL, 15, 2, ADCx},	/* PB15 */ 

#if defined(STM32_XL_DENSITY)
    {GPIOD,   NULL, NULL,  8, 0, ADCx},	/* PD8 */  
    {GPIOD,   NULL, NULL,  9, 0, ADCx},	/* PD0 */  
    {GPIOD,   NULL, NULL, 10, 0, ADCx},	/* PD10 */  
    {GPIOD,   NULL, NULL, 11, 0, ADCx},	/* PD11 */  
    {GPIOD, TIMER4, NULL, 12, 1, ADCx},	/* PD12 */  
    {GPIOD, TIMER4, NULL, 13, 2, ADCx},	/* PD13 */  
    {GPIOD, TIMER4, NULL, 14, 3, ADCx},	/* PD14 */  
    {GPIOD, TIMER4, NULL, 15, 4, ADCx},	/* PD15 */  
#endif

#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
    {GPIOC, TIMER3, NULL,  6, 1, ADCx},	/* PC6 */
    {GPIOC, TIMER3, NULL,  7, 2, ADCx},	/* PC7 */
    {GPIOC, TIMER3, NULL,  8, 3, ADCx},	/* PC8 */
    {GPIOC, TIMER3, NULL,  9, 4, ADCx},	/* PC9 */
#endif

/* on all density devices */
    {GPIOA, TIMER1, NULL,  8, 1, ADCx},	/* PA8 */ 
    {GPIOA, TIMER1, NULL,  9, 2, ADCx},	/* PA9 */ 			/* also TIMER2_CH3 */
    {GPIOA, TIMER1, NULL, 10, 3, ADCx},	/* PA10 */ 			/* also TIMER2 CH4 */
    {GPIOA, TIMER4, NULL, 11, 1, ADCx},	/* PA11 */ 			/* also TIMER1 CH4 */
    {GPIOA, TIMER4, NULL, 12, 2, ADCx},	/* PA12 */ 			/* also TIMER16 CH1 */
    {GPIOA, TIMER4, NULL, 13, 3, ADCx},	/* PA13 */ 
#if defined(STM32_XL_DENSITY)
    {GPIOF, TIMER4, NULL,  6, 4, ADCx},	/* PF6 */  
#endif
    {GPIOA,   NULL, NULL, 14, 0, ADCx},	/* PA14 */ 
    {GPIOA,   NULL, NULL, 15, 0, ADCx},	/* PA15 */ 

#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
    {GPIOC,   NULL, NULL, 10, 0, ADCx},	/* PC10 */  
    {GPIOC,   NULL, NULL, 11, 0, ADCx},	/* PC11 */  
    {GPIOC,   NULL, NULL, 12, 0, ADCx},	/* PC12 */  

#	if defined(STM32_XL_DENSITY)
    {GPIOD,   NULL, NULL,  0, 0, ADCx},	/* PD0 */  
    {GPIOD,   NULL, NULL,  1, 0, ADCx},	/* PD1 */  
#	endif
    {GPIOD,   NULL, NULL,  2, 0, ADCx},	/* PD2 */  
#	if defined(STM32_XL_DENSITY)
    {GPIOD,   NULL, NULL,  3, 0, ADCx},	/* PD3 */  
    {GPIOD, TIMER2, NULL,  4, 2, ADCx},	/* PD4 */  
    {GPIOD,   NULL, NULL,  5, 0, ADCx},	/* PD5 */  
    {GPIOD, TIMER2, NULL,  6, 4, ADCx},	/* PD6 */  
    {GPIOD, TIMER2, NULL,  7, 3, ADCx},	/* PD7 */  
#	endif
#endif

/* on all density devices */
    {GPIOB, TIMER2, NULL,  3, 2, ADCx},	/* PB3 */ 
    {GPIOB, TIMER3, NULL,  4, 1, ADCx},	/* PB4 */ 			/* also TIMER16 CH1 */
    {GPIOB, TIMER3, NULL,  5, 2, ADCx},	/* PB5 */ 			/* also TIMER17 CH1 */
    {GPIOB, TIMER4, NULL,  6, 1, ADCx},	/* PB6 */
    {GPIOB, TIMER4, NULL,  7, 2, ADCx},	/* PB7 */ 			/* also TIMER3 CH4 */
    {GPIOB, TIMER4, NULL,  8, 3, ADCx},	/* PB8 */ 			/* also TIMER16 CH1 */
    {GPIOB, TIMER4, NULL,  9, 4, ADCx},	/* PB9 */ 			/* also TIMER17 CH1 */

#if defined(STM32_XL_DENSITY)
    {GPIOE,TIMER16, NULL,  0, 1, ADCx},	/* PE0 */  
    {GPIOE,TIMER17, NULL,  1, 1, ADCx},	/* PE1 */  
#endif
};

extern const uint8 boardPWMPins[BOARD_NR_PWM_PINS] __FLASH__ = {
		PA0, PA1, PA2, PA3, PA4, PA6, PA7, PB0, PB1, PB10, PB11, PB14, PB15, PA8, PA9, PA10, PA11, PA12, PA13, PB3, PB4, PB5, PB6, PB7, PB8, PB9,
#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
		PC6, PC7, PC8, PC9,
#	if defined(STM32_XL_DENSITY)
		PE2, PE3, PE4, PE5, PF9, PF10, PE9, PE11, PE13, PE14, PD12, PD13, PD14, PD15, PF6, PD4, PD6, PD7, PE0, PE1,
#	endif
#endif
};

extern const uint8 boardADCPins[BOARD_NR_ADC_PINS] __FLASH__ = {
		PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PB2, 
#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
		PC0, PC1, PC2, PC3, PF4, PC4, PC5, 
#	if defined(STM32_XL_DENSITY)
		PF2,
#	endif
#endif
};

#define OSC_IN PF0
#define OSC_OUT PF1

#define USB_DM PA11
#define USB_DP PA12

extern const uint8 boardUsedPins[BOARD_NR_USED_PINS] __FLASH__ = {
    OSC_IN, OSC_OUT, USB_DP, USB_DM
};
