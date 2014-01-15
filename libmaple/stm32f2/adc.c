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
 * @file libmaple/stm32f2/adc.c
 * @author F3-Port by Hanspeter Portner <dev@open-music-kontrollers.ch>
 * @brief STM32F2 ADC.
 */

#include <libmaple/adc.h>
#include <libmaple/gpio.h>

/*
 * Devices
 */

static adc_private_data adc1_priv;
static adc_dev adc1 = {
    .regs   = ADC1_BASE,
    .clk_id = RCC_ADC1,
		.priv = &adc1_priv
};
/** ADC1 device. */
const adc_dev *ADC1 = &adc1;

static adc_private_data adc2_priv;
static adc_dev adc2 = {
    .regs   = ADC2_BASE,
    .clk_id = RCC_ADC2,
		.priv = &adc2_priv
};
/** ADC2 device. */
const adc_dev *ADC2 = &adc2;

static adc_private_data adc3_priv;
static adc_dev adc3 = {
    .regs   = ADC3_BASE,
    .clk_id = RCC_ADC3,
		.priv = &adc3_priv
};
/** ADC3 device. */
const adc_dev *ADC3 = &adc3;

/*
 * STM32F2 routines
 */

void adc_set_extsel(const adc_dev *dev, adc_extsel_event event) {
    uint32 cr2 = dev->regs->CR2;
    cr2 &= ~ADC_CR2_EXTSEL;
    cr2 |= event;
    dev->regs->CR2 = cr2;
}

void adc_set_sample_rate(const adc_dev *dev, adc_smp_rate smp_rate) {
    uint32 adc_smpr1_val = 0, adc_smpr2_val = 0;
    int i;

    for (i = 0; i < 10; i++) {
        if (i < 8) {
            /* ADC_SMPR1 determines sample time for channels [10,17] */
            adc_smpr1_val |= smp_rate << (i * 3);
        }
        /* ADC_SMPR2 determines sample time for channels [0,9] */
        adc_smpr2_val |= smp_rate << (i * 3);
    }

    dev->regs->SMPR1 = adc_smpr1_val;
    dev->regs->SMPR2 = adc_smpr2_val;
}

void adc_enable_scan(const adc_dev *dev) {
    bb_peri_set_bit(&dev->regs->CR1, ADC_CR1_SCAN_BIT, 1);
}

void adc_enable_continuous(const adc_dev *dev) {
    bb_peri_set_bit(&dev->regs->CR2, ADC_CR2_CONT_BIT, 1);
}

void adc_disable_continuous(const adc_dev *dev) {
    bb_peri_set_bit(&dev->regs->CR2, ADC_CR2_CONT_BIT, 0);
}

void adc_disable_scan(const adc_dev *dev) {
    bb_peri_set_bit(&dev->regs->CR1, ADC_CR1_SCAN_BIT, 0);
}

#define BITS_PER_SQ 5
#define SQs_PER_SQR 6
void adc_set_conv_seq(const adc_dev *dev, const uint8 *channels, uint8 len) {
    const uint8 *end;
    __io uint32 *sqr = &dev->regs->SQR3; /* Next SQR to write to */
    uint32 val = 0;                      /* SQR we're building */
    unsigned sq = 0;                     /* SQ in sqr to set next */
    ASSERT(0 < len && len <= 16);

    end = channels + len;
    do {
        val |= *channels << (BITS_PER_SQ * sq++);
        if (sq == SQs_PER_SQR) {
            /* Finished building sqr in val. Set it and move on. This
             * relies on the ADC_SQRx being contiguous. */
            *sqr-- = val;
            val = 0;
            sq = 0;
        }
    } while (++channels < end);
    /* Write the last SQR, in case SQs_PER_SQR doesn't divide len. */
    *sqr = val;
    adc_set_reg_seqlen(dev, len);
}

uint16 adc_read(const adc_dev *dev, uint8 channel) {
    adc_reg_map *regs = dev->regs;

    adc_set_reg_seqlen(dev, 1);

    regs->SQR3 = channel;
    regs->CR2 |= ADC_CR2_SWSTART;
    while (!(regs->SR & ADC_SR_EOC))
        ;

    return (uint16)(regs->DR & ADC_DR_DATA);
}

