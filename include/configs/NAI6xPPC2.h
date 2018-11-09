/*
 * Copyright 2014 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

/*
 * NAI T2080 based PPC2 board configuration file
 */

#ifndef __NAI6XPPC2_H
#define __NAI6XPPC2_H

#define CONFIG_DISPLAY_BOARDINFO
#define CONFIG_NAI6XPPC2
#define CONFIG_6XPPC2_MAJOR 0
#define CONFIG_6XPPC2_MINOR 1
#define CONFIG_6XPPC2_BUILD 4
#define CONFIG_USB_EHCI
#define CONFIG_FSL_SATA_V2

/* High Level Configuration Options */
#define CONFIG_BOOKE
#define CONFIG_E500		/* BOOKE e500 family */
#define CONFIG_E500MC		/* BOOKE e500mc family */
#define CONFIG_SYS_BOOK3E_HV	/* Category E.HV supported */
#define CONFIG_MP		/* support multiple processors */
#define CONFIG_ENABLE_36BIT_PHYS

#ifdef CONFIG_PHYS_64BIT
#define CONFIG_ADDR_MAP 1
#define CONFIG_SYS_NUM_ADDR_MAP 64 /* number of TLB1 entries */
#endif

#define CONFIG_SYS_FSL_CPC	/* Corenet Platform Cache */
#define CONFIG_SYS_NUM_CPC	CONFIG_NUM_DDR_CONTROLLERS
#define CONFIG_FSL_IFC		/* Enable IFC Support */
#define CONFIG_FSL_CAAM		/* Enable SEC/CAAM */
#define CONFIG_FSL_LAW		/* Use common FSL init code */
#define CONFIG_ENV_OVERWRITE

#undef CONFIG_SRIO_PCIE_BOOT_MASTER
#undef CONFIG_SRIO_PCIE_BOOT_SLAVE

#ifndef CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_TEXT_BASE	0xeff40000
#endif

#ifndef CONFIG_RESET_VECTOR_ADDRESS
#define CONFIG_RESET_VECTOR_ADDRESS	0xeffffffc
#endif

/*
 * These can be toggled for performance analysis, otherwise use default.
 */
#define CONFIG_SYS_CACHE_STASHING
#define CONFIG_BTB		/* toggle branch predition */
#define CONFIG_DDR_ECC
#ifdef CONFIG_DDR_ECC
#define CONFIG_ECC_INIT_VIA_DDRCONTROLLER
#define CONFIG_MEM_INIT_VALUE		0xdeadbeef
#endif

#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START	0x00200000 /* memtest works on */
#define CONFIG_SYS_MEMTEST_END		0x00400000
#define CONFIG_SYS_ALT_MEMTEST

#ifndef CONFIG_SYS_NO_FLASH
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE
#define CONFIG_SYS_FLASH_PROTECTION
#endif

#define CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_ADDR		(CONFIG_SYS_MONITOR_BASE - CONFIG_ENV_SECT_SIZE)
#define CONFIG_ENV_SIZE		0x2000 /*8KB*/
#define CONFIG_ENV_SECT_SIZE	0x20000 /* 128K (one sector) */

#ifndef __ASSEMBLY__
unsigned long get_board_sys_clk(void);
unsigned long get_board_ddr_clk(void);
#endif

#define CONFIG_SYS_CLK_FREQ	100000000
#define CONFIG_DDR_CLK_FREQ	133333333


/*
 * Config the L3 Cache as L3 SRAM
 */
#define CONFIG_SYS_INIT_L3_ADDR		0xFFFC0000
#define CONFIG_SYS_L3_SIZE		(512 << 10)
#define CONFIG_SPL_GD_ADDR		(CONFIG_SYS_INIT_L3_ADDR + 32 * 1024)
#define CONFIG_SPL_RELOC_MALLOC_ADDR	(CONFIG_SPL_GD_ADDR + 12 * 1024)
#define CONFIG_SPL_RELOC_MALLOC_SIZE	(50 << 10)
#define CONFIG_SPL_RELOC_STACK		(CONFIG_SPL_GD_ADDR + 64 * 1024)
#define CONFIG_SPL_RELOC_STACK_SIZE	(22 << 10)

