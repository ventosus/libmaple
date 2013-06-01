/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2012 LeafLabs, LLC.
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
 * @file libmaple/stm32f2/include/series/adc.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>,
 *         F3-port by Hanspeter Portner <dev@open-music-kontrollers.ch>
 * @brief STM32F2 ADC support.
 */

#ifndef _LIBMAPLE_STM32F2_ADC_H_
#define _LIBMAPLE_STM32F2_ADC_H_

#include <libmaple/libmaple_types.h>

/*
 * Register map
 */

/** ADC register map type. */
typedef struct adc_reg_map {
    __io uint32 SR;             ///< Status register
    __io uint32 CR1;            ///< Control register 1
    __io uint32 CR2;            ///< Control register 2
    __io uint32 SMPR1;          ///< Sample time register 1
    __io uint32 SMPR2;          ///< Sample time register 2
    __io uint32 JOFR1;          ///< Injected channel data offset register 1
    __io uint32 JOFR2;          ///< Injected channel data offset register 2
    __io uint32 JOFR3;          ///< Injected channel data offset register 3
    __io uint32 JOFR4;          ///< Injected channel data offset register 4
    __io uint32 HTR;            ///< Watchdog high threshold register
    __io uint32 LTR;            ///< Watchdog low threshold register
    __io uint32 SQR1;           ///< Regular sequence register 1
    __io uint32 SQR2;           ///< Regular sequence register 2
    __io uint32 SQR3;           ///< Regular sequence register 3
    __io uint32 JSQR;           ///< Injected sequence register
    __io uint32 JDR1;           ///< Injected data register 1
    __io uint32 JDR2;           ///< Injected data register 2
    __io uint32 JDR3;           ///< Injected data register 3
    __io uint32 JDR4;           ///< Injected data register 4
    __io uint32 DR;             ///< Regular data register
} adc_reg_map;

/** ADC device type. */
typedef struct adc_dev {
    adc_reg_map *regs; /**< Register map */
    rcc_clk_id clk_id; /**< RCC clock information */
		adc_private_data *priv;	/**< ADC private data */
} adc_dev;

/*
 * Devices
 */

extern const struct adc_dev *ADC1;
extern const struct adc_dev *ADC2;
extern const struct adc_dev *ADC3;

/*
 * Common register map
 */

/** ADC common register map type */
typedef struct adc_common_reg_map {
    __io uint32 CSR;            /**< Common status register */
    __io uint32 CCR;            /**< Common control register */
    __io uint32 CDR;            /**<
                                 * @brief Common regular data register
                                 *        for dual and triple modes */
} adc_common_reg_map;

/*
 * Register map base pointers
 */

/** ADC1 register map base pointer. */
#define ADC1_BASE       ((struct adc_reg_map*)0x40012000)
/** ADC2 register map base pointer. */
#define ADC2_BASE       ((struct adc_reg_map*)0x40012100)
/** ADC3 register map base pointer. */
#define ADC3_BASE       ((struct adc_reg_map*)0x40012200)
/** ADC common register map base pointer. */
#define ADC_COMMON_BASE ((struct adc_common_reg_map*)0x40012300)

/*
 * Register bit definitions
 */

/* Status register */

#define ADC_SR_AWD_BIT                  0
#define ADC_SR_EOC_BIT                  1
#define ADC_SR_JEOC_BIT                 2
#define ADC_SR_JSTRT_BIT                3
#define ADC_SR_STRT_BIT                 4
#define ADC_SR_OVR_BIT                  5

#define ADC_SR_AWD                      BIT(ADC_SR_AWD_BIT)
#define ADC_SR_EOC                      BIT(ADC_SR_EOC_BIT)
#define ADC_SR_JEOC                     BIT(ADC_SR_JEOC_BIT)
#define ADC_SR_JSTRT                    BIT(ADC_SR_JSTRT_BIT)
#define ADC_SR_STRT                     BIT(ADC_SR_STRT_BIT)
#define ADC_SR_OVR                      (1U << ADC_SR_OVR_BIT)

