
/*
  This stuff is used to get instruction length and parse it into
  prefix, opcode, modregr/m, address, immediate, etc.
*/

// ADE32 version 2.03c -- C edition


#ifndef __ADE32_C__
#define __ADE32_C__

#include <string.h>

#include "ade32.h"
#include "ade32tbl.h"

//int ade32_disasm (unsigned char *opcode0, ade32_struct* diza)
int ade32_disasm(unsigned char* opcode0, struct ade32_struct* diza)
{

  unsigned char* opcode;
  unsigned char c, mod, rm;
  unsigned long t, a, d, i;

  opcode = opcode0;

  memset(diza, 0x00, sizeof(struct ade32_struct));
  diza->op_defdata = 4;
  diza->op_defaddr = 4;

//  if (*(unsigned short*)opcode == 0x0000) return 0;
  if (*(unsigned short*)opcode == 0xFFFF) return 0;

  unsigned long flag = 0;

repeat_prefix:

  c = *opcode++;

  t = ade32_table[ c ];

  if (t & C_ANYPREFIX)
  {

    if (flag & t) return 0;    // twice LOCK,SEG,REP,66,67

    flag |= t;

    if (t & C_67)
    {
      diza->op_defaddr ^= 2^4;
    }
    else
    if (t & C_66)
    {
      diza->op_defdata ^= 2^4;
    }
    else
    if (t & C_SEG)
    {
      diza->op_seg = c;
    }
    else
    if (t & C_REP)
    {
      diza->op_rep = c;
    }
    // LOCK

    goto repeat_prefix;

  } // C_ANYPREFIX

  flag |= t;

  diza->op_opcode = c;

  if (c == 0x0F)
  {
    c = *opcode++;

    diza->op_opcode2 = c;

    flag |= ade32_table[ 256 + c ]; // 2nd flagtable half

    if (flag == C_ERROR) return 0;
  }
  else
  if (c == 0xF7)
  {
    if (((*opcode) & 0x38)==0)
      flag |= C_DATA66;
  }
  else
  if (c == 0xF6)
  {
    if (((*opcode) & 0x38)==0)
      flag |= C_DATA1;
  }
  else
  if (c == 0xCD)
  {
    if (*opcode == 0x20)
      flag |= C_DATA4;
    else
      flag |= C_DATA1;
  }

  if (flag & C_MODRM)
  {
    c = *opcode++;

    diza->op_modrm = c;

    if ((c & 0x38) == 0x20)
    if (diza->op_opcode == 0xFF)
      flag |= C_STOP;

    mod = c & 0xC0;
    rm  = c & 0x07;

    if (mod != 0xC0)
    {
      if (diza->op_defaddr == 4)
      {
        if (rm == 4)
        {
          flag |= C_SIB;
          c = *opcode++;
          diza->op_sib = c;
          rm = c & 0x07;
        }

        if (mod == 0x40)
        {
          flag |= C_ADDR1;
        }
        else
        if (mod == 0x80)
        {
          flag |= C_ADDR4;
        }
        else
        {
          if (rm == 5)
            flag |= C_ADDR4;
        }
      }
      else // MODRM 16-bit
      {

        if (mod == 0x40)
        {
          flag |= C_ADDR1;
        }
        else
        if (mod == 0x80)
        {
          flag |= C_ADDR2;
        }
        else
        {
          if (rm == 6)
            flag |= C_ADDR2;
        }
      }
    }
  } // C_MODRM

  diza->op_flag = flag;

  a =  flag & (C_ADDR1 | C_ADDR2 | C_ADDR4);
  d = (flag & (C_DATA1 | C_DATA2 | C_DATA4)) >> 8;

  if (flag & C_ADDR67) a += diza->op_defaddr;
  if (flag & C_DATA66) d += diza->op_defdata;

  diza->op_addrsize = a;
  diza->op_datasize = d;

  for(i = 0; i<a; i++)
    diza->op_addr_b[i] = *opcode++;

  for(i = 0; i<d; i++)
    diza->op_data_b[i] = *opcode++;

  diza->op_len = opcode - opcode0;

  return diza->op_len;

} // disasm()

#endif	// __ADE32_C__

