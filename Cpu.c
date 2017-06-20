//
//  Cpu.c
//  LC-3b
//
//  Created by Ian Bravo on 7/4/14.
//  Copyright (c) 2014 Ibrarabay. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cpu.h"

int8_t M[MAX_MEM];
int16_t MAR;
int16_t PC;
uint16_t MDR;
uint16_t IR;
uint16_t R0;
uint16_t R1;
uint16_t R2;
uint16_t R3;
uint16_t R4;
uint16_t R5;
uint16_t R6;
uint16_t R7;
uint8_t CC[3] = {};
uint8_t PSR;

void cpu()
{
    instructionStruct inst;
    fetch();
    decodeExecute(&inst);
}

void loader(FILE *program)
{
    uint32_t i = 0;
    uint8_t temp = 0;
    
    if (program == NULL)
    {
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    
    for (i = 0; i < MAX_MEM; i++)
    {
        M[i] = 0xFF;
    }
    
    i = 0;
    
    while ((fread(&temp, sizeof(uint8_t), 1, program)) != 0)
    {
        M[i] = temp;
        i++;
    }
    PC = 0;
    initRegisters();
}

void fetch()
{
    uint16_t temp = 0;
    MAR = PC;
    PC += 2;
    
    MDR = M[((int8_t)MAR + 1)];
    MDR = MDR << 8;
    MDR = MDR >> 8;
    temp = M[(int8_t)MAR];
    temp = temp << 8;
    MDR |= temp;
    IR = MDR;
}

void decodeExecute(instructionStruct *inst)
{
    uint16_t bit5 = 0;
    sizeTypeEnum typeSize;
    
    inst->opcode = (IR & MASK_OPCODE) >> 12;
    
    switch (inst->opcode)
    {
        case ADD:
            typeSize = i5;
            bit5 = (IR & MASK_BIT5) >> 5;
            if (bit5 == TRUE)
            {
                inst->value = IR & MASK_IMM5;
                inst->dr = (IR & MASK_DR) >> 9;
                inst->sr1 = (IR & MASK_SR1) >> 6;
                
                checkValueStatus(typeSize, inst);
                
                inst->sr1 = getRegisterValue(inst->sr1);
                inst->result = inst->sr1 + inst-> value;
                storeResult(inst->result, inst->dr);
                setCC(inst);
            }
            else
            {
                inst->dr = (IR & MASK_DR) >> 9;
                inst->sr1 = (IR & MASK_SR1) >> 6;
                inst->sr2 = IR & MASK_SR2;
                
                inst->sr1 = getRegisterValue(inst->sr1);
                inst->sr2 = getRegisterValue(inst->sr2);
                inst->result = inst->sr1 + inst->sr2;
                storeResult(inst->result, inst->dr);
                setCC(inst);
            }
            break;
            
        case AND:
            typeSize = i5;
            bit5 = (IR & MASK_BIT5) >> 5;
            if (bit5 == TRUE)
            {
                inst->value = IR & MASK_IMM5;
                inst->dr = (IR & MASK_DR) >> 9;
                inst->sr1 = (IR & MASK_SR1) >> 6;
                
                checkValueStatus(typeSize, inst);
                
                inst->sr1 = getRegisterValue(inst->sr1);
                inst->result = inst->sr1 & inst-> value;
                storeResult(inst->result, inst->dr);
                setCC(inst);
            }
            else
            {
                inst->dr = (IR & MASK_DR) >> 9;
                inst->sr1 = (IR & MASK_SR1) >> 6;
                inst->sr2 = IR & MASK_SR2;
                
                inst->sr1 = getRegisterValue(inst->sr1);
                inst->sr2 = getRegisterValue(inst->sr2);
                inst->result = inst->sr1 & inst->sr2;
                storeResult(inst->result, inst->dr);
                setCC(inst);
            }
            break;
            
        case JMP:
            if (((IR & MASK_RET_JMP) >> 6) == 7)
            {
                PC = getRegisterValue(7);
            }
            else
            {
                inst->sr1 = (IR & MASK_RET_JMP) >> 6;
                PC = getRegisterValue(inst->sr1);
            }
            break;
            
        case JSR:
            R7 = PC;
            typeSize = P9;
            if (((IR & MASK_CPU_JSR) >> 11) == 0)
            {
                inst->sr1 = (IR & MASK_CPU_JSRR) >> 6;
                PC = getRegisterValue(inst->sr1);
            }
            else
            {
                inst->value = IR & MASK_STYPE_PCOFFSET11;
                checkValueStatus(typeSize, inst);
                PC = PC + (inst->value << 1);
            }
            break;
            
        case LDB:
            typeSize = off6;
            
            inst->dr = (IR & MASK_LDB_DR) >> 9;
            inst->sr1 = (IR & MASK_LDB_BR) >> 6;
            inst->value = IR & MASK_LDB_VALUE;
            
            checkValueStatus(typeSize, inst);
            
            inst->result = inst->value + getRegisterValue(inst->sr1);
            inst->result = M[(uint8_t)inst->value];
            storeResult(inst->result, inst->sr1);
            setCC(inst);
            break;
            
        case LDW:
            typeSize = off6;
            uint16_t temp = 0;
            inst->dr = (IR & MASK_LDB_DR) >> 9;
            inst->sr1 = (IR & MASK_LDB_BR) >> 6;
            inst->value = IR & MASK_LDB_VALUE;
            
            checkValueStatus(typeSize, inst);
            
            inst->value = inst->value << 1;
            inst->result = inst->value + getRegisterValue(inst->sr1);
            if (inst->result % 2 != 0)
            {
                printf("Excepcion de direccion impar\n");
                exit(1);
            }
            inst->result = M[(int8_t)inst->result + 1];
            inst->result = inst->result << 8;
            inst->result = inst->result >> 8;
            temp = M[(int8_t)inst->result];
            temp = temp << 8;
            inst->result |= temp;
            
            storeResult(inst->result, inst->dr);
            setCC(inst);
            break;
            
        case LEA:
            typeSize = P9;
            
            inst->dr = (IR & MASK_LDB_DR) >> 9;
            inst->value = IR & MASK_P9_LEA;
            
            checkValueStatus(typeSize, inst);
            storeResult(inst->value, inst->dr);
            setCC(inst);
            break;
            
        case LSHF:
            inst->dr = (IR & MASK_LDB_DR) >> 9;
            inst->sr1 = (IR & MASK_LDB_BR) >> 6;
            inst->value = IR & MASK_SHF_VALUE;
            inst->sr1 = getRegisterValue(inst->sr1);
            
            if (((IR & MASK_SHF_TYPE) >> 4) == 0)
            {
                inst->result = inst->sr1 << inst->value;
            }
            else if (((IR & MASK_SHF_TYPE) >> 4) == 1)
            {
                inst->result = inst->sr1 >> inst->value;
            }
            else if (((IR & MASK_SHF_TYPE) >> 4) == 3)
            {
                uint16_t temp = 0;
                temp = inst->sr1 & 0x8000;
                inst->result = inst->sr1 >> inst->value;
                inst->result |= temp;
            }
            storeResult(inst->result, inst->dr);
            setCC(inst);
            break;
            
        case STB:
            typeSize = off6;
            
            inst->dr = (IR & MASK_LDB_DR) >> 9;
            inst->sr1 = (IR & MASK_LDB_BR) >> 6;
            inst->value = IR & MASK_LDB_VALUE;
            
            checkValueStatus(typeSize, inst);
            
            inst->dr = (uint8_t)getRegisterValue(inst->dr);
            inst->sr1 = getRegisterValue(inst->sr1);
            M[inst->sr1 + inst->value] = inst->dr;
            break;
            
        case STW:
            typeSize = off6;
            uint16_t tempVal = 0;
            inst->dr = (IR & MASK_LDB_DR) >> 9;
            inst->sr1 = (IR & MASK_LDB_BR) >> 6;
            inst->value = IR & MASK_LDB_VALUE;
            
            checkValueStatus(typeSize, inst);
            
            inst->value = inst->value << 1;
            inst->result = inst->value + getRegisterValue(inst->sr1);
            if (inst->result % 2 != 0)
            {
                printf("Excepcion de direccion impar\n");
                exit(1);
            }
            inst->sr1 = getRegisterValue(inst->sr1);
            tempVal = inst->sr1 >> 8;
            M[inst->result] = tempVal;
            M[inst->result + 1] = tempVal & 0x00FF;
            break;
            
        case XOR:
            typeSize = i5;
            
            inst->dr = (IR & MASK_DR) >> 9;
            inst->sr1 = (IR & MASK_SR1) >> 6;
            
            if (((IR & MASK_NOT_XOR) >> 5) == 63)
            {
                inst->sr1 = getRegisterValue(inst->sr1);
                inst->result = ~(inst->sr1);
                storeResult(inst->result, inst->dr);
                break;
            }
            
            if (((IR & MASK_XOR_TYPE) >> 5) == 0)
            {
                inst->sr2 = IR & MASK_SR2;
                inst->sr1 = getRegisterValue(inst->sr1);
                inst->sr2 = getRegisterValue(inst->sr2);
                inst->result = inst->sr1 ^ inst->sr2;
                storeResult(inst->result, inst->dr);
                setCC(inst);
            }
            else
            {
                inst->value = IR & MASK_XOR_VALUE;
                inst->sr1 = getRegisterValue(inst->sr1);
                
                checkValueStatus(typeSize, inst);
                
                inst->result = inst->sr1 ^ inst->value;
                storeResult(inst->result, inst->dr);
                setCC(inst);
            }
            break;
            
        case BR:
            typeSize = P9;
            uint16_t ccCode = (IR & MASK_BR) >> 9;
            inst->value = IR & MASK_BR_P9;
            
            checkValueStatus(typeSize, inst);
            
            switch (ccCode) {
                case 1:
                    if (CC[2] == 1)
                    {
                        PC = (PC + (inst->value << 1)) - 2;
                    }
                    break;
                    
                case 2:
                    if (CC[1] == 1)
                    {
                        PC = (PC + (inst->value << 1)) - 2;
                    }
                    break;
                    
                case 3:
                    if (CC[2] == 1 || CC[1] == 1)
                    {
                        PC = (PC + (inst->value << 1)) - 2;
                    }
                    break;
                    
                case 4:
                    if (CC[0] == 1)
                    {
                        PC = (PC + (inst->value << 1)) - 2;
                    }
                    break;
                    
                case 5:
                    if (CC[0] == 1 || CC[2] == 1)
                    {
                        PC = (PC + (inst->value << 1)) - 2;
                    }
                    break;
                    
                case 6:
                    if (CC[0] == 1 || CC[1] == 1)
                    {
                        PC = (PC + (inst->value << 1)) - 2;
                    }
                    break;
                    
                case 7:
                    if (CC[0] == 1 || CC[1] == 1 || CC[2] == 1)
                    {
                        PC = (PC + (inst->value << 1)) - 2;
                    }
                    break;
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}

void checkValueStatus(sizeTypeEnum sizeType, instructionStruct *inst)
{
    uint16_t temp;
    switch (sizeType)
    {
        case i5:
            if (((inst->value & MASK_STYPE_IMM5) >> 4) == TRUE)
            {
                temp = 0xFFE0 | inst->value;
                temp = (~temp) + 1;
                temp *= -1;
                inst->value = temp;
            }
            break;
            
        case P9:
            if (((inst->value & MASK_STYPE_PCOFFSET9) >> 8) == TRUE)
            {
                temp = inst->value | 0xFE00;
                temp = (~temp) + 1;
                temp *= -1;
                inst->value = temp;
            }
            break;
            
        case P11:
            if (((inst->value & MASK_STYPE_PCOFFSET11) >> 10) == TRUE)
            {
                temp = inst->value | 0xF800;
                temp = (~temp) + 1;
                temp *= -1;
                inst->value = temp;
            }
            break;
            
        case off6:
            if (((inst->value & MASK_STYPE_OFFSET6) >> 5) == TRUE)
            {
                temp = 0xFFE0 | inst->value;
                temp = (~temp) + 1;
                temp *= -1;
                inst->value = temp;
            }
            break;
            
        default:
            break;
    }
}

void go()
{
    while (IR != 0xFFFF)
    {
        cpu();
    }
    printf("Programa completado y reiniciado\n");
    PC = 0;
}

void run(uint16_t lineas)
{
    int8_t i = 0;
    
    for (i = 0; i < lineas; i++)
    {
        if (IR == 0xFFFF)
        {
            PC = 0;
            printf("Programa completado y reiniciado\n");
            return;
        }
        cpu();
    }
}

void rdump()
{
    printf("R0: %X\nR1: %X\nR2: %X\nR3: %X\nR4: %X\nR5: %X\nR6: %X\nR7: %X\n", R0, R1, R2, R3, R4, R5, R6, R7);
    printf("PC: %x\n", PC);
    printf("IR: %x\n\n", IR);
    printf("Condition Codes\n");
    if (CC[0] == 1)
        printf("Negative: True\n");
    else
       printf("Negative: False\n");
    if (CC[1] == 1)
        printf("Zero: True\n");
    else
        printf("Zero: False\n");
    if (CC[2] == 1)
        printf("Positive: True\n");
    else
        printf("Positive: False\n");
}

void storeResult(uint16_t result, uint16_t reg)
{
    switch (reg)
    {
        case Register0:
            R0 = result;
            break;
            
        case Register1:
            R1 = result;
            break;
            
        case Register2:
            R2 = result;
            break;
            
        case Register3:
            R3 = result;
            break;
            
        case Register4:
            R4 = result;
            break;
            
        case Register5:
            R5 = result;
            break;
            
        case Register6:
            R6 = result;
            break;
        case Register7:
            R7 = result;
            break;
            
        default:
            printf("Error");
            exit(1);
            break;
    }
}

void setCC(instructionStruct *inst)
{
    CCenum ccCode;
    if (inst->result < 0)
        ccCode = negative;
    else if (inst->result == 0)
        ccCode = zero;
    else
        ccCode = positive;
        
    
    switch (ccCode)
    {
        case negative:
            CC[0] = 1;
            CC[1] = 0;
            CC[2] = 0;
            break;
            
        case zero:
            CC[0] = 0;
            CC[1] = 1;
            CC[2] = 0;
            break;
            
        case positive:
            CC[0] = 0;
            CC[1] = 0;
            CC[2] = 1;
            break;
            
        default:
            break;
    }
}

void memDump(uint16_t low, uint16_t high)
{
    uint16_t i = 0;
    if (low < 0 || high < 0 || high > MAX_MEM || low > high)
    {
        printf("Valores invalidos\n");
    }
    else
    {
        while (low <= high)
        {
            printf("%x = %x || %d\n", low, M[low], M[low]);
            low++;
        }
    }
}

uint16_t getRegisterValue(uint16_t reg)
{
    switch (reg)
    {
        case Register0:
            return R0;
            break;
            
        case Register1:
            return R1;
            break;
            
        case Register2:
            return R2;
            break;
            
        case Register3:
            return R3;
            break;
            
        case Register4:
            return R4;
            break;
            
        case Register5:
            return R5;
            break;
            
        case Register6:
            return R6;
            break;
        case Register7:
            return R7;
            break;
            
        default:
            printf("Error");
            exit(1);
            break;
    }
}

void initRegisters()
{
    R0 = 0;
    R1 = 0;
    R2 = 0;
    R3 = 0;
    R4 = 0;
    R5 = 0;
    R6 = 0;
    R7 = 0;
}