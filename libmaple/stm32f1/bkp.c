/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs, LLC.
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
 * @file libmaple/stm32f1/bkp.c
 * @author F3-port by Hanspeter Portner <dev@open-music-kontrollers.ch>
 * @brief STM32F1 Backup register support.
 */

#include <libmaple/bkp.h>
#include <libmaple/pwr.h>
#include <libmaple/rcc.h>

void bkp_init(void) {
    /* Don't call pwr_init(), or you'll reset the device.  We just
     * need the clock. */
    rcc_clk_enable(RCC_PWR);
    rcc_clk_enable(RCC_BKP);
    rcc_reset_dev(RCC_BKP);
}
/*
 * Data register memory layout is not contiguous. It's split up from
 * 1--NR_LOW_DRS, beginning at BKP_BASE->DR1, through to
 * (NR_LOW_DRS+1)--BKP_NR_DATA_REGS, beginning at BKP_BASE->DR11.
 */
#define NR_LOW_DRS 10

inline uint32* bkp_data_register(uint8 reg) {
    if (reg < 1 || reg > BKP_NR_DATA_REGS) {
        return 0;
    }

#if BKP_NR_DATA_REGS == NR_LOW_DRS
    return (uint32*)BKP_BASE + reg;
#else
    if (reg <= NR_LOW_DRS) {
        return (uint32*)BKP_BASE + reg;
    } else {
        return (uint32*)&(BKP_BASE->DR11) + (reg - NR_LOW_DRS - 1);
    }
#endif
}
