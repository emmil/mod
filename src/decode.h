#include <stdio.h>

typedef struct {
	char		*name;
	unsigned long	operands [3];
	unsigned int	patch;
} s_instr;

typedef union {
	unsigned char	data;
	struct {
		unsigned char	rm:3;
		unsigned char	reg:3;
		unsigned char	mod:2;
	};
} u_modreg;

typedef union {
	unsigned char	data;
	struct {
		unsigned char	base:3;
		unsigned char	index:3;
		unsigned char	scale:2;
	};
} u_sib;

#define A_NAME		0
#define A_OP1		1
#define A_OP2		2
#define A_OP3		3
#define A_PREFIX	4
#define A_ERROR		5

#define AM_SHIFT	0x0
#define	AM_A	(1 << AM_SHIFT)
#define AM_C	(2 << AM_SHIFT)
#define AM_D	(3 << AM_SHIFT)
#define AM_E	(4 << AM_SHIFT)
#define AM_F	(5 << AM_SHIFT)
#define AM_G	(6 << AM_SHIFT)
#define AM_I	(7 << AM_SHIFT)
#define AM_J	(8 << AM_SHIFT)
#define AM_M	(9 << AM_SHIFT)
#define AM_O	(10 << AM_SHIFT)
#define AM_P	(11 << AM_SHIFT)
#define AM_Q	(12 << AM_SHIFT)
#define AM_R	(13 << AM_SHIFT)
#define AM_S	(14 << AM_SHIFT)
#define AM_T	(15 << AM_SHIFT)
#define AM_V	(16 << AM_SHIFT)
#define AM_W	(17 << AM_SHIFT)
#define AM_X	(18 << AM_SHIFT)
#define AM_Y	(19 << AM_SHIFT)
#define AM_3	(20 << AM_SHIFT)
#define AM_MASK	(0xFF << AM_SHIFT)

#define OT_SHIFT	0x8
#define OT_a	(1 << OT_SHIFT)
#define OT_b	(2 << OT_SHIFT)
#define OT_c	(3 << OT_SHIFT)
#define OT_d	(4 << OT_SHIFT)
#define OT_dq	(5 << OT_SHIFT)
#define OT_p	(6 << OT_SHIFT)
#define OT_pi	(7 << OT_SHIFT)
#define OT_ps	(8 << OT_SHIFT)
#define OT_q	(9 << OT_SHIFT)
#define OT_s	(10 << OT_SHIFT)
#define OT_ss	(11 << OT_SHIFT)
#define OT_si	(12 << OT_SHIFT)
#define OT_v	(13 << OT_SHIFT)
#define OT_w	(14 << OT_SHIFT)

#define OT_pd	(15 << OT_SHIFT)
#define OT_sd	(16 << OT_SHIFT)
#define OT_dp	(17 << OT_SHIFT)

#define OT_MASK	(0xFF << OT_SHIFT)

#define R_SHIFT		0x10
#define R_AL	(1 << R_SHIFT)
#define R_CL	(2 << R_SHIFT)
#define R_DL	(3 << R_SHIFT)
#define R_BL	(4 << R_SHIFT)
#define R_AH	(5 << R_SHIFT)
#define R_CH	(6 << R_SHIFT)
#define R_DH	(7 << R_SHIFT)
#define R_BH	(8 << R_SHIFT)
#define R_AX	(9 << R_SHIFT)
#define R_CX	(10 << R_SHIFT)
#define R_DX	(11 << R_SHIFT)
#define R_BX	(12 << R_SHIFT)
#define R_SP	(13 << R_SHIFT)
#define R_BP	(14 << R_SHIFT)
#define R_SI	(15 << R_SHIFT)
#define R_DI	(16 << R_SHIFT)
#define R_eAX	(17 << R_SHIFT)
#define R_eCX	(18 << R_SHIFT)
#define R_eDX	(19 << R_SHIFT)
#define R_eBX	(20 << R_SHIFT)
#define R_eSP	(21 << R_SHIFT)
#define R_eBP	(22 << R_SHIFT)
#define R_eSI	(23 << R_SHIFT)
#define R_eDI	(24 << R_SHIFT)
#define R_ES	(25 << R_SHIFT)
#define R_CS	(26 << R_SHIFT)
#define R_SS	(27 << R_SHIFT)
#define R_DS	(28 << R_SHIFT)
#define R_FS	(29 << R_SHIFT)
#define R_GS	(30 << R_SHIFT)
#define R_EAX	(31 << R_SHIFT)
#define R_ECX	(32 << R_SHIFT)
#define R_EDX	(33 << R_SHIFT)
#define R_EBX	(34 << R_SHIFT)
#define R_ESP	(35 << R_SHIFT)
#define R_EBP	(36 << R_SHIFT)
#define R_ESI	(37 << R_SHIFT)
#define R_EDI	(38 << R_SHIFT)
#define R_ALEAX	(39 << R_SHIFT)
#define R_STi	(40 << R_SHIFT)
#define R_ST0	(41 << R_SHIFT)
#define R_MASK	(0xFF << R_SHIFT)

#define AM_MIN		AM_A
#define AM_MAX		AM_3
#define R_MIN		R_AL
#define R_MAX		R_ST0
#define R_MIN8		R_AL
#define R_MAX8		R_BH
#define R_MIN16		R_AX
#define R_MAX16		R_DI
#define R_MINSEG	R_ES
#define R_MAXSEG	R_GS
#define R_MIN32		R_EAX
#define R_MAX32		R_EDI
#define R_eMIN		R_eAX
#define R_eMAX		R_eDI

//#define R_MIN		(R_AL)
//#define R_MAX		(R_ST0)

#define P_SHIFT	0
#define PG_1	(1 << P_SHIFT)
#define PG_2	(2 << P_SHIFT)
#define PG_3	(3 << P_SHIFT)
#define PG_4	(4 << P_SHIFT)
#define PG_5	(5 << P_SHIFT)
#define PG_6	(6 << P_SHIFT)
#define PG_7	(7 << P_SHIFT)
#define PG_8	(8 << P_SHIFT)
#define PG_9	(9 << P_SHIFT)
#define PG_10	(10 << P_SHIFT)
#define PG_11	(11 << P_SHIFT)
#define PG_12	(12 << P_SHIFT)
#define PG_13	(13 << P_SHIFT)
#define PG_14	(14 << P_SHIFT)
#define PG_15	(15 << P_SHIFT)
#define PG_16	(16 << P_SHIFT)

#define PG_MIN	(PG_1)
#define PG_MAX	(PG_16)

#define P66_60	(17 << P_SHIFT)		// pusha, pushad
#define P66_61	(18 << P_SHIFT)		// popa, popad
#define P66_6D	(19 << P_SHIFT)		// ins, insw, insd
#define P66_6F	(20 << P_SHIFT)		// outs, outsw, outsd
#define P66_98	(21 << P_SHIFT)		// cbw, cwde
#define P66_99	(22 << P_SHIFT)		// cwd, cdq
#define P66_9C	(23 << P_SHIFT)		// pushf, pushfd
#define P66_9D	(24 << P_SHIFT)		// popf, popfd
#define P66_A5	(25 << P_SHIFT)		// movs, movsw, movsd
#define P66_A7	(26 << P_SHIFT)		// cmps, cmpsw, cmpsd
#define P66_AB	(27 << P_SHIFT)		// stos, stosw, stosd
#define P66_AD  (28 << P_SHIFT)		// lods, lodsw, lodsd
#define P66_AF	(29 << P_SHIFT)		// scas, scasw, scasd

#define P66_MIN	(P66_60)
#define P66_MAX (P66_AF)

#define PFLOAT	(30 << P_SHIFT)
#define PPFLOAT_9D	(31 << P_SHIFT)
#define PPFLOAT_9E	(32 << P_SHIFT)
#define PPFLOAT_9F	(33 << P_SHIFT)
#define PPFLOAT_AE	(34 << P_SHIFT)
#define PPFLOAT_BE	(35 << P_SHIFT)
#define PPFLOAT_ED	(36 << P_SHIFT)
#define PPFLOAT_FE	(37 << P_SHIFT)
#define PMMX_10	(40 << P_SHIFT)
#define PMMX_11	(41 << P_SHIFT)
#define PMMX_12	(42 << P_SHIFT)
#define PMMX_13	(43 << P_SHIFT)
#define PMMX_14	(44 << P_SHIFT)
#define PMMX_15	(45 << P_SHIFT)
#define PMMX_16	(46 << P_SHIFT)
#define PMMX_17	(47 << P_SHIFT)
#define PMMX_28	(48 << P_SHIFT)
#define PMMX_29	(49 << P_SHIFT)
#define PMMX_2A	(50 << P_SHIFT)
#define PMMX_2B	(51 << P_SHIFT)
#define PMMX_2C	(52 << P_SHIFT)
#define PMMX_2D	(53 << P_SHIFT)
#define PMMX_2E	(54 << P_SHIFT)
#define PMMX_2F	(55 << P_SHIFT)
#define PMMX_50	(56 << P_SHIFT)
#define PMMX_51	(57 << P_SHIFT)
#define PMMX_52	(58 << P_SHIFT)
#define PMMX_53	(59 << P_SHIFT)
#define PMMX_54	(60 << P_SHIFT)
#define PMMX_55	(61 << P_SHIFT)
#define PMMX_56	(62 << P_SHIFT)
#define PMMX_57	(63 << P_SHIFT)
#define PMMX_58	(64 << P_SHIFT)
#define PMMX_59	(65 << P_SHIFT)
#define PMMX_5A	(66 << P_SHIFT)
#define PMMX_5B	(67 << P_SHIFT)
#define PMMX_5C	(68 << P_SHIFT)
#define PMMX_5D	(69 << P_SHIFT)
#define PMMX_5E	(70 << P_SHIFT)
#define PMMX_5F	(71 << P_SHIFT)
#define PMMX_60	(72 << P_SHIFT)
#define PMMX_61	(73 << P_SHIFT)
#define PMMX_62	(74 << P_SHIFT)
#define PMMX_63	(75 << P_SHIFT)
#define PMMX_64	(76 << P_SHIFT)
#define PMMX_65	(77 << P_SHIFT)
#define PMMX_66	(78 << P_SHIFT)
#define PMMX_67	(79 << P_SHIFT)
#define PMMX_68	(80 << P_SHIFT)
#define PMMX_69	(81 << P_SHIFT)
#define PMMX_6A	(82 << P_SHIFT)
#define PMMX_6B	(83 << P_SHIFT)
#define PMMX_6C	(84 << P_SHIFT)
#define PMMX_6D	(85 << P_SHIFT)
#define PMMX_6E	(86 << P_SHIFT)
#define PMMX_6F	(87 << P_SHIFT)
#define PMMX_70	(88 << P_SHIFT)
#define PMMX_74	(89 << P_SHIFT)
#define PMMX_75	(90 << P_SHIFT)
#define PMMX_76	(91 << P_SHIFT)
#define PMMX_7E	(92 << P_SHIFT)
#define PMMX_7F	(93 << P_SHIFT)
#define PMMX_C2	(94 << P_SHIFT)
#define PMMX_C4	(95 << P_SHIFT)
#define PMMX_C5	(96 << P_SHIFT)
#define PMMX_C6	(97 << P_SHIFT)
#define PMMX_D1	(98 << P_SHIFT)
#define PMMX_D2	(99 << P_SHIFT)
#define PMMX_D3	(100 << P_SHIFT)
#define PMMX_D4	(101 << P_SHIFT)
#define PMMX_D5	(102 << P_SHIFT)
#define PMMX_D6	(103 << P_SHIFT)
#define PMMX_D7	(104 << P_SHIFT)
#define PMMX_D8	(105 << P_SHIFT)
#define PMMX_D9	(106 << P_SHIFT)
#define PMMX_DA	(107 << P_SHIFT)
#define PMMX_DB	(108 << P_SHIFT)
#define PMMX_DC	(109 << P_SHIFT)
#define PMMX_DD	(110 << P_SHIFT)
#define PMMX_DE	(111 << P_SHIFT)
#define PMMX_DF	(112 << P_SHIFT)
#define PMMX_E0	(113 << P_SHIFT)
#define PMMX_E1	(114 << P_SHIFT)
#define PMMX_E2	(115 << P_SHIFT)
#define PMMX_E3	(116 << P_SHIFT)
#define PMMX_E4	(117 << P_SHIFT)
#define PMMX_E5	(118 << P_SHIFT)
#define PMMX_E6	(119 << P_SHIFT)
#define PMMX_E7	(120 << P_SHIFT)
#define PMMX_E8	(121 << P_SHIFT)
#define PMMX_E9	(122 << P_SHIFT)
#define PMMX_EA	(123 << P_SHIFT)
#define PMMX_EB	(124 << P_SHIFT)
#define PMMX_EC	(125 << P_SHIFT)
#define PMMX_ED	(126 << P_SHIFT)
#define PMMX_EE	(127 << P_SHIFT)
#define PMMX_EF	(128 << P_SHIFT)
#define PMMX_F1	(129 << P_SHIFT)
#define PMMX_F2	(130 << P_SHIFT)
#define PMMX_F3	(131 << P_SHIFT)
#define PMMX_F4	(132 << P_SHIFT)
#define PMMX_F5	(133 << P_SHIFT)
#define PMMX_F6	(134 << P_SHIFT)
#define PMMX_F7	(135 << P_SHIFT)
#define PMMX_F8	(136 << P_SHIFT)
#define PMMX_F9	(137 << P_SHIFT)
#define PMMX_FA	(138 << P_SHIFT)
#define PMMX_FB	(139 << P_SHIFT)
#define PMMX_FC	(140 << P_SHIFT)
#define PMMX_FD	(141 << P_SHIFT)
#define PMMX_FE	(142 << P_SHIFT)
#define PMMX_G122	(143 << P_SHIFT)
#define PMMX_G124	(144 << P_SHIFT)
#define PMMX_G126	(145 << P_SHIFT)
#define PMMX_G132	(146 << P_SHIFT)
#define PMMX_G134	(147 << P_SHIFT)
#define PMMX_G136	(148 << P_SHIFT)
#define PMMX_G142	(149 << P_SHIFT)
#define PMMX_G143	(150 << P_SHIFT)
#define PMMX_G146	(151 << P_SHIFT)
#define PMMX_G147	(152 << P_SHIFT)

