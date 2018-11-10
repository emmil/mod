#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <string.h>

#include "mod.h"
#include "decode.h"
#include "ade32.h"

s_instr	current;
instr_name *curr_name;

void add (int i, char *format, ...) {
	va_list arglist;
        char buffer[1024];
	int l;

        va_start(arglist, format);
        vsprintf(buffer, format, arglist);
        va_end(arglist);

	l = strlen (buffer);

	switch (i) {
		case A_NAME: 	memcpy ((curr_name->name + curr_name->name_len), buffer, l);
				curr_name->name_len += l;
				break;

		case A_OP1:	memcpy ((curr_name->operand1 + curr_name->operand1_len), buffer, l);
				curr_name->operand1_len += l;
				break;


		case A_OP2:	memcpy ((curr_name->operand2 + curr_name->operand2_len), buffer, l);
				curr_name->operand2_len += l;
				break;


		case A_OP3:	memcpy ((curr_name->operand3 + curr_name->operand3_len), buffer, l);
				curr_name->operand3_len += l;
				break;

		case A_PREFIX:	memcpy ((curr_name->prefix + curr_name->prefix_len), buffer, l);
				curr_name->prefix_len += l;
				break;

		case A_ERROR:
		default:	fprintf (stderr, "%s\n", buffer);
	}
}

void decode_prefix (struct ade32_struct *diza) {
	unsigned long	tmp;
	int output;

	tmp = (AM_E | AM_M | AM_Q | AM_W);

	if (diza->op_flag & C_LOCK) add (A_PREFIX, "lock ");
	if (diza->op_flag & C_REP) add (A_PREFIX, "rep ");

	if (current.operands[0] & tmp) output = A_OP1;
	else if (current.operands[1] & tmp) output = A_OP2;
	else if (current.operands[2] & tmp) output = A_OP3;
	else output = A_PREFIX;

	if (diza->op_flag & C_SEG) {
		switch (diza->op_seg) {
			case 0x36: add (output, "ss: "); break;
			case 0x3E: add (output, "ds: "); break;
			case 0x26: add (output, "es: "); break;
			case 0x2E: add (output, "cs: "); break;
			case 0x64: add (output, "fs: "); break;
			case 0x65: add (output, "gs: "); break;
		}
	}
}

void patch_group (struct ade32_struct *diza) {
	u_modreg	modreg;
	unsigned long	patch;
	int		pg, pi;

	if (current.patch > PG_16)
		return;

	modreg.data = diza->op_modrm;
	patch = current.patch;
	pg = ((current.patch - PG_1) >> P_SHIFT);
	pi = modreg.reg;
	if (modreg.mod == 3) pi+= 8;

	switch (patch) {
		case PG_3 : current.name = patchg_list [pg][pi].name;
			    current.operands[1] = patchg_list [pg][pi].operands [1];
			    break;
		case PG_1 :
		case PG_2 :
		case PG_8 :
		case PG_11 : current.name = patchg_list [pg][pi].name; break;
		case PG_4 :
		case PG_5 :
		case PG_6 :
		case PG_7 :
		case PG_9 :
		case PG_12 :
		case PG_13 :
		case PG_14 :
		case PG_15 :
		case PG_16 : current = patchg_list [pg][pi]; break;
		default : add (A_ERROR, "patch group: unhandled PG_X 0%x", patch);
	}
}

void patch_66 (struct ade32_struct *diza) {
	unsigned int	patch, pi;

	if ((current.patch < P66_MIN) || (current.patch > P66_MAX))
		return;

	patch = ((current.patch - P66_MIN) >> P_SHIFT);
	if (diza->op_flag & C_66) pi = 0;
	else pi = 1;

	current.name = patch66_list [patch][pi];
}

void patch_float (struct ade32_struct *diza) {
	u_modreg	modreg;
	unsigned char	fg, fi, tmp, fg2, fi2;

	if (current.patch != PFLOAT)
		return;

	modreg.data = diza->op_modrm;

	if (modreg.data > 0xBF) {
		fg = ((diza->op_opcode & 0xF) - 8);
		fi = ((diza->op_modrm >> 4) & 0x3);

		tmp = (diza->op_modrm & 0xF);
		if (tmp & 8) fi += 4;

		current = finsc0_list [fg][fi];

		if (current.patch) {	// PPFLOAT
			fg2 = current.patch - PPFLOAT_9D;
			fi2 = (diza->op_modrm & 0xF);
			current.name = patchf_list [fg2][fi2];

			if ((diza->op_opcode == 0xDF) && (diza->op_modrm == 0xE0)) {	// patch fstsw ax
				current.operands [0] = R_AX;
			}
		}

	} else {
		fg = ((diza->op_opcode & 0x0F) - 8);
		fi = modreg.reg;
		current = finsbf_list [fg][fi];
	}
}