/* EEPROM */
#undef CONFIG_ID_EEPROM
#undef CONFIG_SYS_I2C_EEPROM_NXID
#define CONFIG_SYS_EEPROM_BUS_NUM	0
#define CONFIG_SYS_I2C_EEPROM_ADDR	0x50
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN	2

/*DCSR Internal Debug Control and Status Register*/
#define CONFIG_SYS_DCSRBAR	0xf0000000
#define CONFIG_SYS_DCSRBAR_PHYS	0xf00000000ull

/*
 * DDR Setup
 */
#define CONFIG_VERY_BIG_RAM
#define CONFIG_SYS_DDR_SDRAM_BASE	0x00000000
#define CONFIG_SYS_SDRAM_BASE		CONFIG_SYS_DDR_SDRAM_BASE
#define CONFIG_DIMM_SLOTS_PER_CTLR	1
#define CONFIG_CHIP_SELECTS_PER_CTRL	(4 * CONFIG_DIMM_SLOTS_PER_CTLR)
#define CONFIG_SYS_FSL_DDR3
#undef CONFIG_FSL_DDR_INTERACTIVE
#undef CONFIG_SYS_DDR_RAW_TIMING
#define CONFIG_SYS_SDRAM_SIZE	8192	/* for fixed parameter use */
#define CTRL_INTLV_PREFERED	cacheline

/*
 * IFC NOR Definitions
 */
#define CONFIG_SYS_FLASH_BASE		0xe8000000
#define CONFIG_SYS_FLASH_BASE_PHYS	(0xf00000000ull | CONFIG_SYS_FLASH_BASE)
#define CONFIG_SYS_NOR0_CSPR_EXT	(0xf)
#define CONFIG_SYS_NOR0_CSPR	(CSPR_PHYS_ADDR(CONFIG_SYS_FLASH_BASE_PHYS) | \
				CSPR_PORT_SIZE_16 | \
				CSPR_MSEL_NOR | \
				CSPR_V)
#define CONFIG_SYS_NOR_AMASK	IFC_AMASK(128*1024*1024)

/* NOR Flash Timing Params */
#define CONFIG_SYS_NOR_CSOR	CSOR_NAND_TRHZ_80

#define CONFIG_SYS_NOR_FTIM0	(FTIM0_NOR_TACSE(0x4) | \
				FTIM0_NOR_TEADC(0x5) | \
				FTIM0_NOR_TEAHC(0x5))
#define CONFIG_SYS_NOR_FTIM1	(FTIM1_NOR_TACO(0x35) | \
				FTIM1_NOR_TRAD_NOR(0x1A) |\
				FTIM1_NOR_TSEQRAD_NOR(0x13))
#define CONFIG_SYS_NOR_FTIM2	(FTIM2_NOR_TCS(0x4) | \
				FTIM2_NOR_TCH(0x4) | \
				FTIM2_NOR_TWPH(0x0E) | \
				FTIM2_NOR_TWP(0x1c))
#define CONFIG_SYS_NOR_FTIM3	0x0

#define CONFIG_SYS_FLASH_QUIET_TEST
#define CONFIG_FLASH_SHOW_PROGRESS	45 /* count down from 45/5: 9..1 */

#define CONFIG_SYS_MAX_FLASH_BANKS		1				/* number of banks */
#define CONFIG_SYS_FLASH_CFI_WIDTH		FLASH_CFI_16BIT
#define CONFIG_SYS_FLASH_BANKS_SIZES	{128*1024*1024}
#define CONFIG_SYS_MAX_FLASH_SECT		1024	/* sectors per device */
#define CONFIG_SYS_FLASH_ERASE_TOUT		60000	/* Flash Erase Timeout (ms) */
#define CONFIG_SYS_FLASH_WRITE_TOUT		500	/* Flash Write Timeout (ms) */
#define CONFIG_SYS_FLASH_EMPTY_INFO
#define CONFIG_SYS_FLASH_BANKS_LIST	{CONFIG_SYS_FLASH_BASE_PHYS}


