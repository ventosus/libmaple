/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung (from <libmaple/i2c.h>).
 * Copyright (c) 2012 LeafLabs, LLC.
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
 * @file libmaple/stm32f1/include/series/i2c.h
 * @brief STM32F1 I2C
 */

#ifndef _LIBMAPLE_STM32F1_I2C_H_
#define _LIBMAPLE_STM32F1_I2C_H_

#include <libmaple/i2c_common.h>
#include <libmaple/gpio.h>
#include <libmaple/stm32.h>

/*
 * Register maps
 */

/** I2C register map type */
typedef struct i2c_reg_map {
    __io uint32 CR1;            /**< Control register 1 */
    __io uint32 CR2;            /**< Control register 2 */
    __io uint32 OAR1;           /**< Own address register 1 */
    __io uint32 OAR2;           /**< Own address register 2 */
    __io uint32 DR;             /**< Data register */
    __io uint32 SR1;            /**< Status register 1 */
    __io uint32 SR2;            /**< Status register 2 */
    __io uint32 CCR;            /**< Clock control register */
    __io uint32 TRISE;          /**< TRISE (rise time) register */
} i2c_reg_map;

/** STM32F1 I2C1 register map base pointer */
#define I2C1_BASE               ((struct i2c_reg_map*)0x40005400)
/** STM32F1 I2C2 register map base pointer */
#define I2C2_BASE               ((struct i2c_reg_map*)0x40005800)

/*
 * Devices
 */

extern i2c_dev* const I2C1;
extern i2c_dev* const I2C2;

/*
 * Register bit definitions
 */

/* Control register 1 */

#define I2C_CR1_SWRST           (1U << 15)    // Software reset
#define I2C_CR1_ALERT           (1U << 13)    // SMBus alert
#define I2C_CR1_PEC             (1U << 12)    // Packet error checking
#define I2C_CR1_POS             (1U << 11)    // Acknowledge/PEC position
#define I2C_CR1_ACK             (1U << 10)    // Acknowledge enable
#define I2C_CR1_STOP            (1U << 9)     // Stop generation
#define I2C_CR1_START           (1U << 8)     // Start generation
#define I2C_CR1_NOSTRETCH       (1U << 7)     // Clock stretching disable
#define I2C_CR1_ENGC            (1U << 6)     // General call enable
#define I2C_CR1_ENPEC           (1U << 5)     // PEC enable
#define I2C_CR1_ENARP           (1U << 4)     // ARP enable
#define I2C_CR1_SMBTYPE         (1U << 3)     // SMBus type
#define I2C_CR1_SMBTYPE_DEVICE  (0U << 3)     //     SMBus type: device
#define I2C_CR1_SMBTYPE_HOST    (1U << 3)     //     SMBus type: host
#define I2C_CR1_SMBUS           (1U << 1)     // SMBus mode
#define I2C_CR1_SMBUS_I2C       (0U << 1)     //     SMBus mode: I2C
#define I2C_CR1_SMBUS_SMBUS     (1U << 1)     //     SMBus mode: SMBus
#define I2C_CR1_PE              (1U << 0)     // Peripheral Enable

/* Control register 2 */

#define I2C_CR2_LAST            (1U << 12)    // DMA last transfer
#define I2C_CR2_DMAEN           (1U << 11)    // DMA requests enable
#define I2C_CR2_ITBUFEN         (1U << 10)    // Buffer interrupt enable
#define I2C_CR2_ITEVTEN         (1U << 9)     // Event interupt enable
#define I2C_CR2_ITERREN         (1U << 8)     // Error interupt enable
#define I2C_CR2_FREQ            0x3F          // Peripheral input frequency

/* Own address register 1 */

#define I2C_OAR1_ADDMODE        (1U << 15)    // Addressing mode
#define I2C_OAR1_ADDMODE_7_BIT  (0U << 15)    //     Addressing mode: 7-bit
#define I2C_OAR1_ADDMODE_10_BIT (1U << 15)    //     Addressing mode: 10-bit
#define I2C_OAR1_ADD            0x3FF         // Interface address

/* Own address register 2 */

#define I2C_OAR2_ADD2           0xFE          // Interface address
#define I2C_OAR2_ENDUAL         1U            // Dual addressing mode enable

/* Status register 1 */

