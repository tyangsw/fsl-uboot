/*
 * (C) Copyright 2018
 * North Atlantic industries, Inc.
 *
 * SPDX-License-Identifier:  GPL-2.0+
 */

/*
 *
 */

#include <common.h>
#include <config.h>
#include <malloc.h>
#include <command.h>
#include <i2c.h>


#define SLV_SMBUS_ADDR 0x74
#define EEPROM_ADDR    0x50

#define CSR_FUNC    0
#define EEPROM_FUNC 1
#define BYTE_SIZE 0
#define WORD_SIZE 1
#define BLOCK_SIZE 2

#define CMD_WRITE_OP 0
#define CMD_READ_OP  1

#define MAX_PAYLOAD_LEN 9

#pragma pack(1)
typedef struct
{
  union {
    uchar reg;
    struct {
      uchar pec    : 1; /*bit 0 end of last read or write sequence*/
      uchar size  : 2; /*bit 1 start of first read or write sequence*/
      uchar func   : 3; /*bit 2 - 4  smbus operation: 0=csr_rw 1=eeprom_rw*/
      uchar start   : 1; /*bit 5 - 6 smbus data size transaction 0=byte 1=word 2=block */
      uchar end    : 1; /*bit 7 smbus transaction packet error */
    } bits;
  } ccode;

  uchar bytecnt;
  union {
    uchar reg;
    struct {
      uchar werr  : 1; /*bit 7 write error*/
      uchar rerr  : 1; /*bit 6 read error*/
      uchar reserved : 1; /*bit 5 reserved*/
      uchar op    : 1; /*bit 4 csr operation 0=csr_write 1=csr_read*/
      uchar beuu  : 1; /*bit 3 byte enable upper*/
      uchar beum  : 1; /*bit 2 byte enable upper middle*/
      uchar belm  : 1; /*bit 1 byte enable lower middle*/
      uchar bell  : 1; /*bit 0 byte enable lower*/
    } bits;
  } csr_cmd;

  union {
    uchar reg;
    struct {
      uchar reserved2  : 2; /*bit 6 - 7 reserved*/
      uchar mss       : 1; /*bit 5 misplaed start & stop error bit*/
      uchar reserved1  : 1; /*bit 4 reserved*/
      uchar naeer     : 1; /*bit 3 No Ack Error*/
      uchar reserved  : 1; /*bit 2 reserved*/
      uchar usa       : 1; /*bit 1 user speicified addr. set this bit to user specified EEADDR addr*/
      uchar op        : 1; /*bit 0 eeprom operation 0=write 1=read*/
    } bits;
  } eeprom_cmd;

  uchar eeaddr;
  uchar addrl;
  uchar addru;
  uchar datall;
  uchar datalm;
  uchar dataum;
  uchar datauu;
} CMD;
#pragma pack()

static void debug_msg(uchar* buf, uint len)
{
   uint index = 0;
   while(index < len)
   {
      printf("%02x ",buf[index]);
      index++;
   }
   printf("\n");
}

static int smbus_write(uchar* buf, uint len)
{
   int ret = 0;
   ret = i2c_write(SLV_SMBUS_ADDR,0,0,buf,len);
   return ret;
}

static int smbus_read(uchar* buf, uint len)
{
   int ret = 0;
   ret = i2c_read(SLV_SMBUS_ADDR,0,0,buf,len);
   return ret;
}

static int send_req(CMD* req)
{
   int ret = 0;
   uchar payload[MAX_PAYLOAD_LEN];
   /*TODO Assert Null pointer*/
   /*verify cmd function*/ 
   
   payload[0] = req->ccode.reg;
   payload[1] = req->bytecnt;
   if(req->ccode.bits.func == CSR_FUNC)
   {
     /*construct payload*/
     payload[2] = req->csr_cmd.reg;
     payload[3] = req->addrl;
     payload[4] = req->addru;
     if(req->csr_cmd.bits.op == CMD_READ_OP)
     {
       debug_msg(payload,5);
       ret = smbus_write(payload,5);
     }  
     else
     {
       payload[5] = req->datall;
       payload[6] = req->datalm;
       payload[7] = req->dataum;
       payload[8] = req->datauu;
       debug_msg(payload,9);
       ret = smbus_write(payload,9);
     }
   }
   else if(req->ccode.bits.func == EEPROM_FUNC)
   {
     /*construct payload*/
     payload[2] = req->eeprom_cmd.reg;
     payload[3] = req->eeaddr;
     payload[4] = req->addrl;
     payload[5] = req->addru;
     if(req->eeprom_cmd.bits.op == CMD_READ_OP)
     {
       debug_msg(payload,6);
       ret = smbus_write(payload,6);
     }  
     else
     {
       payload[6] = req->datall;
       debug_msg(payload,7);
       ret = smbus_write(payload,7);
     }
   }
   else
   {
     /*return error*/
     ret = -1;
   }
   
   return ret;
}