/*NOR Flash Image layout*/
#define RCW_IMAGE_OFFSET				CONFIG_SYS_FLASH_BASE
#define RCW_IMAGE_SIZE					0x20000		/*128KB*/
#define FMAN_UCODE_IMAGE_OFFSET			0xE8020000
#define FMAN_UCODE_IMAGE_SIZE			0x20000		/*128KB*/
#define DTB_IMAGE_OFFSET				0xE8040000
#define DTB_IMAGE_SIZE					0x100000	/*1MB*/
#define KERNEL_IMAGE_OFFSET				0xE8140000
#define KERNEL_IMAGE_SIZE				0x800000	/*8MB*/
#define ROOTFS_IMAGE_OFFSET				0xE8940000
#define ROOTFS_IMAGE_SIZE				0x36C0000	/*54MB + 768KB*/
#define FREE_SPACE_OFFSET				0xEC000000
#define FREE_SPACE_SIZE					0x3F020000	/*63MB + 128KB*/
#define UBOOT_IMAGE_ENV_OFFSET			0xEFF20000
#define UBOOT_IMAGE_ENV_SIZE			0x20000
#define UBOOT_IMAGE_OFFSET				CONFIG_SYS_TEXT_BASE
#define UBOOT_IMAGE_SIZE				0xC0000		/*768KB*/


/* IFC CPLD/Zyqn FPGA Definitions */
#define CONFIG_SYS_CPLD_BASE		0xffdf0000
#define CONFIG_SYS_CPLD_BASE_PHYS	(0xf00000000ull | CONFIG_SYS_CPLD_BASE)
#define CONFIG_SYS_CSPR3_EXT		(0xf)
#define CONFIG_SYS_CSPR3			(CSPR_PHYS_ADDR(CONFIG_SYS_CPLD_BASE) \
				| CSPR_PORT_SIZE_16 \
				| CSPR_MSEL_GPCM \
				| CSPR_V)
#define CONFIG_SYS_AMASK3	IFC_AMASK(64*1024)
#define CONFIG_SYS_CSOR3	0x0

/* IFC CPLD Timing parameters for IFC CS3 */
#define CONFIG_SYS_CS3_FTIM0		(FTIM0_GPCM_TACSE(0x0e) | \
					FTIM0_GPCM_TEADC(0x0e) | \
					FTIM0_GPCM_TEAHC(0x0e))
#define CONFIG_SYS_CS3_FTIM1		(FTIM1_GPCM_TACO(0x0e) | \
					FTIM1_GPCM_TRAD(0x1f))
#define CONFIG_SYS_CS3_FTIM2		(FTIM2_GPCM_TCS(0x0e) | \
					FTIM2_GPCM_TCH(0x8) | \
					FTIM2_GPCM_TWP(0x1f))
#define CONFIG_SYS_CS3_FTIM3		0x0

#define CONFIG_SYS_CSPR0_EXT		CONFIG_SYS_NOR0_CSPR_EXT
#define CONFIG_SYS_CSPR0			CONFIG_SYS_NOR0_CSPR
#define CONFIG_SYS_AMASK0			CONFIG_SYS_NOR_AMASK
#define CONFIG_SYS_CSOR0			CONFIG_SYS_NOR_CSOR
#define CONFIG_SYS_CS0_FTIM0		CONFIG_SYS_NOR_FTIM0
#define CONFIG_SYS_CS0_FTIM1		CONFIG_SYS_NOR_FTIM1
#define CONFIG_SYS_CS0_FTIM2		CONFIG_SYS_NOR_FTIM2
#define CONFIG_SYS_CS0_FTIM3		CONFIG_SYS_NOR_FTIM3

#define CONFIG_SYS_MONITOR_BASE  CONFIG_SYS_TEXT_BASE /* start of monitor */

#define CONFIG_BOARD_EARLY_INIT_R	/* call board_early_init_r function */
#define CONFIG_MISC_INIT_R
#define CONFIG_HWCONFIG

/* define to use L1 as initial stack */
#define CONFIG_L1_INIT_RAM
#define CONFIG_SYS_INIT_RAM_LOCK
#define CONFIG_SYS_INIT_RAM_ADDR	0xfdd00000 /* Initial L1 address */
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS_HIGH	0xf
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS_LOW	0xfe03c000
/* The assembler doesn't like typecast */
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS \
			((CONFIG_SYS_INIT_RAM_ADDR_PHYS_HIGH * 1ull << 32) | \
			CONFIG_SYS_INIT_RAM_ADDR_PHYS_LOW)