void	patch_mmx (struct ade32_struct *diza) {
	int	mg, mi;

	if ((current.patch < PMMX_MIN) || (current.patch > PMMX_MAX)) {
		return;
	}

	mg = current.patch - PMMX_MIN;
	if (diza->op_flag & C_66) mi = 1;
	else if ((diza->op_flag & C_REP) && (diza->op_rep == 0xF2)) mi = 2;
	else if ((diza->op_flag & C_REP) && (diza->op_rep == 0xF3)) mi = 3;
	else mi = 0;
	current = patchmmx_list [mg][mi];
}

void kill_decode (void) {
	current.name = NULL;
	current.operands[0] = 0;
	current.operands[1] = 0;
	current.operands[2] = 0;
}


void decode_name (struct ade32_struct *diza) {
	unsigned int	index;

	if (diza->op_flag & C_OPCODE2) {
		index = diza->op_opcode2 + 0x100;
	} else {
		index = diza->op_opcode;
	}

	current = ins_list [index];

	if (current.patch) {
		patch_group (diza);
		patch_66 (diza);
		patch_float (diza);
		patch_mmx (diza);
	}

	if (current.name != NULL) {
		add (A_NAME, "%s", current.name);
	}
}


void decode_register (struct ade32_struct *diza, int output, int i) {
	char		**names;
	unsigned long	index;
	unsigned char	modreg;

	index = current.operands [i];

	if ((current.operands[i] >= R_MIN8) && (current.operands[i] <= R_MAX8)) {
		names = reg8_tbl;
		index = index - R_MIN8;
	} else

	if ((current.operands[i] >= R_MIN16) && (current.operands[i] <= R_MAX16)) {
		names = reg16_tbl;
		index = index - R_MIN16;
	} else

	if ((current.operands[i] >= R_MIN32) && (current.operands[i] <= R_MAX32)) {
		names = reg32_tbl;
		index = index - R_MIN32;
	} else

	if ((current.operands[i] >= R_MINSEG) && (current.operands[i] <= R_MAXSEG)) {
		names = seg_tbl;
		index = index - R_MINSEG;
  	} else

	if ((current.operands[i] >= R_eMIN) && (current.operands[i] <= R_eMAX)) {
		if (diza->op_flag & C_66) names = reg16_tbl;
		else names = reg32_tbl;
		index = index - R_eMIN;
	} else

	if (current.operands[i] == R_ALEAX) {
		if (diza->op_flag & C_66) names = reg16_tbl;
		else names = reg32_tbl;
		index = index - R_ALEAX;
	} else

	if (current.operands[i] == R_ST0) {
		add (output, "st0");
		return;
	} else

	if (current.operands[i] == R_STi) {
		modreg = (diza->op_modrm & 0x7);
		add (output, "st%x", modreg);
		return;
	} else

	{
		add (A_ERROR, "decode_register: unhandled R_X 0%x ", (current.operands [i] & R_MASK));
		return;
	}

	index = index >> R_SHIFT;
	add (output, "%s", names[index]);
}

void decode_A (struct ade32_struct *diza, int output, int i) {
	switch (current.operands[i] & OT_MASK) {
		case OT_p: if (diza->op_flag & C_66) add (output, "far 0%xh : 0%xh", diza->op_data_w[1], diza->op_data_w[0]);
			   else add (output, "far 0%xh : 0%xh", diza->op_data_w[2], diza->op_data_d[0]);
			   break;
		default: add (A_ERROR, "decode_A : unhandled OT_x 0%x", (current.operands [i] & OT_MASK));
	}
}

void decode_C (struct ade32_struct *diza, int output, int i) {
	u_modreg	modreg;

	modreg.data = diza->op_modrm;

	if (modreg.reg <= 4) {
		add (output, "%s", cr_tbl [modreg.reg]);
	}
	else add (A_ERROR, "decode_C : invalid control register");
}