/* FIXME make an enum out of this */
#define ADC_WATCHDOG_INTERRUPT					ADC_SR_AWD
#define ADC_CONV_INTERRUPT							ADC_SR_EOC
#define ADC_INJ_CONV_INTERRUPT					ADC_SR_JEOC
#define ADC_OVERRUN_INTERRUPT						ADC_SR_OVR
#define ADC_ALL_INTERRUPTS							(ADC_CONV_INTERRUPT | ADC_WATCHDOG_INTERRUPT | ADC_INJ_CONV_INTERRUPT | ADC_OVERRUN_INTERRUPT)

/* Control register 1 */

#define ADC_CR1_EOCIE_BIT               5
#define ADC_CR1_AWDIE_BIT               6
#define ADC_CR1_JEOCIE_BIT              7
#define ADC_CR1_SCAN_BIT                8
#define ADC_CR1_AWDSGL_BIT              9
#define ADC_CR1_JAUTO_BIT               10
#define ADC_CR1_DISCEN_BIT              11
#define ADC_CR1_JDISCEN_BIT             12
#define ADC_CR1_JAWDEN_BIT              22
#define ADC_CR1_AWDEN_BIT               23
#define ADC_CR1_OVRIE_BIT               26

#define ADC_CR1_AWDCH                   (0x1F)
#define ADC_CR1_EOCIE                   BIT(ADC_CR1_EOCIE_BIT)
#define ADC_CR1_AWDIE                   BIT(ADC_CR1_AWDIE_BIT)
#define ADC_CR1_JEOCIE                  BIT(ADC_CR1_JEOCIE_BIT)
#define ADC_CR1_SCAN                    BIT(ADC_CR1_SCAN_BIT)
#define ADC_CR1_AWDSGL                  BIT(ADC_CR1_AWDSGL_BIT)
#define ADC_CR1_JAUTO                   BIT(ADC_CR1_JAUTO_BIT)
#define ADC_CR1_DISCEN                  BIT(ADC_CR1_DISCEN_BIT)
#define ADC_CR1_JDISCEN                 BIT(ADC_CR1_JDISCEN_BIT)
#define ADC_CR1_DISCNUM                 (0xE000)
#define ADC_CR1_JAWDEN                  BIT(ADC_CR1_JAWDEN_BIT)
#define ADC_CR1_AWDEN                   BIT(ADC_CR1_AWDEN_BIT)
/** Conversion resolution. */
#define ADC_CR1_RES                     (0x3U << 24)
/** Conversion resolution: 12 bit (at least 15 ADCCLK cycles). */
#define ADC_CR1_RES_12BIT               (0x0U << 24)
/** Conversion resolution: 10 bit (at least 13 ADCCLK cycles). */
#define ADC_CR1_RES_10BIT               (0x1U << 24)
/** Conversion resolution: 8 bit (at least 11 ADCCLK cycles). */
#define ADC_CR1_RES_8BIT                (0x2U << 24)
/** Conversion resolution: 6 bit (at least 9 ADCCLK cycles). */
#define ADC_CR1_RES_6BIT                (0x3U << 24)
#define ADC_CR1_OVRIE                   (1U << ADC_CR1_OVRIE_BIT)

/* Control register 2 */

#define ADC_CR2_SWSTART_BIT             30
#define ADC_CR2_JSWSTART_BIT            22
#define ADC_CR2_ALIGN_BIT               11
#define ADC_CR2_EOCS_BIT                10
#define ADC_CR2_DDS_BIT                 9
#define ADC_CR2_DMA_BIT                 8
#define ADC_CR2_CONT_BIT                1
#define ADC_CR2_ADON_BIT                0

