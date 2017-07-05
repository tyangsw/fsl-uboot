/**
 * Copyright 2011 Freescale Semiconductor
 * Author: Mingkai Hu <Mingkai.hu@freescale.com>
 *
 * Copyright 2011 North Atlantic Industries Inc
 * Author: Obi Okafor <ookafor@naii.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This file provides support for the CPLD on the NAI 68PPC2 board.
 */

/*
 * CPLD register set. Feel free to add board-specific #ifdefs where necessary.
 */
#ifndef __CPLD_H_
#define __CPLD_H_

#define CPLD_BANK_SEL			0x00000000
#define CPLD_SPARE			0x00000002
#define CPLD_BOOT_WDT			0x00000004
#define CPLD_FW_REV			0x00000006
#define CPLD_TTL_RW			0x00000008
#define CPLD_TTL_LPBK			0x0000000A
#define CPLD_RD_TTL_DATA		0x0000000C
#define CPLD_WR_TTL_DATA		0x0000000E
#define CPLD_ENABLE_WDT			0x00000010
#define CPLD_RELOAD_WDT			0x00000012
#define CPLD_WR_TTL_INT_EN		0x00000014
#define CPLD_WR_TTL_INT_DIR		0x00000016
#define CPLD_INT_STAT			0x00000018
#define CPLD_WR_TEMP_ALM_OVRD		0x0000001A
#define CPLD_PWR_DWN_CMD		0x0000001C
#define CPLD_TEMP_ALM_INT_STAT		0x0000001E
#define CPLD_WR_TEMP_ALM_INT_EN		0x00000020

#define CPLD_BANK_USER_BOOT		0x00
#define CPLD_BANK_FACT_BOOT		0x01
#define CPLD_BANK_FACT_DATA		0x02
#define CPLD_BANK_USER_DATA		0x03

u16 cpld_read(unsigned int reg);
void cpld_write(unsigned int reg, u16 value);
void hw_watchdog_init(void);
void cpld_set_bit_fail(void);

#endif
