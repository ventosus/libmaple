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
 * @file libmaple/stm32f3/include/series/usart.h
 * @author F3-port by Hanspeter Portner <dev@open-music-kontrollers.ch>
 * @brief STM32F3 USART support.
 */

#ifndef _LIBMAPLE_STM32F3_USART_H_
#define _LIBMAPLE_STM32F3_USART_H_

#ifdef __cplusplus
extern "C"{
#endif

/*
 * Register maps
 */

///** I2C register map type */
//typedef struct usart_reg_map {
//    __io uint32 CR1;            /**< Control register 1 */
//    __io uint32 CR2;            /**< Control register 2 */
//    __io uint32 CR3;            /**< Control register 3 */
//    __io uint32 BRR;            /**< Baud rate register */
//    __io uint32 GTPR;           /**< Guard time and prescaler register */
//    __io uint32 RTOR;           /**< Receiver timeout register */
//    __io uint32 RQR;            /**< Request register */
//    __io uint32 ISR;            /**< Interrupt and status register */
//    __io uint32 ICR;            /**< Interrupt clear register */
//    __io uint32 RDR;            /**< Receive data register */
//    __io uint32 TDR;            /**< Transmit data register */
//} usart_reg_map;

/*
 * Register map base pointers
 */

/** USART1 register map base pointer */
#define USART1_BASE                     ((struct usart_reg_map*)0x40013800)
/** USART2 register map base pointer */
#define USART2_BASE                     ((struct usart_reg_map*)0x40004400)
/** USART3 register map base pointer */
#define USART3_BASE                     ((struct usart_reg_map*)0x40004800)

#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
/** UART4 register map base pointer */
#define UART4_BASE                      ((struct usart_reg_map*)0x40004C00)
/** UART5 register map base pointer */
#define UART5_BASE                      ((struct usart_reg_map*)0x40005000)
#endif

/* TODO add register bit definitions */
/* TODO add some routines */

#ifdef __cplusplus
}
#endif

#endif
