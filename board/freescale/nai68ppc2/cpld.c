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
 * This file provides support for the board-specific CPLD used on some Freescale
 * reference boards.
 *
 * The following macros need to be defined:
 *
 * CPLD_BASE - The virtual address of the base of the CPLD register map
 *
 */

#include <common.h>
#include <command.h>
#include <asm/io.h>
#ifdef CONFIG_HW_WATCHDOG
#include <watchdog.h>
#endif
#include "cpld.h"

#ifdef CONFIG_HW_WATCHDOG
static unsigned int cpld_dog = 0;
static unsigned int cpld_die = 0;
#endif

static u16 __cpld_read(unsigned int reg) {
	void *p = (void *)CONFIG_SYS_CPLD_BASE;

	return (in_be16(p + reg));
}
u16 cpld_read(unsigned int reg) __attribute__((weak, alias("__cpld_read")));

static void __cpld_write(unsigned int reg, u16 value) {
	void *p = (void *)CONFIG_SYS_CPLD_BASE;

	out_be16(p + reg, value);
}
void cpld_write(unsigned int reg, u16 value)
	__attribute__((weak, alias("__cpld_write")));

void cpld_set_bit_fail(void) {
	u16 val = 0x40;

	cpld_write(CPLD_TTL_RW, val);
	cpld_write(CPLD_WR_TTL_DATA, val);
}

#ifdef CONFIG_HW_WATCHDOG
void hw_watchdog_init(void) {
	puts ("Wdt:   Watchdog enabled\n");
	cpld_write(CPLD_ENABLE_WDT, 0xFFFF);
	cpld_dog = 1;
}

void hw_watchdog_reset(void) {
	if(cpld_dog && !cpld_die)
		cpld_write(CPLD_RELOAD_WDT, 0x5AFE);
}
#endif

int cpld_cmd(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]) {
	int rc = 0;

	if (argc <= 1)
		return cmd_usage(cmdtp);

	if (strcmp(argv[1], "ttldir") == 0) {
		ulong val = simple_strtoul(argv[2], NULL, 16);

		if ((val & 0xFFFFFF00) == 0) {
			cpld_write(CPLD_TTL_RW, (u16)val);
		}
		else {
			printf("Invalid value\n");
		}
	} else if (strcmp(argv[1], "ttlrd") == 0) {
		u16 val = cpld_read(CPLD_RD_TTL_DATA);

		printf("TTL read = 0x%02X\n", (u8)val);
	} else if (strcmp(argv[1], "ttlwr") == 0) {
		ulong val = simple_strtoul(argv[2], NULL, 16);

		if ((val & 0xFFFFFF00) == 0) {
			cpld_write(CPLD_WR_TTL_DATA, (u16)val);
		}
		else {
			printf("Invalid value\n");
		}
	} else if (strcmp(argv[1], "fwrev") == 0) {
		u16 val = cpld_read(CPLD_FW_REV);
		printf("FW revision = 0x%04X\n", val);
	} else if (strcmp(argv[1], "ttllpbk") == 0){
		u16 val = cpld_read(CPLD_TTL_LPBK);
		printf("TTL loopback = 0x%02X\n", (u8)val);
#ifdef CONFIG_HW_WATCHDOG
	} else if (strcmp(argv[1], "dog") == 0) {
		hw_watchdog_init();
	} else if(strcmp(argv[1], "die") == 0) {
		cpld_die = 1;
#endif
	} else if (strcmp(argv[1], "poweroff") == 0) {
		board_poweroff();
	} else if (strcmp(argv[1], "altbank") == 0) {
		u16 val = simple_strtoul(argv[2], NULL, 16);
		switch (val) {
			case CPLD_FLASH_BANK_0:
			case CPLD_FLASH_BANK_1:
				printf("Set flash bank to 0x%02X\n", val);
				cpld_write(CPLD_BANK_SEL, val);
				break;
			default:
				printf("Invalid flash bank 0x%02X\n", val);
				break;
		}
	} else if (strcmp(argv[1], "getbank") == 0) {
		u16 val = cpld_read(CPLD_BANK_SEL);
		printf("Flash bank 0x%02X\n", val);
	} else
		rc = cmd_usage(cmdtp);

	return rc;
}

U_BOOT_CMD(
	cpld, CONFIG_SYS_MAXARGS, 1, cpld_cmd,
	"Set the direction and read/write the TTL IO lines",
	"ttldir <dir> - set the direction, dir is in hex\n"
	"cpld ttlrd        - read the TTL IO lines\n"
	"cpld ttlwr <val>  - write the TTL IO lines, val is in hex\n"
	"cpld ttllpbk      - read the value written to the TTL IO lines\n"
	"cpld fwrev        - read the CPLD firmware revision\n"
	"cpld atlbank <val>  - change flash bank, val in is hex\n"
	"cpld getbank      - read flash bank select\n"
#ifdef CONFIG_HW_WATCHDOG
	"cpld dog          - enable HW watchdog, cannot be disabled!\n"
	"cpld die          - stop kicking HW watchdog, board will reset!\n"
#endif
	"cpld poweroff     - power off the board\n"
	);



