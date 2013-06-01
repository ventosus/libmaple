/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2012 LeafLabs, LLC.
 * Copyright (c) 2010 Perry Hung.
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
 * @file libmaple/stm32f1/include/series/adc.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>,
 *         Perry Hung <perry@leaflabs.com>,
 *         F3-port by Hanspeter Portner <dev@open-music-kontrollers.ch>
 * @brief STM32F1 ADC header.
 */

#ifndef _LIBMAPLE_STM32F1_ADC_H_
#define _LIBMAPLE_STM32F1_ADC_H_

#include <libmaple/bitband.h>
#include <libmaple/libmaple_types.h>
#include <libmaple/rcc.h>       /* For the prescalers */

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

extern const adc_dev *ADC1;
extern const adc_dev *ADC2;
#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
extern const adc_dev *ADC3;
#endif

/*
 * Register map base pointers
 */

/** STM32F1 ADC1 register map base pointer. */
#define ADC1_BASE                       ((struct adc_reg_map*)0x40012400)
/** STM32F1 ADC2 register map base pointer. */
#define ADC2_BASE                       ((struct adc_reg_map*)0x40012800)
/** STM32F1 ADC3 register map base pointer. */
#define ADC3_BASE                       ((struct adc_reg_map*)0x40013C00)

/*
 * Register bit definitions
 */

/* Status register */

#define ADC_SR_AWD_BIT                  0
#define ADC_SR_EOC_BIT                  1
#define ADC_SR_JEOC_BIT                 2
#define ADC_SR_JSTRT_BIT                3
#define ADC_SR_STRT_BIT                 4
#define ADC_SR_OVR_BIT                 	5

#define ADC_SR_AWD                      BIT(ADC_SR_AWD_BIT)
#define ADC_SR_EOC                      BIT(ADC_SR_EOC_BIT)
#define ADC_SR_JEOC                     BIT(ADC_SR_JEOC_BIT)
#define ADC_SR_JSTRT                    BIT(ADC_SR_JSTRT_BIT)
#define ADC_SR_STRT                     BIT(ADC_SR_STRT_BIT)
#define ADC_SR_OVR	                    BIT(ADC_SR_OVR_BIT)

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
#define ADC_CR1_OVRIE                   BIT(ADC_CR1_OVRIE_BIT)

/* Control register 2 */

#define ADC_CR2_ADON_BIT                0
#define ADC_CR2_CONT_BIT                1
#define ADC_CR2_CAL_BIT                 2
#define ADC_CR2_RSTCAL_BIT              3
#define ADC_CR2_DMA_BIT                 8
#define ADC_CR2_ALIGN_BIT               11
#define ADC_CR2_JEXTTRIG_BIT            15
#define ADC_CR2_EXTTRIG_BIT             20
#define ADC_CR2_JSWSTART_BIT            21
#define ADC_CR2_SWSTART_BIT             22
#define ADC_CR2_TSEREFE_BIT             23

#define ADC_CR2_ADON                    (1U << ADC_CR2_ADON_BIT)
#define ADC_CR2_CONT                    (1U << ADC_CR2_CONT_BIT)
#define ADC_CR2_CAL                     (1U << ADC_CR2_CAL_BIT)
#define ADC_CR2_RSTCAL                  (1U << ADC_CR2_RSTCAL_BIT)
#define ADC_CR2_DMA                     (1U << ADC_CR2_DMA_BIT)
#define ADC_CR2_ALIGN                   (1U << ADC_CR2_ALIGN_BIT)
#define ADC_CR2_JEXTSEL                 0x7000
#define ADC_CR2_JEXTTRIG                (1U << ADC_CR2_JEXTTRIG_BIT)
#define ADC_CR2_EXTSEL                  0xE0000
#define ADC_CR2_EXTTRIG                 (1U << ADC_CR2_EXTTRIG_BIT)
#define ADC_CR2_JSWSTART                (1U << ADC_CR2_JSWSTART_BIT)
#define ADC_CR2_SWSTART                 (1U << ADC_CR2_SWSTART_BIT)
#define ADC_CR2_TSEREFE                 (1U << ADC_CR2_TSEREFE_BIT)

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

/*
 * Other types
 */

/**
 * @brief STM32F1 external event selectors for regular group
 *        conversion.
 *
 * Some external events are only available on ADCs 1 and 2, others
 * only on ADC3, while others are available on all three ADCs.
 * Additionally, some events are only available on high- and
 * XL-density STM32F1 MCUs, as they use peripherals only available on
 * those MCU densities.
 *
 * For ease of use, each event selector is given along with the ADCs
 * it's available on, along with any other availability restrictions.
 *
 * @see adc_set_extsel()
 */