#define CONFIG_SYS_INIT_RAM_SIZE	0x00004000
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_SIZE - \
						GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET
#define CONFIG_SYS_MONITOR_LEN		(768 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(4 * 1024 * 1024)

/*
 * Serial Port
 */
#define CONFIG_CONS_INDEX		1
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	1
#define CONFIG_SYS_NS16550_CLK		(get_bus_freq(0)/2)
#define CONFIG_SYS_BAUDRATE_TABLE	\
	{300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200}
#define CONFIG_SYS_NS16550_COM1 (CONFIG_SYS_CCSRBAR+0x11C500)
#define CONFIG_SYS_NS16550_COM2 (CONFIG_SYS_CCSRBAR+0x11C600)
#define CONFIG_SYS_NS16550_COM3 (CONFIG_SYS_CCSRBAR+0x11D500)
#define CONFIG_SYS_NS16550_COM4 (CONFIG_SYS_CCSRBAR+0x11D600)



/*
 * I2C
 */
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_FSL
#define CONFIG_SYS_FSL_I2C_SLAVE   0x7F
#define CONFIG_SYS_FSL_I2C2_SLAVE  0x7F
#define CONFIG_SYS_FSL_I2C3_SLAVE  0x7F
#define CONFIG_SYS_FSL_I2C4_SLAVE  0x7F
#define CONFIG_SYS_FSL_I2C_OFFSET  0x118000
#define CONFIG_SYS_FSL_I2C2_OFFSET 0x118100
#define CONFIG_SYS_FSL_I2C3_OFFSET 0x119000
#define CONFIG_SYS_FSL_I2C4_OFFSET 0x119100
#define CONFIG_SYS_FSL_I2C_SPEED   100000
#define CONFIG_SYS_FSL_I2C2_SPEED  100000
#define CONFIG_SYS_FSL_I2C3_SPEED  100000
#define CONFIG_SYS_FSL_I2C4_SPEED  100000

/*
 * eSPI - Enhanced SPI
 */
#ifdef CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_BAR
#define CONFIG_SF_DEFAULT_SPEED	 10000000
#define CONFIG_SF_DEFAULT_MODE	  0
#endif

/*
 * General PCI
 * Memory space is mapped 1-1, but I/O space must start from 0.
 */
#define CONFIG_PCI			/* Enable PCI/PCIE */
#define CONFIG_PCIE1		/* PCIE controller 1 */
#define CONFIG_PCIE2		/* PCIE controller 2 */
#define CONFIG_PCIE3		/* PCIE controller 3 */
#define CONFIG_PCIE4		/* PCIE controller 4 */
#define CONFIG_FSL_PCI_INIT	/* Use common FSL init code */
#define CONFIG_SYS_PCI_64BIT	/* enable 64-bit PCI resources */
/* controller 1, direct to uli, tgtid 3, Base address 20000 */
#define CONFIG_SYS_PCIE1_MEM_VIRT	0x80000000
#define CONFIG_SYS_PCIE1_MEM_BUS	0xe0000000
#define CONFIG_SYS_PCIE1_MEM_PHYS	0xc00000000ull
#define CONFIG_SYS_PCIE1_MEM_SIZE	0x20000000      /* 512M */
#define CONFIG_SYS_PCIE1_IO_VIRT	0xf8000000
#define CONFIG_SYS_PCIE1_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE1_IO_PHYS	0xff8000000ull
#define CONFIG_SYS_PCIE1_IO_SIZE	0x00010000	/* 64k */

/* controller 2, Slot 2, tgtid 2, Base address 201000 */
#define CONFIG_SYS_PCIE2_MEM_VIRT	0xa0000000
#define CONFIG_SYS_PCIE2_MEM_BUS	0xe0000000
#define CONFIG_SYS_PCIE2_MEM_PHYS	0xc20000000ull
#define CONFIG_SYS_PCIE2_MEM_SIZE	0x10000000 /* 256M */
#define CONFIG_SYS_PCIE2_IO_VIRT	0xf8010000
#define CONFIG_SYS_PCIE2_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE2_IO_PHYS	0xff8010000ull
#define CONFIG_SYS_PCIE2_IO_SIZE	0x00010000	/* 64k */