#define	PMMX_MAX	PMMX_G147
#define PMMX_MIN	PMMX_10

#define P_MASK	(0xFF << P_SHIFT)

#define Ap	(AM_A | OT_p)
#define Cd	(AM_C | OT_d)
#define	Dd	(AM_D | OT_d)
#define Eb	(AM_E | OT_b)
#define Ed	(AM_E | OT_d)
#define Ep	(AM_E | OT_p)
#define Eq	(AM_E | OT_q)
#define Ev	(AM_E | OT_v)
#define Ew	(AM_E | OT_w)
#define Fv	(AM_F | OT_v)
#define Gb	(AM_G | OT_b)
#define Gd	(AM_G | OT_d)
#define Gv	(AM_G | OT_v)
#define Gw	(AM_G | OT_w)
#define Ib	(AM_I | OT_b)
#define Iv	(AM_I | OT_v)
#define Iw	(AM_I | OT_w)
#define Jb	(AM_J | OT_b)
#define Jv	(AM_J | OT_v)
#define Ma	(AM_M | OT_a)
#define Mb	(AM_M | OT_b)
#define Ms	(AM_M | OT_s)
#define Mq	(AM_M | OT_q)
#define Mp	(AM_M | OT_p)
#define Ob	(AM_O | OT_b)
#define Ov	(AM_O | OT_v)
#define Pd	(AM_P | OT_d)
#define Pdq	(AM_P | OT_dq)
#define Pq	(AM_P | OT_q)
#define Ppi	(AM_P | OT_pi)
#define Qd	(AM_Q | OT_d)
#define Qdq	(AM_Q | OT_dq)
#define Qq	(AM_Q | OT_q)
#define Qpi	(AM_Q | OT_pi)
#define Rd	(AM_R | OT_d)
#define Sw	(AM_S | OT_w)
#define Td	(AM_T | OT_d)
#define Vq	(AM_V | OT_q)
#define Vdq	(AM_V | OT_dq)
#define Vpd	(AM_V | OT_pd)
#define Vps	(AM_V | OT_ps)
#define Vsd	(AM_V | OT_sd)
#define Vss	(AM_V | OT_ss)
#define Wdp	(AM_W | OT_dp)
#define Wdq	(AM_W | OT_dq)
#define Wq	(AM_W | OT_q)
#define Wpd	(AM_W | OT_pd)
#define Wps	(AM_W | OT_ps)
#define Ws	(AM_W | OT_s)
#define Wsd	(AM_W | OT_sd)
#define Wss	(AM_W | OT_ss)
#define Xb	(AM_X | OT_b)
#define Xv	(AM_X | OT_v)
#define Yb	(AM_Y | OT_b)
#define Yv	(AM_Y | OT_v)
#define XX	0

#define RR16_SHIFT	0x0
#define RR16_MASK	(0xF << RR16_SHIFT)
#define	RR16_BXSI	(1 << RR16_SHIFT)
#define RR16_BXDI	(2 << RR16_SHIFT)
#define RR16_BPSI	(3 << RR16_SHIFT)
#define RR16_BPDI	(4 << RR16_SHIFT)
#define RR16_SI		(5 << RR16_SHIFT)
#define	RR16_DI		(6 << RR16_SHIFT)
#define RR16_BP		(7 << RR16_SHIFT)
#define RR16_BX		(8 << RR16_SHIFT)

#define RD16_SHIFT	0x4
#define RD16_MASK	(0xF << RD16_SHIFT)
#define RD16_DISP8	(1 << RD16_SHIFT)
#define RD16_DISP16	(2 << RD16_SHIFT)

#define RR32_SHIFT	0x0
#define RR32_MASK	(0xF << RR32_SHIFT)
#define RR32_EAX	(1 << RR32_SHIFT)
#define RR32_ECX	(2 << RR32_SHIFT)
#define RR32_EDX	(3 << RR32_SHIFT)
#define RR32_EBX	(4 << RR32_SHIFT)
#define RR32_SIB	(5 << RR32_SHIFT)
#define RR32_EBP	(6 << RR32_SHIFT)
#define RR32_ESI	(7 << RR32_SHIFT)
#define RR32_EDI	(8 << RR32_SHIFT)

#define RD32_SHIFT	0x4
#define RD32_MASK	(0xF << RD32_SHIFT)
#define RD32_DISP8	(1 << RD32_SHIFT)
#define RD32_DISP32	(2 << RD32_SHIFT)

#define SR_SHIFT	0x0
#define SR_MASK	(0xF << SR_SHIFT)
#define SR_EAX	(1 << SR_SHIFT)
#define SR_ECX	(2 << SR_SHIFT)
#define SR_EDX	(3 << SR_SHIFT)
#define SR_EBX	(4 << SR_SHIFT)
#define SR_NONE	(5 << SR_SHIFT)
#define SR_EBP	(6 << SR_SHIFT)
#define SR_ESI	(7 << SR_SHIFT)
#define SR_EDI	(8 << SR_SHIFT)

#define SM_SHIFT	0x4
#define SM_MASK	(0xF << SM_SHIFT)
#define SM_2	(1 << SM_SHIFT)
#define SM_4	(2 << SM_SHIFT)
#define SM_8	(3 << SM_SHIFT)