void decode_D (struct ade32_struct *diza, int output, int i) {
	u_modreg	modreg;

	modreg.data = diza->op_modrm;

	add (output, "%s", dr_tbl [modreg.reg]);
}

void decode_E16 (struct ade32_struct *diza, int output, int i) {
	u_modreg	modreg;
	unsigned char	modrm;
	unsigned int	tmp, j;

	modreg.data = diza->op_modrm;
	modrm = ((modreg.mod << 3) | (modreg.rm));
	tmp = rm16_tbl [modrm];

	add (output, "[");

	if (tmp & RR16_MASK) {
		j = ((tmp & RR16_MASK) >> RR16_SHIFT);
		add (output, "%s", ea16_tbl [(j - 1)]);
	}

	if (tmp & RD16_MASK) {
		j = (tmp & RD16_MASK);
		if (tmp & RR16_MASK) {
			if (j & RD16_DISP8) {
				if (diza->op_addr_b[0] & 0x80) {
					add (output, " - ");
					diza->op_addr_c [0] = - (signed char) diza->op_addr_b [0];
				} else add (output, " + ");
			}
			else add (output, " + ");
		}
		add (output, "%lxh", diza->op_addr_l[0]);
	}

	add (output, "]");
}

void decode_E32 (struct ade32_struct *diza, int output, int i) {
	u_modreg	modreg;
	u_sib		sib;
	unsigned char	modrm;
	unsigned int	j, tmp;
	unsigned int	sign;

	modreg.data = diza->op_modrm;
	sib.data = diza->op_sib;
	modrm = ((modreg.mod << 3) | (modreg.rm));
	tmp = rm32_tbl [modrm];
	sign = 0;

	add (output, "[");

	if ((tmp & RR32_MASK) && ((tmp & RR32_MASK) != RR32_SIB)) {
		j = ((tmp & RR32_MASK) >> RR32_SHIFT);
		add (output, "%s", ea32_tbl [(j - 1)]);

	}

	if ((tmp & RR32_MASK) && ((tmp & RR32_MASK) == RR32_SIB)) {

		if (sib.base != 5) {
			add (output, "%s", base_tbl [sib.base]);
		} else {
			if (modreg.mod != 0) add (output, "ebp");
		}

		if (sib.index != 4) {
			if ((sib.base !=5) || (modreg.mod != 0)) add (output, " + ");
			add (output, "%s", sib_tbl [sib.index]);
			add (output, "%s", mul_tbl [sib.scale]);
		}

		if ((tmp & RD32_MASK) && ((sib.base != 5 || modreg.mod != 0) || (sib.index != 4))) sign = 1;

	}

	if ((tmp & RD32_MASK) || (sib.base == 5 && modreg.mod < 3)) {
		if ((tmp & RR32_MASK) && ((tmp & RR32_MASK) != RR32_SIB)) sign = 1;
		if (sib.base == 5 && modreg.mod < 3) sign = 1;

		if (sign) {
			if (((tmp & RD32_MASK) & RD32_DISP8)  && (diza->op_addr_b[0] & 0x80)) {
				add (output, " - ");
				diza->op_addr_c [0] = - (signed char) diza->op_addr_b [0];
			} else add (output, " + ");
		}

		add (output, "%lxh", diza->op_addr_l [0]);
	}

	add (output, "]");
}

void decode_E (struct ade32_struct *diza, int output, int i) {
	u_modreg	modreg;
	char		**name;

	modreg.data = diza->op_modrm;
	if (modreg.mod == 3) {
		switch (current.operands[i] & OT_MASK) {
			case OT_b : name = reg8_tbl; break;
			case OT_w : name = reg16_tbl; break;
			case OT_d : name = reg32_tbl; break;
			case OT_v : if (diza->op_flag & C_66) name = reg16_tbl;
				    else name = reg32_tbl;
				    break;
			case OT_p : kill_decode (); // is this correct ??!!
				    return;
				    break;
			default : add (A_ERROR, "decode_E 1: unhandled OT_x 0%x", (current.operands [i] & OT_MASK));
				  return;
		}
		add (output, "%s", name [modreg.rm]);
	} else {
		switch (current.operands[i] & OT_MASK) {
			case OT_w :
			case OT_p :
			case OT_q :
			case OT_b :
			case OT_d : decode_E32 (diza, output, i); break;
			case OT_s :
			case OT_v : if (diza->op_flag & C_67) decode_E16 (diza, output, i);
				    else decode_E32 (diza, output, i);
				    break;
			default: add (A_ERROR, "decode_E 2: unhandled OT_x 0%x", (current.operands [i] & OT_MASK));
		}
	}
}

