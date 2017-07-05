/*
 * Copyright 2014 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __DDR_H__
#define __DDR_H__

#if !defined(CONFIG_SYS_DDR_RAW_TIMING)
typedef struct fixed_ddr_param_t
{
        uint32_t data_rate_low;
        uint32_t data_rate_high;
        fsl_ddr_cfg_regs_t* p_ddr_cfg;
} fixed_ddr_param_t;

#define DATARATE_300MHZ        300000000
#define DATARATE_400MHZ        400000000
#define DATARATE_500MHZ        500000000
#define DATARATE_600MHZ        600000000
#define DATARATE_700MHZ        700000000
#define DATARATE_800MHZ        800000000
#define DATARATE_900MHZ        900000000
#define DATARATE_1000MHZ      1000000000
#define DATARATE_1200MHZ      1200000000
#define DATARATE_1300MHZ      1300000000
#define DATARATE_1400MHZ      1400000000
#define DATARATE_1500MHZ      1500000000
#define DATARATE_1600MHZ      1600000000
#define DATARATE_1700MHZ      1700000000
#define DATARATE_1800MHZ      1800000000
#define DATARATE_1900MHZ      1900000000
#define DATARATE_2000MHZ      2000000000
#define DATARATE_2100MHZ      2100000000
#define DATARATE_2200MHZ      2200000000
#define DATARATE_2300MHZ      2300000000
#define DATARATE_2400MHZ      2400000000

/* DDR Controller 1 register values */
#define DDRmc1_CS0_BNDS_VAL         0x000000FF
#define DDRmc1_CS1_BNDS_VAL         0x010001FF
#define DDRmc1_CS0_CONFIG_VAL       0x80044402
#define DDRmc1_CS1_CONFIG_VAL       0x80044402
#define DDRmc1_CS0_CONFIG_2_VAL     0x00000000
#define DDRmc1_CS1_CONFIG_2_VAL     0x00000000
#define DDRmc1_CS2_BNDS_VAL         0x0300033F
#define DDRmc1_CS3_BNDS_VAL         0x0340037F
#define DDRmc1_CS2_CONFIG_VAL       0x00000202
#define DDRmc1_CS3_CONFIG_VAL       0x00040202
#define DDRmc1_CS2_CONFIG_2_VAL     0x00000000
#define DDRmc1_CS3_CONFIG_2_VAL     0x00000000
#define DDRmc1_TIMING_CFG_0_VAL     0xFF530004
#define DDRmc1_TIMING_CFG_1_VAL     0x98906345
#define DDRmc1_TIMING_CFG_2_VAL     0x0040A114
#define DDRmc1_TIMING_CFG_3_VAL     0x010A1100
#define DDRmc1_TIMING_CFG_4_VAL     0x00000001
#define DDRmc1_TIMING_CFG_5_VAL     0x04402400
#define DDRmc1_SDRAM_CFG_VAL        0xE7040000
#define DDRmc1_SDRAM_CFG_2_VAL      0x00401010
#define DDRmc1_SDRAM_INTERVAL_VAL   0x0C300100
#define DDRmc1_SDRAM_CLK_CNTL_VAL   0x02400000
#define DDRmc1_ZQ_CNTL_VAL          0x89080600
#define DDRmc1_WRLVL_CNTL_VAL       0x8675F604
#define DDRmc1_WRLVL_CNTL_2_VAL     0x05060607
#define DDRmc1_WRLVL_CNTL_3_VAL     0x080A0A0B
#define DDRmc1_SDRAM_MODE_VAL       0x00441C70
#define DDRmc1_SDRAM_MODE_2_VAL     0x00980000
#define DDRmc1_SDRAM_MODE_3_VAL     0x00000000
#define DDRmc1_SDRAM_MODE_4_VAL     0x00000000
#define DDRmc1_SDRAM_MODE_5_VAL     0x00000000
#define DDRmc1_SDRAM_MODE_6_VAL     0x00000000
#define DDRmc1_SDRAM_MODE_7_VAL     0x00000000
#define DDRmc1_SDRAM_MODE_8_VAL     0x00000000
#define DDRmc1_DDRCDR_1_VAL         0x80040000
#define DDRmc1_DDRCDR_2_VAL         0x00000001
#define DDRmc1_INIT_ADDR_VAL        0x00000000
#define DDRmc1_INIT_EXT_ADDR_VAL    0x00000000
#define DDRmc1_SDRAM_RCW_1_VAL      0x00000000
#define DDRmc1_SDRAM_RCW_2_VAL      0x00000000
#define DDRmc1_ERR_DISABLE_VAL      0x00000000
#define DDRmc1_ERR_INT_EN_VAL       0x0000001D
#define DDRmc1_ERR_SBE_VAL          0x00010000
#define DDRmc1_DATA_INIT_VAL        0xDEADBEEF
#define DDRmc1_SDRAM_MD_CNTL_VAL    0x00000000

