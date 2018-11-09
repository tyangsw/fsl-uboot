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

#define CPLD_SPARE					0x00000000
#define CPLD_SATA_MUX_SEL			0x00000002
#define CPLD_BANK_SEL				0x00000004
#define CPLD_FW_REV					0x00000006
#define CPLD_TTL_RW					0x00000008
#define CPLD_TTL_LPBK				0x0000000A
#define CPLD_TTL_DATA				0x0000000C
#define CPLD_PROC_STATUS			0x0000000E /*write 1 to enable proc reset function, reset default value is 0*/
#define CPLD_FPGA_RDY				0x00000010 /*read only when reg read 0x0DB1 then fpga is ready */
#define CPLD_PCIE_SW_RESET			0x00000012 /*write 1 to reset the PCIe switch*/
#define CPLD_WR_TTL_INT_EN			0x00000014
#define CPLD_WR_TTL_INT_DIR			0x00000016
#define CPLD_INT_STAT				0x00000018
#define CPLD_WR_TEMP_ALM_OVRD		0x0000001A /*write 0 to enable temp shutdown. reset default value is 1*/
#define CPLD_PWR_DWN_CMD			0x0000001C
#define CPLD_TEMP_ALM_INT_STAT		0x0000001E
#define CPLD_WR_TEMP_ALM_INT_EN		0x00000020 

#define CPLD_FLASH_BANK_0		0x00
#define CPLD_FLASH_BANK_1		0x01

u16 cpld_read(unsigned int reg);
void cpld_write(unsigned int reg, u16 value);
void hw_watchdog_init(void);
void cpld_set_bit_fail(void);

#endif