s_instr	ins_list [512] = {
// one byte instructions

// 00
		{"add",		{Eb, Gb, XX}, 0}, 	// 00
		{"add",		{Ev, Gv, XX}, 0}, 	// 01
		{"add",		{Gb, Eb, XX}, 0}, 	// 02
		{"add",		{Gv, Ev, XX}, 0}, 	// 03
		{"add",		{R_AL, Ib, XX}, 0}, 	// 04
		{"add",		{R_eAX, Iv, XX}, 0}, 	// 05
		{"push",	{R_ES, XX, XX}, 0}, 	// 06
		{"pop",		{R_ES, XX, XX}, 0}, 	// 07
		{"or",		{Eb, Gb, XX}, 0}, 	// 08
		{"or", 		{Ev, Gv, XX}, 0}, 	// 09
		{"or",		{Gb, Eb, XX}, 0}, 	// 0A
		{"or",		{Gv, Ev, XX}, 0}, 	// 0B
		{"or",		{R_AL, Ib, XX}, 0}, 	// 0C
		{"or",		{R_eAX, Iv, XX}, 0}, 	// 0D
		{"push",	{R_CS, XX, XX}, 0}, 	// 0E
		{"*escape*",	{XX, XX, XX}, 0}, 	// 0F
// 10
		{"adc",		{Eb, Gb, XX}, 0}, 	// 10
		{"adc",		{Ev, Gv, XX}, 0}, 	// 11
		{"adc",		{Gb, Eb, XX}, 0}, 	// 12
		{"adc",		{Gv, Ev, XX}, 0}, 	// 13
		{"adc",		{R_AL, Ib, XX}, 0}, 	// 14
		{"adc",		{R_eAX, Iv, XX}, 0}, 	// 15
		{"push",	{R_ES, XX, XX}, 0}, 	// 16
		{"pop",		{R_ES, XX, XX}, 0}, 	// 17
		{"sbb",		{Eb, Gb, XX}, 0}, 	// 18
		{"sbb",		{Ev, Gv, XX}, 0}, 	// 19
		{"sbb", 	{Gb, Eb, XX}, 0}, 	// 1A
		{"sbb",		{Gv, Ev, XX}, 0}, 	// 1B
		{"sbb",		{R_AL, Ib, XX}, 0}, 	// 1C
		{"sbb",		{R_eAX, Iv, XX}, 0}, 	// 1D
		{"push",	{R_DS, XX, XX}, 0}, 	// 1E
		{"pop",		{R_DS, XX, XX}, 0}, 	// 1F
// 20
		{"and",		{Eb, Gb, XX}, 0}, 	// 20
		{"and",		{Ev, Gv, XX}, 0}, 	// 21
		{"and",		{Gb, Eb, XX}, 0}, 	// 22
		{"and",		{Gv, Ev, XX}, 0}, 	// 23
		{"and",		{R_AL, Ib, XX}, 0}, 	// 24
		{"and",		{R_eAX, Iv, XX}, 0}, 	// 25
		{"es:",		{XX, XX, XX}, 0}, 	// 26
		{"daa",		{XX, XX, XX}, 0}, 	// 27
		{"sub",		{Eb, Gb, XX}, 0}, 	// 28
		{"sub",		{Ev, Gv, XX}, 0}, 	// 29
		{"sub",		{Gb, Eb, XX}, 0}, 	// 2A
		{"sub",		{Gv, Ev, XX}, 0}, 	// 2B
		{"sub",		{R_AL, Ib, XX}, 0}, 	// 2C
		{"sub",		{R_eAX, Iv, XX}, 0}, 	// 2D
		{"cs:",		{XX, XX, XX}, 0}, 	// 2E
		{"das",		{XX, XX, XX}, 0}, 	// 2F
// 30
		{"xor",		{Eb, Gb, XX}, 0}, 	// 30
		{"xor",		{Ev, Gv, XX}, 0}, 	// 31
		{"xor",		{Gb, Eb, XX}, 0}, 	// 32
		{"xor",		{Gv, Ev, XX}, 0}, 	// 33
		{"xor",		{R_AL, Ib, XX}, 0}, 	// 34
		{"xor",		{R_eAX, Iv, XX}, 0}, 	// 35
		{"ss:",		{XX, XX, XX}, 0}, 	// 36
		{"aaa",		{XX, XX, XX}, 0}, 	// 37
		{"cmp",		{Eb, Gb, XX}, 0}, 	// 38
		{"cmp",		{Ev, Gv, XX}, 0}, 	// 39
		{"cmp",		{Gb, Eb, XX}, 0}, 	// 3A
		{"cmp",		{Gv, Ev, XX}, 0}, 	// 3B
		{"cmp",		{R_AL, Ib, XX}, 0}, 	// 3C
		{"cmp",		{R_eAX, Iv, XX}, 0}, 	// 3D
		{"ds:",		{XX, XX, XX}, 0}, 	// 3E
		{"aas",		{XX, XX, XX}, 0}, 	// 3F
// 40
		{"inc",		{R_eAX, XX, XX}, 0}, 	// 40
		{"inc",		{R_eCX, XX, XX}, 0}, 	// 41
		{"inc",		{R_eDX, XX, XX}, 0}, 	// 42
		{"inc",		{R_eBX, XX, XX}, 0}, 	// 43
		{"inc",		{R_eSP, XX, XX}, 0}, 	// 44
		{"inc",		{R_eBP, XX, XX}, 0}, 	// 45
		{"inc",		{R_eSI, XX, XX}, 0}, 	// 46
		{"inc",		{R_eDI, XX, XX}, 0}, 	// 47
		{"dec",		{R_eAX, XX, XX}, 0}, 	// 48
		{"dec",		{R_eCX, XX, XX}, 0}, 	// 49
		{"dec",		{R_eDX, XX, XX}, 0}, 	// 4A
		{"dec",		{R_eBX, XX, XX}, 0}, 	// 4B
		{"dec",		{R_eSP, XX, XX}, 0}, 	// 4C
		{"dec",		{R_eBP, XX, XX}, 0}, 	// 4D
		{"dec",		{R_eSI, XX, XX}, 0}, 	// 4E
		{"dec",		{R_eDI, XX, XX}, 0}, 	// 4F

// 50
		{"push",	{R_eAX, XX, XX}, 0}, 	// 50
		{"push",	{R_eCX, XX, XX}, 0}, 	// 51
		{"push",	{R_eDX, XX, XX}, 0}, 	// 52
		{"push",	{R_eBX, XX, XX}, 0}, 	// 53
		{"push",	{R_eSP, XX, XX}, 0}, 	// 54
		{"push",	{R_eBP, XX, XX}, 0}, 	// 55
		{"push",	{R_eSI, XX, XX}, 0}, 	// 56
		{"push",	{R_eDI, XX, XX}, 0}, 	// 57
		{"pop",		{R_eAX, XX, XX}, 0}, 	// 58
		{"pop",		{R_eCX, XX, XX}, 0}, 	// 59
		{"pop",		{R_eDX, XX, XX}, 0}, 	// 5A
		{"pop",		{R_eBX, XX, XX}, 0}, 	// 5B
		{"pop",		{R_eSP, XX, XX}, 0}, 	// 5C
		{"pop",		{R_eBP, XX, XX}, 0}, 	// 5D
		{"pop",		{R_eSI, XX, XX}, 0}, 	// 5E
		{"pop",		{R_eDI, XX, XX}, 0}, 	// 5F
// 60
		{NULL, 		{XX, XX, XX}, P66_60},	// 60 pusha, pushd
		{NULL,		{XX, XX, XX}, P66_61}, 	// 61 popa, popd
		{"bound",	{Gv, Ma, XX}, 0}, 	// 62
		{"arpl",	{Ew, Gw, XX}, 0}, 	// 63
		{"fs:",		{XX, XX, XX}, 0}, 	// 64
		{"gs:",		{XX, XX, XX}, 0}, 	// 65
		{"*opd size*",	{XX, XX, XX}, 0}, 	// 66
		{"*addr size*",	{XX, XX, XX}, 0}, 	// 67
		{"push",	{Iv, XX, XX}, 0}, 	// 68
		{"imul",	{Gv, Ev, Iv}, 0}, 	// 69
		{"push",	{Ib, XX, XX}, 0}, 	// 6A
		{"imul",	{Gv, Ev, Ib}, 0}, 	// 6B
		{"insb",	{XX, XX, XX}, 0}, 	// 6C
		{NULL,		{XX, XX, XX}, P66_6D}, 	// 6D insw, insd
		{"outsb",	{XX, XX, XX}, 0}, 	// 6E
		{NULL,		{XX, XX, XX}, P66_6F}, 	// 6F outsw, outsd

// 70
		{"jo",		{Jb, XX, XX}, 0}, 	// 70
		{"jno",		{Jb, XX, XX}, 0}, 	// 71
		{"jb",		{Jb, XX, XX}, 0}, 	// 72
		{"jnb",		{Jb, XX, XX}, 0}, 	// 73
		{"je",		{Jb, XX, XX}, 0}, 	// 74
		{"jne",		{Jb, XX, XX}, 0}, 	// 75
		{"jna",		{Jb, XX, XX}, 0}, 	// 76
		{"ja",		{Jb, XX, XX}, 0}, 	// 77
		{"js",		{Jb, XX, XX}, 0}, 	// 78
		{"jns",		{Jb, XX, XX}, 0}, 	// 79
		{"jp",		{Jb, XX, XX}, 0}, 	// 7A
		{"jnp",		{Jb, XX, XX}, 0}, 	// 7B
		{"jnge",	{Jb, XX, XX}, 0}, 	// 7C
		{"jge",		{Jb, XX, XX}, 0}, 	// 7D
		{"jle",		{Jb, XX, XX}, 0}, 	// 7E
		{"jnle",	{Jb, XX, XX}, 0}, 	// 7F
// 80
		{NULL,		{Eb, Ib, XX}, PG_1}, 	// 80
		{NULL,		{Ev, Iv, XX}, PG_1}, 	// 81
		{NULL,		{Eb, Ib, XX}, PG_1}, 	// 82
		{NULL,		{Ev, Ib, XX}, PG_1}, 	// 83
		{"test",	{Eb, Gb, XX}, 0}, 	// 84
		{"test",	{Ev, Gv, XX}, 0}, 	// 85
		{"xchg",	{Eb, Gb, XX}, 0}, 	// 86
		{"xchg",	{Ev, Gv, XX}, 0}, 	// 87
		{"mov",		{Eb, Gb, XX}, 0}, 	// 88
		{"mov",		{Ev, Gv, XX}, 0}, 	// 89
		{"mov",		{Gb, Eb, XX}, 0}, 	// 8A
		{"mov",		{Gv, Ev, XX}, 0}, 	// 8B
		{"mov",		{Ew, Sw, XX}, 0}, 	// 8C
		{"lea",		{Gv, AM_M, XX}, 0}, 	// 8D
		{"mov",		{Sw, Ew, XX}, 0}, 	// 8E
		{"pop",		{Ev, XX, XX}, 0}, 	// 8F
// 90
		{"nop",		{XX, XX, XX}, 0}, 	// 90
		{"xchg",	{R_eAX, R_eCX, XX}, 0}, // 91
		{"xchg",	{R_eAX, R_eDX, XX}, 0}, // 92
		{"xchg",	{R_eAX, R_eBX, XX}, 0}, // 93
		{"xchg",	{R_eAX, R_eSP, XX}, 0}, // 94
		{"xchg",	{R_eAX, R_eBP, XX}, 0}, // 95
		{"xchg",	{R_eAX, R_eSI, XX}, 0}, // 96
		{"xchg",	{R_eAX, R_eDI, XX}, 0}, // 97
		{NULL,		{XX, XX, XX}, P66_98}, 	// 98	cbw, cwde
		{NULL,		{XX, XX, XX}, P66_99}, 	// 99	cwd, cdq
		{"callf",	{Ap, XX, XX}, 0}, 	// 9A
		{"wait",	{XX, XX, XX}, 0}, 	// 9B
		{NULL,		{Fv, XX, XX}, P66_9C}, 	// 9C	pushf, pushfd
		{NULL,		{Fv, XX, XX}, P66_9D}, 	// 9D	popf, popfd
		{"sahf",	{XX, XX, XX}, 0}, 	// 9E
		{"lahf",	{XX, XX, XX}, 0}, 	// 9F
// A0
		{"mov",		{R_AL, Ob, XX}, 0}, 	// A0
		{"mov",		{R_eAX, Ov, XX}, 0}, 	// A1
		{"mov",		{Ob, R_AL, XX}, 0}, 	// A2
		{"mov",		{Ov, R_eAX, XX}, 0}, 	// A3
		{"movsb",	{Yb, Xb, XX}, 0}, 	// A4
		{NULL,		{Yv, Xv, XX}, P66_A5}, 	// A5	movsw, movsd
		{"cmpsb",	{Yb, Xb, XX}, 0}, 	// A6
		{NULL,		{Xv, Yv, XX}, P66_A7}, 	// A7	cmpsw, cmpsd
		{"test",	{R_AL, Ib, XX}, 0}, 	// A8
		{"test",	{R_eAX, Iv, XX}, 0}, 	// A9
		{"stosb",	{XX, XX, XX}, 0}, 	// AA
		{NULL,		{Yv, XX, XX}, P66_AB},	// AB	stosw, stosd
		{"lodsb",	{XX, XX, XX}, 0}, 	// AC
		{NULL,		{XX, XX, XX}, P66_AD},	// AD	lodsw, lodsd
		{"scasb",	{XX, XX, XX}, 0}, 	// AE
		{NULL,		{XX, XX, XX}, P66_AF},	// AF	scasw, scasd
// B0
		{"mov",		{R_AL, Ib, XX}, 0}, 	// B0
		{"mov",		{R_CL, Ib, XX}, 0}, 	// B1
		{"mov",		{R_DL, Ib, XX}, 0}, 	// B2
		{"mov",		{R_BL, Ib, XX}, 0}, 	// B3
		{"mov",		{R_AH, Ib, XX}, 0}, 	// B4
		{"mov",		{R_CH, Ib, XX}, 0}, 	// B5
		{"mov",		{R_DH, Ib, XX}, 0}, 	// B6
		{"mov",		{R_BH, Ib, XX}, 0}, 	// B7
		{"mov",		{R_eAX, Iv, XX}, 0}, 	// B8
		{"mov",		{R_eCX, Iv, XX}, 0}, 	// B9
		{"mov",		{R_eDX, Iv, XX}, 0}, 	// BA
		{"mov",		{R_eBX, Iv, XX}, 0}, 	// BB
		{"mov",		{R_eSP, Iv, XX}, 0}, 	// BC
		{"mov",		{R_eBP, Iv, XX}, 0}, 	// BD
		{"mov",		{R_eSI, Iv, XX}, 0}, 	// BE
		{"mov",		{R_eDI, Iv, XX}, 0}, 	// BF
// C0
		{NULL,		{Eb, Ib, XX}, PG_2}, 	// C0
		{NULL,		{Ev, Ib, XX}, PG_2}, 	// C1
		{"ret",		{Iw, XX, XX}, 0}, 	// C2
		{"ret",		{XX, XX, XX}, 0}, 	// C3
		{"les",		{Gv, Mp, XX}, 0}, 	// C4
		{"lds",		{Gv, Mp, XX}, 0}, 	// C5
		{NULL,		{Eb, Ib, XX}, PG_11}, 	// C6
		{NULL,		{Ev, Iv, XX}, PG_11}, 	// C7
		{"enter",	{Iw, Ib, XX}, 0}, 	// C8
		{"leave",	{XX, XX, XX}, 0}, 	// C9
		{"retf",	{Iw, XX, XX}, 0}, 	// CA
		{"retf",	{XX, XX, XX}, 0}, 	// CB
		{"int",		{AM_3, XX, XX}, 0}, 	// CC
		{"int",		{Ib, XX, XX}, 0}, 	// CD
		{"into",	{XX, XX, XX}, 0}, 	// CE
		{"iret",	{XX, XX, XX}, 0}, 	// CF
// D0
		{NULL,		{Eb, XX, XX}, PG_2}, 	// D0
		{NULL,		{Ev, XX, XX}, PG_2}, 	// D1
		{NULL,		{Eb, R_CL, XX}, PG_2}, 	// D2
		{NULL,		{Ev, R_CL, XX}, PG_2}, 	// D3
		{"aam",		{Ib, XX, XX}, 0}, 	// D4
		{"aad",		{Ib, XX, XX}, 0}, 	// D5
		{"salc",	{XX, XX, XX}, 0}, 	// D6
		{"xlatb",	{XX, XX, XX}, 0}, 	// D7

// escape to coprocessor instruction set
		{NULL,		{XX, XX, XX}, PFLOAT}, 	// D8
		{NULL,		{XX, XX, XX}, PFLOAT}, 	// D9
		{NULL,		{XX, XX, XX}, PFLOAT}, 	// DA
		{NULL,		{XX, XX, XX}, PFLOAT}, 	// DB
		{NULL,		{XX, XX, XX}, PFLOAT}, 	// DC
		{NULL,		{XX, XX, XX}, PFLOAT}, 	// DD
		{NULL,		{XX, XX, XX}, PFLOAT}, 	// DE
		{NULL,		{XX, XX, XX}, PFLOAT}, 	// DF
// E0
		{"loopnz",	{Jb, XX, XX}, 0}, 	// E0
		{"loopz",	{Jb, XX, XX}, 0}, 	// E1
		{"loop",	{Jb, XX, XX}, 0}, 	// E2
		{"jcxz",	{Jb, XX, XX}, 0}, 	// E3
		{"in",		{R_AL, Ib, XX}, 0}, 	// E4
		{"in",		{R_eAX, Ib, XX}, 0}, 	// E5
		{"out",		{Ib, R_AL, XX}, 0}, 	// E6
		{"out",		{Ib, R_eAX, XX}, 0}, 	// E7
		{"call",	{Jv, XX, XX}, 0}, 	// E8
		{"jmp",		{Jv, XX, XX}, 0}, 	// E9
		{"jmp",		{Ap, XX, XX}, 0}, 	// EA
		{"jmp",		{Jb, XX, XX}, 0}, 	// EB
		{"in",		{R_AL, R_DX, XX}, 0}, 	// EC
		{"in",		{R_eAX, R_DX, XX}, 0}, 	// ED
		{"out",		{R_DX, R_AL, XX}, 0}, 	// EE
		{"out",		{R_DX, R_eAX, XX}, 0}, 	// EF
// F0
		{"lock",	{XX, XX, XX}, 0}, 	// F0
		{NULL,		{XX, XX, XX}, 0}, 	// F1
		{"repne",	{XX, XX, XX}, 0}, 	// F2
		{"rep",		{XX, XX, XX}, 0}, 	// F3
		{"hlt",		{XX, XX, XX}, 0}, 	// F4
		{"cmc",		{XX, XX, XX}, 0}, 	// F5
		{NULL,		{Eb, XX, XX}, PG_3}, 	// F6
		{NULL,		{Ev, XX, XX}, PG_3}, 	// F7
		{"clc",		{XX, XX, XX}, 0}, 	// F8
		{"stc",		{XX, XX, XX}, 0}, 	// F9
		{"cli",		{XX, XX, XX}, 0}, 	// FA
		{"sti",		{XX, XX, XX}, 0}, 	// FB
		{"cld",		{XX, XX, XX}, 0}, 	// FC
		{"std",		{XX, XX, XX}, 0}, 	// FD
		{NULL,		{XX, XX, XX}, PG_4}, 	// FE
		{NULL,		{XX, XX, XX}, PG_5}, 	// FF

// two byte instructions

// 0F00
		{NULL,		{XX, XX, XX}, PG_6}, 	// 0F00
		{NULL,		{XX, XX, XX}, PG_7}, 	// 0F01
		{"lar",		{Gv, Ew, XX}, 0}, 	// 0F02
		{"lsl",		{Gv, Ew, XX}, 0}, 	// 0F03
		{NULL,		{XX, XX, XX}, 0}, 	// 0F04
		{NULL,		{XX, XX, XX}, 0}, 	// 0F05
		{"clts",	{XX, XX, XX}, 0}, 	// 0F06
		{NULL,		{XX, XX, XX}, 0}, 	// 0F07
		{"invd",	{XX, XX, XX}, 0}, 	// 0F08
		{"wbinvd",	{XX, XX, XX}, 0}, 	// 0F09
		{NULL,		{XX, XX, XX}, 0}, 	// 0F0A
		{"ud2",		{XX, XX, XX}, 0}, 	// 0F0B // ??? 2-byte illegal opcodes UD2 ???
		{NULL,		{XX, XX, XX}, 0}, 	// 0F0C
		{NULL,		{XX, XX, XX}, 0}, 	// 0F0D
		{NULL,		{XX, XX, XX}, 0}, 	// 0F0E
		{NULL,		{XX, XX, XX}, 0}, 	// 0F0F
// 0F10
		{NULL,		{XX, XX, XX}, PMMX_10}, // 0F10
		{NULL,		{XX, XX, XX}, PMMX_11}, // 0F11
		{NULL,		{XX, XX, XX}, PMMX_12}, // 0F12
		{NULL,		{XX, XX, XX}, PMMX_13}, // 0F13
		{NULL,		{XX, XX, XX}, PMMX_14}, // 0F14
		{NULL,		{XX, XX, XX}, PMMX_15}, // 0F15
		{NULL,		{XX, XX, XX}, PMMX_16}, // 0F16
		{NULL,		{XX, XX, XX}, PMMX_17}, // 0F17
		{NULL,		{XX, XX, XX}, PG_16}, 	// 0F18	?? prefetch??
		{NULL,		{XX, XX, XX}, 0}, 	// 0F19
		{NULL,		{XX, XX, XX}, 0}, 	// 0F1A
		{NULL,		{XX, XX, XX}, 0}, 	// 0F1B
		{NULL,		{XX, XX, XX}, 0}, 	// 0F1C
		{NULL,		{XX, XX, XX}, 0}, 	// 0F1D
		{NULL,		{XX, XX, XX}, 0}, 	// 0F1E
		{NULL,		{XX, XX, XX}, 0}, 	// 0F1F
// 0F20
		{"mov",		{Rd, Cd, XX}, 0}, 	// 0F20
		{"mov",		{Rd, Dd, XX}, 0}, 	// 0F21
		{"mov",		{Cd, Rd, XX}, 0}, 	// 0F22
		{"mov",		{Dd, Rd, XX}, 0}, 	// 0F23
		{"mov",		{Rd, Td, XX}, 0}, 	// 0F24	// mov Rd, Td not suported now
		{NULL,		{XX, XX, XX}, 0}, 	// 0F25
		{"mov",		{Td, Rd, XX}, 0}, 	// 0F26	// mov Td, Rd not supported any more
		{NULL,		{XX, XX, XX}, 0}, 	// 0F27
		{NULL,		{XX, XX, XX}, PMMX_28}, // 0F28
		{NULL,		{XX, XX, XX}, PMMX_29}, // 0F29
		{NULL,		{XX, XX, XX}, PMMX_2A}, // 0F2A
		{NULL,		{XX, XX, XX}, PMMX_2B}, // 0F2B
		{NULL,		{XX, XX, XX}, PMMX_2C}, // 0F2C
		{NULL,		{XX, XX, XX}, PMMX_2D}, // 0F2D
		{NULL,		{XX, XX, XX}, PMMX_2E}, // 0F2E
		{NULL,		{XX, XX, XX}, PMMX_2F}, // 0F2F
// 0F30
		{"wrmsr",	{XX, XX, XX}, 0}, 	// 0F30
		{"rdtsc",	{XX, XX, XX}, 0}, 	// 0F31
		{"rdmsr",	{XX, XX, XX}, 0}, 	// 0F32
		{"rdpmc",	{XX, XX, XX}, 0}, 	// 0F33
		{"sysenter",	{XX, XX, XX}, 0}, 	// 0F34
		{"sysexit",	{XX, XX, XX}, 0}, 	// 0F35
		{NULL,		{XX, XX, XX}, 0}, 	// 0F36
		{NULL,		{XX, XX, XX}, 0}, 	// 0F37
		{NULL,		{XX, XX, XX}, 0}, 	// 0F38
		{NULL,		{XX, XX, XX}, 0}, 	// 0F39
		{NULL,		{XX, XX, XX}, 0}, 	// 0F3A
		{NULL,		{XX, XX, XX}, 0}, 	// 0F3B
		{"movnti",	{Gv, Ev, XX}, 0}, 	// 0F3C
		{NULL,		{XX, XX, XX}, 0}, 	// 0F3D
		{NULL,		{XX, XX, XX}, 0}, 	// 0F3E
		{NULL,		{XX, XX, XX}, 0}, 	// 0F3F
// 0F40
		{"cmovo",	{Gv, Ev, XX}, 0}, 	// 0F40
		{"cmovno",	{Gv, Ev, XX}, 0}, 	// 0F41
		{"cmovb",	{Gv, Ev, XX}, 0}, 	// 0F42
		{"cmovnb",	{Gv, Ev, XX}, 0}, 	// 0F43
		{"cmove",	{Gv, Ev, XX}, 0}, 	// 0F44
		{"cmovne",	{Gv, Ev, XX}, 0}, 	// 0F45
		{"cmovna",	{Gv, Ev, XX}, 0}, 	// 0F46
		{"cmova",	{Gv, Ev, XX}, 0}, 	// 0F47
		{"cmovs",	{Gv, Ev, XX}, 0}, 	// 0F48
		{"cmovns",	{Gv, Ev, XX}, 0}, 	// 0F49
		{"cmovp",	{Gv, Ev, XX}, 0}, 	// 0F4A
		{"cmovnp",	{Gv, Ev, XX}, 0}, 	// 0F4B
		{"cmovl",	{Gv, Ev, XX}, 0}, 	// 0F4C
		{"cmovnl",	{Gv, Ev, XX}, 0}, 	// 0F4D
		{"cmovng",	{Gv, Ev, XX}, 0}, 	// 0F4E
		{"cmovg",	{Gv, Ev, XX}, 0}, 	// 0F4F
// 0F50
		{NULL,		{XX, XX, XX}, PMMX_50}, // 0F50
		{NULL,		{XX, XX, XX}, PMMX_51}, // 0F51
		{NULL,		{XX, XX, XX}, PMMX_52}, // 0F52
		{NULL,		{XX, XX, XX}, PMMX_53}, // 0F53
		{NULL,		{XX, XX, XX}, PMMX_54}, // 0F54
		{NULL,		{XX, XX, XX}, PMMX_55}, // 0F55
		{NULL,		{XX, XX, XX}, PMMX_56}, // 0F56
		{NULL,		{XX, XX, XX}, PMMX_57}, // 0F57
		{NULL,		{XX, XX, XX}, PMMX_58}, // 0F58
		{NULL,		{XX, XX, XX}, PMMX_59}, // 0F59
		{NULL,		{XX, XX, XX}, PMMX_5A}, // 0F5A
		{NULL,		{XX, XX, XX}, PMMX_5B}, // 0F5B
		{NULL,		{XX, XX, XX}, PMMX_5C}, // 0F5C
		{NULL,		{XX, XX, XX}, PMMX_5D}, // 0F5D
		{NULL,		{XX, XX, XX}, PMMX_5E}, // 0F5E
		{NULL,		{XX, XX, XX}, PMMX_5F}, // 0F5F
// 0F60
		{NULL,		{XX, XX, XX}, PMMX_60}, // 0F60
		{NULL,		{XX, XX, XX}, PMMX_61}, // 0F61
		{NULL,		{XX, XX, XX}, PMMX_62}, // 0F62
		{NULL,		{XX, XX, XX}, PMMX_63}, // 0F63
		{NULL,		{XX, XX, XX}, PMMX_64}, // 0F64
		{NULL,		{XX, XX, XX}, PMMX_65}, // 0F65
		{NULL,		{XX, XX, XX}, PMMX_66}, // 0F66
		{NULL,		{XX, XX, XX}, PMMX_67}, // 0F67
		{NULL,		{XX, XX, XX}, PMMX_68}, // 0F68
		{NULL,		{XX, XX, XX}, PMMX_69}, // 0F69
		{NULL,		{XX, XX, XX}, PMMX_6A}, // 0F6A
		{NULL,		{XX, XX, XX}, PMMX_6B}, // 0F6B
		{NULL,		{XX, XX, XX}, PMMX_6C}, // 0F6C
		{NULL,		{XX, XX, XX}, PMMX_6D}, // 0F6D
		{NULL,		{XX, XX, XX}, PMMX_6E}, // 0F6E
		{NULL,		{XX, XX, XX}, PMMX_6F}, // 0F6F
// 0F70
		{NULL,		{XX, XX, XX}, PMMX_70}, // 0F70
		{NULL,		{XX, XX, XX}, PG_12}, 	// 0F71
		{NULL,		{XX, XX, XX}, PG_13}, 	// 0F72
		{NULL,		{XX, XX, XX}, PG_14}, 	// 0F73
		{NULL,		{XX, XX, XX}, PMMX_74}, // 0F74
		{NULL,		{XX, XX, XX}, PMMX_75}, // 0F75
		{NULL,		{XX, XX, XX}, PMMX_76}, // 0F76
		{"emms",	{XX, XX, XX}, 0}, 	// 0F77
		{NULL,		{XX, XX, XX}, 0}, 	// 0F78
		{NULL,		{XX, XX, XX}, 0}, 	// 0F79
		{NULL,		{XX, XX, XX}, 0}, 	// 0F7A
		{NULL,		{XX, XX, XX}, 0}, 	// 0F7B
		{NULL,		{XX, XX, XX}, 0}, 	// 0F7C
		{NULL,		{XX, XX, XX}, 0}, 	// 0F7D
		{NULL,		{XX, XX, XX}, PMMX_7E}, // 0F7E
		{NULL,		{XX, XX, XX}, PMMX_7F}, // 0F7F
// 0F80
		{"jo",		{Jv, XX, XX}, 0}, 	// 0F80
		{"jno",		{Jv, XX, XX}, 0}, 	// 0F81
		{"jb",		{Jv, XX, XX}, 0}, 	// 0F82
		{"jnb",		{Jv, XX, XX}, 0}, 	// 0F83
		{"je",		{Jv, XX, XX}, 0}, 	// 0F84
		{"jne",		{Jv, XX, XX}, 0}, 	// 0F85
		{"jna",		{Jv, XX, XX}, 0}, 	// 0F86
		{"ja",		{Jv, XX, XX}, 0}, 	// 0F87
		{"js",		{Jv, XX, XX}, 0}, 	// 0F88
		{"jns",		{Jv, XX, XX}, 0}, 	// 0F89
		{"jp",		{Jv, XX, XX}, 0}, 	// 0F8A
		{"jnp",		{Jv, XX, XX}, 0}, 	// 0F8B
		{"jl",		{Jv, XX, XX}, 0}, 	// 0F8C
		{"jnl",		{Jv, XX, XX}, 0}, 	// 0F8D
		{"jng",		{Jv, XX, XX}, 0}, 	// 0F8E
		{"jg",		{Jv, XX, XX}, 0}, 	// 0F8F
// 0F90
		{"seto",	{Eb, XX, XX}, 0}, 	// 0F90
		{"setno",	{Eb, XX, XX}, 0}, 	// 0F91
		{"setb",	{Eb, XX, XX}, 0}, 	// 0F92
		{"setnb",	{Eb, XX, XX}, 0}, 	// 0F93
		{"sete",	{Eb, XX, XX}, 0}, 	// 0F94
		{"setne",	{Eb, XX, XX}, 0}, 	// 0F95
		{"setna",	{Eb, XX, XX}, 0}, 	// 0F96
		{"seta",	{Eb, XX, XX}, 0}, 	// 0F97
		{"sets",	{Eb, XX, XX}, 0}, 	// 0F98
		{"setns",	{Eb, XX, XX}, 0}, 	// 0F99
		{"setp",	{Eb, XX, XX}, 0}, 	// 0F9A
		{"setnp",	{Eb, XX, XX}, 0}, 	// 0F9B
		{"setl",	{Eb, XX, XX}, 0}, 	// 0F9C
		{"setnl",	{Eb, XX, XX}, 0}, 	// 0F9D
		{"setng",	{Eb, XX, XX}, 0}, 	// 0F9E
		{"setg",	{Eb, XX, XX}, 0}, 	// 0F9F
// 0FA0
		{"push",	{R_FS, XX, XX}, 0}, 	// 0FA0
		{"pop",		{R_FS, XX, XX}, 0}, 	// 0FA1
		{"cpuid",	{XX, XX, XX}, 0}, 	// 0FA2
		{"bt",		{Ev, Gv, XX}, 0}, 	// 0FA3
		{"shld",	{Ev, Gv, Ib}, 0}, 	// 0FA4
		{"shld",	{Ev, Gv, R_CL}, 0}, 	// 0FA5
		{NULL,		{XX, XX, XX}, 0}, 	// 0FA6
		{NULL,		{XX, XX, XX}, 0}, 	// 0FA7
		{"push",	{R_GS, XX, XX}, 0}, 	// 0FA8
		{"pop",		{R_GS, XX, XX}, 0}, 	// 0FA9
		{"rsm",		{XX, XX, XX}, 0}, 	// 0FAA
		{"bts",		{Ev, Gv, XX}, 0}, 	// 0FAB
		{"shrd",	{Ev, Gv, Ib}, 0}, 	// 0FAC
		{"shrd",	{Ev, Gv, R_CL}, 0}, 	// 0FAD
		{NULL,		{XX, XX, XX}, PG_15}, 	// 0FAE
		{"imul",	{Gv, Ev, XX}, 0}, 	// 0FAF
// 0FB0
		{"cmpxchg",	{Eb, Gb, XX}, 0}, 	// 0FB0
		{"cmpxchg",	{Ev, Gv, XX}, 0}, 	// 0FB1
		{"lss",		{Mp, XX, XX}, 0}, 	// 0FB2
		{"btr",		{Ev, Gv, XX}, 0}, 	// 0FB3
		{"lfs",		{Mp, XX, XX}, 0}, 	// 0FB4
		{"lgs",		{Mp, XX, XX}, 0}, 	// 0FB5
		{"movzx",	{Gv, Eb, XX}, 0}, 	// 0FB6
		{"movzx",	{Gv, Ew, XX}, 0}, 	// 0FB7
		{NULL,		{XX, XX, XX}, 0}, 	// 0FB8
		{NULL,		{XX, XX, XX}, PG_10}, 	// 0FB9
		{NULL,		{Ev, Ib, XX}, PG_8}, 	// 0FBA
		{"btc",		{Ev, Gv, XX}, 0}, 	// 0FBB
		{"bsf",		{Gv, Ev, XX}, 0}, 	// 0FBC
		{"bsr",		{Gv, Ev, XX}, 0}, 	// 0FBD
		{"movsx",	{Gv, Eb, XX}, 0}, 	// 0FBE
		{"movsx",	{Gv, Ew, XX}, 0}, 	// 0FBF
// 0FC0
		{"xadd",	{Eb, Gb, XX}, 0}, 	// 0FC0
		{"xadd",	{Ev, Gv, XX}, 0}, 	// 0FC1
		{NULL,		{XX, XX, XX}, PMMX_C2}, // 0FC2
		{"movinti",	{Ed, Gd, XX}, 0}, 	// 0FC3
		{NULL,		{XX, XX, XX}, PMMX_C4}, // 0FC4
		{NULL,		{XX, XX, XX}, PMMX_C5}, // 0FC5
		{NULL,		{XX, XX, XX}, PMMX_C6}, // 0FC6
		{NULL,		{XX, XX, XX}, PG_9}, 	// 0FC7
		{"bswap",	{R_EAX, XX, XX}, 0}, 	// 0FC8
		{"bswap",	{R_ECX, XX, XX}, 0}, 	// 0FC9
		{"bswap",	{R_EDX, XX, XX}, 0}, 	// 0FCA
		{"bswap",	{R_EBX, XX, XX}, 0}, 	// 0FCB
		{"bswap",	{R_ESP, XX, XX}, 0}, 	// 0FCC
		{"bswap",	{R_EBP, XX, XX}, 0}, 	// 0FCD
		{"bswap",	{R_ESI, XX, XX}, 0}, 	// 0FCE
		{"bswap",	{R_EDI, XX, XX}, 0}, 	// 0FCF
// 0FD0
		{NULL,		{XX, XX, XX}, 0}, 	// 0FD0
		{NULL,		{XX, XX, XX}, PMMX_D1}, // 0FD1
		{NULL,		{XX, XX, XX}, PMMX_D2}, // 0FD2
		{NULL,		{XX, XX, XX}, PMMX_D3}, // 0FD3
		{NULL,		{XX, XX, XX}, PMMX_D4}, // 0FD4
		{NULL,		{XX, XX, XX}, PMMX_D5}, // 0FD5
		{NULL,		{XX, XX, XX}, PMMX_D6}, // 0FD6
		{NULL,		{XX, XX, XX}, PMMX_D7}, // 0FD7
		{NULL,		{XX, XX, XX}, PMMX_D8}, // 0FD8
		{NULL,		{XX, XX, XX}, PMMX_D9}, // 0FD9
		{NULL,		{XX, XX, XX}, PMMX_DA}, // 0FDA
		{NULL,		{XX, XX, XX}, PMMX_DB}, // 0FDB
		{NULL,		{XX, XX, XX}, PMMX_DC}, // 0FDC
		{NULL,		{XX, XX, XX}, PMMX_DD}, // 0FDD
		{NULL,		{XX, XX, XX}, PMMX_DE}, // 0FDE
		{NULL,		{XX, XX, XX}, PMMX_DF}, // 0FDF
// 0FE0
		{NULL,		{XX, XX, XX}, PMMX_E0}, // 0FD0
		{NULL,		{XX, XX, XX}, PMMX_E1}, // 0FD1
		{NULL,		{XX, XX, XX}, PMMX_E2}, // 0FD2
		{NULL,		{XX, XX, XX}, PMMX_E3}, // 0FD3
		{NULL,		{XX, XX, XX}, PMMX_E4}, // 0FD4
		{NULL,		{XX, XX, XX}, PMMX_E5}, // 0FD5
		{NULL,		{XX, XX, XX}, PMMX_E6}, // 0FD6
		{NULL,		{XX, XX, XX}, PMMX_E7}, // 0FD7
		{NULL,		{XX, XX, XX}, PMMX_E8}, // 0FD8
		{NULL,		{XX, XX, XX}, PMMX_E9}, // 0FD9
		{NULL,		{XX, XX, XX}, PMMX_EA}, // 0FDA
		{NULL,		{XX, XX, XX}, PMMX_EB}, // 0FDB
		{NULL,		{XX, XX, XX}, PMMX_EC}, // 0FDC
		{NULL,		{XX, XX, XX}, PMMX_ED}, // 0FDD
		{NULL,		{XX, XX, XX}, PMMX_EE}, // 0FDE
		{NULL,		{XX, XX, XX}, PMMX_EF}, // 0FDF
// 0FF0
		{NULL,		{XX, XX, XX}, 0}, 	// 0FD0
		{NULL,		{XX, XX, XX}, PMMX_F1}, // 0FD1
		{NULL,		{XX, XX, XX}, PMMX_F2}, // 0FD2
		{NULL,		{XX, XX, XX}, PMMX_F3}, // 0FD3
		{NULL,		{XX, XX, XX}, PMMX_F4}, // 0FD4
		{NULL,		{XX, XX, XX}, PMMX_F5}, // 0FD5
		{NULL,		{XX, XX, XX}, PMMX_F6}, // 0FD6
		{NULL,		{XX, XX, XX}, PMMX_F7}, // 0FD7
		{NULL,		{XX, XX, XX}, PMMX_F8}, // 0FD8
		{NULL,		{XX, XX, XX}, PMMX_F9}, // 0FD9
		{NULL,		{XX, XX, XX}, PMMX_FA}, // 0FDA
		{NULL,		{XX, XX, XX}, PMMX_FB}, // 0FDB
		{NULL,		{XX, XX, XX}, PMMX_FC}, // 0FDC
		{NULL,		{XX, XX, XX}, PMMX_FD}, // 0FDD
		{NULL,		{XX, XX, XX}, PMMX_FE}, // 0FDE
		{NULL,		{XX, XX, XX}, 0}, 	// 0FDF
};