/* controller 3, Slot 1, tgtid 1, Base address 202000 */
#define CONFIG_SYS_PCIE3_MEM_VIRT	0xb0000000
#define CONFIG_SYS_PCIE3_MEM_BUS	0xe0000000
#define CONFIG_SYS_PCIE3_MEM_PHYS	0xc30000000ull
#define CONFIG_SYS_PCIE3_MEM_SIZE	0x10000000	/* 256M */
#define CONFIG_SYS_PCIE3_IO_VIRT	0xf8020000
#define CONFIG_SYS_PCIE3_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE3_IO_PHYS	0xff8020000ull
#define CONFIG_SYS_PCIE3_IO_SIZE	0x00010000	/* 64k */

/* controller 4, Base address 203000 */
#define CONFIG_SYS_PCIE4_MEM_VIRT	0xc0000000
#define CONFIG_SYS_PCIE4_MEM_BUS	0xe0000000
#define CONFIG_SYS_PCIE4_MEM_PHYS	0xc40000000ull
#define CONFIG_SYS_PCIE4_MEM_SIZE	0x10000000	/* 256M */
#define CONFIG_SYS_PCIE4_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE4_IO_PHYS	0xff8030000ull
#define CONFIG_SYS_PCIE4_IO_SIZE	0x00010000	/* 64k */

#ifdef CONFIG_PCI
#define CONFIG_PCI_INDIRECT_BRIDGE
#define CONFIG_FSL_PCIE_RESET           /* need PCIe reset errata LSZ ADD */
#define CONFIG_PCI_PNP		/* do pci plug-and-play */
#define CONFIG_PCI_SCAN_SHOW	/* show pci devices on startup */
#define CONFIG_DOS_PARTITION
#endif

/* Qman/Bman */
#ifndef CONFIG_NOBQFMAN
#define CONFIG_SYS_DPAA_QBMAN		/* Support Q/Bman */
#define CONFIG_SYS_BMAN_NUM_PORTALS	18
#define CONFIG_SYS_BMAN_MEM_BASE	0xf4000000
#define CONFIG_SYS_BMAN_MEM_PHYS	0xff4000000ull
#define CONFIG_SYS_BMAN_MEM_SIZE	0x02000000
#define CONFIG_SYS_BMAN_SP_CENA_SIZE    0x4000
#define CONFIG_SYS_BMAN_SP_CINH_SIZE    0x1000
#define CONFIG_SYS_BMAN_CENA_BASE       CONFIG_SYS_BMAN_MEM_BASE
#define CONFIG_SYS_BMAN_CENA_SIZE       (CONFIG_SYS_BMAN_MEM_SIZE >> 1)
#define CONFIG_SYS_BMAN_CINH_BASE       (CONFIG_SYS_BMAN_MEM_BASE + \
					CONFIG_SYS_BMAN_CENA_SIZE)
#define CONFIG_SYS_BMAN_CINH_SIZE       (CONFIG_SYS_BMAN_MEM_SIZE >> 1)
#define CONFIG_SYS_BMAN_SWP_ISDR_REG	0xE08
#define CONFIG_SYS_QMAN_NUM_PORTALS	18
#define CONFIG_SYS_QMAN_MEM_BASE	0xf6000000
#define CONFIG_SYS_QMAN_MEM_PHYS	0xff6000000ull
#define CONFIG_SYS_QMAN_MEM_SIZE	0x02000000
#define CONFIG_SYS_QMAN_SP_CENA_SIZE    0x4000
#define CONFIG_SYS_QMAN_SP_CINH_SIZE    0x1000
#define CONFIG_SYS_QMAN_CENA_BASE       CONFIG_SYS_QMAN_MEM_BASE
#define CONFIG_SYS_QMAN_CENA_SIZE       (CONFIG_SYS_QMAN_MEM_SIZE >> 1)
#define CONFIG_SYS_QMAN_CINH_BASE       (CONFIG_SYS_QMAN_MEM_BASE + \
					CONFIG_SYS_QMAN_CENA_SIZE)