static int get_resp(CMD* resp)
{
   int ret = 0;
   uchar payload[MAX_PAYLOAD_LEN];
   /*TODO Assert Null pointer*/
   /*verify cmd function*/ 
   
   payload[0] = resp->ccode.reg;
   if(resp->ccode.bits.func == CSR_FUNC)
   {
     ret = smbus_write(payload,1);
     if(!ret)
     {
        ret = smbus_read(payload,8);
        debug_msg(payload,8);
       	resp->bytecnt = payload[0];
	resp->csr_cmd.reg = payload[1];
	resp->addrl = payload[2];
	resp->addru = payload[3];
	resp->datall = payload[4];
	resp->datalm = payload[5];
	resp->dataum = payload[6];
	resp->datauu = payload[7];
     }
   }
   else if(resp->ccode.bits.func == EEPROM_FUNC)
   {
     ret = smbus_write(payload,1);
     if(!ret)
     {
        ret = smbus_read(payload,6);
        debug_msg(payload,6);
       	resp->bytecnt = payload[0];
	resp->eeprom_cmd.reg = payload[1];
	resp->eeaddr = payload[2];
	resp->addrl = payload[3];
	resp->addru = payload[4];
	resp->datall = payload[5];
     }
   }
   else
   {
     /*return error*/
     ret = -1;
   }
   return ret;
   
}

static void read_csr(uint addr)
{
    CMD *req, *resp;
    int ret = 0;

    req = (CMD* )malloc(sizeof(CMD));
    if(!req)
    {
      return;
    }
    
    resp = (CMD* )malloc(sizeof(CMD));
    if(!resp)
    {
      fREe(req);
      return;
    }

    req->ccode.bits.end = 1;
    req->ccode.bits.start = 1;
    req->ccode.bits.func = CSR_FUNC;
    req->ccode.bits.size = BLOCK_SIZE;
    req->ccode.bits.pec = 0;
    req->bytecnt = 3;
    req->csr_cmd.bits.bell = 1;
    req->csr_cmd.bits.belm = 1;
    req->csr_cmd.bits.beum = 1;
    req->csr_cmd.bits.beuu = 1;
    req->csr_cmd.bits.op = CMD_READ_OP;
    req->csr_cmd.bits.werr = 0;
    req->csr_cmd.bits.rerr = 0;
    req->addrl = ((addr >> 2) & 0x00FF);
    req->addru = (((addr >> 2) & 0xFF00)>>8);
    
    ret = send_req(req);
    if(!ret)
    {
       udelay(500000);
       resp->ccode.reg = req->ccode.reg;
       ret = get_resp(resp);
       printf("%s out: bytecnt=%d data=0x%02x%02x%02x%02x\n",__func__,
               resp->bytecnt,resp->datauu,resp->dataum,resp->datalm,resp->datall);
    }
    else
    {
      printf("%s error ret=%d \n",__func__,ret);
    }

    fREe(req);
    fREe(resp);
    
    return;
}

static void write_csr(uint addr, uint data)
{
    CMD *req;
    int ret = 0;

    req = (CMD* )malloc(sizeof(CMD));
    if(!req)
    {
      return;
    }
    
    req->ccode.bits.end = 1;
    req->ccode.bits.start = 1;
    req->ccode.bits.func = CSR_FUNC;
    req->ccode.bits.size = BLOCK_SIZE;
    req->ccode.bits.pec = 0;
    req->bytecnt = 4;
    req->csr_cmd.bits.bell = 1;
    req->csr_cmd.bits.belm = 1;
    req->csr_cmd.bits.beum = 1;
    req->csr_cmd.bits.beuu = 1;
    req->csr_cmd.bits.op = CMD_WRITE_OP;
    req->csr_cmd.bits.werr = 0;
    req->csr_cmd.bits.rerr = 0;
    req->addrl = ((addr >> 2) & 0x00FF);
    req->addru = (((addr >> 2) & 0xFF00)>>8);
    req->datall = (data & 0x000000FF);
    req->datalm = ((data & 0x0000FF00) >> 8);
    req->dataum = ((data & 0x00FF0000) >> 16);
    req->datauu = ((data & 0xFF000000) >> 24);

    ret = send_req(req);
    if(ret)
    {
      printf("%s error ret=%d\n",__func__,ret);
    }
    fREe(req);
    
    return;
}

