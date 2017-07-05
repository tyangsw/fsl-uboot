/*
 * Copyright 2009-2013 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <i2c.h>
#include <netdev.h>
#include <linux/compiler.h>
#include <asm/mmu.h>
#include <asm/processor.h>
#include <asm/immap_85xx.h>
#include <asm/fsl_law.h>
#include <asm/fsl_serdes.h>
#include <asm/fsl_liodn.h>
#include <fm_eth.h>
#include "nai68ppc2.h"
#include "cpld.h"

DECLARE_GLOBAL_DATA_PTR;

int checkboard(void)
{
	//struct cpu_type *cpu = gd->arch.cpu;
	static const char *freq[3] = {"100.00MHZ", "125.00MHz", "156.25MHZ"};

	printf("Board: NAI68PPC2, ");
	printf("CPLD ver: 0x%02x\n", cpld_read(CPLD_FW_REV));

	puts("SERDES Reference Clocks:\n");
	printf("SD1_CLK1=%s, SD1_CLK2=%s\n", freq[0], freq[0]);
	printf("SD2_CLK1=%s, SD2_CLK2=%s\n", freq[0], freq[0]);

	return 0;
}

int board_early_init_r(void)
{
	const unsigned int flashbase = CONFIG_SYS_FLASH_BASE;
	int flash_esel = find_tlb_idx((void *)flashbase, 1);
	/*
	 * Remap Boot flash + PROMJET region to caching-inhibited
	 * so that flash can be erased properly.
	 */

	/* Flush d-cache and invalidate i-cache of any FLASH data */
	flush_dcache();
	invalidate_icache();
	if (flash_esel == -1) {
		/* very unlikely unless something is messed up */
		puts("Error: Could not find TLB for FLASH BASE\n");
		flash_esel = 2;	/* give our best effort to continue */
	} else {
		/* invalidate existing TLB entry for flash + promjet */
		disable_tlb(flash_esel);
	}

	set_tlb(1, flashbase, CONFIG_SYS_FLASH_BASE_PHYS,
		MAS3_SX|MAS3_SW|MAS3_SR, MAS2_I|MAS2_G,
		0, flash_esel, BOOKE_PAGESZ_256M, 1);

	return 0;
}

unsigned long get_board_sys_clk(void)
{
	return CONFIG_SYS_CLK_FREQ;
}

unsigned long get_board_ddr_clk(void)
{
	return CONFIG_DDR_CLK_FREQ;
}

void board_poweroff (void)
{
	cpld_write(CPLD_PWR_DWN_CMD, 0xDEAD);
	cpld_write(CPLD_PWR_DWN_CMD, 0xC0DE);
}

int misc_init_r(void)
{
	/* Kick the boot watchdog */
	cpld_write(CPLD_BOOT_WDT, 0xFF);

	/* TODO reset PHYs (and anyhing else.....) */
#if 0
	u8 reg;

	/* Reset CS4315 PHY */
	reg = CPLD_READ(reset_ctl);
	reg |= CPLD_RSTCON_EDC_RST;
	CPLD_WRITE(reset_ctl, reg);
#endif
	return 0;
}

int ft_board_setup(void *blob, bd_t *bd)
{
	phys_addr_t base;
	phys_size_t size;

	ft_cpu_setup(blob, bd);

	base = getenv_bootm_low();
	size = getenv_bootm_size();

	fdt_fixup_memory(blob, (u64)base, (u64)size);

#ifdef CONFIG_PCI
	pci_of_setup(blob, bd);
#endif

	fdt_fixup_liodn(blob);
	fdt_fixup_dr_usb(blob, bd);

#ifdef CONFIG_SYS_DPAA_FMAN
	fdt_fixup_fman_ethernet(blob);
	fdt_fixup_board_enet(blob);
#endif

	return 0;
}