/* DDR Controller 1 configuration global structures */
fsl_ddr_cfg_regs_t ddr_cfg_regs_0 = {
  .cs[0].bnds = DDRmc1_CS0_BNDS_VAL,
  .cs[1].bnds = DDRmc1_CS1_BNDS_VAL,
  .cs[0].config = DDRmc1_CS0_CONFIG_VAL,
  .cs[1].config = DDRmc1_CS1_CONFIG_VAL,
  .cs[0].config_2 = DDRmc1_CS0_CONFIG_2_VAL,
  .cs[1].config_2 =  DDRmc1_CS1_CONFIG_2_VAL,
  .cs[2].bnds = DDRmc1_CS2_BNDS_VAL,
  .cs[3].bnds = DDRmc1_CS3_BNDS_VAL,
  .cs[2].config = DDRmc1_CS2_CONFIG_VAL,
  .cs[3].config = DDRmc1_CS3_CONFIG_VAL,
  .cs[2].config_2 =  DDRmc1_CS2_CONFIG_2_VAL,
  .cs[3].config_2 =  DDRmc1_CS3_CONFIG_2_VAL,
  
  .timing_cfg_3 = DDRmc1_TIMING_CFG_3_VAL,
  .timing_cfg_0 = DDRmc1_TIMING_CFG_0_VAL,
  .timing_cfg_1 = DDRmc1_TIMING_CFG_1_VAL,
  .timing_cfg_2 = DDRmc1_TIMING_CFG_2_VAL,
  .ddr_sdram_cfg = DDRmc1_SDRAM_CFG_VAL,
  .ddr_sdram_cfg_2 = DDRmc1_SDRAM_CFG_2_VAL,
  .ddr_sdram_mode = DDRmc1_SDRAM_MODE_VAL,
  .ddr_sdram_mode_2 = DDRmc1_SDRAM_MODE_2_VAL,
  .ddr_sdram_mode_3 = DDRmc1_SDRAM_MODE_3_VAL,
  .ddr_sdram_mode_4 = DDRmc1_SDRAM_MODE_4_VAL,
  .ddr_sdram_mode_5 = DDRmc1_SDRAM_MODE_5_VAL,
  .ddr_sdram_mode_6 = DDRmc1_SDRAM_MODE_6_VAL,
  .ddr_sdram_mode_7 = DDRmc1_SDRAM_MODE_7_VAL,
  .ddr_sdram_mode_8 = DDRmc1_SDRAM_MODE_8_VAL,
  .ddr_sdram_md_cntl = DDRmc1_SDRAM_MD_CNTL_VAL,
  .ddr_sdram_interval = DDRmc1_SDRAM_INTERVAL_VAL,
  .ddr_data_init = DDRmc1_DATA_INIT_VAL,
  .ddr_sdram_clk_cntl = DDRmc1_SDRAM_CLK_CNTL_VAL,
  .ddr_init_addr = DDRmc1_INIT_ADDR_VAL,
  .ddr_init_ext_addr = DDRmc1_INIT_EXT_ADDR_VAL,
  .timing_cfg_4 = DDRmc1_TIMING_CFG_4_VAL,
  .timing_cfg_5 = DDRmc1_TIMING_CFG_5_VAL,
  .ddr_zq_cntl = DDRmc1_ZQ_CNTL_VAL,
  .ddr_wrlvl_cntl = DDRmc1_WRLVL_CNTL_VAL,
  .ddr_wrlvl_cntl_2 = DDRmc1_WRLVL_CNTL_2_VAL,
  .ddr_wrlvl_cntl_3 = DDRmc1_WRLVL_CNTL_3_VAL,
  .ddr_sdram_rcw_1 = DDRmc1_SDRAM_RCW_1_VAL,
  .ddr_sdram_rcw_2 = DDRmc1_SDRAM_RCW_2_VAL,
  .ddr_cdr1 = DDRmc1_DDRCDR_1_VAL,
  .ddr_cdr2 = DDRmc1_DDRCDR_2_VAL,
  .err_disable = DDRmc1_ERR_DISABLE_VAL,
  .err_int_en = DDRmc1_ERR_INT_EN_VAL
  
};

fixed_ddr_param_t fixed_ddr_param_0[] = {
  { DATARATE_1300MHZ, DATARATE_1400MHZ, &ddr_cfg_regs_0 },
  {0, 0, NULL}
};
#endif /* CONFIG_SYS_DDR_RAW_TIMING */

struct board_specific_parameters {
	u32 n_ranks;
	u32 datarate_mhz_high;
	u32 rank_gb;
	u32 clk_adjust;
	u32 wrlvl_start;
	u32 wrlvl_ctl_2;
	u32 wrlvl_ctl_3;
};

/*
 * These tables contain all valid speeds we want to override with board
 * specific parameters. datarate_mhz_high values need to be in ascending order
 * for each n_ranks group.
 */

static const struct board_specific_parameters udimm0[] = {
	/*
	 * memory controller 0
	 *   num|  hi| rank|  clk| wrlvl |   wrlvl   |  wrlvl |
	 * ranks| mhz| GB  |adjst| start |   ctl2    |  ctl3  |
	 */
	{2,  1200, 2, 5,     7, 0x0808090a, 0x0b0c0c0a},
	{2,  1500, 2, 5,     6, 0x07070809, 0x0a0b0b09},
	{2,  1600, 2, 5,     8, 0x0808070b, 0x0c0d0e0a},
	{2,  1700, 2, 4,     7, 0x080a0a0c, 0x0c0d0e0a},
	{2,  1900, 0, 5,     7, 0x0808080c, 0x0b0c0c09},
	{1,  1200, 2, 5,     7, 0x0808090a, 0x0b0c0c0a},
	{1,  1500, 2, 5,     6, 0x07070809, 0x0a0b0b09},
	{1,  1600, 2, 5,     8, 0x0808070b, 0x0c0d0e0a},
	{1,  1700, 2, 4,     7, 0x080a0a0c, 0x0c0d0e0a},
	{1,  1900, 0, 5,     7, 0x0808080c, 0x0b0c0c09},
	{}
};

static const struct board_specific_parameters *udimms[] = {
	udimm0,
};
#endif