s_instr	patchg_list [16][16] = {
// G1
	{
		// mem
		{"add",		{XX, XX, XX}, 0},	// 0
		{"or",		{XX, XX, XX}, 0},	// 1
		{"adc",		{XX, XX, XX}, 0},	// 2
		{"sbb",		{XX, XX, XX}, 0},	// 3
		{"and",		{XX, XX, XX}, 0},	// 4
		{"sub",		{XX, XX, XX}, 0},	// 5
		{"xor",		{XX, XX, XX}, 0},	// 6
		{"cmp",		{XX, XX, XX}, 0},	// 7

		// mod = 3
		{"add",		{XX, XX, XX}, 0},	// 0
		{"or",		{XX, XX, XX}, 0},	// 1
		{"adc",		{XX, XX, XX}, 0},	// 2
		{"sbb",		{XX, XX, XX}, 0},	// 3
		{"and",		{XX, XX, XX}, 0},	// 4
		{"sub",		{XX, XX, XX}, 0},	// 5
		{"xor",		{XX, XX, XX}, 0},	// 6
		{"cmp",		{XX, XX, XX}, 0},	// 7
	},
// G2
	{
		// mem
		{"rol",		{XX, XX, XX}, 0},	// 0
		{"ror",		{XX, XX, XX}, 0},	// 1
		{"rcl",		{XX, XX, XX}, 0},	// 2
		{"rcr",		{XX, XX, XX}, 0},	// 3
		{"shl",		{XX, XX, XX}, 0},	// 4
		{"shr",		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{"sar",		{XX, XX, XX}, 0},	// 7

		// mod = 3
		{"rol",		{XX, XX, XX}, 0},	// 0
		{"ror",		{XX, XX, XX}, 0},	// 1
		{"rcl",		{XX, XX, XX}, 0},	// 2
		{"rcr",		{XX, XX, XX}, 0},	// 3
		{"shl",		{XX, XX, XX}, 0},	// 4
		{"shr",		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{"sar",		{XX, XX, XX}, 0},	// 7
	},
// G3
	{
		// mem
		{"test",	{XX, Iv, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{"not",		{XX, XX, XX}, 0},	// 2
		{"neg",		{XX, XX, XX}, 0},	// 3
		{"mul",		{XX, R_ALEAX, XX}, 0},	// 4
		{"imul",	{XX, R_ALEAX, XX}, 0},	// 5
		{"div",		{XX, R_ALEAX, XX}, 0},	// 6
		{"idiv",	{XX, R_ALEAX, XX}, 0},	// 7

		// mod = 3
		{"test",	{XX, Iv, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{"not",		{XX, XX, XX}, 0},	// 2
		{"neg",		{XX, XX, XX}, 0},	// 3
		{"mul",		{XX, R_ALEAX, XX}, 0},	// 4
		{"imul",	{XX, R_ALEAX, XX}, 0},	// 5
		{"div",		{XX, R_ALEAX, XX}, 0},	// 6
		{"idiv",	{XX, R_ALEAX, XX}, 0},	// 7
},
// G4
	{
		// mem
		{"inc",		{Eb, XX, XX}, 0},	// 0
		{"dec",		{Eb, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7

		// mod = 3
		{"inc",		{Eb, XX, XX}, 0},	// 0
		{"dec",		{Eb, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7
	},
// G5
	{
		// mem
		{"inc",		{Ev, XX, XX}, 0},	// 0
		{"dec",		{Ev, XX, XX}, 0},	// 1
		{"call near",	{Ev, XX, XX}, 0},	// 2
		{"call far",	{Ep, XX, XX}, 0},	// 3
		{"jmp near",	{Ev, XX, XX}, 0},	// 4
		{"jmp far",	{Ep, XX, XX}, 0},	// 5
		{"push",	{Ev, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7

		// mod = 3
		{"inc",		{Ev, XX, XX}, 0},	// 0
		{"dec",		{Ev, XX, XX}, 0},	// 1
		{"call near",	{Ev, XX, XX}, 0},	// 2
		{"call far",	{Ep, XX, XX}, 0},	// 3
		{"jmp near",	{Ev, XX, XX}, 0},	// 4
		{"jmp far",	{Ep, XX, XX}, 0},	// 5
		{"push",	{Ev, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7
	},
// G6
	{
		// mem
		{"sldt",	{Ew, XX, XX}, 0},	// 0
		{"str",		{Ev, XX, XX}, 0},	// 1
		{"lldt",	{Ew, XX, XX}, 0},	// 2
		{"ltr",		{Ew, XX, XX}, 0},	// 3
		{"verr",	{Ew, XX, XX}, 0},	// 4
		{"verw",	{Ew, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7

		// mod = 3
		{"sldt",	{Ew, XX, XX}, 0},	// 0
		{"str",		{Ev, XX, XX}, 0},	// 1
		{"lldt",	{Ew, XX, XX}, 0},	// 2
		{"ltr",		{Ew, XX, XX}, 0},	// 3
		{"verr",	{Ew, XX, XX}, 0},	// 4
		{"verw",	{Ew, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7
	},
// G7
	{
		// mem
		{"sgdt",	{Ms, XX, XX}, 0},	// 0
		{"sidt",	{Ms, XX, XX}, 0},	// 1
		{"lgdt",	{Ms, XX, XX}, 0},	// 2
		{"lidt",	{Ms, XX, XX}, 0},	// 3
		{"smsw",	{Ew, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{"lmsw",	{Ew, XX, XX}, 0},	// 6
		{"invlpg",	{Mb, XX, XX}, 0},	// 7

		// mod = 3
		{"sgdt",	{Ms, XX, XX}, 0},	// 0
		{"sidt",	{Ms, XX, XX}, 0},	// 1
		{"lgdt",	{Ms, XX, XX}, 0},	// 2
		{"lidt",	{Ms, XX, XX}, 0},	// 3
		{"smsw",	{Ew, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{"lmsw",	{Ew, XX, XX}, 0},	// 6
		{"invlpg",	{Mb, XX, XX}, 0},	// 7
	},
// G8
	{
		// mem
		{NULL,		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{"bt",		{XX, XX, XX}, 0},	// 4
		{"bts",		{XX, XX, XX}, 0},	// 5
		{"btr",		{XX, XX, XX}, 0},	// 6
		{"btc",		{XX, XX, XX}, 0},	// 7

		// mod = 3
		{NULL,		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{"bt",		{XX, XX, XX}, 0},	// 4
		{"bts",		{XX, XX, XX}, 0},	// 5
		{"btr",		{XX, XX, XX}, 0},	// 6
		{"btc",		{XX, XX, XX}, 0},	// 7
	},
// G9
	{
		// mem
		{NULL,		{XX, XX, XX}, 0},	// 0
		{"cmpxch8b",	{Mq, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7

		// mod = 3
		{NULL,		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7
	},
// G10
	{
		// mem
		{NULL,		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7

		// mod = 3
		{NULL,		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7
	},
// G11
	{
		// mem
		{"mov",		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7

		// mod = 3
		{"mov",		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7
	},
// G12
	{
		// mem
		{NULL,		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7

		// mod = 3
		{NULL,		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, PMMX_G122},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, PMMX_G124},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, PMMX_G126},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7
	},
// G13
	{

		// mem
		{NULL,		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7

		// mod = 3
		{NULL,		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, PMMX_G132},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, PMMX_G134},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, PMMX_G136},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7
	},
// G14
	{
		// mem
		{NULL,		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7

		// mod = 3
		{NULL,		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, PMMX_G142},	// 2
		{NULL,		{XX, XX, XX}, PMMX_G143},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, PMMX_G146},	// 6
		{NULL,		{XX, XX, XX}, PMMX_G147},	// 7
	},
// G15
	{
		// mem
		{"fxsave",	{XX, XX, XX}, 0},	// 0
		{"fxrstor",	{XX, XX, XX}, 0},	// 1
		{"ldmxcsr",	{XX, XX, XX}, 0},	// 2
		{"stmxcsr",	{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{"cflush",	{XX, XX, XX}, 0},	// 7

		// mod = 3
		{NULL,		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{"lfence",	{XX, XX, XX}, 0},	// 5
		{"mfence",	{XX, XX, XX}, 0},	// 6
		{"sfence",	{XX, XX, XX}, 0},	// 7
	},
// G16
	{
		// mem
		{},	// 0
		{},	// 1
		{},	// 2
		{},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7

		// mod = 3
		{NULL,		{XX, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{NULL,		{XX, XX, XX}, 0},	// 2
		{NULL,		{XX, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{NULL,		{XX, XX, XX}, 0},	// 7
	}
};

char *patch66_list [0xD][2] = {
	{"pusha", "pushad"},	// P66_60
	{"popa", "popad"},	// P66_61
	{"insw", "insd"},	// P66_6d
	{"outsw", "outsd"},	// P66_6f
	{"cbw", "cwde"},	// P66_98
	{"cwd", "cdq"},		// P66_99
	{"pushf", "pushfd"},	// P66_9c
	{"popf", "popfd"},	// P66_9d
	{"mowsw", "movsd"},	// P66_a5
	{"cmpsw", "cmpsd"},	// P66_a7
	{"stosw", "stosd"},	// P66_ab
	{"lodsw", "lodsd"},	// P66_ad
	{"scasw", "scasd"}	// P66_af
};

s_instr	finsbf_list [8][8] = {
// 8
	{
		{"fadd",	{Ed, XX, XX}, 0},	// 0
		{"fmul",	{Ed, XX, XX}, 0},	// 1
		{"fcom",	{Ed, XX, XX}, 0},	// 2
		{"fcomp",	{Ed, XX, XX}, 0},	// 3
		{"fsub",	{Ed, XX, XX}, 0},	// 4
		{"fsubr",	{Ed, XX, XX}, 0},	// 5
		{"fdiv",	{Ed, XX, XX}, 0},	// 6
		{"fdivr",	{Ed, XX, XX}, 0},	// 7
	},
// 9
	{
		{"fld",		{Ed, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{"fst",		{Ed, XX, XX}, 0},	// 2
		{"fstp",	{Ed, XX, XX}, 0},	// 3
		{"fldenv",	{Ed, XX, XX}, 0},	// 4
		{"fldcw",	{Ew, XX, XX}, 0},	// 5
		{"fstenv",	{Ed, XX, XX}, 0},	// 6
		{"fstcw",	{Ew, XX, XX}, 0},	// 7
	},
// A
	{
		{"fiadd",	{Ed, XX, XX}, 0},	// 0
		{"fimul",	{Ed, XX, XX}, 0},	// 1
		{"ficom",	{Ed, XX, XX}, 0},	// 2
		{"ficomp",	{Ed, XX, XX}, 0},	// 3
		{"fisub",	{Ed, XX, XX}, 0},	// 4
		{"fisubr",	{Ed, XX, XX}, 0},	// 5
		{"fidiv",	{Ed, XX, XX}, 0},	// 6
		{"fidivr",	{Ed, XX, XX}, 0},	// 7
	},
// B
	{
		{"fild",	{Ed, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{"fist",	{Ed, XX, XX}, 0},	// 2
		{"fistp",	{Ed, XX, XX}, 0},	// 3
		{NULL,		{XX, XX, XX}, 0},	// 4
		{"fld",		{XX, XX, XX}, 0},	// 5
		{NULL,		{XX, XX, XX}, 0},	// 6
		{"fstp",	{XX, XX, XX}, 0},	// 7
	},
// C
	{
		{"fadd",	{Ed, XX, XX}, 0},	// 0
		{"fmul",	{Ed, XX, XX}, 0},	// 1
		{"fcom",	{Ed, XX, XX}, 0},	// 2
		{"fcomp",	{Ed, XX, XX}, 0},	// 3
		{"fsub",	{Ed, XX, XX}, 0},	// 4
		{"fsubr",	{Ed, XX, XX}, 0},	// 5
		{"fdiv",	{Ed, XX, XX}, 0},	// 6
		{"fdivr",	{Ed, XX, XX}, 0},	// 7
	},
// D
	{
		{"fld",		{Ed, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{"fst",		{Ed, XX, XX}, 0},	// 2
		{"fstp",	{Ed, XX, XX}, 0},	// 3
		{"frstor",	{Ed, XX, XX}, 0},	// 4
		{NULL,		{XX, XX, XX}, 0},	// 5
		{"fsave",	{Ed, XX, XX}, 0},	// 6
		{"tstsw",	{Ew, XX, XX}, 0},	// 7
	},
// E
	{
		{"fiadd",	{Ew, XX, XX}, 0},	// 0
		{"fimul",	{Ew, XX, XX}, 0},	// 1
		{"ficom",	{Ew, XX, XX}, 0},	// 2
		{"ficomp",	{Ew, XX, XX}, 0},	// 3
		{"fisub",	{Ew, XX, XX}, 0},	// 4
		{"fisubr",	{Ew, XX, XX}, 0},	// 5
		{"fidiv",	{Ew, XX, XX}, 0},	// 6
		{"fidivr",	{Ew, XX, XX}, 0},	// 7
	},
// F
	{
		{"fild",	{Ew, XX, XX}, 0},	// 0
		{NULL,		{XX, XX, XX}, 0},	// 1
		{"fist",	{Ew, XX, XX}, 0},	// 2
		{"fistp",	{Ew, XX, XX}, 0},	// 3
		{"fbld",	{Ew, XX, XX}, 0},	// 4
		{"fild",	{Eq, XX, XX}, 0},	// 5
		{"fbstp",	{Ew, XX, XX}, 0},	// 6
		{"fistp",	{Eq, XX, XX}, 0},	// 7
	}
};


s_instr	finsc0_list [8][8] = {
// 8
	{
		// 0 - 7
		{"fadd",	{R_ST0, R_STi, XX}, 0},	// C
		{"fcom",	{R_ST0, R_STi, XX}, 0},	// D
		{"fsub",	{R_ST0, R_STi, XX}, 0},	// E
		{"fdiv",	{R_ST0, R_STi, XX}, 0},	// F

		// 8 - F
		{"fmul",	{R_ST0, R_STi, XX}, 0},	// C
		{"fcomp",	{R_ST0, R_STi, XX}, 0},	// D
		{"fsubr",	{R_ST0, R_STi, XX}, 0},	// E
		{"fdivr",	{R_ST0, R_STi, XX}, 0},	// F
	},
// 9
	{
		// 0 - 7
		{"fld",		{R_ST0, R_STi, XX}, 0},	// C
		{NULL,		{XX, XX, XX}, PPFLOAT_9D},	// D
		{NULL,		{XX, XX, XX}, PPFLOAT_9E},	// E
		{NULL,		{XX, XX, XX}, PPFLOAT_9F},	// F

		// 8 - F
		{"fxch",	{R_ST0, R_STi, XX}, 0},	// C
		{NULL,		{XX, XX, XX}, 0},	// D
		{NULL,		{XX, XX, XX}, PPFLOAT_9E},	// E
		{NULL,		{XX, XX, XX}, PPFLOAT_9F},	// F
	},
// A
	{
		// 0 - 7
		{"fcmovb",	{R_ST0, R_STi, XX}, 0},	// C
		{"fcmovbe",	{R_ST0, R_STi, XX}, 0},	// D
		{NULL,		{XX, XX, XX}, 0},	// E
		{NULL,		{XX, XX, XX}, 0},	// F

		// 8 - F
		{"fcmove",	{R_ST0, R_STi, XX}, 0},	// C
		{"fcmovu",	{R_ST0, R_STi, XX}, 0},	// D
		{NULL,		{XX, XX, XX}, PPFLOAT_AE},	// E
		{NULL,		{XX, XX, XX}, 0},	// F
	},
// B
	{
		// 0 - 7
		{"fcmovnb",	{R_ST0, R_STi, XX}, 0},	// C
		{"fcmovnbe",	{R_ST0, R_STi, XX}, 0},	// D
		{NULL,		{XX, XX, XX}, PPFLOAT_BE},	// E
		{"fcomi",	{R_ST0, R_STi, XX}, 0},	// F

		// 8 - F
		{"fcmovne",	{R_ST0, R_STi, XX}, 0},	// C
		{"fcmovnu",	{R_ST0, R_STi, XX}, 0},	// D
		{"fucomi",	{R_ST0, R_STi, XX}, 0},	// E
		{NULL,		{XX, XX, XX}, 0},	// F
	},
// C
	{
		// 0 - 7
		{"fadd",	{R_STi, R_ST0, XX}, 0},	// C
		{NULL,		{XX, XX, XX}, 0},	// D
		{"fusbr",	{R_STi, R_ST0, XX}, 0},	// E
		{"fdivr",	{R_STi, R_ST0, XX}, 0},	// F

		// 8 - F
		{"fmul",	{R_STi, R_ST0, XX}, 0},	// C
		{NULL,		{XX, XX, XX}, 0},	// D
		{"fsub",	{R_STi, R_ST0, XX}, 0},	// E
		{"fdiv",	{R_STi, R_ST0, XX}, 0},	// F
	},
// D
	{
		// 0 - 7
		{"free",	{R_STi, XX, XX}, 0},	// C
		{"fst",		{R_STi, XX, XX}, 0},	// D
		{"fucom",	{R_STi, R_ST0, XX}, 0},	// E
		{NULL,		{XX, XX, XX}, 0},	// F

		// 8 - F
		{NULL,		{XX, XX, XX}, 0},	// C
		{"fstp",	{R_STi, XX, XX}, 0},	// D
		{"fucomp",	{R_STi, XX, XX}, 0},	// E
		{NULL,		{XX, XX, XX}, 0},	// F
	},
// E
	{
		// 0 - 7
		{"faddp",	{R_ST0, R_STi, XX}, 0},	// C
		{NULL,		{XX, XX, XX}, 0},	// D
		{"fsubrp",	{R_STi, R_ST0, XX}, 0},	// E
		{"fdivrp",	{R_STi, R_ST0, XX}, 0},	// F

		// 8 - F
		{"fmulp",	{R_STi, R_ST0, XX}, 0},	// C
		{NULL,		{XX, XX, XX}, PPFLOAT_ED},	// D
		{"fsubp",	{R_STi, R_ST0, XX}, 0},	// E
		{"fdivp",	{R_STi, R_ST0, XX}, 0},	// F
	},
// F
	{
		// 0 - 7
		{NULL,		{XX, XX, XX}, 0},	// C
		{NULL,		{XX, XX, XX}, 0},	// D
		{NULL,		{XX, XX, XX}, PPFLOAT_FE},	// E
		{"fcomip",	{R_ST0, R_STi, XX}, 0},	// F

		// 8 - F
		{NULL,		{XX, XX, XX}, 0},	// C
		{NULL,		{XX, XX, XX}, 0},	// D
		{"fucomip",	{R_ST0, R_STi, XX}, 0},	// E
		{NULL,		{XX, XX, XX}, 0},	// F
	},
};

char *patchf_list [7][16] = {
// 0 PPFLOAT_9D
	{"fnop", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
// 1 PPFLOAT_9E
	{"fchs", "fabs", NULL, NULL, "ftst", "fxam", NULL, NULL, "fld1", "fldl2t", "fldl2e", "fldpi", "fldlg2", "fldln2", "fldz", NULL},
// 2 PPFLOAT_9F
	{"f2xm1", "fyl2x", "fptan", "fpatan", "fxtract", "fprem1", "fdecstop", "fincstp", "fprem", "fyl2xp1", "fsqrt", "fsincos", "frndint", "fscale", "fsin", "fcos"},
// 3 PPFLOAT_AE
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "fucompp", NULL, NULL, NULL, NULL, NULL, NULL},
// 4 PPFLOAT_BE
	{NULL, NULL, "fclex", "finit", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
// 5 PPFLOAT_ED
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "fcompp", NULL, NULL, NULL, NULL, NULL, NULL},
// 6 PPFLOAT_FE
	{"fstsw", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}
// fstsw ax !!!
};


s_instr	patchmmx_list [113][4] = {

// PMMX_10
	{
		{"movups",	{Vps, Wps, XX}, 0},	//
		{"movupd",	{Vpd, Wpd, XX}, 0},	// 66
		{"movsd",	{Vsd, Wsd, XX}, 0},	// f2
		{"movss",	{Vss, Wss, XX}, 0},	// f3
	},
// PMMX_11
	{
		{"movups",	{Wps, Vps, XX}, 0},	//
		{"movupd",	{Wpd, Vpd, XX}, 0},	// 66
		{"movsd",	{Wsd, Vsd, XX}, 0},	// f2
		{"movss",	{Wss, Vss, XX}, 0},	// f3
	},
// PMMX_12
	{
		{"movlps",	{Wq, Vq, XX}, 0},	//
		{"movlpd",	{Vq, Ws, XX}, 0},	// 66
		{"movhlps",	{Vq, Vq, XX}, 0},	// f2
		{"movhlps",	{Vq, Vq, XX}, 0},	// f3
	},
// PMMX_13
	{
		{"movlps",	{Vq, Wq, XX}, 0},	//
		{"movlpd",	{Vq, Wq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_14
	{
		{"unpcklps",	{Vps, Wq, XX}, 0},	//
		{"unpcklpd",	{Vpd, Wq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_15
	{
		{"unpckhps",	{Vps, Wq, XX}, 0},	//
		{"unpckhpd",	{Vpd, Wq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_16
	{
		{"movhps",	{Vq, Wq, XX}, 0},	//
		{"movhpd",	{Vq, Wq, XX}, 0},	// 66
		{"movlhps",	{Vq, Vq, XX}, 0},	// f2
		{"movlhps",	{Vq, Vq, XX}, 0},	// f3
	},
// PMMX_17
	{
		{"movhps",	{Wq, Vq, XX}, 0},	//
		{"movhpd",	{Wq, Vq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_28
	{
		{"movaps",	{Vps, Wps, XX}, 0},	//
		{"movapd",	{Vpd, Wpd, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_29
	{
		{"movaps",	{Wps, Vps, XX}, 0},	//
		{"movapd",	{Wpd, Vpd, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_2A
	{
		{"cvtpi2ps",	{Vps, Qd, XX}, 0},	//
		{"cvtsi2ss",	{Vpd, Qdq, XX}, 0},	// 66
		{"cvtsi2sd",	{Vsd, Ed, XX}, 0},	// f2
		{"cvtsi2ss",	{Vss, Ed, XX}, 0},	// f3
	},
// PMMX_2B
	{
		{"movntps",	{Wps, Vps, XX}, 0},	//
		{"movntpd",	{Wdp, Vpd, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_2C
	{
		{"cvttps2pi",	{Qd, Wps, XX}, 0},	//
		{"cvttpd2pi",	{Qdq, Wpd, XX}, 0},	// 66
		{"cvttsd2si",	{Gd, Wsd, XX}, 0},	// f2
		{"cvttss2si",	{Gd, Wss, XX}, 0},	// f3
	},
// PMMX_2D
	{
		{"cvtps2pi",	{Qd, Wps, XX}, 0},	//
		{"cvtpd2pi",	{Qdq, Wpd, XX}, 0},	// 66
		{"cvtsd2si",	{Gd, Wsd, XX}, 0},	// f2
		{"cvtss2si",	{Qd, Wss, XX}, 0},	// f3
	},
// PMMX_2E
	{
		{"ucomiss",	{Vss, Wss, XX}, 0},	//
		{"ucomisd",	{Vsd, Wsd, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_2F
	{
		{"comiss",	{Vps, Wps, XX}, 0},	//
		{"comisd",	{Vsd, Wsd, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},

// PMMX_50
	{
		{"movmskps",	{Ed, Vps, XX}, 0},	//
		{"movmskpd",	{Ed, Vpd, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_51
	{
		{"sqrtps",	{Vps, Wps, XX}, 0},	//
		{"sqrtpd",	{Vpd, Wpd, XX}, 0},	// 66
		{"sqrtsd",	{Vsd, Wsd, XX}, 0},	// f2
		{"sqrtss",	{Vss, Wss, XX}, 0},	// f3
	},
// PMMX_52
	{
		{"rsqrtps",	{Vps, Wps, XX}, 0},	//
		{NULL,		{XX, XX, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{"rsqrtss",	{Vss, Wss, XX}, 0},	// f3
	},
// PMMX_53
	{
		{"rcpps",	{Vps, Wps, XX}, 0},	//
		{NULL,		{XX, XX, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{"rcpss", 	{Vss, Wss, XX}, 0},	// f3
	},
// PMMX_54
	{
		{"andps",	{Vps, Wps, XX}, 0},	//
		{"andpd",	{Vpd, Wdp, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3

	},
// PMMX_55
	{
		{"andnps",	{Vps, Wps, XX}, 0},	//
		{"andnpd",	{Vpd, Wpd, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_56
	{
		{"orps",	{Vps, Wps, XX}, 0},	//
		{"orpd",	{Vpd, Wpd, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_57
	{
		{"xorps",	{Vps, Wps, XX}, 0},	//
		{"xorpd",	{Vpd, Wpd, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_58
	{
		{"addps",	{Vps, Wps, XX}, 0},	//
		{"addpd",	{Vpd, Wdp, XX}, 0},	// 66
		{"addsd",	{Vsd, Wsd, XX}, 0},	// f2
		{"addss",	{Vsd, Wsd, XX}, 0},	// f3
	},
// PMMX_59
	{
		{"mulps",	{Vps, Wps, XX}, 0},	//
		{"mulpd",	{Vpd, Wpd, XX}, 0},	// 66
		{"mulsd",	{Vsd, Wsd, XX}, 0},	// f2
		{"mulss",	{Vss, Wpd, XX}, 0},	// f3
	},
// PMMX_5A
	{
		{"cvtps2pd",	{Vpd, Wps, XX}, 0},	//
		{"cvtpd2ps",	{Vps, Wpd, XX}, 0},	// 66
		{"cvtss2ss",	{Vsd, Wsd, XX}, 0},	// f2
		{"cvtss2sd",	{Vss, Wss, XX}, 0},	// f3
	},
// PMMX_5B
	{
		{"cvtdq2ps",	{Vps, Wdq, XX}, 0},	//
		{"cvtps2dq",	{Vdq, Wps, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{"cvttps2dq",	{Vdq, Wps, XX}, 0},	// f3
	},
// PMMX_5C
	{
		{"subps",	{Vps, Wps, XX}, 0},	//
		{"subpd",	{Vpd, Wps, XX}, 0},	// 66
		{"subsd",	{Vsd, Wsd, XX}, 0},	// f2
		{"subss",	{Vss, Wss, XX}, 0},	// f3
	},
// PMMX_5D
	{
		{"minps",	{Vps, Wps, XX}, 0},	//
		{"minpd",	{Vpd, Wpd, XX}, 0},	// 66
		{"minsd",	{Vsd, Wsd, XX}, 0},	// f2
		{"minss",	{Vss, Wss, XX}, 0},	// f3
	},
// PMMX_5E
	{
		{"divps",	{Vps, Wps, XX}, 0},	//
		{"divpd",	{Vpd, Wpd, XX}, 0},	// 66
		{"divsd",	{Vsd, Wsd, XX}, 0},	// f2
		{"divsd",	{Vsd, Wsd, XX}, 0},	// f3
	},
// PMMX_5F
	{
		{"maxps",	{Vps, Wps, XX}, 0},	//
		{"maxpd",	{Vpd, Wpd, XX}, 0},	// 66
		{"maxsd",	{Vsd, Wsd, XX}, 0},	// f2
		{"maxss",	{Vss, Wss, XX}, 0},	// f3
	},
// PMMX_60
	{
		{"punpcklbw", 	{Pq, Qd, XX}, 0},	//
		{"punpcklbw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_61
	{
		{"punpcklwd",	{Pq, Qd, XX}, 0},	//
		{"punpcklwd",	{Qdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_62
	{
		{"punpckldq",	{Pq, Qd, XX}, 0},	//
		{"punpckldq",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_63
	{
		{"packsswb",	{Pq, Qd, XX}, 0},	//
		{"packsswb",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_64
	{
		{"pcmpgtb",	{Pq, Qq, XX}, 0},	//
		{"pcmpgtb",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_65
	{
		{"pcmpgtw",	{Pq, Qq, XX}, 0},	//
		{"pcmpgtw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_66
	{
		{"pcmpgtd",	{Pq, Qq, XX}, 0},	//
		{"pcmpgtd",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_67
	{
		{"packuswb",	{Pq, Qq, XX}, 0},	//
		{"packuswb",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_68
	{
		{"punpckhbw",	{Pq, Qd, XX}, 0},	//
		{"punpckhbw",	{Pdq, Qdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_69
	{
		{"punpckhwd",	{Pq, Qd, XX}, 0},	//
		{"punpckhwd",	{Pdq, Qdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_6A
	{
		{"punpckhdq",	{Pq, Qd, XX}, 0},	//
		{"punpckhdq",	{Pdq, Qdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_6B
	{
		{"packssdw", 	{Pq, Qd, XX}, 0},	//
		{"packssdw",	{Pdq, Qdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_6C
	{
		{NULL,		{XX, XX, XX}, 0},	//
		{"punpclkqdq",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_6D
	{
		{NULL,		{XX, XX, XX}, 0},	//
		{"punpckhqd",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_6E
	{
		{"movd",	{Pd, Ed, XX}, 0},	//
		{"movd",	{Vdq, Ed, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_6F
	{
		{"movq",	{Pq, Qq, XX}, 0},	//
		{"movdqa",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{"movdqu",	{Vdq, Wdq, XX}, 0},	// f3
	},
// PMMX_70
	{
		{"pshufw",	{Pq, Qq, Ib}, 0},	//
		{"pshufd",	{Qdq, Qdq, Ib}, 0},	// 66
		{"pshulflw",	{Vdq, Wdq, Ib}, 0},	// f2
		{"pshufhw",	{Vdq, Wdq, Ib}, 0},	// f3
	},
// PMMX_74
	{
		{"pcmpeqb",	{Pq, Qq, XX}, 0},	//
		{"pcmpeqb",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_75
	{
		{"pcmpeqw",	{Pq, Qq, XX}, 0},	//
		{"pcmpeqw",	{Vdq, Qdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_76
	{
		{"pcmpeqd",	{Pq, Qq, XX}, 0},	//
		{"pcmpeqd",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_7E
	{
		{"movd",	{Ed, Pd, XX}, 0},	//
		{"movd",	{Ed, Vdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{"movq",	{Vq, Wq, XX}, 0},	// f3
	},
// PMMX_7F
	{
		{"movq",	{Qq, Pq, XX}, 0},	//
		{"movdqa",	{Wdq, Vdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{"movdqu",	{Wdq, Vdq, XX}, 0},	// f3
	},
// PMMX_C2
	{
		{"cmpps",	{Vps, Wps, Ib}, 0},	//
		{"cmppd",	{Vpd, Wpd, Ib}, 0},	// 66
		{"cmpsd",	{Vsd, Wsd, Ib}, 0},	// f2
		{"cmpss",	{Vss, Wss, Ib}, 0},	// f3
	},
// PMMX_C4
	{
		{"pinsrw",	{Pq, Ed, Ib}, 0},	//
		{"pinsrw",	{Vdq, Ed, Ib}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_C5
	{
		{"pextrw",	{Gd, Pq, Ib}, 0},	//
		{"pextrw",	{Gd, Vdq, Ib}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_C6
	{
		{"shufps",	{Vps, Wps, Ib}, 0},	//
		{"shufpd",	{Vpd, Wpd, Ib}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_D1
	{
		{"psrlw",	{Pq, Qd, XX}, 0},	//
		{"psrlw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_D2
	{
		{"psrld",	{Pq, Qd, XX}, 0},	//
		{"psrld",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_D3
	{
		{"psrlq",	{Pq, Qq, XX}, 0},	//
		{"psrlq",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_D4
	{
		{"paddq",	{Pq, Qq, XX}, 0},	//
		{"paddq",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_D5
	{
		{"pmullw",	{Pq, Qq, XX}, 0},	//
		{"pmullw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_D6
	{
		{NULL,		{XX, XX, XX}, 0},	//
		{"movq",	{Wq, Vq, XX}, 0},	// 66
		{"movdq2q",	{Pq, Wq, XX}, 0},	// f2
		{"movq2dq",	{Vdq, Qq, XX}, 0},	// f3
	},
// PMMX_D7
	{
		{"pmovmskb",	{Gd, Pq, XX}, 0},	//
		{"pmovmskb",	{Gd, Vdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_D8
	{
		{"psubusb",	{Pq, Qq, XX}, 0},	//
		{"psubusb",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_D9
	{
		{"psubusw",	{Pq, Qq, XX}, 0},	//
		{"psubusw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},

// PMMX_DA
	{
		{"pminub",	{Pq, Qq, XX}, 0},	//
		{"pminub",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_DB
	{
		{"pand",	{Pq, Qq, XX}, 0},	//
		{"pand",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_DC
	{
		{"paddusb",	{Pq, Qq, XX}, 0},	//
		{"paddusb",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_DD
	{
		{"paddusw",	{Pq, Qq, XX}, 0},	//
		{"paddusw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_DE
	{
		{"pmaxub",	{Pq, Qq, XX}, 0},	//
		{"pmaxub",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_DF
	{
		{"pandn",	{Pq, Qq, XX}, 0},	//
		{"pandn",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_E0
	{
		{"pavgb",	{Pq, Qq, XX}, 0},	//
		{"pavgb",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_E1
	{
		{"psraw",	{Pq, Qq, XX}, 0},	//
		{"psraw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_E2
	{
		{"psrad",	{Pq, Qq, XX}, 0},	//
		{"psrad",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_E3
	{
		{"pavgw",	{Pq, Qq, XX}, 0},	//
		{"pavgw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_E4
	{
		{"pmulhuw",	{Pq, Qq, XX}, 0},	//
		{"pmulhuw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_E5
	{
		{"pmulhw",	{Pq, Qq, XX}, 0},	//
		{"pmulhw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_E6
	{
		{NULL,		{XX, XX, XX}, 0},	//
		{"cvttpd2dq",	{XX, XX, XX}, 0},	// 66
		{"cvtpd2dq",	{Vdq, Wpd, XX}, 0},	// f2
		{"cvtdq2pd",	{Vpd, Wdq, XX}, 0},	// f3
	},
// PMMX_E7
	{
		{"movntq",	{Wq, Vq, XX}, 0},	//
		{"movntdq",	{Wdq, Vdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_E8
	{
		{"psubsb",	{Pq, Qq, XX}, 0},	//
		{"psubsb",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_E9
	{
		{"psubsw",	{Pq, Qq, XX}, 0},	//
		{"psubsw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_EA
	{
		{"pminsw",	{Pq, Qq, XX}, 0},	//
		{"pminsw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_EB
	{
		{"por",		{Pq, Qq, XX}, 0},	//
		{"por",		{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_EC
	{
		{"paddsb",	{Pq, Qq, XX}, 0},	//
		{"paddsb",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_ED
	{
		{"paddsw",	{Pq, Qq, XX}, 0},	//
		{"paddsw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_EE
	{
		{"pmaxsw",	{Pq, Qq, XX}, 0},	//
		{"pmaxsw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_EF
	{
		{"pxor",	{Pq, Qq, XX}, 0},	//
		{"pxor",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_F1
	{
		{"psllw",	{Pq, Qq, XX}, 0},	//
		{"psllw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_F2
	{
		{"pslld",	{Pq, Qq, XX}, 0},	//
		{"pslld",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_F3
	{
		{"psllq",	{Pq, Qq, XX}, 0},	//
		{"psllq",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_F4
	{
		{"pmuludq",	{Pq, Qq, XX}, 0},	//
		{"pmuludq",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_F5
	{
		{"pmaddwd",	{Pq, Qq, XX}, 0},	//
		{"pmaddwd",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_F6
	{
		{"psadbw",	{Pq, Qq, XX}, 0},	//
		{"psadbw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_F7
	{
		{"maskmovq",	{Ppi, Qpi, XX}, 0},	//
		{"maskmovdqu",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_F8
	{
		{"psubb",	{Pq, Qq, XX}, 0},	//
		{"psubb",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_F9
	{
		{"psubw",	{Pq, Qq, XX}, 0},	//
		{"psubw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_FA
	{
		{"psubd",	{Pq, Qq, XX}, 0},	//
		{"psubd",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_FB
	{
		{"psubq",	{Pq, Qq, XX}, 0},	//
		{"psubq",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_FC
	{
		{"paddb",	{Pq, Qq, XX}, 0},	//
		{"paddb",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_FD
	{
		{"paddw",	{Pq, Qq, XX}, 0},	//
		{"paddw",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_FE
	{
		{"paddd",	{Pq, Qq, XX}, 0},	//
		{"paddd",	{Vdq, Wdq, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_G122
	{
		{"psrlw",	{Qq, Ib, XX}, 0},	//
		{"psrlw",	{Qdq, Ib, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_G124
	{
		{"psraw",	{Qq, Ib, XX}, 0},	//
		{"psraw",	{Qdq, Ib, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_G126
	{
		{"psllw",	{Qq, Ib, XX}, 0},	//
		{"psllw",	{Wdq, Ib, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_G132
	{
		{"psrld",	{Qq, Ib, XX}, 0},	//
		{"psrld",	{Wdq, Ib, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_G134
	{
		{"psrad",	{Qq, Ib, XX}, 0},	//
		{"psrad",	{Wdq, Ib, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_G136
	{
		{"pslld",	{Qq, Ib, XX}, 0},	//
		{"pslld",	{Wdq, Ib, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_G142
	{
		{"psrlq",	{Pq, Ib, XX}, 0},	//
		{"psrlq",	{Wdq, Ib, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_G143
	{
		{NULL,		{XX, XX, XX}, 0},	//
		{"psrldq",	{Wdq, Ib, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_G146
	{
		{"psllq",	{Pq, Ib, XX}, 0},	//
		{"psllq",	{Wdq, Ib, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
// PMMX_G147
	{
		{NULL,		{XX, XX, XX}, 0},	//
		{"pslldq",	{Wdq, Ib, XX}, 0},	// 66
		{NULL,		{XX, XX, XX}, 0},	// f2
		{NULL,		{XX, XX, XX}, 0},	// f3
	},
};

char	*seg_tbl [6] = {
	"es",
	"cs",
	"ss",
	"ds",
	"fs",
	"gs"
};

char	*reg8_tbl [8] = {
	"al",
	"cl",
	"dl",
	"bl",
	"ah",
	"ch",
	"dh",
	"bh"
};

char	*reg16_tbl [8] = {
	"ax",
	"cx",
	"dx",
	"bx",
	"sp",
	"bp",
	"si",
	"di"
};

char	*reg32_tbl [8] = {
	"eax",
	"ecx",
	"edx",
	"ebx",
	"esp",
	"ebp",
	"esi",
	"edi"
};

char *cr_tbl [5] = {
	"cr0",
	"cr1",
	"cr2",
	"cr3",
	"cr4"
};

char *dr_tbl [8] = {
	"dr0",
	"dr1",
	"dr2",
	"dr3",
	"dr4",
	"dr5",
	"dr6",
	"dr7"
};

char *tr_tbl [8] = {
	"tr0",
	"tr1",
	"tr2",
	"tr3",
	"tr4",
	"tr5",
	"tr6",
	"tr7"
};

char*	ea16_tbl [] = {
	"bx + si",
	"bx + di",
	"bp + si",
	"bp + di",
	"si",
	"di",
	"bp",
	"bx"
};

char*	ea32_tbl [] = {
	"eax",
	"ecx",
	"edx",
	"ebx",
	"",
	"ebp",
	"esi",
	"edi"
};

char*	sib_tbl [] = {
	"eax",
	"ecx",
	"edx",
	"ebx",
	"",
	"ebp",
	"esi",
	"edi"
};

char	*base_tbl [8] = {
	"eax",
	"ecx",
	"edx",
	"ebx",
	"esp",
	"",
	"esi",
	"edi"
};


char*	mul_tbl [] = {
	"",
	" * 2",
	" * 4",
	" * 8",
};

char*	mm_tbl [] = {
	"mm0",
	"mm1",
	"mm2",
	"mm3",
	"mm4",
	"mm5",
	"mm6",
	"mm7",
};

char*	xmm_tbl [] = {
	"xmm0",
	"xmm1",
	"xmm2",
	"xmm3",
	"xmm4",
	"xmm5",
	"xmm6",
	"xmm7",
};


unsigned int	rm16_tbl [8*3] = {
	(RR16_BXSI),
	(RR16_BXDI),
	(RR16_BPSI),
	(RR16_BPDI),
	(RR16_SI),
	(RR16_DI),
	(RD16_DISP16),
	(RR16_BX),
// ---------------------
	(RR16_BXSI | RD16_DISP8),
	(RR16_BXDI | RD16_DISP8),
	(RR16_BPSI | RD16_DISP8),
	(RR16_BPDI | RD16_DISP8),
	(RR16_SI | RD16_DISP8),
	(RR16_DI | RD16_DISP8),
	(RR16_BP | RD16_DISP8),
	(RR16_BX | RD16_DISP8),
// ---------------------
	(RR16_BXSI | RD16_DISP16),
	(RR16_BXDI | RD16_DISP16),
	(RR16_BPSI | RD16_DISP16),
	(RR16_BPDI | RD16_DISP16),
	(RR16_SI | RD16_DISP16),
	(RR16_DI | RD16_DISP16),
	(RR16_BP | RD16_DISP16),
	(RR16_BX | RD16_DISP16)
};

unsigned int	rm32_tbl [8*3] = {
	(RR32_EAX),
	(RR32_ECX),
	(RR32_EDX),
	(RR32_EBX),
	(RR32_SIB),
	(RD32_DISP32),
	(RR32_ESI),
	(RR32_EDI),
// -----------------------
	(RR32_EAX + RD32_DISP8),
	(RR32_ECX + RD32_DISP8),
	(RR32_EDX + RD32_DISP8),
	(RR32_EBX + RD32_DISP8),
	(RR32_SIB + RD32_DISP8),
	(RR32_EBP + RD32_DISP8),
	(RR32_ESI + RD32_DISP8),
	(RR32_EDI + RD32_DISP8),
// ------------------------
	(RR32_EAX + RD32_DISP32),
	(RR32_ECX + RD32_DISP32),
	(RR32_EDX + RD32_DISP32),
	(RR32_EBX + RD32_DISP32),
	(RR32_SIB + RD32_DISP32),
	(RR32_EBP + RD32_DISP32),
	(RR32_ESI + RD32_DISP32),
	(RR32_EDI + RD32_DISP32)
};

