/*
 * Copyright 2014 Freescale Semiconductor, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * Version 2 or later as published by the Free Software Foundation.
 */

#include <common.h>
#include <i2c.h>
#include <hwconfig.h>
#include <asm/mmu.h>
#include <fsl_ddr_sdram.h>
#include <fsl_ddr_dimm_params.h>
#include <asm/fsl_law.h>
#include "ddr.h"

DECLARE_GLOBAL_DATA_PTR;

void fsl_ddr_board_options(memctl_options_t *popts,
				dimm_params_t *pdimm,
				unsigned int ctrl_num)
{
	const struct board_specific_parameters *pbsp, *pbsp_highest = NULL;
	ulong ddr_freq;

	if (ctrl_num > 1) {
		printf("Not supported controller number %d\n", ctrl_num);
		return;
	}
	if (!pdimm->n_ranks)
		return;

	pbsp = udimms[0];

	/* Get clk_adjust, wrlvl_start, wrlvl_ctl, according to the board ddr
	 * freqency and n_banks specified in board_specific_parameters table.
	 */
	ddr_freq = get_ddr_freq(0) / 1000000;
	while (pbsp->datarate_mhz_high) {
		if (pbsp->n_ranks == pdimm->n_ranks &&
		    (pdimm->rank_density >> 30) >= pbsp->rank_gb) {
			if (ddr_freq <= pbsp->datarate_mhz_high) {
				popts->clk_adjust = pbsp->clk_adjust;
				popts->wrlvl_start = pbsp->wrlvl_start;
				popts->wrlvl_ctl_2 = pbsp->wrlvl_ctl_2;
				popts->wrlvl_ctl_3 = pbsp->wrlvl_ctl_3;
				goto found;
			}
			pbsp_highest = pbsp;
		}
		pbsp++;
	}

	if (pbsp_highest) {
		printf("Error: board specific timing not found");
		printf("for data rate %lu MT/s\n", ddr_freq);
		printf("Trying to use the highest speed (%u) parameters\n",
		       pbsp_highest->datarate_mhz_high);
		popts->clk_adjust = pbsp_highest->clk_adjust;
		popts->wrlvl_start = pbsp_highest->wrlvl_start;
		popts->wrlvl_ctl_2 = pbsp->wrlvl_ctl_2;
		popts->wrlvl_ctl_3 = pbsp->wrlvl_ctl_3;
	} else {
		panic("DIMM is not supported by this board");
	}
found:
	debug("Found timing match: n_ranks %d, data rate %d, rank_gb %d\n"
		"\tclk_adjust %d, wrlvl_start %d, wrlvl_ctrl_2 0x%x, "
		"wrlvl_ctrl_3 0x%x\n",
		pbsp->n_ranks, pbsp->datarate_mhz_high, pbsp->rank_gb,
		pbsp->clk_adjust, pbsp->wrlvl_start, pbsp->wrlvl_ctl_2,
		pbsp->wrlvl_ctl_3);

	/*
	 * Factors to consider for half-strength driver enable:
	 *	- number of DIMMs installed
	 */
	popts->half_strength_driver_enable = 0;
	/*
	 * Write leveling override
	 */
	popts->wrlvl_override = 1;
	popts->wrlvl_sample = 0xf;

	/*
	 * Rtt and Rtt_WR override
	 */
	popts->rtt_override = 0;

	/* Enable ZQ calibration */
	popts->zq_en = 1;

	/* DHC_EN =1, ODT = 75 Ohm */
	popts->ddr_cdr1 = DDR_CDR1_DHC_EN | DDR_CDR1_ODT(DDR_CDR_ODT_75ohm);
	popts->ddr_cdr2 = DDR_CDR2_ODT(DDR_CDR_ODT_75ohm);
}