#define ADC_CR2_SWSTART                 (1U << ADC_CR2_SWSTART_BIT)
#define ADC_CR2_EXTEN                   (0x3 << 28)
#define ADC_CR2_EXTEN_DISABLED          (0x0 << 28)
#define ADC_CR2_EXTEN_RISE              (0x1 << 28)
#define ADC_CR2_EXTEN_FALL              (0x2 << 28)
#define ADC_CR2_EXTEN_RISE_FALL         (0x3 << 28)
#define ADC_CR2_EXTSEL                  (0xF << 24)
#define ADC_CR2_EXTSEL_TIM1_CC1         (0x0 << 24)
#define ADC_CR2_EXTSEL_TIM1_CC2         (0x1 << 24)
#define ADC_CR2_EXTSEL_TIM1_CC3         (0x2 << 24)
#define ADC_CR2_EXTSEL_TIM2_CC2         (0x3 << 24)
#define ADC_CR2_EXTSEL_TIM2_CC3         (0x4 << 24)
#define ADC_CR2_EXTSEL_TIM2_CC4         (0x5 << 24)
#define ADC_CR2_EXTSEL_TIM1_TRGO        (0x6 << 24)
#define ADC_CR2_EXTSEL_TIM3_CC1         (0x7 << 24)
#define ADC_CR2_EXTSEL_TIM3_TRGO        (0x8 << 24)
#define ADC_CR2_EXTSEL_TIM4_CC4         (0x9 << 24)
#define ADC_CR2_EXTSEL_TIM5_CC1         (0xA << 24)
#define ADC_CR2_EXTSEL_TIM5_CC2         (0xB << 24)
#define ADC_CR2_EXTSEL_TIM5_CC3         (0xC << 24)
#define ADC_CR2_EXTSEL_TIM8_CC1         (0xD << 24)
#define ADC_CR2_EXTSEL_TIM8_TRGO        (0xE << 24)
#define ADC_CR2_EXTSEL_TIM1_EXTI11      (0xF << 24)
#define ADC_CR2_JSWSTART                (1U << ADC_CR2_JSWSTART_BIT)
#define ADC_CR2_JEXTEN                  (0x3 << 20)
#define ADC_CR2_JEXTEN_DISABLED         (0x0 << 20)
#define ADC_CR2_JEXTEN_RISE             (0x1 << 20)
#define ADC_CR2_JEXTEN_FALL             (0x2 << 20)
#define ADC_CR2_JEXTEN_RISE_FALL        (0x3 << 20)
#define ADC_CR2_JEXTSEL                 (0xF << 16)
#define ADC_CR2_JEXTSEL_TIM1_CC4        (0x0 << 16)
#define ADC_CR2_JEXTSEL_TIM1_TRGO       (0x1 << 16)
#define ADC_CR2_JEXTSEL_TIM2_CC1        (0x2 << 16)
#define ADC_CR2_JEXTSEL_TIM2_TRGO       (0x3 << 16)
#define ADC_CR2_JEXTSEL_TIM3_CC2        (0x4 << 16)
#define ADC_CR2_JEXTSEL_TIM3_CC4        (0x5 << 16)
#define ADC_CR2_JEXTSEL_TIM4_CC1        (0x6 << 16)
#define ADC_CR2_JEXTSEL_TIM4_CC2        (0x7 << 16)
#define ADC_CR2_JEXTSEL_TIM4_CC3        (0x8 << 16)
#define ADC_CR2_JEXTSEL_TIM4_TRGO       (0x9 << 16)
#define ADC_CR2_JEXTSEL_TIM5_CC4        (0xA << 16)
#define ADC_CR2_JEXTSEL_TIM5_TRGO       (0xB << 16)
#define ADC_CR2_JEXTSEL_TIM8_CC2        (0xC << 16)
#define ADC_CR2_JEXTSEL_TIM8_CC3        (0xD << 16)
#define ADC_CR2_JEXTSEL_TIM8_CC4        (0xE << 16)
#define ADC_CR2_JEXTSEL_TIM1_EXTI15     (0xF << 16)
#define ADC_CR2_ALIGN                   (1U << ADC_CR2_ALIGN_BIT)
#define ADC_CR2_ALIGN_RIGHT             (0U << ADC_CR2_ALIGN_BIT)
#define ADC_CR2_ALIGN_LEFT              (1U << ADC_CR2_ALIGN_BIT)
#define ADC_CR2_EOCS                    (1U << ADC_CR2_EOCS_BIT)
#define ADC_CR2_EOCS_SEQUENCE           (0U << ADC_CR2_EOCS_BIT)
#define ADC_CR2_EOCS_CONVERSION         (1U << ADC_CR2_EOCS_BIT)
#define ADC_CR2_DDS                     (1U << ADC_CR2_DDS_BIT)
#define ADC_CR2_DMA                     (1U << ADC_CR2_DMA_BIT)
#define ADC_CR2_CONT                    (1U << ADC_CR2_CONT_BIT)
#define ADC_CR2_ADON                    (1U << ADC_CR2_ADON_BIT)