typedef enum adc_extsel_event {
    /* TODO: Smarten this up a bit, as follows.
     *
     * The EXTSEL bits on F1 are a little brain-damaged in that the
     * TIM8 TRGO event has different bits depending on whether you're
     * using ADC1/2 or ADC3.  We route around this by declaring two
     * enumerators, ADC_EXT_EV_ADC12_TIM8_TRGO and
     * ADC_EXT_EV_ADC3_TIM8_TRGO.
     *
     * The right thing to do is to provide a single
     * ADC_EXT_EV_TIM8_TRGO enumerator and override adc_set_extsel on
     * STM32F1 to handle this situation correctly. We can do that
     * later, though, and change the per-ADC enumerator values to
     * ADC_EXT_EV_TIM8_TRGO to preserve compatibility. */

    /* ADC1 and ADC2 only: */
    ADC_EXT_EV_TIM1_CC1  = 0x00000, /**< ADC1, ADC2: Timer 1 CC1 event */
    ADC_EXT_EV_TIM1_CC2  = 0x20000, /**< ADC1, ADC2: Timer 1 CC2 event */
    ADC_EXT_EV_TIM2_CC2  = 0x60000, /**< ADC1, ADC2: Timer 2 CC2 event */
    ADC_EXT_EV_TIM3_TRGO = 0x80000, /**< ADC1, ADC2: Timer 3 TRGO event */
    ADC_EXT_EV_TIM4_CC4  = 0xA0000, /**< ADC1, ADC2: Timer 4 CC4 event */
    ADC_EXT_EV_EXTI11    = 0xC0000, /**< ADC1, ADC2: EXTI11 event */

    /* Common: */
    ADC_EXT_EV_TIM1_CC3  = 0x40000, /**< ADC1, ADC2, ADC3: Timer 1 CC3 event */
    ADC_EXT_EV_SWSTART   = 0xE0000, /**< ADC1, ADC2, ADC3: Software start */

    /* HD only: */
    ADC_EXT_EV_TIM3_CC1  = 0x00000, /**<
                                     * ADC3: Timer 3 CC1 event
                                     * Availability: high- and XL-density. */
    ADC_EXT_EV_TIM2_CC3  = 0x20000, /**<
                                     * ADC3: Timer 2 CC3 event
                                     * Availability: high- and XL-density. */
    ADC_EXT_EV_TIM8_CC1  = 0x60000, /**<
                                     * ADC3: Timer 8 CC1 event
                                     * Availability: high- and XL-density. */
    ADC_EXT_EV_ADC3_TIM8_TRGO = 0x80000, /**<
                                     * ADC3: Timer 8 TRGO event
                                     * Availability: high- and XL-density. */
    ADC_EXT_EV_TIM5_CC1  = 0xA0000, /**<
                                     * ADC3: Timer 5 CC1 event
                                     * Availability: high- and XL-density. */
    ADC_EXT_EV_ADC12_TIM8_TRGO = 0xC0000, /**<
                                     * ADC1, ADC2: Timer 8 TRGO event
                                     * Availability: high- and XL-density. */
    ADC_EXT_EV_TIM5_CC3  = 0xC0000, /**<
                                     * ADC3: Timer 5 CC3 event
                                     * Availability: high- and XL-density. */
} adc_extsel_event;

/* We'll keep these old adc_extsel_event enumerators around for a
 * while, for backwards compatibility: */
