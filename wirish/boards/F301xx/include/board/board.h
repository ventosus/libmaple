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
 * @file   wirish/boards/F301xx/include/board/board.h
 * @author F3-port: Hanspeter Portner <dev@open-music-kontrollers.ch>
 * @brief  F301xx board header (F301K6, F301K8, F301C6, F301C8, F301R6, F301R8).
 *
 * See wirish/boards/maple/include/board/board.h for more information
 * on these definitions.
 */

#ifndef _BOARD_F301xx_H_
#define _BOARD_F301xx_H_

#include <libmaple/stm32.h>

#define CYCLES_PER_MICROSECOND    72
#define SYSTICK_RELOAD_VAL     71999 /* takes a cycle to reload */

enum {
		PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7,
		PB0,
		PA8, PA9, PA10, PA11, PA12, PA13, PA14, PA15,
		PB3, PB4, PB5, PB6, PB7,
#if defined(STM32_MEDIUM_DENSITY) || defined(STM32_HIGH_DENSITY)
		PC13, PC14, PC15,
		PF0, PF1,
		PB1, PB2,
		PB10, PB11, PB12, PB13, PB14, PB15,
		PB8, PB9,
#	if defined(STM32_HIGH_DENSITY)
		PC0, PC1, PC2, PC3,
		PF4,
		PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12,
		PD2,
#	endif
#endif
};

#define BOARD_USART1_TX_PIN       PA9		/* also PB6 */
#define BOARD_USART1_RX_PIN       PA10	/* also PB7 */

#define BOARD_USART2_TX_PIN       PA2		/* also PA14, PB3 */
#define BOARD_USART2_RX_PIN       PA3		/* also PA15, PB4 */

#if !defined(STM32_LOW_DENSITY)
#	define BOARD_USART3_TX_PIN      PB10
#	define BOARD_USART3_RX_PIN      PB11
#endif

#define BOARD_NR_SPI              2

#define BOARD_SPI2_NSS_PIN        PB12
#define BOARD_SPI2_SCK_PIN        PB13
#define BOARD_SPI2_MISO_PIN       PB14
#define BOARD_SPI2_MOSI_PIN       PB15

#define BOARD_SPI3_NSS_PIN        PA15
#define BOARD_SPI3_SCK_PIN        PB3
#define BOARD_SPI3_MISO_PIN       PB4
#define BOARD_SPI3_MOSI_PIN       PB5

#define BOARD_JTMS_SWDIO_PIN      PA13
#define BOARD_JTCK_SWCLK_PIN      PA14
#define BOARD_JTDI_PIN            PA15
#define BOARD_JTDO_PIN            PB3
#define BOARD_NJTRST_PIN          PB4

#elif defined(STM32_LOW_DENSITY)
# define BOARD_NR_USARTS           2
#	define BOARD_NR_GPIO_PINS        22
#	define BOARD_NR_PWM_PINS         9
#	define BOARD_NR_ADC_PINS         8
#	define BOARD_NR_USED_PINS         4
#elif defined(STM32_MEDIUM_DENSITY)
# define BOARD_NR_USARTS           3
#	define BOARD_NR_GPIO_PINS        37
#	define BOARD_NR_PWM_PINS         13 
#	define BOARD_NR_ADC_PINS         11
#	define BOARD_NR_USED_PINS         4
#elif defined(STM32_HIGH_DENSITY)
# define BOARD_NR_USARTS           3
#	define BOARD_NR_GPIO_PINS        52
#	define BOARD_NR_PWM_PINS         17
#	define BOARD_NR_ADC_PINS         15
#	define BOARD_NR_USED_PINS         4
#endif

/* redefine the following ones to match your hardware design */
#define BOARD_BUTTON_PIN          PC13
#define BOARD_LED_PIN             PC14

#define BOARD_USB_DISC_DEV        GPIOC
#define BOARD_USB_DISC_BIT        15

#endif