/* Sample time register 1 */

#define ADC_SMPR1_SMP17                 (0x7 << 21)
#define ADC_SMPR1_SMP16                 (0x7 << 18)
#define ADC_SMPR1_SMP15                 (0x7 << 15)
#define ADC_SMPR1_SMP14                 (0x7 << 12)
#define ADC_SMPR1_SMP13                 (0x7 << 9)
#define ADC_SMPR1_SMP12                 (0x7 << 6)
#define ADC_SMPR1_SMP11                 (0x7 << 3)
#define ADC_SMPR1_SMP10                 0x7

/* Sample time register 2 */

#define ADC_SMPR2_SMP9                  (0x7 << 27)
#define ADC_SMPR2_SMP8                  (0x7 << 24)
#define ADC_SMPR2_SMP7                  (0x7 << 21)
#define ADC_SMPR2_SMP6                  (0x7 << 18)
#define ADC_SMPR2_SMP5                  (0x7 << 15)
#define ADC_SMPR2_SMP4                  (0x7 << 12)
#define ADC_SMPR2_SMP3                  (0x7 << 9)
#define ADC_SMPR2_SMP2                  (0x7 << 6)
#define ADC_SMPR2_SMP1                  (0x7 << 3)
#define ADC_SMPR2_SMP0                  0x7

/* Injected channel data offset register */

#define ADC_JOFR_JOFFSET                0x3FF

/* Watchdog high threshold register */

#define ADC_HTR_HT                      0x3FF

/* Watchdog low threshold register */

#define ADC_LTR_LT                      0x3FF

/* Regular sequence register 1 */

#define ADC_SQR1_L                      (0x1F << 20)
#define ADC_SQR1_SQ16                   (0x1F << 15)
#define ADC_SQR1_SQ15                   (0x1F << 10)
#define ADC_SQR1_SQ14                   (0x1F << 5)
#define ADC_SQR1_SQ13                   0x1F

/* Regular sequence register 2 */

#define ADC_SQR2_SQ12                   (0x1F << 25)
#define ADC_SQR2_SQ11                   (0x1F << 20)
#define ADC_SQR2_SQ10                   (0x1F << 16)
#define ADC_SQR2_SQ9                    (0x1F << 10)
#define ADC_SQR2_SQ8                    (0x1F << 5)
#define ADC_SQR2_SQ7                    0x1F

/* Regular sequence register 3 */

#define ADC_SQR3_SQ6                    (0x1F << 25)
#define ADC_SQR3_SQ5                    (0x1F << 20)
#define ADC_SQR3_SQ4                    (0x1F << 16)
#define ADC_SQR3_SQ3                    (0x1F << 10)
#define ADC_SQR3_SQ2                    (0x1F << 5)
#define ADC_SQR3_SQ1                    0x1F

/* Injected sequence register */