#if defined(CONFIG_SYS_DDR_RAW_TIMING)
/* 8GB discrete DDR3 IM8G08D3EBDG-15E on NAI68PPC2 */
dimm_params_t ddr_raw_timing = {
	.n_ranks = 2,
	.rank_density = 0x100000000,
	.capacity = 0x200000000,
	.primary_sdram_width = 64,
	.ec_sdram_width = 8,
	.registered_dimm = 0,
	.mirrored_dimm = 0,
	.n_row_addr = 16,
	.n_col_addr = 10,
	.n_banks_per_sdram_device = 8,
	.edc_config = 2,
	.burst_lengths_bitmask = 0x0c,
	.tckmin_x_ps = 1500,
	.tckmax_ps = 3000,
	.caslat_x = 0x000007E0,
	.taa_ps = 13500,
	.trcd_ps = 13500,
	.trp_ps = 13500,
	.tras_ps = 36000,
	.trc_ps = 49500,
	.tfaw_ps = 30000,
	.twr_ps = 15000,
	.trfc_ps = 260000,
	.trrd_ps = 6000,
	.twtr_ps = 7500,
	.trtp_ps = 7500,
	.refresh_rate_ps = 7800000,
};

int fsl_ddr_get_dimm_params(dimm_params_t *pdimm,
		unsigned int controller_number,
		unsigned int dimm_number)
{
	const char dimm_model[] = "Fixed DDR3 on board";

	if (((controller_number == 0) && (dimm_number == 0)) ||
	    ((controller_number == 0) && (dimm_number == 1))) {
		memcpy(pdimm, &ddr_raw_timing, sizeof(dimm_params_t));
		memset(pdimm->mpart, 0, sizeof(pdimm->mpart));
		memcpy(pdimm->mpart, dimm_model, sizeof(dimm_model) - 1);
	}

	return 0;
}
#else /* !CONFIG_SYS_DDR_RAW_TIMING */
phys_size_t fixed_sdram(void)
{
	int i;
	fsl_ddr_cfg_regs_t ddr_cfg_regs;
	char buf[32];
	phys_size_t ddr_size;
	ulong ddr_freq;

	ddr_freq = get_ddr_freq(0);

	printf("Configuring DDR for %s MT/s data rate\n",
	       strmhz(buf, ddr_freq));

	for (i = 0; fixed_ddr_param_0[i].data_rate_high > 0; i++) {
		if ((ddr_freq > fixed_ddr_param_0[i].data_rate_low) &&
		   (ddr_freq <= fixed_ddr_param_0[i].data_rate_high)) {
			memcpy(&ddr_cfg_regs,
				fixed_ddr_param_0[i].p_ddr_cfg,
				sizeof(ddr_cfg_regs));
			break;
		}
	}

	if (fixed_ddr_param_0[i].data_rate_high == 0)
		panic("Unsupported DDR data rate %s MT/s data rate\n",
		      strmhz(buf, ddr_freq));

	ddr_size = (phys_size_t) CONFIG_SYS_SDRAM_SIZE * 1024 * 1024;
	fsl_ddr_set_memctl_regs(&ddr_cfg_regs, 0, 0);
#if 1
	/*
	 * setup laws for DDR.
	 */
	if (set_ddr_laws(CONFIG_SYS_DDR_SDRAM_BASE,
			 ddr_size,
			 LAW_TRGT_IF_DDR_1) < 0) {
		printf("ERROR setting Local Access Windows for DDR\n");
		return 0;
	}
#endif
	return ddr_size;
}

#endif /* CONFIG_SYS_DDR_RAW_TIMING */

phys_size_t initdram(int board_type)
{
	phys_size_t dram_size;

	puts("Initializing....using ");
#if defined(CONFIG_SYS_DDR_RAW_TIMING)
	puts("raw timing\n");
	dram_size = fsl_ddr_sdram();
#else
	puts("fixed parameters\n");
	dram_size = fixed_sdram();
#endif

	dram_size = setup_ddr_tlbs(dram_size / 0x100000);
	dram_size *= 0x100000;

	return dram_size;
}