/** Deprecated. Use ADC_EXT_EV_TIM1_CC1 instead. */
#define ADC_ADC12_TIM1_CC1  ADC_EXT_EV_TIM1_CC1
/** Deprecated. Use ADC_EXT_EV_TIM1_CC2 instead. */
#define ADC_ADC12_TIM1_CC2  ADC_EXT_EV_TIM1_CC2
/** Deprecated. Use ADC_EXT_EV_TIM1_CC3 instead. */
#define ADC_ADC12_TIM1_CC3  ADC_EXT_EV_TIM1_CC3
/** Deprecated. Use ADC_EXT_EV_TIM2_CC2 instead. */
#define ADC_ADC12_TIM2_CC2  ADC_EXT_EV_TIM2_CC2
/** Deprecated. Use ADC_EXT_EV_TIM3_TRGO instead. */
#define ADC_ADC12_TIM3_TRGO ADC_EXT_EV_TIM3_TRGO
/** Deprecated. Use ADC_EXT_EV_TIM4_CC4 instead. */
#define ADC_ADC12_TIM4_CC4  ADC_EXT_EV_TIM4_CC4
/** Deprecated. Use ADC_EXT_EV_EXTI11 instead. */
#define ADC_ADC12_EXTI11    ADC_EXT_EV_EXTI11
/** Deprecated. Use ADC_EXT_EV_ADC12_TIM8_TRGO instead. */
#define ADC_ADC12_TIM8_TRGO ADC_EXT_EV_ADC12_TIM8_TRGO
/** Deprecated. Use ADC_EXT_EV_SWSTART instead. */
#define ADC_ADC12_SWSTART   ADC_EXT_EV_SWSTART
/** Deprecated. Use ADC_EXT_EV_TIM1_CC1 instead. */
#define ADC_ADC3_TIM3_CC1   ADC_EXT_EV_TIM1_CC1
/** Deprecated. Use ADC_EXT_EV_TIM1_CC2 instead. */
#define ADC_ADC3_TIM2_CC3   ADC_EXT_EV_TIM1_CC2
/** Deprecated. Use ADC_EXT_EV_TIM1_CC3 instead. */
#define ADC_ADC3_TIM1_CC3   ADC_EXT_EV_TIM1_CC3
/** Deprecated. Use ADC_EXT_EV_TIM2_CC2 instead. */
#define ADC_ADC3_TIM8_CC1   ADC_EXT_EV_TIM2_CC2
/** Deprecated. Use ADC_EXT_EV_TIM3_TRGO instead. */
#define ADC_ADC3_TIM8_TRGO  ADC_EXT_EV_TIM3_TRGO
/** Deprecated. Use ADC_EXT_EV_TIM4_CC4 instead. */
#define ADC_ADC3_TIM5_CC1   ADC_EXT_EV_TIM4_CC4
/** Deprecated. Use ADC_EXT_EV_EXTI11 instead. */
#define ADC_ADC3_TIM5_CC3   ADC_EXT_EV_EXTI11
/** Deprecated. Use ADC_EXT_EV_TIM8_TRGO instead. */
#define ADC_ADC3_SWSTART    ADC_EXT_EV_TIM8_TRGO
/** Deprecated. Use ADC_EXT_EV_SWSTART instead. */
#define ADC_SWSTART         ADC_EXT_EV_SWSTART

/**
 * @brief STM32F1 sample times, in ADC clock cycles.
 *
 * These control the amount of time spent sampling the input voltage.
 */
typedef enum adc_smp_rate {
    ADC_SMPR_1_5,               /**< 1.5 ADC cycles */
    ADC_SMPR_7_5,               /**< 7.5 ADC cycles */
    ADC_SMPR_13_5,              /**< 13.5 ADC cycles */
    ADC_SMPR_28_5,              /**< 28.5 ADC cycles */
    ADC_SMPR_41_5,              /**< 41.5 ADC cycles */
    ADC_SMPR_55_5,              /**< 55.5 ADC cycles */
    ADC_SMPR_71_5,              /**< 71.5 ADC cycles */
    ADC_SMPR_239_5,             /**< 239.5 ADC cycles */
} adc_smp_rate;

/**
 * @brief STM32F1 ADC prescalers, as divisors of PCLK2.
 */
typedef enum adc_prescaler {
    /** PCLK2 divided by 2 */
    ADC_PRE_PCLK2_DIV_2 = RCC_ADCPRE_PCLK_DIV_2,
    /** PCLK2 divided by 4 */
    ADC_PRE_PCLK2_DIV_4 = RCC_ADCPRE_PCLK_DIV_4,
    /** PCLK2 divided by 6 */
    ADC_PRE_PCLK2_DIV_6 = RCC_ADCPRE_PCLK_DIV_6,
    /** PCLK2 divided by 8 */
    ADC_PRE_PCLK2_DIV_8 = RCC_ADCPRE_PCLK_DIV_8,
} adc_prescaler;

/*
 * Routines
 */

/**
 * @brief Calibrate an ADC peripheral
 *
 * Availability: STM32F1, STM32F3.
 *
 * @param dev adc device
 */
void adc_calibrate(const adc_dev *dev);

/**
 * @brief Set external trigger conversion mode event for regular channels
 *
 * Availability: STM32F1, STM32F3.
 *
 * @param dev    ADC device
 * @param enable If 1, conversion on external events is enabled; if 0,
 *               disabled.
 */
static inline void adc_set_exttrig(const adc_dev *dev, uint8 enable) {
    *bb_perip(&dev->regs->CR2, ADC_CR2_EXTTRIG_BIT) = !!enable;
}

#endif