#define ADC_JSQR_JL                     (0x3 << 20)
#define ADC_JSQR_JL_1CONV               (0x0 << 20)
#define ADC_JSQR_JL_2CONV               (0x1 << 20)
#define ADC_JSQR_JL_3CONV               (0x2 << 20)
#define ADC_JSQR_JL_4CONV               (0x3 << 20)
#define ADC_JSQR_JSQ4                   (0x1F << 15)
#define ADC_JSQR_JSQ3                   (0x1F << 10)
#define ADC_JSQR_JSQ2                   (0x1F << 5)
#define ADC_JSQR_JSQ1                   0x1F

/* Injected data registers */

#define ADC_JDR_JDATA                   0xFFFF

/* Regular data register */

#define ADC_DR_ADC2DATA                 (0xFFFF << 16)
#define ADC_DR_DATA                     0xFFFF

/* Common status register */

#define ADC_CSR_OVR3_BIT                21
#define ADC_CSR_STRT3_BIT               20
#define ADC_CSR_JSTRT3_BIT              19
#define ADC_CSR_JEOC3_BIT               18
#define ADC_CSR_EOC3_BIT                17
#define ADC_CSR_AWD3_BIT                16
#define ADC_CSR_OVR2_BIT                13
#define ADC_CSR_STRT2_BIT               12
#define ADC_CSR_JSTRT2_BIT              11
#define ADC_CSR_JEOC2_BIT               10
#define ADC_CSR_EOC2_BIT                9
#define ADC_CSR_AWD2_BIT                8
#define ADC_CSR_OVR1_BIT                5
#define ADC_CSR_STRT1_BIT               4
#define ADC_CSR_JSTRT1_BIT              3
#define ADC_CSR_JEOC1_BIT               2
#define ADC_CSR_EOC1_BIT                1
#define ADC_CSR_AWD1_BIT                0

#define ADC_CSR_OVR3                    (1U << ADC_CSR_OVR3_BIT)
#define ADC_CSR_STRT3                   (1U << ADC_CSR_STRT3_BIT)
#define ADC_CSR_JSTRT3                  (1U << ADC_CSR_JSTRT3_BIT)
#define ADC_CSR_JEOC3                   (1U << ADC_CSR_JEOC3_BIT)
#define ADC_CSR_EOC3                    (1U << ADC_CSR_EOC3_BIT)
#define ADC_CSR_AWD3                    (1U << ADC_CSR_AWD3_BIT)
#define ADC_CSR_OVR2                    (1U << ADC_CSR_OVR2_BIT)
#define ADC_CSR_STRT2                   (1U << ADC_CSR_STRT2_BIT)
#define ADC_CSR_JSTRT2                  (1U << ADC_CSR_JSTRT2_BIT)
#define ADC_CSR_JEOC2                   (1U << ADC_CSR_JEOC2_BIT)
#define ADC_CSR_EOC2                    (1U << ADC_CSR_EOC2_BIT)
#define ADC_CSR_AWD2                    (1U << ADC_CSR_AWD2_BIT)
#define ADC_CSR_OVR1                    (1U << ADC_CSR_OVR1_BIT)
#define ADC_CSR_STRT1                   (1U << ADC_CSR_STRT1_BIT)
#define ADC_CSR_JSTRT1                  (1U << ADC_CSR_JSTRT1_BIT)
#define ADC_CSR_JEOC1                   (1U << ADC_CSR_JEOC1_BIT)
#define ADC_CSR_EOC1                    (1U << ADC_CSR_EOC1_BIT)
#define ADC_CSR_AWD1                    (1U << ADC_CSR_AWD1_BIT)

/* Common control register */

#define ADC_CCR_TSVREFE_BIT             23
#define ADC_CCR_VBATE_BIT               22
#define ADC_CCR_DDS_BIT                 13

