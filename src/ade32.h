/*
  ADE32 -- Advanced Disassembler Engine -- FREEWARE
  version 2.03
*/

#ifndef __ADE32_H__
#define __ADE32_H__

#define C_ERROR   0xFFFFFFFF  /* "invalid" instruction                       */
#define C_ADDR1   0x00000001
#define C_ADDR2   0x00000002
#define C_ADDR4   0x00000004
#define C_LOCK    0x00000008
#define C_67      0x00000010
#define C_66      0x00000020
#define C_REP     0x00000040
#define C_SEG     0x00000080
#define C_ANYPREFIX  (C_66+C_67+C_LOCK+C_REP+C_SEG)
#define C_DATA1   0x00000100
#define C_DATA2   0x00000200
#define C_DATA4   0x00000400
#define C_SIB     0x00000800
#define C_ADDR67  0x00001000
#define C_DATA66  0x00002000
#define C_MODRM   0x00004000
#define C_BAD     0x00008000  /* very rarely appears in the executable code  */
#define C_OPCODE2 0x00010000              /*  (see pe_stat.zip for details)  */
#define C_REL     0x00020000  /* has relative argument, like in Jxx          */
#define C_STOP    0x00040000  /* is something like RET or JMP                */

/* instruction is split/merged into/from the following structure: */

struct ade32_struct
{
  unsigned char  op_defaddr;
  unsigned char  op_defdata;
  unsigned long  op_len;
  unsigned long  op_flag;
  unsigned long  op_addrsize;
  unsigned long  op_datasize;
  unsigned char  op_rep;
  unsigned char  op_seg;
  unsigned char  op_opcode;
  unsigned char  op_opcode2;
  unsigned char  op_modrm;
  unsigned char  op_sib;
  /* its not your fukkin perl, dude */
  union
  {
  unsigned char  op_addr_b[8];
  unsigned short op_addr_w[4];
  unsigned long  op_addr_d[2];
  char           op_addr_c[8];
  short          op_addr_s[4];
  long           op_addr_l[2];
  };
  union
  {
  unsigned char  op_data_b[8];
  unsigned short op_data_w[4];
  unsigned long  op_data_d[2];
  char           op_data_c[8];
  short          op_data_s[4];
  long           op_data_l[2];
  };
}; /* ade32_struct */

int ade32_disasm(unsigned char* opcode0, struct ade32_struct* diza);

#endif /* __ADE32_H__ */