void decode_G (struct ade32_struct *diza, int output, int i) {
	u_modreg	modreg;
	char		**names;

	modreg.data = diza->op_modrm;

	switch (current.operands[i] & OT_MASK) {
		case OT_b: names = reg8_tbl; break;
		case OT_w: names = reg16_tbl; break;
		case OT_d: names = reg32_tbl; break;
		case OT_v: if (diza->op_flag & C_66) names = reg16_tbl;
			   else names = reg32_tbl;
			   break;
		default: add (A_ERROR, "decode_G : unhandled OT_x 0%x", (current.operands [i] & OT_MASK));
			 return;
	}
	add (output, "%s", names[modreg.reg]);
}

void decode_I (struct ade32_struct *diza, int output, int i) {
	switch (current.operands[i] & OT_MASK) {
		case OT_b:
		case OT_w:
		case OT_d:
		case OT_v: add (output, "0%xh", diza->op_data_d [0]); break;
		default: add (A_ERROR, "decode_I : unhandled OT_x 0%x", (current.operands [i] & OT_MASK));
	}
}

void decode_J (struct ade32_struct *diza, int output, int i, unsigned long ip) {

	switch (current.operands[i] & OT_MASK) {
		case OT_b: add (output, "short 0%xh", (diza->op_data_c [0] + ip)); break;

		case OT_v: if (diza->op_flag & C_67) add (output, "short ");
			   else add (output, "near ");
			   add (output, "0%xh", (diza->op_data_l [0] + ip));
			   break;

		default: add (A_ERROR, "decode_J : unhandled OT_x 0%x", (current.operands [i] & OT_MASK));
	}
}

void decode_M (struct ade32_struct *diza, int output, int i) {
	u_modreg	modreg;

	modreg.data = diza->op_modrm;

	if (modreg.mod == 3) {
		kill_decode (); // is this correct ??!!
		return;
	} else {
		switch (current.operands[i] & OT_MASK) {
			case OT_a :
			case 0 :
			case OT_w :
			case OT_p :
			case OT_q :
			case OT_b :
			case OT_d : decode_E32 (diza, output, i); break;
			case OT_s :
			case OT_v : if (diza->op_flag & C_67) decode_E16 (diza, output, i);
				    else decode_E32 (diza, output, i);
				    break;

			default: add (A_ERROR, "decode_M: unhandled OT_x 0%x", (current.operands [i] & OT_MASK));
		}
	}
}

void decode_O (struct ade32_struct *diza, int output, int i) {
	switch (current.operands[i] & OT_MASK) {
		case OT_b:
		case OT_w:
		case OT_d:
		case OT_v: add (output, "[0%xh] ", diza->op_addr_d [0]); break;
		default: add (A_ERROR, "decode_O : unhandled OT_x 0%x", (current.operands [i] & OT_MASK));
	}
}

void decode_P (struct ade32_struct *diza, int output, int i) {
	u_modreg	modreg;

	modreg.data = diza->op_modrm;

		add (output, "%s", mm_tbl [modreg.reg]);
}

void decode_Q (struct ade32_struct *diza, int output, int i) {
	u_modreg	modreg;

	modreg.data = diza->op_modrm;

	if (modreg.mod == 3) {
		add (output, "%s", mm_tbl [modreg.rm]);
	} else {
		switch (current.operands[i] & OT_MASK) {
			case OT_w :
			case OT_p :
			case OT_q :
			case OT_b :
			case OT_d : decode_E32 (diza, output, i); break;
			case OT_v : if (diza->op_flag & C_67) decode_E16 (diza, output, i);
				    else decode_E32 (diza, output, i);
				    break;
			default: add (A_ERROR, "decode_M: unhandled OT_x 0%x", (current.operands [i] & OT_MASK));
		}
	}
}

void decode_R (struct ade32_struct *diza, int output, int i) {
	u_modreg	modreg;
	char		**names;

	modreg.data = diza->op_modrm;

	switch (current.operands[i] & OT_MASK) {
		case OT_b : names = reg8_tbl; break;
		case OT_w : names = reg16_tbl; break;
		case OT_d : names = reg32_tbl; break;
		case OT_v : if (diza->op_flag & C_66) names = reg16_tbl;
			    else names = reg32_tbl;
			    break;
		default: add (A_ERROR, "decode_M: unhandled OT_x 0%x", (current.operands [i] & OT_MASK));
			 return;
	}

	add (output, "%s", names [modreg.reg]);
}