#define CONFIG_SYS_QMAN_CINH_SIZE       (CONFIG_SYS_QMAN_MEM_SIZE >> 1)
#define CONFIG_SYS_QMAN_SWP_ISDR_REG	0xE08

#define CONFIG_SYS_DPAA_FMAN
#define CONFIG_SYS_DPAA_PME
#define CONFIG_SYS_PMAN
#define CONFIG_SYS_DPAA_DCE
#define CONFIG_SYS_DPAA_RMAN		/* RMan */
#define CONFIG_SYS_INTERLAKEN

/* Default address of microcode for the Linux Fman driver */
#define CONFIG_SYS_QE_FMAN_FW_IN_NOR
#define CONFIG_SYS_FMAN_FW_ADDR			FMAN_UCODE_IMAGE_OFFSET
#define CONFIG_SYS_QE_FMAN_FW_LENGTH	0x10000
#define CONFIG_SYS_FDT_PAD				(0x3000 + CONFIG_SYS_QE_FMAN_FW_LENGTH)
#endif /* CONFIG_NOBQFMAN */

#ifdef CONFIG_SYS_DPAA_FMAN
#define CONFIG_FMAN_ENET
#define CONFIG_PHY_MARVELL
#define RGMII_PHY1_ADDR		0x00	/* Marvell 88E1512 */
#define RGMII_PHY2_ADDR		0x01	/* Marvell 88E1512 */
#endif

#ifdef CONFIG_FMAN_ENET
#define CONFIG_MII		/* MII PHY management */
#define CONFIG_ETHPRIME		"FM1@DTSEC3"
#define CONFIG_PHY_GIGE		/* Include GbE speed/duplex detection */
#endif

/*
 * SATA
 */
#ifdef CONFIG_FSL_SATA_V2
#define CONFIG_LIBATA
#define CONFIG_FSL_SATA
#define CONFIG_SYS_SATA_MAX_DEVICE	2
#define CONFIG_SATA1
#define CONFIG_SYS_SATA1		CONFIG_SYS_MPC85xx_SATA1_ADDR
#define CONFIG_SYS_SATA1_FLAGS		FLAGS_DMA
#define CONFIG_SATA2
#define CONFIG_SYS_SATA2		CONFIG_SYS_MPC85xx_SATA2_ADDR
#define CONFIG_SYS_SATA2_FLAGS		FLAGS_DMA
#define CONFIG_LBA48
#define CONFIG_CMD_SATA
#define CONFIG_DOS_PARTITION
#endif

/*
 * USB
 */
#ifdef CONFIG_USB_EHCI

#define CONFIG_USB_EHCI_FSL
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET

#define CONFIG_HAS_FSL_DR_USB
#endif

/*
 * Dynamic MTD Partition support with mtdparts
 */
#ifndef CONFIG_SYS_NO_FLASH
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_MTDPARTS
#define CONFIG_FLASH_CFI_MTD
#define MTDIDS_DEFAULT "nor0=fe8000000.nor"
#define MTDPARTS_DEFAULT "mtdparts=fe8000000.nor:1m(uboot),5m(kernel)," \
			"128k(dtb),44m(fs),-(user);"
#endif

/*
 * Environment
 */

/*
 * Command line configuration.
 */

#define CONFIG_CMD_ERRATA

#define CONFIG_CMD_REGINFO

#ifdef CONFIG_PCI
#define CONFIG_CMD_PCI
#endif

/* Hash command with SHA acceleration supported in hardware */
#ifdef CONFIG_FSL_CAAM
#define CONFIG_CMD_HASH
#define CONFIG_SHA_HW_ACCEL
#endif

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_CMDLINE_EDITING		/* Command-line editing */
#define CONFIG_AUTO_COMPLETE		/* add autocompletion support */
#define CONFIG_SYS_LOAD_ADDR	0x2000000 /* default load address */
#ifdef CONFIG_CMD_KGDB
#define CONFIG_SYS_CBSIZE	1024	  /* Console I/O Buffer Size */
#else
#define CONFIG_SYS_CBSIZE	256	  /* Console I/O Buffer Size */
#endif
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)
#define CONFIG_SYS_MAXARGS	16	/* max number of command args */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE/* Boot Argument Buffer Size */

