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
 * @file libmaple/stm32f3/usart.c
 * @author F3-port by Hanspeter Portner <dev@open-music-kontrollers.ch>
 * @brief STM32F3 USART.
 */

#include <libmaple/usart.h>
#include <libmaple/gpio.h>
#include "usart_private.h"

/*
 * Devices
 */

static ring_buffer usart1_rb;
static usart_dev usart1 = {
    .regs     = USART1_BASE,
    .rb       = &usart1_rb,
    .max_baud = 4500000UL,
    .clk_id   = RCC_USART1,
    .irq_num  = NVIC_USART1,
};
/** USART1 device */
usart_dev *USART1 = &usart1;

static ring_buffer usart2_rb;
static usart_dev usart2 = {
    .regs     = USART2_BASE,
    .rb       = &usart2_rb,
    .max_baud = 2250000UL,
    .clk_id   = RCC_USART2,
    .irq_num  = NVIC_USART2,
};
/** USART2 device */
usart_dev *USART2 = &usart2;

static ring_buffer usart3_rb;
static usart_dev usart3 = {
    .regs     = USART3_BASE,
    .rb       = &usart3_rb,
    .max_baud = 2250000UL,
    .clk_id   = RCC_USART3,
    .irq_num  = NVIC_USART3,
};
/** USART3 device */
usart_dev *USART3 = &usart3;

#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
static ring_buffer uart4_rb;
static usart_dev uart4 = {
    .regs     = UART4_BASE,
    .rb       = &uart4_rb,
    .max_baud = 2250000UL,
    .clk_id   = RCC_UART4,
    .irq_num  = NVIC_UART4,
};
/** UART4 device */
usart_dev *UART4 = &uart4;

static ring_buffer uart5_rb;
static usart_dev uart5 = {
    .regs     = UART5_BASE,
    .rb       = &uart5_rb,
    .max_baud = 2250000UL,
    .clk_id   = RCC_UART5,
    .irq_num  = NVIC_UART5,
};
/** UART5 device */
usart_dev *UART5 = &uart5;
#endif

/*
 * Routines
 */

void usart_config_gpios_async(usart_dev *udev,
                              gpio_dev *rx_dev, uint8 rx,
                              gpio_dev *tx_dev, uint8 tx,
                              unsigned flags) {
    gpio_set_modef(rx_dev, rx, GPIO_MODE_AF, GPIO_MODEF_PUPD_NONE);
    gpio_set_modef(tx_dev, tx, GPIO_MODE_AF, GPIO_MODEF_TYPE_PP);
}

void usart_set_baud_rate(usart_dev *dev, uint32 clock_speed, uint32 baud) {
		//TODO
}

void usart_enable(usart_dev *dev)
{
		//TODO
}

void usart_disable(usart_dev *dev)
{
		//TODO
}

uint32 usart_tx(usart_dev *dev, const uint8 *buf, uint32 len)
{
		//TODO
		return 0U;
}

uint32 usart_rx(usart_dev *dev, uint8 *buf, uint32 len)
{
		//TODO
		return 0U;
}

void usart_putudec(usart_dev *dev, uint32 val)
{
		//TODO
}

/**
 * @brief Call a function on each USART.
 * @param fn Function to call.
 */
void usart_foreach(void (*fn)(usart_dev*)) {
    fn(USART1);
    fn(USART2);
    fn(USART3);
#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
    fn(UART4);
    fn(UART5);
#endif
}

/*
 * Interrupt handlers.
 */

void __irq_usart1(void) {
		//TODO
}

void __irq_usart2(void) {
		//TODO
}

void __irq_usart3(void) {
		//TODO
}

#ifdef STM32_HIGH_DENSITY
void __irq_uart4(void) {
		//TODO
}

void __irq_uart5(void) {
		//TODO
}
#endif
