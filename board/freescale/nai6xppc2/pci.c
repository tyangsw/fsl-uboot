/*
 * Copyright 2007-2014 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <pci.h>
#include <asm/fsl_pci.h>
#include <libfdt.h>
#include <fdt_support.h>
#include <asm/fsl_serdes.h>
#include "cpld.h"
/*Function prototype declartion*/
static void _wait_fpga_ready(void);
static void _init_pcie_switch(void);

static void _wait_fpga_ready()
{
	ulong time = get_timer(0);
	u16 val = 0;
	
	do{
		val = cpld_read(CPLD_FPGA_RDY);
		//timeout
		if(get_timer(time) > (10 * 1000))
			break;
	}while(val != 0x0db1);

	if(val == 0x0db1)
	{
		printf("FPGA is ready: 0x%02X\n", val);
	}
	else
	{
		printf("FPGA not ready: 0x%02X\n", val);
	}
	return;
}

static void _init_pcie_switch()
{
	/*take IDT PCIe switch out of reset*/
	printf("Release PCIe Switch from reset\n");
	cpld_write(CPLD_PCIE_SW_RESET, 1);
	/*wait 500ms for PCIe to link up with downstream card*/
	udelay(500000);
	return;
}

void pci_init_board(void)
{
	_wait_fpga_ready();
	_init_pcie_switch();
	fsl_pcie_init_board(0);
}

void pci_of_setup(void *blob, bd_t *bd)
{
	FT_FSL_PCI_SETUP;
}