/*
 * For booting Linux, the board info and command line data
 * have to be in the first 64 MB of memory, since this is
 * the maximum mapped by the Linux kernel during initialization.
 */
#define CONFIG_SYS_BOOTMAPSZ	(64 << 20)	/* Initial map for Linux*/
#define CONFIG_SYS_BOOTM_LEN	(64 << 20)	/* Increase max gunzip size */

#ifdef CONFIG_CMD_KGDB
#define CONFIG_KGDB_BAUDRATE	230400	/* speed to run kgdb serial port */
#define CONFIG_KGDB_SER_INDEX	2	/* which serial port to use */
#endif

/*
 * Environment Configuration
 */
#define CONFIG_ROOTPATH	 "/nfsroot"
#define CONFIG_BOOTFILE	 "6xppc2/uImage"
#define CONFIG_RCWPATH "6xppc2/rcw.bin"	/* rcw image on TFTP server */
#define CONFIG_UBOOTPATH "6xppc2/u-boot.bin"	/* U-Boot image on TFTP server */
#define CONFIG_FMANPATH "6xppc2/fman.bin"	/* fman ucode image on TFTP server */
#define CONFIG_DTBPATH "6xppc2/68ppc2.dtb"	/* dtb image on TFTP server */
#define CONFIG_KERNELPATH "6xppc2/uImage"	/* kernel image on TFTP server */
#define CONFIG_ROOTFSPATH "6xppc2/rootfs.ext2.gz"	/* ramdisk image on TFTP server */


/* default location for tftp and bootm */
#define CONFIG_LOADADDR				1000000
#define CONFIG_DTB_LOADADDR			1800000
#define CONFIG_ROOTFS_LOADADDR		2000000


#define CONFIG_BAUDRATE		115200
#define CONFIG_SERVERIP		10.111.1.21
#define __USB_PHY_TYPE		utmi