static void write_eeprom(uint addr, uchar data, uint cnt)
{
   
    CMD *req;
    int ret = 0;

    req = (CMD* )malloc(sizeof(CMD));
    if(!req)
    {
      return;
    }
   
    req->ccode.bits.end = 1;
    req->ccode.bits.start = 1;
    req->ccode.bits.func = EEPROM_FUNC;
    req->ccode.bits.size = BLOCK_SIZE;
    req->ccode.bits.pec = 0;
    req->bytecnt = 5;
    req->eeprom_cmd.bits.op = CMD_WRITE_OP;
    req->eeprom_cmd.bits.usa = 1;
    req->eeprom_cmd.bits.naeer = 0;
    req->eeprom_cmd.bits.mss = 0;
    req->eeaddr = (EEPROM_ADDR << 1);
    req->datall = data;
    
    while(cnt > 0) 
    {
      req->addrl = (addr & 0x00FF);
      req->addru = ((addr & 0xFF00)>>8);
      ret = send_req(req);
      if(ret)
      {
        printf("%s error ret=%d\n",__func__,ret);
      }
      cnt--;
      addr++;
    }

    fREe(req);
}

static void read_eeprom(uint addr, uchar* data, uint cnt)
{
   
    CMD *req, *resp;
    int ret = 0;

    req = (CMD* )malloc(sizeof(CMD));
    if(!req)
    {
      return;
    }

    resp = (CMD* )malloc(sizeof(CMD));
    if(!resp)
    {
      fREe(req);
      return;
    }

    req->ccode.bits.end = 1;
    req->ccode.bits.start = 1;
    req->ccode.bits.func = EEPROM_FUNC;
    req->ccode.bits.size = BLOCK_SIZE;
    req->ccode.bits.pec = 0;
    req->bytecnt = 4;
    req->eeprom_cmd.bits.op = CMD_READ_OP;
    req->eeprom_cmd.bits.usa = 1;
    req->eeprom_cmd.bits.naeer = 0;
    req->eeprom_cmd.bits.mss = 0;
    req->eeaddr = (EEPROM_ADDR << 1);
    while(cnt > 0) 
    {
      req->addrl = (addr & 0x00FF);
      req->addru = ((addr & 0xFF00)>>8);
      ret = send_req(req);
      if(!ret)
      {
        udelay(50000);
        resp->ccode.reg = req->ccode.reg;
        ret = get_resp(resp);
	if(!ret)
	{
	  *data = resp->datall;
	  data++;
	  addr++;
	}
	else
	{
	  printf("%s error ret=%d\n",__func__,ret);
	}
      }
      cnt--;
    }
     
    fREe(req);
    fREe(resp);
}

int do_swconfig(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
  uint addr, cnt, val;
  char op;
  uchar *pdata, data, *memaddr;

  if (argc < 1)
    return CMD_RET_USAGE;
  op = *argv[1];
  switch (op)
  {
      case '1': /*read to csr*/
        addr = simple_strtoul(argv[2],NULL,16); 
        printf("addr %x\n",addr);
        read_csr(addr);
        break;
      case '2': /*write from csr*/
        addr = simple_strtoul(argv[2],NULL,16);
        val = simple_strtoul(argv[3],NULL,16);
        printf("addr %x data %x\n",addr,val);
        write_csr(addr,val);
        break;
      case '3': /*read eerpom*/
        addr = simple_strtoul(argv[2],NULL,16); 
        cnt = simple_strtoul(argv[3],NULL,10); 
        printf("addr 0x%x cnt=%d\n",addr,cnt);
        pdata = malloc(cnt);
        read_eeprom(addr, pdata,cnt);
        debug_msg(pdata,cnt);
	fREe(pdata);
        break;
      case '4': /*write data to eeprom*/
        addr = simple_strtoul(argv[2],NULL,16);
        data = simple_strtoul(argv[3],NULL,16);
        cnt = simple_strtoul(argv[4],NULL,10); 
        printf("addr 0x%x cnt=%d\n",addr,cnt);
        write_eeprom(addr,data,cnt);
        break;
      case '5': /*dump eeprom to memory*/
        memaddr = (uchar  *)simple_strtoul(argv[2],NULL,16);
        addr  = simple_strtoul(argv[3],NULL,16);
        cnt = simple_strtoul(argv[4],NULL,10); 
        read_eeprom(addr, memaddr, cnt);
	break;
      case '6': /*copy date from local memory to eeprom*/
        memaddr = (uchar  *)simple_strtoul(argv[2],NULL,16);
        addr  = simple_strtoul(argv[3],NULL,16);
        cnt = simple_strtoul(argv[4],NULL,10);
        while(cnt > 0)	
	{ 
	  data = *memaddr;
          write_eeprom(addr, data, 1);
          addr++;
	  memaddr++;
	  cnt--;
	}
	break;
      default:
	break;
  }

  return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
  swconfig,  6,  0,  do_swconfig,
  "pcie switch port configuration",
  "\n"
)