#define ADC_CCR_TSVREFE                       (1U << ADC_CCR_TSVREFE_BIT)
#define ADC_CCR_VBATE                         (1U << ADC_CCR_VBATE_BIT)
#define ADC_CCR_ADCPRE                        (0x3 << 16)
#define ADC_CCR_ADCPRE_PCLK2_DIV_2            (0x0 << 16)
#define ADC_CCR_ADCPRE_PCLK2_DIV_4            (0x1 << 16)
#define ADC_CCR_ADCPRE_PCLK2_DIV_6            (0x2 << 16)
#define ADC_CCR_ADCPRE_PCLK2_DIV_8            (0x3 << 16)
#define ADC_CCR_DMA                           (0x3 << 14)
#define ADC_CCR_DMA_DIS                       (0x0 << 14)
#define ADC_CCR_DMA_MODE_1                    (0x1 << 14)
#define ADC_CCR_DMA_MODE_2                    (0x2 << 14)
#define ADC_CCR_DMA_MODE_3                    (0x3 << 14)
#define ADC_CCR_DDS                           (1U << ADC_CCR_DDS_BIT)
#define ADC_CCR_DELAY                         (0xF << 8)
#define ADC_CCR_DELAY_5                       (0x0 << 8)
#define ADC_CCR_DELAY_6                       (0x1 << 8)
#define ADC_CCR_DELAY_7                       (0x2 << 8)
#define ADC_CCR_DELAY_8                       (0x3 << 8)
#define ADC_CCR_DELAY_9                       (0x4 << 8)
#define ADC_CCR_DELAY_10                      (0x5 << 8)
#define ADC_CCR_DELAY_11                      (0x6 << 8)
#define ADC_CCR_DELAY_12                      (0x7 << 8)
#define ADC_CCR_DELAY_13                      (0x8 << 8)
#define ADC_CCR_DELAY_14                      (0x9 << 8)
#define ADC_CCR_DELAY_15                      (0xA << 8)
#define ADC_CCR_DELAY_16                      (0xB << 8)
#define ADC_CCR_DELAY_17                      (0xC << 8)
#define ADC_CCR_DELAY_18                      (0xD << 8)
#define ADC_CCR_DELAY_19                      (0xE << 8)
#define ADC_CCR_DELAY_20                      (0xF << 8)
/** Multi ADC mode selection. */
#define ADC_CCR_MULTI                         0x1F
/** All ADCs independent. */
#define ADC_CCR_MULTI_INDEPENDENT             0x0
/** Dual mode: combined regular simultaneous/injected simultaneous. */
#define ADC_CCR_MULTI_DUAL_REG_SIM_INJ_SIM    0x1
/** Dual mode: combined regular simultaneous/alternate trigger. */
#define ADC_CCR_MULTI_DUAL_REG_SIM_ALT_TRIG   0x2
/** Dual mode: injected simultaneous mode only. */
#define ADC_CCR_MULTI_DUAL_INJ_SIM            0x5
/** Dual mode: regular simultaneous mode only. */
#define ADC_CCR_MULTI_DUAL_REG_SIM            0x6
/** Dual mode: interleaved mode only. */
#define ADC_CCR_MULTI_DUAL_INTER              0x7
/** Dual mode: alternate trigger mode only. */
#define ADC_CCR_MULTI_DUAL_ALT_TRIG           0x9
/** Triple mode: combined regular simultaneous/injected simultaneous. */
#define ADC_CCR_MULTI_TRIPLE_REG_SIM_INJ_SIM  0x10
/** Triple mode: combined regular simultaneous/alternate trigger. */
#define ADC_CCR_MULTI_TRIPLE_REG_SIM_ALT_TRIG 0x11
/** Triple mode: injected simultaneous mode only. */
#define ADC_CCR_MULTI_TRIPLE_INJ_SIM          0x12
/** Triple mode: regular simultaneous mode only. */
#define ADC_CCR_MULTI_TRIPLE_REG_SIM          0x15
/** Triple mode: interleaved mode only. */
#define ADC_CCR_MULTI_TRIPLE_INTER            0x17
/** Triple mode: alternate trigger mode only. */
#define ADC_CCR_MULTI_TRIPLE_ALT_TRIG         0x19