#define	CONFIG_EXTRA_ENV_SETTINGS				\
	"hwconfig=fsl_ddr:"					\
	"ctlr_intlv=" __stringify(CTRL_INTLV_PREFERED) ","	\
	"bank_intlv=auto;"					\
	"usb1:dr_mode=host,phy_type=" __stringify(__USB_PHY_TYPE) "\0"\
	"netdev=eth0\0"						\
	"consoledev=ttyS0\0"					\
	"eth2addr=00:45:21:52:56:00\0"			\
	"bdev=sda3\0" \
	"rcw=" __stringify(CONFIG_RCWPATH) "\0"		\
	"rcwaddr=" __stringify(RCW_IMAGE_OFFSET) "\0"	\
	"rcwsize=" __stringify(RCW_IMAGE_SIZE) "\0"	\
	"uboot=" __stringify(CONFIG_UBOOTPATH) "\0"		\
	"ubootaddr=" __stringify(CONFIG_SYS_TEXT_BASE) "\0"	\
	"ubootsize=" __stringify(UBOOT_IMAGE_SIZE) "\0"	\
	"envaddr=" __stringify(UBOOT_IMAGE_ENV_OFFSET) "\0"	\
	"envsize=" __stringify(UBOOT_IMAGE_ENV_SIZE) "\0"	\
	"fman=" __stringify(CONFIG_FMANPATH) "\0"		\
	"fmanaddr=" __stringify(FMAN_UCODE_IMAGE_OFFSET) "\0"	\
	"fmansize=" __stringify(FMAN_UCODE_IMAGE_SIZE) "\0"	\
	"dtb=" __stringify(CONFIG_DTBPATH) "\0"		\
	"dtbaddr=" __stringify(DTB_IMAGE_OFFSET) "\0"	\
	"dtbloadaddr=" __stringify(CONFIG_DTB_LOADADDR) "\0"	\
	"dtbsize=" __stringify(DTB_IMAGE_SIZE) "\0"	\
	"kernel=" __stringify(CONFIG_KERNELPATH) "\0"		\
	"kerneladdr=" __stringify(KERNEL_IMAGE_OFFSET) "\0"	\
	"kernelloadaddr=" __stringify(CONFIG_LOADADDR) "\0"	\
	"kernelsize=" __stringify(KERNEL_IMAGE_SIZE) "\0"	\
	"rootfs=" __stringify(CONFIG_ROOTFSPATH) "\0"		\
	"rootfsaddr=" __stringify(ROOTFS_IMAGE_OFFSET) "\0"	\
	"rootfsloadaddr=" __stringify(CONFIG_ROOTFS_LOADADDR) "\0"	\
	"rootfssize=" __stringify(ROOTFS_IMAGE_SIZE) "\0"	\
	"eraseenv=" \
		"protect off $envaddr +$envsize;"		\
		"erase $envaddr +$envsize;"		\
		"protect on $envaddr +$envsize;\0"		\
	"flashrcw=" \
		"tftpboot $loadaddr $rcw;"	\
		"protect off $rcwaddr +$rcwsize;"		\
		"erase $rcwaddr +$rcwsize;"		\
		"cp.b $loadaddr $rcwaddr $filesize;"		\
		"protect on $rcwaddr +$rcwsize;"		\
		"cmp.b $loadaddr $rcwaddr $filesize;\0"		\
	"flashfman=" \
		"tftpboot $loadaddr $fman;"	\
		"protect off $fmanaddr +$fmansize;"		\
		"erase $fmanaddr +$fmansize;"		\
		"cp.b $loadaddr $fmanaddr $filesize;"		\
		"protect on $fmanaddr +$fmansize;"		\
		"cmp.b $loadaddr $fmanaddr $filesize;\0"		\
	"flashuboot="\
		"tftpboot $loadaddr $uboot;"	\
		"protect off $ubootaddr +$ubootsize;"		\
		"erase $ubootaddr +$ubootsize;"		\
		"cp.b $loadaddr $ubootaddr $filesize;"		\
		"protect on $ubootaddr +$ubootsize;"		\
		"cmp.b $loadaddr $ubootaddr $filesize;"		\
		"run eraseenv; \0 " \
	"flashdtb="\
		"tftpboot $loadaddr $dtb;"	\
		"protect off $dtbaddr +$dtbsize;"		\
		"erase $dtbaddr +$dtbsize;"		\
		"cp.b $loadaddr $dtbaddr $filesize;"		\
		"protect on $dtbaddr +$dtbsize;"		\
		"cmp.b $loadaddr $dtbaddr $filesize;\0"		\
	"flashkernel="\
		"tftpboot $loadaddr $kernel;"	\
		"protect off $kerneladdr +$kernelsize;"		\
		"erase $kerneladdr +$kernelsize;"		\
		"cp.b $loadaddr $kerneladdr $filesize;"		\
		"protect on $kerneladdr +$kernelsize;"		\
		"cmp.b $loadaddr $kerneladdr $filesize;\0"		\
	"flashrootfs="\
		"tftpboot $loadaddr $rootfs;"	\
		"protect off $rootfsaddr +$rootfssize;"		\
		"erase $rootfsaddr +$rootfssize;"		\
		"cp.b $loadaddr $rootfsaddr $filesize;"		\
		"protect on $rootfsaddr +$rootfssize;"		\
		"cmp.b $loadaddr $rootfsaddr $filesize\0"		\
	"norboot=echo NOR BOOT;" \
			"setenv bootargs root=/dev/ram rw "		\
			"console=$consoledev,$baudrate $othbootargs;"	\
			"setenv verify no;"	\
			"bootm $kerneladdr $rootfsaddr $dtbaddr;\0"	\
	"netboot=echo NET BOOT;" \
		"tftp $loadaddr $kernel;"		\
		"tftp $rootfsloadaddr $rootfs;"			\
		"tftp $dtbloadaddr $dtb;"			\
		"setenv bootargs root=/dev/ram rw "		\
		"console=$consoledev,$baudrate $othbootargs;"	\
		"setenv verify no;"	\
		"bootm $loadaddr $rootfsloadaddr $dtbloadaddr;\0" \
	"default_bootcmd=run norboot\0"

#define CONFIG_PROC_RESET_CONFIG				\
	"cpld procreset 1;" \
	"cpld tempalarm 0;"

#define CONFIG_BOOTCOMMAND	\
	CONFIG_PROC_RESET_CONFIG \
	"run default_bootcmd"

#include <asm/fsl_secure_boot.h>

#endif	/* __NAI6XPPC2_H */
