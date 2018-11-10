/*
  ADE32 -- Advanced Disassembler Engine -- FREEWARE
  version 2.03
*/

#ifndef __ADE32TBL_C__
#define __ADE32TBL_C__

unsigned long ade32_table[512] = {
                       /*    these values were ripped from the M$ Detours library:  */
C_MODRM,               /* 00 CopyBytes2Mod        ADD /r                            */
C_MODRM,               /* 01 CopyBytes2Mod        ADD /r                            */
C_MODRM,               /* 02 CopyBytes2Mod        ADD /r                            */
C_MODRM,               /* 03 CopyBytes2Mod        ADD /r                            */
C_DATA1,               /* 04 CopyBytes2           ADD ib                            */
C_DATA66,              /* 05 CopyBytes3Or5        ADD iw                            */
C_BAD,                 /* 06 CopyBytes1           PUSH                              */
C_BAD,                 /* 07 CopyBytes1           POP                               */
C_MODRM,               /* 08 CopyBytes2Mod        OR /r                             */
C_MODRM,               /* 09 CopyBytes2Mod        OR /r                             */
C_MODRM,               /* 0A CopyBytes2Mod        OR /r                             */
C_MODRM,               /* 0B CopyBytes2Mod        OR /r                             */
C_DATA1,               /* 0C CopyBytes2           OR ib                             */
C_DATA66,              /* 0D CopyBytes3Or5        OR iw                             */
C_BAD,                 /* 0E CopyBytes1           PUSH                              */
C_OPCODE2,             /* 0F Copy0F               Extension Ops                     */
C_MODRM+C_BAD,         /* 10 CopyBytes2Mod        ADC /r                            */
C_MODRM,               /* 11 CopyBytes2Mod        ADC /r                            */
C_MODRM+C_BAD,         /* 12 CopyBytes2Mod        ADC /r                            */
C_MODRM,               /* 13 CopyBytes2Mod        ADC /r                            */
C_DATA1+C_BAD,         /* 14 CopyBytes2           ADC ib                            */
C_DATA66+C_BAD,        /* 15 CopyBytes3Or5        ADC id                            */
C_BAD,                 /* 16 CopyBytes1           PUSH                              */
C_BAD,                 /* 17 CopyBytes1           POP                               */
C_MODRM+C_BAD,         /* 18 CopyBytes2Mod        SBB /r                            */
C_MODRM,               /* 19 CopyBytes2Mod        SBB /r                            */
C_MODRM,               /* 1A CopyBytes2Mod        SBB /r                            */
C_MODRM,               /* 1B CopyBytes2Mod        SBB /r                            */
C_DATA1+C_BAD,         /* 1C CopyBytes2           SBB ib                            */
C_DATA66+C_BAD,        /* 1D CopyBytes3Or5        SBB id                            */
C_BAD,                 /* 1E CopyBytes1           PUSH                              */
C_BAD,                 /* 1F CopyBytes1           POP                               */
C_MODRM,               /* 20 CopyBytes2Mod        AND /r                            */
C_MODRM,               /* 21 CopyBytes2Mod        AND /r                            */
C_MODRM,               /* 22 CopyBytes2Mod        AND /r                            */
C_MODRM,               /* 23 CopyBytes2Mod        AND /r                            */
C_DATA1,               /* 24 CopyBytes2           AND ib                            */
C_DATA66,              /* 25 CopyBytes3Or5        AND id                            */
C_SEG+C_BAD,           /* 26 CopyBytesPrefix      ES prefix                         */
C_BAD,                 /* 27 CopyBytes1           DAA                               */
C_MODRM,               /* 28 CopyBytes2Mod        SUB /r                            */
C_MODRM,               /* 29 CopyBytes2Mod        SUB /r                            */
C_MODRM,               /* 2A CopyBytes2Mod        SUB /r                            */
C_MODRM,               /* 2B CopyBytes2Mod        SUB /r                            */
C_DATA1,               /* 2C CopyBytes2           SUB ib                            */
C_DATA66,              /* 2D CopyBytes3Or5        SUB id                            */
C_SEG+C_BAD,           /* 2E CopyBytesPrefix      CS prefix                         */
C_BAD,                 /* 2F CopyBytes1           DAS                               */
C_MODRM,               /* 30 CopyBytes2Mod        XOR /r                            */
C_MODRM,               /* 31 CopyBytes2Mod        XOR /r                            */
C_MODRM,               /* 32 CopyBytes2Mod        XOR /r                            */
C_MODRM,               /* 33 CopyBytes2Mod        XOR /r                            */
C_DATA1,               /* 34 CopyBytes2           XOR ib                            */
C_DATA66,              /* 35 CopyBytes3Or5        XOR id                            */
C_SEG+C_BAD,           /* 36 CopyBytesPrefix      SS prefix                         */
C_BAD,                 /* 37 CopyBytes1           AAA                               */
C_MODRM,               /* 38 CopyBytes2Mod        CMP /r                            */
C_MODRM,               /* 39 CopyBytes2Mod        CMP /r                            */
C_MODRM,               /* 3A CopyBytes2Mod        CMP /r                            */
C_MODRM,               /* 3B CopyBytes2Mod        CMP /r                            */
C_DATA1,               /* 3C CopyBytes2           CMP ib                            */
C_DATA66,              /* 3D CopyBytes3Or5        CMP id                            */
C_SEG+C_BAD,           /* 3E CopyBytesPrefix      DS prefix                         */
C_BAD,                 /* 3F CopyBytes1           AAS                               */
0,                     /* 40 CopyBytes1           INC                               */
0,                     /* 41 CopyBytes1           INC                               */
0,                     /* 42 CopyBytes1           INC                               */
0,                     /* 43 CopyBytes1           INC                               */
C_BAD,                 /* 44 CopyBytes1           INC                               */
0,                     /* 45 CopyBytes1           INC                               */
0,                     /* 46 CopyBytes1           INC                               */
0,                     /* 47 CopyBytes1           INC                               */
0,                     /* 48 CopyBytes1           DEC                               */
0,                     /* 49 CopyBytes1           DEC                               */
0,                     /* 4A CopyBytes1           DEC                               */
0,                     /* 4B CopyBytes1           DEC                               */
C_BAD,                 /* 4C CopyBytes1           DEC                               */
0,                     /* 4D CopyBytes1           DEC                               */
0,                     /* 4E CopyBytes1           DEC                               */
0,                     /* 4F CopyBytes1           DEC                               */
0,                     /* 50 CopyBytes1           PUSH                              */
0,                     /* 51 CopyBytes1           PUSH                              */
0,                     /* 52 CopyBytes1           PUSH                              */
0,                     /* 53 CopyBytes1           PUSH                              */
0,                     /* 54 CopyBytes1           PUSH                              */
0,                     /* 55 CopyBytes1           PUSH                              */
0,                     /* 56 CopyBytes1           PUSH                              */
0,                     /* 57 CopyBytes1           PUSH                              */
0,                     /* 58 CopyBytes1           POP                               */
0,                     /* 59 CopyBytes1           POP                               */
0,                     /* 5A CopyBytes1           POP                               */
0,                     /* 5B CopyBytes1           POP                               */
C_BAD,                 /* 5C CopyBytes1           POP                               */
0,                     /* 5D CopyBytes1           POP                               */
0,                     /* 5E CopyBytes1           POP                               */
0,                     /* 5F CopyBytes1           POP                               */
C_BAD,                 /* 60 CopyBytes1           PUSHAD                            */
C_BAD,                 /* 61 CopyBytes1           POPAD                             */
C_MODRM+C_BAD,         /* 62 CopyBytes2Mod        BOUND /r                          */
C_MODRM+C_BAD,         /* 63 CopyBytes2Mod        ARPL /r                           */
C_SEG,                 /* 64 CopyBytesPrefix      FS prefix                         */
C_SEG+C_BAD,           /* 65 CopyBytesPrefix      GS prefix                         */
C_66,                  /* 66 Copy66               Operand Prefix                    */
C_67,                  /* 67 Copy67               Address Prefix                    */
C_DATA66,              /* 68 CopyBytes3Or5        PUSH                              */
C_MODRM+C_DATA66,      /* 69 CopyBytes2ModOperand                                   */
C_DATA1,               /* 6A CopyBytes2           PUSH                              */
C_MODRM+C_DATA1,       /* 6B CopyBytes2Mod1       IMUL /r ib                        */
C_BAD,                 /* 6C CopyBytes1           INS                               */
C_BAD,                 /* 6D CopyBytes1           INS                               */
C_BAD,                 /* 6E CopyBytes1           OUTS/OUTSB                        */
C_BAD,                 /* 6F CopyBytes1           OUTS/OUTSW                        */
C_DATA1+C_REL+C_BAD,   /* 70 CopyBytes2Jump       JO                                */
C_DATA1+C_REL+C_BAD,   /* 71 CopyBytes2Jump       JNO                               */
C_DATA1+C_REL,         /* 72 CopyBytes2Jump       JB/JC/JNAE                        */
C_DATA1+C_REL,         /* 73 CopyBytes2Jump       JAE/JNB/JNC                       */
C_DATA1+C_REL,         /* 74 CopyBytes2Jump       JE/JZ                             */
C_DATA1+C_REL,         /* 75 CopyBytes2Jump       JNE/JNZ                           */
C_DATA1+C_REL,         /* 76 CopyBytes2Jump       JBE/JNA                           */
C_DATA1+C_REL,         /* 77 CopyBytes2Jump       JA/JNBE                           */
C_DATA1+C_REL,         /* 78 CopyBytes2Jump       JS                                */
C_DATA1+C_REL,         /* 79 CopyBytes2Jump       JNS                               */
C_DATA1+C_REL+C_BAD,   /* 7A CopyBytes2Jump       JP/JPE                            */
C_DATA1+C_REL+C_BAD,   /* 7B CopyBytes2Jump       JNP/JPO                           */
C_DATA1+C_REL,         /* 7C CopyBytes2Jump       JL/JNGE                           */
C_DATA1+C_REL,         /* 7D CopyBytes2Jump       JGE/JNL                           */
C_DATA1+C_REL,         /* 7E CopyBytes2Jump       JLE/JNG                           */
C_DATA1+C_REL,         /* 7F CopyBytes2Jump       JG/JNLE                           */
C_MODRM+C_DATA1,       /* 80 CopyBytes2Mod1       ADC/2 ib, etc.s                   */
C_MODRM+C_DATA66,      /* 81 CopyBytes2ModOperand                                   */
C_MODRM+C_DATA1+C_BAD, /* 82 CopyBytes2           MOV al,x                          */
C_MODRM+C_DATA1,       /* 83 CopyBytes2Mod1       ADC/2 ib, etc.                    */
C_MODRM,               /* 84 CopyBytes2Mod        TEST /r                           */
C_MODRM,               /* 85 CopyBytes2Mod        TEST /r                           */
C_MODRM,               /* 86 CopyBytes2Mod        XCHG /r @todo                     */
C_MODRM,               /* 87 CopyBytes2Mod        XCHG /r @todo                     */
C_MODRM,               /* 88 CopyBytes2Mod        MOV /r                            */
C_MODRM,               /* 89 CopyBytes2Mod        MOV /r                            */
C_MODRM,               /* 8A CopyBytes2Mod        MOV /r                            */
C_MODRM,               /* 8B CopyBytes2Mod        MOV /r                            */
C_MODRM+C_BAD,         /* 8C CopyBytes2Mod        MOV /r                            */
C_MODRM,               /* 8D CopyBytes2Mod        LEA /r                            */
C_MODRM+C_BAD,         /* 8E CopyBytes2Mod        MOV /r                            */
C_MODRM,               /* 8F CopyBytes2Mod        POP /0                            */
0,                     /* 90 CopyBytes1           NOP                               */
0,                     /* 91 CopyBytes1           XCHG                              */
0,                     /* 92 CopyBytes1           XCHG                              */
C_BAD,                 /* 93 CopyBytes1           XCHG                              */
C_BAD,                 /* 94 CopyBytes1           XCHG                              */
C_BAD,                 /* 95 CopyBytes1           XCHG                              */
C_BAD,                 /* 96 CopyBytes1           XCHG                              */
C_BAD,                 /* 97 CopyBytes1           XCHG                              */
C_BAD,                 /* 98 CopyBytes1           CWDE                              */
0,                     /* 99 CopyBytes1           CDQ                               */
C_DATA66+C_DATA2+C_BAD,/* 9A CopyBytes5Or7Dynamic CALL cp                           */
0,                     /* 9B CopyBytes1           WAIT/FWAIT                        */
C_BAD,                 /* 9C CopyBytes1           PUSHFD                            */
C_BAD,                 /* 9D CopyBytes1           POPFD                             */
C_BAD,                 /* 9E CopyBytes1           SAHF                              */
C_BAD,                 /* 9F CopyBytes1           LAHF                              */
C_ADDR67,              /* A0 CopyBytes3Or5Address MOV                               */
C_ADDR67,              /* A1 CopyBytes3Or5Address MOV                               */
C_ADDR67,              /* A2 CopyBytes3Or5Address MOV                               */
C_ADDR67,              /* A3 CopyBytes3Or5Address MOV                               */
0,                     /* A4 CopyBytes1           MOVS                              */
0,                     /* A5 CopyBytes1           MOVS/MOVSD                        */
0,                     /* A6 CopyBytes1           CMPS/CMPSB                        */
0,                     /* A7 CopyBytes1           CMPS/CMPSW                        */
C_DATA1,               /* A8 CopyBytes2           TEST                              */
C_DATA66,              /* A9 CopyBytes3Or5        TEST                              */
0,                     /* AA CopyBytes1           STOS/STOSB                        */
0,                     /* AB CopyBytes1           STOS/STOSW                        */
0,                     /* AC CopyBytes1           LODS/LODSB                        */
C_BAD,                 /* AD CopyBytes1           LODS/LODSW                        */
0,                     /* AE CopyBytes1           SCAS/SCASB                        */
C_BAD,                 /* AF CopyBytes1           SCAS/SCASD                        */
C_DATA1,               /* B0 CopyBytes2           MOV B0+rb                         */
C_DATA1,               /* B1 CopyBytes2           MOV B0+rb                         */
C_DATA1,               /* B2 CopyBytes2           MOV B0+rb                         */
C_DATA1,               /* B3 CopyBytes2           MOV B0+rb                         */
C_DATA1,               /* B4 CopyBytes2           MOV B0+rb                         */
C_DATA1,               /* B5 CopyBytes2           MOV B0+rb                         */
C_DATA1+C_BAD,         /* B6 CopyBytes2           MOV B0+rb                         */
C_DATA1+C_BAD,         /* B7 CopyBytes2           MOV B0+rb                         */
C_DATA66,              /* B8 CopyBytes3Or5        MOV B8+rb                         */
C_DATA66,              /* B9 CopyBytes3Or5        MOV B8+rb                         */
C_DATA66,              /* BA CopyBytes3Or5        MOV B8+rb                         */
C_DATA66,              /* BB CopyBytes3Or5        MOV B8+rb                         */
C_DATA66+C_BAD,        /* BC CopyBytes3Or5        MOV B8+rb                         */
C_DATA66,              /* BD CopyBytes3Or5        MOV B8+rb                         */
C_DATA66,              /* BE CopyBytes3Or5        MOV B8+rb                         */
C_DATA66,              /* BF CopyBytes3Or5        MOV B8+rb                         */
C_MODRM+C_DATA1,       /* C0 CopyBytes2Mod1       RCL/2 ib, etc.                    */
C_MODRM+C_DATA1,       /* C1 CopyBytes2Mod1       RCL/2 ib, etc.                    */
C_DATA2+C_STOP,        /* C2 CopyBytes3           RET                               */
C_STOP,                /* C3 CopyBytes1           RET                               */
C_MODRM+C_BAD,         /* C4 CopyBytes2Mod        LES                               */
C_MODRM+C_BAD,         /* C5 CopyBytes2Mod        LDS                               */
C_MODRM+C_DATA1,       /* C6 CopyBytes2Mod1       MOV                               */
C_MODRM+C_DATA66,      /* C7 CopyBytes2ModOperand MOV                               */
C_DATA2+C_DATA1,       /* C8 CopyBytes4           ENTER                             */
0,                     /* C9 CopyBytes1           LEAVE                             */
C_DATA2+C_STOP+C_BAD,  /* CA CopyBytes3Dynamic    RET                               */
C_STOP+C_BAD,          /* CB CopyBytes1Dynamic    RET                               */
C_BAD,                 /* CC CopyBytes1Dynamic    INT 3                             */
C_BAD,                 /* CD CopyBytes2Dynamic    INT ib                            */
C_BAD,                 /* CE CopyBytes1Dynamic    INTO                              */
C_STOP+C_BAD,          /* CF CopyBytes1Dynamic    IRET                              */
C_MODRM,               /* D0 CopyBytes2Mod        RCL/2, etc.                       */
C_MODRM,               /* D1 CopyBytes2Mod        RCL/2, etc.                       */
C_MODRM,               /* D2 CopyBytes2Mod        RCL/2, etc.                       */
C_MODRM,               /* D3 CopyBytes2Mod        RCL/2, etc.                       */
C_DATA1+C_BAD,         /* D4 CopyBytes2           AAM                               */
C_DATA1+C_BAD,         /* D5 CopyBytes2           AAD                               */
C_BAD,                 /* D6 Invalid                                                */
C_BAD,                 /* D7 CopyBytes1           XLAT/XLATB                        */
C_MODRM,               /* D8 CopyBytes2Mod        FADD, etc.                        */
C_MODRM,               /* D9 CopyBytes2Mod        F2XM1, etc.                       */
C_MODRM,               /* DA CopyBytes2Mod        FLADD, etc.                       */
C_MODRM,               /* DB CopyBytes2Mod        FCLEX, etc.                       */
C_MODRM,               /* DC CopyBytes2Mod        FADD/0, etc.                      */
C_MODRM,               /* DD CopyBytes2Mod        FFREE, etc.                       */
C_MODRM,               /* DE CopyBytes2Mod        FADDP, etc.                       */
C_MODRM,               /* DF CopyBytes2Mod        FBLD/4, etc.                      */
C_DATA1+C_REL+C_BAD,   /* E0 CopyBytes2CantJump   LOOPNE cb                         */
C_DATA1+C_REL+C_BAD,   /* E1 CopyBytes2CantJump   LOOPE cb                          */
C_DATA1+C_REL,         /* E2 CopyBytes2CantJump   LOOP cb                           */
C_DATA1+C_REL,         /* E3 CopyBytes2Jump       JCXZ/JECXZ                        */
C_DATA1+C_BAD,         /* E4 CopyBytes2           IN ib                             */
C_DATA1+C_BAD,         /* E5 CopyBytes2           IN id                             */
C_DATA1+C_BAD,         /* E6 CopyBytes2           OUT ib                            */
C_DATA1+C_BAD,         /* E7 CopyBytes2           OUT ib                            */
C_DATA66+C_REL,        /* E8 CopyBytes3Or5Target  CALL cd                           */
C_DATA66+C_REL+C_STOP, /* E9 CopyBytes3Or5Target  JMP cd                            */
C_DATA66+C_DATA2+C_BAD,/* EA CopyBytes5Or7Dynamic JMP cp                            */
C_DATA1+C_REL+C_STOP,  /* EB CopyBytes2Jump       JMP cb                            */
C_BAD,                 /* EC CopyBytes1           IN ib                             */
C_BAD,                 /* ED CopyBytes1           IN id                             */
C_BAD,                 /* EE CopyBytes1           OUT                               */
C_BAD,                 /* EF CopyBytes1           OUT                               */
C_LOCK+C_BAD,          /* F0 CopyBytesPrefix      LOCK prefix                       */
C_BAD,                 /* F1 Invalid                                                */
C_REP,                 /* F2 CopyBytesPrefix      REPNE prefix                      */
C_REP,                 /* F3 CopyBytesPrefix      REPE prefix                       */
C_BAD,                 /* F4 CopyBytes1           HLT                               */
C_BAD,                 /* F5 CopyBytes1           CMC                               */
C_MODRM,               /* F6 CopyF6               TEST/0, DIV/6                     */
C_MODRM,               /* F7 CopyF7               TEST/0, DIV/6                     */
0,                     /* F8 CopyBytes1           CLC                               */
0,                     /* F9 CopyBytes1           STC                               */
C_BAD,                 /* FA CopyBytes1           CLI                               */
C_BAD,                 /* FB CopyBytes1           STI                               */
0,                     /* FC CopyBytes1           CLD                               */
0,                     /* FD CopyBytes1           STD                               */
C_MODRM,               /* FE CopyBytes2Mod        DEC/1,INC/0                       */
C_MODRM,               /* FF CopyFF               CALL/2                            */

C_MODRM+C_BAD,         /* 00 CopyBytes2Mod        LLDT/2, etc.                      */
C_MODRM+C_BAD,         /* 01 CopyBytes2Mod        INVLPG/7, etc.                    */
C_MODRM+C_BAD,         /* 02 CopyBytes2Mod        LAR/r                             */
C_MODRM+C_BAD,         /* 03 CopyBytes2Mod        LSL/r                             */
C_ERROR,               /* 04 Invalid              _04                               */
C_ERROR,               /* 05 Invalid              _05                               */
C_BAD,                 /* 06 CopyBytes2           CLTS                              */
C_ERROR,               /* 07 Invalid              _07                               */
C_BAD,                 /* 08 CopyBytes2           INVD                              */
C_BAD,                 /* 09 CopyBytes2           WBINVD                            */
C_ERROR,               /* 0A Invalid              _0A                               */
C_BAD,                 /* 0B CopyBytes2           UD2                               */
C_ERROR,               /* 0C Invalid              _0C                               */
C_MODRM,	//C_ERROR,               /* 0D Invalid              _0D                               */
C_ERROR,               /* 0E Invalid              _0E                               */
C_MODRM,	//C_ERROR,               /* 0F Invalid              _0F                               */
C_MODRM,	//C_ERROR,               /* 10 Invalid              _10                               */
C_MODRM,	//C_ERROR,               /* 11 Invalid              _11                               */
C_MODRM,	//C_ERROR,               /* 12 Invalid              _12                               */
C_MODRM,	//C_ERROR,               /* 13 Invalid              _13                               */
C_MODRM,	//C_ERROR,               /* 14 Invalid              _14                               */
C_MODRM,	//C_ERROR,               /* 15 Invalid              _15                               */
C_MODRM,	//C_ERROR,               /* 16 Invalid              _16                               */
C_MODRM,	//C_ERROR,               /* 17 Invalid              _17                               */
C_MODRM,	//C_ERROR,               /* 18 Invalid              _18                               */
C_ERROR,               /* 19 Invalid              _19                               */
C_ERROR,               /* 1A Invalid              _1A                               */
C_ERROR,               /* 1B Invalid              _1B                               */
C_ERROR,               /* 1C Invalid              _1C                               */
C_ERROR,               /* 1D Invalid              _1D                               */
C_ERROR,               /* 1E Invalid              _1E                               */
C_ERROR,               /* 1F Invalid              _1F                               */
C_MODRM+C_BAD,         /* 20 CopyBytes2Mod        MOV/r                             */
C_MODRM+C_BAD,         /* 21 CopyBytes2Mod        MOV/r                             */
C_MODRM+C_BAD,         /* 22 CopyBytes2Mod        MOV/r                             */
C_MODRM+C_BAD,         /* 23 CopyBytes2Mod        MOV/r                             */
C_MODRM+C_BAD,//C_ERROR,               /* 24 Invalid              _24                               */
C_ERROR,               /* 25 Invalid              _25                               */
C_MODRM+C_BAD,//C_ERROR,               /* 26 Invalid              _26                               */
C_ERROR,               /* 27 Invalid              _27                               */
C_MODRM,	//C_ERROR,               /* 28 Invalid              _28                               */
C_MODRM,	//C_ERROR,               /* 29 Invalid              _29                               */
C_MODRM,	//C_ERROR,               /* 2A Invalid              _2A                               */
C_MODRM,	//C_ERROR,               /* 2B Invalid              _2B                               */
C_MODRM,	//C_ERROR,               /* 2C Invalid              _2C                               */
C_MODRM,	//C_ERROR,               /* 2D Invalid              _2D                               */
C_MODRM,	//C_ERROR,               /* 2E Invalid              _2E                               */
C_MODRM,	//C_ERROR,               /* 2F Invalid              _2F                               */
C_BAD,                 /* 30 CopyBytes2           WRMSR                             */
0,                     /* 31 CopyBytes2           RDTSC                             */
C_BAD,                 /* 32 CopyBytes2           RDMSR                             */
C_BAD,                 /* 33 CopyBytes2           RDPMC                             */
0,                     /* 34 CopyBytes2           SYSENTER                          */
0,                     /* 35 CopyBytes2           SYSEXIT                           */
C_ERROR,               /* 36 Invalid              _36                               */
C_ERROR,               /* 37 Invalid              _37                               */
C_ERROR,               /* 38 Invalid              _38                               */
C_ERROR,               /* 39 Invalid              _39                               */
C_ERROR,               /* 3A Invalid              _3A                               */
C_ERROR,               /* 3B Invalid              _3B                               */
C_ERROR,               /* 3C Invalid              _3C                               */
C_ERROR,               /* 3D Invalid              _3D                               */
C_ERROR,               /* 3E Invalid              _3E                               */
C_ERROR,               /* 3F Invalid              _3F                               */
C_MODRM,               /* 40 CopyBytes2Mod        CMOVO (0F 40)                     */
C_MODRM,               /* 41 CopyBytes2Mod        CMOVNO (0F 41)                    */
C_MODRM,               /* 42 CopyBytes2Mod        CMOVB & CMOVNE (0F 42)            */
C_MODRM,               /* 43 CopyBytes2Mod        CMOVAE & CMOVNB (0F 43)           */
C_MODRM,               /* 44 CopyBytes2Mod        CMOVE & CMOVZ (0F 44)             */
C_MODRM,               /* 45 CopyBytes2Mod        CMOVNE & CMOVNZ (0F 45)           */
C_MODRM,               /* 46 CopyBytes2Mod        CMOVBE & CMOVNA (0F 46)           */
C_MODRM,               /* 47 CopyBytes2Mod        CMOVA & CMOVNBE (0F 47)           */
C_MODRM,               /* 48 CopyBytes2Mod        CMOVS (0F 48)                     */
C_MODRM,               /* 49 CopyBytes2Mod        CMOVNS (0F 49)                    */
C_MODRM,               /* 4A CopyBytes2Mod        CMOVP & CMOVPE (0F 4A)            */
C_MODRM,               /* 4B CopyBytes2Mod        CMOVNP & CMOVPO (0F 4B)           */
C_MODRM,               /* 4C CopyBytes2Mod        CMOVL & CMOVNGE (0F 4C)           */
C_MODRM,               /* 4D CopyBytes2Mod        CMOVGE & CMOVNL (0F 4D)           */
C_MODRM,               /* 4E CopyBytes2Mod        CMOVLE & CMOVNG (0F 4E)           */
C_MODRM,               /* 4F CopyBytes2Mod        CMOVG & CMOVNLE (0F 4F)           */
C_MODRM,	//C_ERROR,               /* 50 Invalid              _50                               */
C_MODRM,	//C_ERROR,               /* 51 Invalid              _51                               */
C_MODRM,	//C_ERROR,               /* 52 Invalid              _52                               */
C_MODRM,	//C_ERROR,               /* 53 Invalid              _53                               */
C_MODRM,	//C_ERROR,               /* 54 Invalid              _54                               */
C_MODRM,	//C_ERROR,               /* 55 Invalid              _55                               */
C_MODRM,	//C_ERROR,               /* 56 Invalid              _56                               */
C_MODRM,	//C_ERROR,               /* 57 Invalid              _57                               */
C_MODRM,	//C_ERROR,               /* 58 Invalid              _58                               */
C_MODRM,	//C_ERROR,               /* 59 Invalid              _59                               */
C_MODRM,	//C_ERROR,               /* 5A Invalid              _5A                               */
C_MODRM,	//C_ERROR,               /* 5B Invalid              _5B                               */
C_MODRM,	//C_ERROR,               /* 5C Invalid              _5C                               */
C_MODRM,	//C_ERROR,               /* 5D Invalid              _5D                               */
C_MODRM,	//C_ERROR,               /* 5E Invalid              _5E                               */
C_MODRM,	//C_ERROR,               /* 5F Invalid              _5F                               */
C_MODRM,               /* 60 CopyBytes2Mod        PUNPCKLBW/r                       */
C_MODRM, //C_ERROR,               /* 61 Invalid              _61                               */
C_MODRM,               /* 62 CopyBytes2Mod        PUNPCKLWD/r                       */
C_MODRM,               /* 63 CopyBytes2Mod        PACKSSWB/r                        */
C_MODRM,               /* 64 CopyBytes2Mod        PCMPGTB/r                         */
C_MODRM,               /* 65 CopyBytes2Mod        PCMPGTW/r                         */
C_MODRM,               /* 66 CopyBytes2Mod        PCMPGTD/r                         */
C_MODRM,               /* 67 CopyBytes2Mod        PACKUSWB/r                        */
C_MODRM,               /* 68 CopyBytes2Mod        PUNPCKHBW/r                       */
C_MODRM,               /* 69 CopyBytes2Mod        PUNPCKHWD/r                       */
C_MODRM,               /* 6A CopyBytes2Mod        PUNPCKHDQ/r                       */
C_MODRM,               /* 6B CopyBytes2Mod        PACKSSDW/r                        */
C_MODRM,	//C_ERROR,               /* 6C Invalid              _6C                               */
C_MODRM,	//C_ERROR,               /* 6D Invalid              _6D                               */
C_MODRM,               /* 6E CopyBytes2Mod        MOVD/r                            */
C_MODRM,               /* 6F CopyBytes2Mod        MOV/r                             */
C_MODRM,	//C_ERROR,               /* 70 Invalid              _70                               */
C_MODRM+C_DATA1,       /* 71 CopyBytes2Mod1       PSLLW/6 ib,PSRAW/4 ib,PSRLW/2 ib  */
C_MODRM+C_DATA1,       /* 72 CopyBytes2Mod1       PSLLD/6 ib,PSRAD/4 ib,PSRLD/2 ib  */
C_MODRM+C_DATA1,       /* 73 CopyBytes2Mod1       PSLLQ/6 ib,PSRLQ/2 ib             */
C_MODRM,               /* 74 CopyBytes2Mod        PCMPEQB/r                         */
C_MODRM,               /* 75 CopyBytes2Mod        PCMPEQW/r                         */
C_MODRM,               /* 76 CopyBytes2Mod        PCMPEQD/r                         */
0,                     /* 77 CopyBytes2           EMMS                              */
C_ERROR,               /* 78 Invalid              _78                               */
C_ERROR,               /* 79 Invalid              _79                               */
C_ERROR,               /* 7A Invalid              _7A                               */
C_ERROR,               /* 7B Invalid              _7B                               */
C_ERROR,               /* 7C Invalid              _7C                               */
C_ERROR,               /* 7D Invalid              _7D                               */
C_MODRM,               /* 7E CopyBytes2Mod        MOVD/r                            */
C_MODRM,               /* 7F CopyBytes2Mod        MOV/r                             */
C_DATA66+C_REL,        /* 80 CopyBytes3Or5Target  JO                                */
C_DATA66+C_REL,        /* 81 CopyBytes3Or5Target  JNO                               */
C_DATA66+C_REL,        /* 82 CopyBytes3Or5Target  JB,JC,JNAE                        */
C_DATA66+C_REL,        /* 83 CopyBytes3Or5Target  JAE,JNB,JNC                       */
C_DATA66+C_REL,        /* 84 CopyBytes3Or5Target  JE,JZ,JZ                          */
C_DATA66+C_REL,        /* 85 CopyBytes3Or5Target  JNE,JNZ                           */
C_DATA66+C_REL,        /* 86 CopyBytes3Or5Target  JBE,JNA                           */
C_DATA66+C_REL,        /* 87 CopyBytes3Or5Target  JA,JNBE                           */
C_DATA66+C_REL,        /* 88 CopyBytes3Or5Target  JS                                */
C_DATA66+C_REL,        /* 89 CopyBytes3Or5Target  JNS                               */
C_DATA66+C_REL,        /* 8A CopyBytes3Or5Target  JP,JPE                            */
C_DATA66+C_REL,        /* 8B CopyBytes3Or5Target  JNP,JPO                           */
C_DATA66+C_REL,        /* 8C CopyBytes3Or5Target  JL,NGE                            */
C_DATA66+C_REL,        /* 8D CopyBytes3Or5Target  JGE,JNL                           */
C_DATA66+C_REL,        /* 8E CopyBytes3Or5Target  JLE,JNG                           */
C_DATA66+C_REL,        /* 8F CopyBytes3Or5Target  JG,JNLE                           */
C_MODRM,               /* 90 CopyBytes2Mod        CMOVO (0F 40)                     */
C_MODRM,               /* 91 CopyBytes2Mod        CMOVNO (0F 41)                    */
C_MODRM,               /* 92 CopyBytes2Mod        CMOVB & CMOVC & CMOVNAE (0F 42)   */
C_MODRM,               /* 93 CopyBytes2Mod        CMOVAE & CMOVNB & CMOVNC (0F 43)  */
C_MODRM,               /* 94 CopyBytes2Mod        CMOVE & CMOVZ (0F 44)             */
C_MODRM,               /* 95 CopyBytes2Mod        CMOVNE & CMOVNZ (0F 45)           */
C_MODRM,               /* 96 CopyBytes2Mod        CMOVBE & CMOVNA (0F 46)           */
C_MODRM,               /* 97 CopyBytes2Mod        CMOVA & CMOVNBE (0F 47)           */
C_MODRM,               /* 98 CopyBytes2Mod        CMOVS (0F 48)                     */
C_MODRM,               /* 99 CopyBytes2Mod        CMOVNS (0F 49)                    */
C_MODRM,               /* 9A CopyBytes2Mod        CMOVP & CMOVPE (0F 4A)            */
C_MODRM,               /* 9B CopyBytes2Mod        CMOVNP & CMOVPO (0F 4B)           */
C_MODRM,               /* 9C CopyBytes2Mod        CMOVL & CMOVNGE (0F 4C)           */
C_MODRM,               /* 9D CopyBytes2Mod        CMOVGE & CMOVNL (0F 4D)           */
C_MODRM,               /* 9E CopyBytes2Mod        CMOVLE & CMOVNG (0F 4E)           */
C_MODRM,               /* 9F CopyBytes2Mod        CMOVG & CMOVNLE (0F 4F)           */
0,                     /* A0 CopyBytes2           PUSH                              */
0,                     /* A1 CopyBytes2           POP                               */
0,                     /* A2 CopyBytes2           CPUID                             */
C_MODRM,               /* A3 CopyBytes2Mod        BT  (0F A3)                       */
C_MODRM+C_DATA1,       /* A4 CopyBytes2Mod1       SHLD                              */
C_MODRM,               /* A5 CopyBytes2Mod        SHLD                              */
C_ERROR,               /* A6 Invalid              _A6                               */
C_ERROR,               /* A7 Invalid              _A7                               */
0,                     /* A8 CopyBytes2           PUSH                              */
0,                     /* A9 CopyBytes2           POP                               */
0,                     /* AA CopyBytes2           RSM                               */
C_MODRM,               /* AB CopyBytes2Mod        BTS (0F AB)                       */
C_MODRM+C_DATA1,       /* AC CopyBytes2Mod1       SHRD                              */
C_MODRM,               /* AD CopyBytes2Mod        SHRD                              */
C_MODRM,               /* AE CopyBytes2Mod        FXRSTOR/1,FXSAVE/0                */
C_MODRM,               /* AF CopyBytes2Mod        IMUL (0F AF)                      */
C_MODRM,               /* B0 CopyBytes2Mod        CMPXCHG (0F B0)                   */
C_MODRM,               /* B1 CopyBytes2Mod        CMPXCHG (0F B1)                   */
C_MODRM,               /* B2 CopyBytes2Mod        LSS/r                             */
C_MODRM,               /* B3 CopyBytes2Mod        BTR (0F B3)                       */
C_MODRM,               /* B4 CopyBytes2Mod        LFS/r                             */
C_MODRM,               /* B5 CopyBytes2Mod        LGS/r                             */
C_MODRM,               /* B6 CopyBytes2Mod        MOVZX/r                           */
C_MODRM,               /* B7 CopyBytes2Mod        MOVZX/r                           */
C_ERROR,               /* B8 Invalid              _B8                               */
C_ERROR,               /* B9 Invalid              _B9                               */
C_MODRM+C_DATA1,       /* BA CopyBytes2Mod1       BT & BTC & BTR & BTS (0F BA)      */
C_MODRM,               /* BB CopyBytes2Mod        BTC (0F BB)                       */
C_MODRM,               /* BC CopyBytes2Mod        BSF (0F BC)                       */
C_MODRM,               /* BD CopyBytes2Mod        BSR (0F BD)                       */
C_MODRM,               /* BE CopyBytes2Mod        MOVSX/r                           */
C_MODRM,               /* BF CopyBytes2Mod        MOVSX/r                           */
C_MODRM,               /* C0 CopyBytes2Mod        XADD/r                            */
C_MODRM,               /* C1 CopyBytes2Mod        XADD/r                            */
C_MODRM,	//C_ERROR,               /* C2 Invalid              _C2                               */
C_MODRM,	//C_ERROR,               /* C3 Invalid              _C3                               */
C_MODRM,	//C_ERROR,               /* C4 Invalid              _C4                               */
C_MODRM,	//C_ERROR,               /* C5 Invalid              _C5                               */
C_MODRM,	//C_ERROR,               /* C6 Invalid              _C6                               */
C_MODRM,               /* C7 CopyBytes2Mod        CMPXCHG8B (0F C7)                 */
0,                     /* C8 CopyBytes2           BSWAP 0F C8 + rd                  */
0,                     /* C9 CopyBytes2           BSWAP 0F C8 + rd                  */
0,                     /* CA CopyBytes2           BSWAP 0F C8 + rd                  */
0,                     /* CB CopyBytes2           BSWAP 0F C8 + rd                  */
0,                     /* CC CopyBytes2           BSWAP 0F C8 + rd                  */
0,                     /* CD CopyBytes2           BSWAP 0F C8 + rd                  */
0,                     /* CE CopyBytes2           BSWAP 0F C8 + rd                  */
0,                     /* CF CopyBytes2           BSWAP 0F C8 + rd                  */
C_ERROR,               /* D0 Invalid              _D0                               */
C_MODRM,               /* D1 CopyBytes2Mod        PSRLW/r                           */
C_MODRM,               /* D2 CopyBytes2Mod        PSRLD/r                           */
C_MODRM,               /* D3 CopyBytes2Mod        PSRLQ/r                           */
C_MODRM,	//C_ERROR,               /* D4 Invalid              _D4                               */
C_MODRM,               /* D5 CopyBytes2Mod        PMULLW/r                          */
C_MODRM,	//C_ERROR,               /* D6 Invalid              _D6                               */
C_MODRM,	//C_ERROR,               /* D7 Invalid              _D7                               */
C_MODRM,               /* D8 CopyBytes2Mod        PSUBUSB/r                         */
C_MODRM,               /* D9 CopyBytes2Mod        PSUBUSW/r                         */
C_MODRM,	//C_ERROR,               /* DA Invalid              _DA                               */
C_MODRM,               /* DB CopyBytes2Mod        PAND/r                            */
C_MODRM,               /* DC CopyBytes2Mod        PADDUSB/r                         */
C_MODRM,               /* DD CopyBytes2Mod        PADDUSW/r                         */
C_MODRM,	//C_ERROR,               /* DE Invalid              _DE                               */
C_MODRM,               /* DF CopyBytes2Mod        PANDN/r                           */
C_MODRM,	//C_ERROR,               /* E0 Invalid              _E0                               */
C_MODRM,               /* E1 CopyBytes2Mod        PSRAW/r                           */
C_MODRM,               /* E2 CopyBytes2Mod        PSRAD/r                           */
C_MODRM,	//C_ERROR,               /* E3 Invalid              _E3                               */
C_MODRM,	//C_ERROR,               /* E4 Invalid              _E4                               */
C_MODRM,               /* E5 CopyBytes2Mod        PMULHW/r                          */
C_MODRM,	//C_ERROR,               /* E6 Invalid              _E6                               */
C_MODRM,	//C_ERROR,               /* E7 Invalid              _E7                               */
C_MODRM,               /* E8 CopyBytes2Mod        PSUBB/r                           */
C_MODRM,               /* E9 CopyBytes2Mod        PSUBW/r                           */
C_MODRM,	//C_ERROR,               /* EA Invalid              _EA                               */
C_MODRM,               /* EB CopyBytes2Mod        POR/r                             */
C_MODRM,               /* EC CopyBytes2Mod        PADDSB/r                          */
C_MODRM,               /* ED CopyBytes2Mod        PADDSW/r                          */
C_MODRM,	//C_ERROR,               /* EE Invalid              _EE                               */
C_MODRM,               /* EF CopyBytes2Mod        PXOR/r                            */
C_ERROR,               /* F0 Invalid              _F0                               */
C_MODRM,               /* F1 CopyBytes2Mod        PSLLW/r                           */
C_MODRM,               /* F2 CopyBytes2Mod        PSLLD/r                           */
C_MODRM,               /* F3 CopyBytes2Mod        PSLLQ/r                           */
C_MODRM,	//C_ERROR,               /* F4 Invalid              _F4                               */
C_MODRM,               /* F5 CopyBytes2Mod        PMADDWD/r                         */
C_MODRM,	//C_ERROR,               /* F6 Invalid              _F6                               */
C_MODRM,	//C_ERROR,               /* F7 Invalid              _F7                               */
C_MODRM,               /* F8 CopyBytes2Mod        PSUBB/r                           */
C_MODRM,               /* F9 CopyBytes2Mod        PSUBW/r                           */
C_MODRM,               /* FA CopyBytes2Mod        PSUBD/r                           */
C_MODRM,	//C_ERROR,               /* FB Invalid              _FB                               */
C_MODRM,               /* FC CopyBytes2Mod        PADDB/r                           */
C_MODRM,               /* FD CopyBytes2Mod        PADDW/r                           */
C_MODRM,               /* FE CopyBytes2Mod        PADDD/r                           */
C_ERROR                /* FF Invalid              _FF                               */
}; /* ade32_table[] */

#endif /* __ADE32TBL_C__ */