/* Common regular data register for dual and triple modes */

#define ADC_CDR_DATA2                   0xFFFF0000
#define ADC_CDR_DATA1                   0xFFFF

/*
 * Other types
 */

/**
 * @brief STM32F2 external event selectors for regular group
 *        conversion.
 * @see adc_set_extsel()
 */
typedef enum adc_extsel_event {
    ADC_EXT_EV_TIM1_CC1    = ADC_CR2_EXTSEL_TIM1_CC1,
    ADC_EXT_EV_TIM1_CC2    = ADC_CR2_EXTSEL_TIM1_CC2,
    ADC_EXT_EV_TIM1_CC3    = ADC_CR2_EXTSEL_TIM1_CC3,
    ADC_EXT_EV_TIM2_CC2    = ADC_CR2_EXTSEL_TIM2_CC2,
    ADC_EXT_EV_TIM2_CC3    = ADC_CR2_EXTSEL_TIM2_CC3,
    ADC_EXT_EV_TIM2_CC4    = ADC_CR2_EXTSEL_TIM2_CC4,
    ADC_EXT_EV_TIM1_TRGO   = ADC_CR2_EXTSEL_TIM1_TRGO,
    ADC_EXT_EV_TIM3_CC1    = ADC_CR2_EXTSEL_TIM3_CC1,
    ADC_EXT_EV_TIM3_TRGO   = ADC_CR2_EXTSEL_TIM3_TRGO,
    ADC_EXT_EV_TIM4_CC4    = ADC_CR2_EXTSEL_TIM4_CC4,
    ADC_EXT_EV_TIM5_CC1    = ADC_CR2_EXTSEL_TIM5_CC1,
    ADC_EXT_EV_TIM5_CC2    = ADC_CR2_EXTSEL_TIM5_CC2,
    ADC_EXT_EV_TIM5_CC3    = ADC_CR2_EXTSEL_TIM5_CC3,
    ADC_EXT_EV_TIM8_CC1    = ADC_CR2_EXTSEL_TIM8_CC1,
    ADC_EXT_EV_TIM8_TRGO   = ADC_CR2_EXTSEL_TIM8_TRGO,
    ADC_EXT_EV_TIM1_EXTI11 = ADC_CR2_EXTSEL_TIM1_EXTI11,
} adc_extsel_event;

/**
 * @brief STM32F2 sample times, in ADC clock cycles.
 */
typedef enum adc_smp_rate {
    ADC_SMPR_3,                 /**< 3 ADC cycles */
    ADC_SMPR_15,                /**< 15 ADC cycles */
    ADC_SMPR_28,                /**< 28 ADC cycles */
    ADC_SMPR_56,                /**< 56 ADC cycles */
    ADC_SMPR_84,                /**< 84 ADC cycles */
    ADC_SMPR_112,               /**< 112 ADC cycles */
    ADC_SMPR_144,               /**< 144 ADC cycles */
    ADC_SMPR_480,               /**< 480 ADC cycles */
} adc_smp_rate;

/**
 * @brief STM32F2 ADC prescalers, as divisors of PCLK2.
 */
typedef enum adc_prescaler {
    /** PCLK2 divided by 2 */
    ADC_PRE_PCLK2_DIV_2 = ADC_CCR_ADCPRE_PCLK2_DIV_2,
    /** PCLK2 divided by 4 */
    ADC_PRE_PCLK2_DIV_4 = ADC_CCR_ADCPRE_PCLK2_DIV_4,
    /** PCLK2 divided by 6 */
    ADC_PRE_PCLK2_DIV_6 = ADC_CCR_ADCPRE_PCLK2_DIV_6,
    /** PCLK2 divided by 8 */
    ADC_PRE_PCLK2_DIV_8 = ADC_CCR_ADCPRE_PCLK2_DIV_8,
} adc_prescaler;

#endif
