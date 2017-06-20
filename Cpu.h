//
//  Cpu.h
//  LC-3b
//
//  Created by Ian Bravo on 7/4/14.
//  Copyright (c) 2014 Ibrarabay. All rights reserved.
//

#ifndef LC_3b_Cpu_h
#define LC_3b_Cpu_h

#define TRUE 1
#define FALSE 0

#define MAX_MEM 0xFDFF

#define MASK_OPCODE 0xF000
#define MASK_DR 0x0E00
#define MASK_SR1 0x01C0
#define MASK_SR2 0x0007
#define MASK_BIT5 0x0020

#define MASK_XOR_TYPE 0x0020
#define MASK_XOR_VALUE 0x001F

#define MASK_NOT_XOR 0x003F

#define MASK_BR 0x0E00
#define MASK_BR_P9 0x01FF

#define MASK_RET_JMP 0x01C0

#define MASK_CPU_JSR 0x0800
#define MASK_CPU_JSRR 0x01C0

#define MASK_SHF_VALUE 0x000F
#define MASK_SHF_TYPE 0x0030

#define MASK_P9_LEA 0x01FF

#define MASK_LDB_DR 0x0F80
#define MASK_LDB_BR 0x01C0
#define MASK_LDB_VALUE 0x003F

#define MASK_IMM5 0x001F

#define MASK_STYPE_IMM5 0x0010
#define MASK_STYPE_PCOFFSET9 0x0100
#define MASK_STYPE_PCOFFSET11 0x0400
#define MASK_STYPE_OFFSET6 0x0020

typedef struct instructionStruct
{
    uint16_t opcode;
    uint16_t mode;
    uint16_t dr;
    uint16_t sr1;
    uint16_t sr2;
    uint16_t value;
    int16_t result;
}instructionStruct;

typedef enum CCenum
{
    negative = 0,
    zero,
    positive
}CCenum;

typedef enum opcodeEnum
{
    BR = 0,
    ADD,
    LDB,
    STB,
    JSR,
    AND,
    LDW,
    STW,
    RTI,
    XOR,
    NOTUSED,
    NOTUSED2,
    JMP,
    LSHF,
    LEA
}opcodeEnum;

typedef enum sizeTypeEnum
{
    i5 = 0,
    P9,
    P11,
    off6
}sizeTypeEnum;

typedef enum registersEnum
{
    Register0 = 0,
    Register1,
    Register2,
    Register3,
    Register4,
    Register5,
    Register6,
    Register7
}registersEnum;

void cpu();
void fetch();
void decodeExecute(instructionStruct *inst);
void execute();
void loader(FILE *program);
void initRegisters();
void checkValueStatus(sizeTypeEnum sizeType, instructionStruct *inst);
void storeResult(uint16_t result, uint16_t reg);
uint16_t getRegisterValue(uint16_t reg);
void setCC(instructionStruct *inst);
void rdump();
void go();
void run(uint16_t lineas);
void memDump(uint16_t low, uint16_t high);
#endif