void adc_attach_interrupt(const adc_dev *dev, uint32 interrupt_flags,
                          void (*handler)(adc_callback_data*), void *arg) {
    struct adc_private_data *priv = dev->priv;
    priv->handler = handler;
    priv->handler_flags = interrupt_flags;
    priv->cb_data.arg = arg;
    adc_enable_interrupts(dev, interrupt_flags);
}

void adc_detach_interrupt(const adc_dev *dev) {
    struct adc_private_data *priv;
    adc_disable_interrupts(dev, ADC_ALL_INTERRUPTS);
    priv = dev->priv;
    priv->handler = NULL;
    priv->handler_flags = 0;
}

#ifdef ADC_SR_OVR
#define ADC_OVERRUN_FLAG ADC_CR1_OVRIE
#else
#define ADC_OVERRUN_FLAG 0
#endif

static uint32 flags_to_cr1_bits(uint32 flags) {
    uint32 cr1_bits = 0;
    if (flags & ADC_CONV_INTERRUPT) {
        cr1_bits |= ADC_CR1_EOCIE;
    }
    if (flags & ADC_INJ_CONV_INTERRUPT) {
        cr1_bits |= ADC_CR1_JEOCIE;
    }
    if (flags & ADC_WATCHDOG_INTERRUPT) {
        cr1_bits |= ADC_CR1_AWDIE;
    }
    if (flags & ADC_OVERRUN_INTERRUPT) {
        cr1_bits |= ADC_OVERRUN_FLAG;
    }
    return cr1_bits;
}

void adc_enable_interrupts(const adc_dev *dev, uint32 interrupt_flags) {
    uint32 flags_to_set = flags_to_cr1_bits(interrupt_flags);
    uint32 cr1 = dev->regs->CR1;
    cr1 |= flags_to_set;
    dev->regs->CR1 = cr1;
    _adc_enable_dev_irq(dev);
}

void adc_disable_interrupts(const adc_dev *dev, uint32 interrupt_flags) {
    /* Don't use nvic_irq_disable()! IRQs are shared among ADCs. */
    uint32 flags_to_clear = flags_to_cr1_bits(interrupt_flags);
    uint32 cr1 = dev->regs->CR1;
    cr1 &= ~flags_to_clear;
    dev->regs->CR1 = cr1;
}

void adc_set_prescaler(adc_prescaler pre) {
    uint32 ccr = ADC_COMMON_BASE->CCR;
    ccr &= ~ADC_CCR_ADCPRE;
    ccr |= (uint32)pre;
    ADC_COMMON_BASE->CCR = ccr;
}

void adc_foreach(void (*fn)(const adc_dev*)) {
    fn(ADC1);
    fn(ADC2);
    fn(ADC3);
}

void adc_config_gpio(const adc_dev *ignored, gpio_dev *gdev, uint8 bit) {
    gpio_set_modef(gdev, bit, GPIO_MODE_ANALOG, GPIO_MODEF_PUPD_NONE);
}

void adc_enable_single_swstart(const adc_dev *dev) {
    adc_init(dev);
    adc_enable(dev);
}

void adc_set_reg_seqlen(const adc_dev *dev, uint8 length) {
    uint32 tmp = dev->regs->SQR1;
    tmp &= ~ADC_SQR1_L;
    tmp |= (length - 1) << 20;
    dev->regs->SQR1 = tmp;
}

void adc_enable(const adc_dev *dev) {
    *bb_perip(&dev->regs->CR2, ADC_CR2_ADON_BIT) = 1;
}

void adc_disable(const adc_dev *dev) {
    *bb_perip(&dev->regs->CR2, ADC_CR2_ADON_BIT) = 0;
}

/* IRQ handler for adc_attach_interrupt() */
static inline __always_inline void adc_irq(const adc_dev *dev) {
    struct adc_private_data *priv = dev->priv;
    uint32 irq_flags = dev->regs->SR & priv->handler_flags;

    if (!irq_flags) {
        /* The user isn't interested in this IRQ. */
        return;
    } else if (priv->handler) {
        priv->cb_data.irq_flags = irq_flags;
        priv->handler(&priv->cb_data);
    }
}

/*
 * IRQ handlers for adc_attach_interrupt()
 */
/* FIXME uncomment
void __irq_adc(void) {
    adc_irq(ADC1);
    adc_irq(ADC2);
		adc_irq(ADC3);
}
*/