void decode_S (struct ade32_struct *diza, int output, int i) {
	u_modreg	modreg;

	modreg.data = diza->op_modrm;

	add (output, "%s", seg_tbl [modreg.reg]);
}

void decode_T (struct ade32_struct *diza, int output, int i) {
	u_modreg	modreg;

	modreg.data = diza->op_modrm;

	add (output, "%s", tr_tbl [modreg.reg]);
}

void decode_V (struct ade32_struct *diza, int output, int i) {
	u_modreg	modreg;

	modreg.data = diza->op_modrm;

		add (output, "%s", xmm_tbl [modreg.reg]);
}

void decode_W (struct ade32_struct *diza, int output, int i) {
	u_modreg	modreg;

	modreg.data = diza->op_modrm;

	if (modreg.mod == 3) {
		add (output, "%s", xmm_tbl [modreg.rm]);
	} else {
		switch (current.operands[i] & OT_MASK) {
			case OT_w :
			case OT_p :
			case OT_q :
			case OT_b :
			case OT_d : decode_E32 (diza, output, i); break;
			case OT_v : if (diza->op_flag & C_67) decode_E16 (diza, output, i);
				    else decode_E32 (diza, output, i);
				    break;
			default: add (A_ERROR, "decode_M: unhandled OT_x 0%x", (current.operands [i] & OT_MASK));
		}
	}
}


void decode_am (struct ade32_struct *diza, int output, int i, unsigned long ip) {

	switch (current.operands[i] & AM_MASK) {

		case AM_A : decode_A (diza, output, i); break;
		case AM_C : decode_C (diza, output, i); break;
		case AM_D : decode_D (diza, output, i); break;
		case AM_E : decode_E (diza, output, i); break;
		case AM_F : break;
		case AM_G : decode_G (diza, output, i); break;
		case AM_I : decode_I (diza, output, i); break;
		case AM_J : decode_J (diza, output, i, ip); break;
		case AM_M : decode_M (diza, output, i); break;
		case AM_O : decode_O (diza, output, i); break;
		case AM_P : decode_P (diza, output, i); break;
		case AM_Q : decode_Q (diza, output, i); break;
		case AM_R : decode_R (diza, output, i); break;
		case AM_S : decode_S (diza, output, i); break;
		case AM_T : decode_T (diza, output, i); break; // ?? unable to find any test register description
		case AM_V : decode_V (diza, output, i); break;
		case AM_W : decode_W (diza, output, i); break;
		case AM_X : break;
		case AM_Y : break;
		case AM_3 : add (output, "3"); break;
		default : add (A_ERROR, "decode_am : unhandled AM_X 0%x", (current.operands [i] & AM_MASK));
	}
}

void decode_operands (struct ade32_struct *diza, unsigned long ip) {
	int	i;	// operand index
	int	output;

	i = 0;
	output = A_OP1;

	while (current.operands[i]) {

		if (current.operands[i] & R_MASK) {
			decode_register (diza, output, i);
		}

		if (current.operands[i] & AM_MASK) {
			decode_am (diza, output, i, ip);
		}
		i++;
		output++;
	}

	return;
}

void terminate_name (instr_name *name) {


	if (name->prefix_len) {
		name->prefix[name->prefix_len] = 0;
		name->prefix_len++;
	}


	if (name->name_len) {
		name->name [name->name_len] = 0;
		name->name_len ++;
	}

	if (name->operand1_len) {
		name->operand1 [name->operand1_len] = 0;
		name->operand1_len ++;
	}

	if (name->operand2_len) {
		name->operand2 [name->operand2_len] = 0;
		name->operand2_len ++;
	}

	if (name->operand3_len) {
		name->operand3 [name->operand3_len] = 0;
		name->operand3_len ++;
	}

}


int instr_decode (struct ade32_struct *diza, instr_name *name, unsigned long ip) {

	if (diza->op_len == 0) {		// nothing to decode
		return 0;
	}

	curr_name = name;

	decode_name (diza);
	decode_prefix (diza);

	if (current.name == NULL) return 0;

	decode_operands (diza, ip);

	if (current.name == NULL) return 0;

	terminate_name (name);

	return 1;
}