#define I2C_SR1_SMBALERT        (1U << 15)    // SMBus alert
#define I2C_SR1_TIMEOUT         (1U << 14)    // Timeout or Tlow error
#define I2C_SR1_PECERR          (1U << 12)    // PEC Error in reception
#define I2C_SR1_OVR             (1U << 11)    // Overrun/underrun
#define I2C_SR1_AF              (1U << 10)    // Acknowledge failure
#define I2C_SR1_ARLO            (1U << 9)     // Arbitration lost
#define I2C_SR1_BERR            (1U << 8)     // Bus error
#define I2C_SR1_TXE             (1U << 7)     // Data register empty
#define I2C_SR1_RXNE            (1U << 6)     // Data register not empty
#define I2C_SR1_STOPF           (1U << 4)     // Stop detection
#define I2C_SR1_ADD10           (1U << 3)     // 10-bit header sent
#define I2C_SR1_BTF             (1U << 2)     // Byte transfer finished
#define I2C_SR1_ADDR            (1U << 1)     // Address sent/matched
#define I2C_SR1_SB              (1U << 0)     // Start bit

/* Status register 2 */

#define I2C_SR2_PEC             0xFF00        // Packet error checking register
#define I2C_SR2_DUALF           (1U << 7)     // Dual flag
#define I2C_SR2_SMBHOST         (1U << 6)     // SMBus host header
#define I2C_SR2_SMBDEFAULT      (1U << 5)     // SMBus device default address
#define I2C_SR2_GENCALL         (1U << 4)     // General call address
#define I2C_SR2_TRA             (1U << 2)     // Transmitter/receiver
#define I2C_SR2_BUSY            (1U << 1)     // Bus busy
#define I2C_SR2_MSL             (1U << 0)     // Master/slave

/* Clock control register */

#define I2C_CCR_FS              (1U << 15)    // Fast mode selection
#define I2C_CCR_DUTY            (1U << 14)    // Fast mode duty cycle
#define I2C_CCR_DUTY_2_1        (0U << 14)    //     Fast mode duty: 2/1
#define I2C_CCR_DUTY_16_9       (1U << 14)    //     Fast mode duty: 16/9
#define I2C_CCR_CCR             0xFFF         // Clock control bits

/*
 * For internal use
 */
static inline uint32 _i2c_bus_clk(i2c_dev *dev) {
    /* Both I2C peripherals are on APB1 */
    return STM32_PCLK1 / (1000 * 1000);
}

#define _I2C_HAVE_IRQ_FIXUP 1
void _i2c_irq_priority_fixup(i2c_dev *dev);

/*
 * Deprecated functionality
 */

/* Flag to use alternate pin mapping in i2c_master_enable(). */
#define _I2C_HAVE_DEPRECATED_I2C_REMAP 1
#define I2C_REMAP 0x4
static inline void _i2c_handle_remap(i2c_dev *dev, uint32 flags) {
    if ((dev == I2C1) && (flags & I2C_REMAP)) {
        afio_remap(AFIO_REMAP_I2C1);
        I2C1->sda_pin = 9;
        I2C1->scl_pin = 8;
    }
}

/**
 * @brief Set input clock frequency, in MHz
 * @param dev I2C device
 * @param freq Frequency, in MHz. This must be at least 2, and at most
 *             the APB frequency of dev's bus. (For example, if
 *             rcc_dev_clk(dev) == RCC_APB1, freq must be at most
 *             PCLK1, in MHz). There is an additional limit of 46 MHz.
 */
static inline void i2c_set_input_clk(i2c_dev *dev, uint32 freq) {
#define I2C_MAX_FREQ_MHZ 46
    ASSERT(2 <= freq && freq <= _i2c_bus_clk(dev) && freq <= I2C_MAX_FREQ_MHZ);
    uint32 cr2 = dev->regs->CR2;
    cr2 &= ~I2C_CR2_FREQ;
    cr2 |= freq;
    dev->regs->CR2 = freq;
#undef I2C_MAX_FREQ_MHZ
}

/**
 * @brief Set I2C clock control register.
 *
 * See the chip reference manual for the details.
 *
 * @param dev I2C device
 * @param val Value to use for clock control register (in
 *            Fast/Standard mode)
 */
static inline void i2c_set_clk_control(i2c_dev *dev, uint32 val) {
    uint32 ccr = dev->regs->CCR;
    ccr &= ~I2C_CCR_CCR;
    ccr |= val;
    dev->regs->CCR = ccr;
}

/* Auxiliary procedure for enabling an I2C peripheral; `flags' as for
 * i2c_master_enable(). */
void _i2c_set_ccr_trise(i2c_dev *dev, uint32 flags);

/**
 * @brief Set SCL rise time
 * @param dev I2C device
 * @param trise Maximum rise time in fast/standard mode (see chip
 *              reference manual for the relevant formulas).
 */
static inline void i2c_set_trise(i2c_dev *dev, uint32 trise) {
    dev->regs->TRISE = trise;
}

#endif  /* _LIBMAPLE_STM32F1_I2C_H_ */
