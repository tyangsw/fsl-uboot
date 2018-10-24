#include  <common.h>
#include <command.h>
#include <asm/io.h>
#include "cpld.h"

#define DMA_DESC_EN_OFFSET    0x00003F6C
#define DMA_FLAG_HEADER       0xc0de0000

static void toggle_signal(u8 state)
{
         
    if(state == 1)
    {  
       cpld_write(CPLD_TTL_RW, 0xff);
       cpld_write(CPLD_TTL_DATA,1);   
       //printf("high\n");
    }
    else
    {
       cpld_write(CPLD_TTL_DATA,0);
       // printf("low\n");
    }
}

int do_pci_dma(cmd_tbl_t *cmdtp, int flag, int argc, char* const argv[])
{
    u32 flagaddr, cardaddr, flagdata;
    u8  descid, tmp;

    if(argc < 5)
      return CMD_RET_USAGE;
    
    /*get flag address*/
    flagaddr = simple_strtoul(argv[1], NULL, 16);
    
    /*get flag data 0x0 ~ 0xff */
    tmp = simple_strtoul(argv[2], NULL, 16);
    flagdata = DMA_FLAG_HEADER | tmp;
    
    /*pci card base address*/
    cardaddr = simple_strtoul(argv[3], NULL, 16);
    
    /*dma descriptor id 0 ~ 31*/
    descid = simple_strtoul(argv[4], NULL, 10);

    /*clear flag data*/
    out_le32((void *)flagaddr, 0xc0de0000);
    
    /*toggle start*/
    toggle_signal(1);
   
    /*enable dma over pci bus*/
    out_le32((void *)(cardaddr+DMA_DESC_EN_OFFSET),(1 << descid));
    
    /*wait for flag data*/
    while(in_le32((void *)flagaddr) != flagdata);

    /*toggle end*/
    toggle_signal(0);

    printf("done !");
    
    return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
  pci_dma, 6, 0, do_pci_dma,
  "PCI DMA test",
  "pci_dma flag_addr flag_data card_addr desc_id \n"
  "    flag_addr    : In HEX 32bit address\n"
  "    flag_data    : In HEX 0x0 - 0xff\n"
  "    card_addr    : In HEX 32bit address\n"
  "    desc_id      : In INT 0 - 31\n"
);
