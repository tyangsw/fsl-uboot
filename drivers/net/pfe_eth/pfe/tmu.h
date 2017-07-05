/* Copyright (C) 2016 Freescale Semiconductor Inc.
 *
 * SPDX-License-Identifier:GPL-2.0+
 */
#ifndef _TMU_H_
#define _TMU_H_

#define TMU_DMEM_BASE_ADDR	0x00000000
#define TMU_PMEM_BASE_ADDR	0x00010000


#define CBUS_BASE_ADDR		0xc0000000
#define TMU_APB_BASE_ADDR	0xc1000000

#include "cbus.h"

#define GPT_BASE_ADDR		(TMU_APB_BASE_ADDR + 0x00000)
#define UART_BASE_ADDR		(TMU_APB_BASE_ADDR + 0x10000)


#define SHAPER0_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x020000)
#define SHAPER1_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x030000)
#define SHAPER2_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x040000)
#define SHAPER3_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x050000)
#define SHAPER4_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x060000)
#define SHAPER5_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x070000)
#define SHAPER6_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x080000)
#define SHAPER7_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x090000)
#define SHAPER8_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x0a0000)
#define SHAPER9_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x0b0000)

#define SCHED0_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x1c0000)
#define SCHED1_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x1d0000)
#define SCHED2_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x1e0000)
#define SCHED3_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x1f0000)
#define SCHED4_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x200000)
#define SCHED5_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x210000)
#define SCHED6_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x220000)
#define SCHED7_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x230000)


#define PHY_QUEUE_BASE_ADDR	(TMU_APB_BASE_ADDR + 0x260000)
/**< [9:0] bitmask of shapers that have positive credit */
#define SHAPER_STATUS		(TMU_APB_BASE_ADDR + 0x270000)


#include "gpt.h"
#include "uart.h"
#include "tmu/shaper.h"
#include "tmu/sched.h"
#include "tmu/phy_queue.h"

#endif /* _TMU_H_ */
