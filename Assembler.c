//
//  Assembler.c
//  LC-3b
//
//  Created by Ian Bravo on 7/2/14.
//  Copyright (c) 2014 Ibrarabay. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Types.h"
#include "Assembler.h"

FILE *hex;

void assembler(FILE *programa)
{
    uint8_t linea[20] = {};
    
    hex = fopen("/Users/Ian_Bravo/Desktop/programa.hex", "w");
    
    if (programa == NULL)
    {
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    
    while ((fgets(linea, 20, programa)) != 0)
    {
        printf("%s\n", linea);
        assembleCommand(linea);
    }
    fflush(programa);
    fflush(hex);
    fclose(programa);
    fclose(hex);
}

void assembleCommand(uint8_t instruction[])
{
    uint16_t i = 0;
    uint16_t j = 0;
    uint16_t k = 0;
    uint8_t opcode[5] = {};
    uint8_t operandos[20] = {};
    uint8_t immVal[4] = {};
    uint8_t primero = 0;
    uint8_t segundo = 0;
    uint8_t negativeFlag = FALSE;
    uint16_t command = 0;
    uint16_t value = 0;
    enum twoCType twoType = boffset6;
    
    while (instruction[i] != ' ' && instruction[i] != '\0' && instruction[i] != '\n')
    {
        opcode[i] = instruction[i];
        i++;
    }
    i++;
    opcode[i] = '\0';
    
    while (instruction[i] != '\0')
    {
        operandos[j] = instruction[i];
        i++;
        j++;
    }
    
    if (strcmp(opcode, "ADD") == 0)
    {
        command |= (uint16_t)MASK_ADD;
        if (operandos[0] == 'R')
        {
            if (operandos[1] == '0' || operandos[1] == '1' || operandos[1] == '2' || operandos[1] == '3' || operandos[1] == '4' || operandos[1] == '5' || operandos[1] == '6' || operandos[1] == '7')
            {
                if (operandos[1] == '0')
                    command |= MASK_ADD_DR_R0;
                else if (operandos[1] == '1')
                    command |= MASK_ADD_DR_R1;
                else if (operandos[1] == '2')
                    command |= MASK_ADD_DR_R2;
                else if (operandos[1] == '3')
                    command |= MASK_ADD_DR_R3;
                else if (operandos[1] == '4')
                    command |= MASK_ADD_DR_R4;
                else if (operandos[1] == '5')
                    command |= MASK_ADD_DR_R5;
                else if (operandos[1] == '6')
                    command |= MASK_ADD_DR_R6;
                else if (operandos[1] == '7')
                    command |= MASK_ADD_DR_R7;
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[3] == 'R')
            {
                if (operandos[4] == '0' || operandos[4] == '1' || operandos[4] == '2' || operandos[4] == '3' || operandos[4] == '4' || operandos[4] == '5' || operandos[4] == '6' || operandos[4] == '7')
                {
                    if (operandos[4] == '0')
                        command |= MASK_ADD_SR1_R0;
                    else if (operandos[4] == '1')
                        command |= MASK_ADD_SR1_R1;
                    else if (operandos[4] == '2')
                        command |= MASK_ADD_SR1_R2;
                    else if (operandos[4] == '3')
                        command |= MASK_ADD_SR1_R3;
                    else if (operandos[4] == '4')
                        command |= MASK_ADD_SR1_R4;
                    else if (operandos[4] == '5')
                        command |= MASK_ADD_SR1_R5;
                    else if (operandos[4] == '6')
                        command |= MASK_ADD_SR1_R6;
                    else if (operandos[4] == '7')
                        command |= MASK_ADD_SR1_R7;
                    else
                    {
                        printf("Rutina erronea\n");
                        exit(1);
                    }
                }
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[6] == 'R')
            {
                if (operandos[7] == '0' || operandos[7] == '1' || operandos[7] == '2' || operandos[7] == '3' || operandos[7] == '4' || operandos[7] == '5' || operandos[7] == '6' || operandos[7] == '7')
                {
                    if (operandos[7] == '0')
                        command |= MASK_ADD_SR2_R0;
                    else if (operandos[7] == '1')
                        command |= MASK_ADD_SR2_R1;
                    else if (operandos[7] == '2')
                        command |= MASK_ADD_SR2_R2;
                    else if (operandos[7] == '3')
                        command |= MASK_ADD_SR2_R3;
                    else if (operandos[7] == '4')
                        command |= MASK_ADD_SR2_R4;
                    else if (operandos[7] == '5')
                        command |= MASK_ADD_SR2_R5;
                    else if (operandos[7] == '6')
                        command |= MASK_ADD_SR2_R6;
                    else if (operandos[7] == '7')
                        command |= MASK_ADD_SR2_R7;
                    else
                    {
                        printf("Rutina erronea\n");
                        exit(1);
                    }
                }
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else if (operandos[6] == '#')
            {
                if (operandos[7] == '-')
                {
                    negativeFlag = TRUE;
                    twoType = imm5;
                    i = 0;
                    k = 8;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                    command |= MASK_BIT5_ADD;
                }
                else
                {
                    negativeFlag = FALSE;
                    twoType = imm5;
                    i = 0;
                    k = 7;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                    command |= MASK_BIT5_ADD;
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "AND") == 0)
    {
        command |= (uint16_t)MASK_AND;
        if (operandos[0] == 'R')
        {
            if (operandos[1] == '0' || operandos[1] == '1' || operandos[1] == '2' || operandos[1] == '3' || operandos[1] == '4' || operandos[1] == '5' || operandos[1] == '6' || operandos[1] == '7')
            {
                if (operandos[1] == '0')
                    command |= MASK_ADD_DR_R0;
                else if (operandos[1] == '1')
                    command |= MASK_ADD_DR_R1;
                else if (operandos[1] == '2')
                    command |= MASK_ADD_DR_R2;
                else if (operandos[1] == '3')
                    command |= MASK_ADD_DR_R3;
                else if (operandos[1] == '4')
                    command |= MASK_ADD_DR_R4;
                else if (operandos[1] == '5')
                    command |= MASK_ADD_DR_R5;
                else if (operandos[1] == '6')
                    command |= MASK_ADD_DR_R6;
                else if (operandos[1] == '7')
                    command |= MASK_ADD_DR_R7;
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[3] == 'R')
            {
                if (operandos[4] == '0' || operandos[4] == '1' || operandos[4] == '2' || operandos[4] == '3' || operandos[4] == '4' || operandos[4] == '5' || operandos[4] == '6' || operandos[4] == '7')
                {
                    if (operandos[4] == '0')
                        command |= MASK_ADD_SR1_R0;
                    else if (operandos[4] == '1')
                        command |= MASK_ADD_SR1_R1;
                    else if (operandos[4] == '2')
                        command |= MASK_ADD_SR1_R2;
                    else if (operandos[4] == '3')
                        command |= MASK_ADD_SR1_R3;
                    else if (operandos[4] == '4')
                        command |= MASK_ADD_SR1_R4;
                    else if (operandos[4] == '5')
                        command |= MASK_ADD_SR1_R5;
                    else if (operandos[4] == '6')
                        command |= MASK_ADD_SR1_R6;
                    else if (operandos[4] == '7')
                        command |= MASK_ADD_SR1_R7;
                    else
                    {
                        printf("Rutina erronea\n");
                        exit(1);
                    }
                }
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[6] == 'R')
            {
                if (operandos[7] == '0' || operandos[7] == '1' || operandos[7] == '2' || operandos[7] == '3' || operandos[7] == '4' || operandos[7] == '5' || operandos[7] == '6' || operandos[7] == '7')
                {
                    if (operandos[7] == '0')
                        command |= MASK_ADD_SR2_R0;
                    else if (operandos[7] == '1')
                        command |= MASK_ADD_SR2_R1;
                    else if (operandos[7] == '2')
                        command |= MASK_ADD_SR2_R2;
                    else if (operandos[7] == '3')
                        command |= MASK_ADD_SR2_R3;
                    else if (operandos[7] == '4')
                        command |= MASK_ADD_SR2_R4;
                    else if (operandos[7] == '5')
                        command |= MASK_ADD_SR2_R5;
                    else if (operandos[7] == '6')
                        command |= MASK_ADD_SR2_R6;
                    else if (operandos[7] == '7')
                        command |= MASK_ADD_SR2_R7;
                    else
                    {
                        printf("Rutina erronea\n");
                        exit(1);
                    }
                }
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else if (operandos[6] == '#')
            {
                if (operandos[7] == '-')
                {
                    negativeFlag = TRUE;
                    twoType = imm5;
                    i = 0;
                    k = 8;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                    command |= MASK_BIT5_ADD;
                }
                else
                {
                    negativeFlag = FALSE;
                    twoType = imm5;
                    i = 0;
                    k = 7;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                    command |= MASK_BIT5_ADD;
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "NOT") == 0)
    {
        command |= (uint16_t)MASK_XOR;
        if (operandos[0] == 'R')
        {
            if (operandos[1] == '0' || operandos[1] == '1' || operandos[1] == '2' || operandos[1] == '3' || operandos[1] == '4' || operandos[1] == '5' || operandos[1] == '6' || operandos[1] == '7')
            {
                if (operandos[1] == '0')
                    command |= MASK_ADD_DR_R0;
                else if (operandos[1] == '1')
                    command |= MASK_ADD_DR_R1;
                else if (operandos[1] == '2')
                    command |= MASK_ADD_DR_R2;
                else if (operandos[1] == '3')
                    command |= MASK_ADD_DR_R3;
                else if (operandos[1] == '4')
                    command |= MASK_ADD_DR_R4;
                else if (operandos[1] == '5')
                    command |= MASK_ADD_DR_R5;
                else if (operandos[1] == '6')
                    command |= MASK_ADD_DR_R6;
                else if (operandos[1] == '7')
                    command |= MASK_ADD_DR_R7;
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[3] == 'R')
            {
                if (operandos[4] == '0' || operandos[4] == '1' || operandos[4] == '2' || operandos[4] == '3' || operandos[4] == '4' || operandos[4] == '5' || operandos[4] == '6' || operandos[4] == '7')
                {
                    if (operandos[4] == '0')
                        command |= MASK_ADD_SR1_R0;
                    else if (operandos[4] == '1')
                        command |= MASK_ADD_SR1_R1;
                    else if (operandos[4] == '2')
                        command |= MASK_ADD_SR1_R2;
                    else if (operandos[4] == '3')
                        command |= MASK_ADD_SR1_R3;
                    else if (operandos[4] == '4')
                        command |= MASK_ADD_SR1_R4;
                    else if (operandos[4] == '5')
                        command |= MASK_ADD_SR1_R5;
                    else if (operandos[4] == '6')
                        command |= MASK_ADD_SR1_R6;
                    else if (operandos[4] == '7')
                        command |= MASK_ADD_SR1_R7;
                    else
                    {
                        printf("Rutina erronea\n");
                        exit(1);
                    }
                }
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        
        command |= MASK_LASTBITS_NOT;
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "XOR") == 0)
    {
        command |= (uint16_t)MASK_XOR;
        if (operandos[0] == 'R')
        {
            if (operandos[1] == '0' || operandos[1] == '1' || operandos[1] == '2' || operandos[1] == '3' || operandos[1] == '4' || operandos[1] == '5' || operandos[1] == '6' || operandos[1] == '7')
            {
                if (operandos[1] == '0')
                    command |= MASK_ADD_DR_R0;
                else if (operandos[1] == '1')
                    command |= MASK_ADD_DR_R1;
                else if (operandos[1] == '2')
                    command |= MASK_ADD_DR_R2;
                else if (operandos[1] == '3')
                    command |= MASK_ADD_DR_R3;
                else if (operandos[1] == '4')
                    command |= MASK_ADD_DR_R4;
                else if (operandos[1] == '5')
                    command |= MASK_ADD_DR_R5;
                else if (operandos[1] == '6')
                    command |= MASK_ADD_DR_R6;
                else if (operandos[1] == '7')
                    command |= MASK_ADD_DR_R7;
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[3] == 'R')
            {
                if (operandos[4] == '0' || operandos[4] == '1' || operandos[4] == '2' || operandos[4] == '3' || operandos[4] == '4' || operandos[4] == '5' || operandos[4] == '6' || operandos[4] == '7')
                {
                    if (operandos[4] == '0')
                        command |= MASK_ADD_SR1_R0;
                    else if (operandos[4] == '1')
                        command |= MASK_ADD_SR1_R1;
                    else if (operandos[4] == '2')
                        command |= MASK_ADD_SR1_R2;
                    else if (operandos[4] == '3')
                        command |= MASK_ADD_SR1_R3;
                    else if (operandos[4] == '4')
                        command |= MASK_ADD_SR1_R4;
                    else if (operandos[4] == '5')
                        command |= MASK_ADD_SR1_R5;
                    else if (operandos[4] == '6')
                        command |= MASK_ADD_SR1_R6;
                    else if (operandos[4] == '7')
                        command |= MASK_ADD_SR1_R7;
                    else
                    {
                        printf("Rutina erronea\n");
                        exit(1);
                    }
                }
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[6] == 'R')
            {
                if (operandos[7] == '0' || operandos[7] == '1' || operandos[7] == '2' || operandos[7] == '3' || operandos[7] == '4' || operandos[7] == '5' || operandos[7] == '6' || operandos[7] == '7')
                {
                    if (operandos[7] == '0')
                        command |= MASK_ADD_SR2_R0;
                    else if (operandos[7] == '1')
                        command |= MASK_ADD_SR2_R1;
                    else if (operandos[7] == '2')
                        command |= MASK_ADD_SR2_R2;
                    else if (operandos[7] == '3')
                        command |= MASK_ADD_SR2_R3;
                    else if (operandos[7] == '4')
                        command |= MASK_ADD_SR2_R4;
                    else if (operandos[7] == '5')
                        command |= MASK_ADD_SR2_R5;
                    else if (operandos[7] == '6')
                        command |= MASK_ADD_SR2_R6;
                    else if (operandos[7] == '7')
                        command |= MASK_ADD_SR2_R7;
                    else
                    {
                        printf("Rutina erronea\n");
                        exit(1);
                    }
                }
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else if (operandos[6] == '#')
            {
                if (operandos[7] == '-')
                {
                    negativeFlag = TRUE;
                    twoType = imm5;
                    i = 0;
                    k = 8;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                    command |= MASK_BIT5_ADD;
                }
                else
                {
                    negativeFlag = FALSE;
                    twoType = imm5;
                    i = 0;
                    k = 7;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                    command |= MASK_BIT5_ADD;
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "JSRR") == 0)
    {
        command |= (uint16_t)MASK_JSRR;
        if (operandos[0] == 'R')
        {
            if (operandos[1] == '0' || operandos[1] == '1' || operandos[1] == '2' || operandos[1] == '3' || operandos[1] == '4' || operandos[1] == '5' || operandos[1] == '6')
            {
                if (operandos[1] == '0')
                    command |= MASK_ADD_SR1_R0;
                else if (operandos[1] == '1')
                    command |= MASK_ADD_SR1_R1;
                else if (operandos[1] == '2')
                    command |= MASK_ADD_SR1_R2;
                else if (operandos[1] == '3')
                    command |= MASK_ADD_SR1_R3;
                else if (operandos[1] == '4')
                    command |= MASK_ADD_SR1_R4;
                else if (operandos[1] == '5')
                    command |= MASK_ADD_SR1_R5;
                else if (operandos[1] == '6')
                    command |= MASK_ADD_SR1_R6;
                else if (operandos[1] == '7')
                    command |= MASK_ADD_SR1_R7;
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "JMP") == 0)
    {
        command |= (uint16_t)MASK_JMP;
        if (operandos[0] == 'R')
        {
            if (operandos[1] == '0' || operandos[1] == '1' || operandos[1] == '2' || operandos[1] == '3' || operandos[1] == '4' || operandos[1] == '5' || operandos[1] == '6')
            {
                if (operandos[1] == '0')
                    command |= MASK_ADD_SR1_R0;
                else if (operandos[1] == '1')
                    command |= MASK_ADD_SR1_R1;
                else if (operandos[1] == '2')
                    command |= MASK_ADD_SR1_R2;
                else if (operandos[1] == '3')
                    command |= MASK_ADD_SR1_R3;
                else if (operandos[1] == '4')
                    command |= MASK_ADD_SR1_R4;
                else if (operandos[1] == '5')
                    command |= MASK_ADD_SR1_R5;
                else if (operandos[1] == '6')
                    command |= MASK_ADD_SR1_R6;
                else if (operandos[1] == '7')
                    command |= MASK_ADD_SR1_R7;
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "LDB") == 0)
    {
        command |= (uint16_t)MASK_LDB;
        if (operandos[0] == 'R')
        {
            if (operandos[1] == '0' || operandos[1] == '1' || operandos[1] == '2' || operandos[1] == '3' || operandos[1] == '4' || operandos[1] == '5' || operandos[1] == '6' || operandos[1] == '7')
            {
                if (operandos[1] == '0')
                    command |= MASK_ADD_DR_R0;
                else if (operandos[1] == '1')
                    command |= MASK_ADD_DR_R1;
                else if (operandos[1] == '2')
                    command |= MASK_ADD_DR_R2;
                else if (operandos[1] == '3')
                    command |= MASK_ADD_DR_R3;
                else if (operandos[1] == '4')
                    command |= MASK_ADD_DR_R4;
                else if (operandos[1] == '5')
                    command |= MASK_ADD_DR_R5;
                else if (operandos[1] == '6')
                    command |= MASK_ADD_DR_R6;
                else if (operandos[1] == '7')
                    command |= MASK_ADD_DR_R7;
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[3] == 'R')
            {
                if (operandos[4] == '0' || operandos[4] == '1' || operandos[4] == '2' || operandos[4] == '3' || operandos[4] == '4' || operandos[4] == '5' || operandos[4] == '6' || operandos[4] == '7')
                {
                    if (operandos[4] == '0')
                        command |= MASK_ADD_SR1_R0;
                    else if (operandos[4] == '1')
                        command |= MASK_ADD_SR1_R1;
                    else if (operandos[4] == '2')
                        command |= MASK_ADD_SR1_R2;
                    else if (operandos[4] == '3')
                        command |= MASK_ADD_SR1_R3;
                    else if (operandos[4] == '4')
                        command |= MASK_ADD_SR1_R4;
                    else if (operandos[4] == '5')
                        command |= MASK_ADD_SR1_R5;
                    else if (operandos[4] == '6')
                        command |= MASK_ADD_SR1_R6;
                    else if (operandos[4] == '7')
                        command |= MASK_ADD_SR1_R7;
                    else
                    {
                        printf("Rutina erronea\n");
                        exit(1);
                    }
                }
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[6] == '#')
            {
                if (operandos[7] == '-')
                {
                    negativeFlag = TRUE;
                    twoType = boffset6;
                    i = 0;
                    k = 8;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                }
                else
                {
                    negativeFlag = FALSE;
                    twoType = boffset6;
                    i = 0;
                    k = 7;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }

        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "LDW") == 0)
    {
        command |= (uint16_t)MASK_LDW;
        if (operandos[0] == 'R')
        {
            if (operandos[1] == '0' || operandos[1] == '1' || operandos[1] == '2' || operandos[1] == '3' || operandos[1] == '4' || operandos[1] == '5' || operandos[1] == '6' || operandos[1] == '7')
            {
                if (operandos[1] == '0')
                    command |= MASK_ADD_DR_R0;
                else if (operandos[1] == '1')
                    command |= MASK_ADD_DR_R1;
                else if (operandos[1] == '2')
                    command |= MASK_ADD_DR_R2;
                else if (operandos[1] == '3')
                    command |= MASK_ADD_DR_R3;
                else if (operandos[1] == '4')
                    command |= MASK_ADD_DR_R4;
                else if (operandos[1] == '5')
                    command |= MASK_ADD_DR_R5;
                else if (operandos[1] == '6')
                    command |= MASK_ADD_DR_R6;
                else if (operandos[1] == '7')
                    command |= MASK_ADD_DR_R7;
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[3] == 'R')
            {
                if (operandos[4] == '0' || operandos[4] == '1' || operandos[4] == '2' || operandos[4] == '3' || operandos[4] == '4' || operandos[4] == '5' || operandos[4] == '6' || operandos[4] == '7')
                {
                    if (operandos[4] == '0')
                        command |= MASK_ADD_SR1_R0;
                    else if (operandos[4] == '1')
                        command |= MASK_ADD_SR1_R1;
                    else if (operandos[4] == '2')
                        command |= MASK_ADD_SR1_R2;
                    else if (operandos[4] == '3')
                        command |= MASK_ADD_SR1_R3;
                    else if (operandos[4] == '4')
                        command |= MASK_ADD_SR1_R4;
                    else if (operandos[4] == '5')
                        command |= MASK_ADD_SR1_R5;
                    else if (operandos[4] == '6')
                        command |= MASK_ADD_SR1_R6;
                    else if (operandos[4] == '7')
                        command |= MASK_ADD_SR1_R7;
                    else
                    {
                        printf("Rutina erronea\n");
                        exit(1);
                    }
                }
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[6] == '#')
            {
                if (operandos[7] == '-')
                {
                    negativeFlag = TRUE;
                    twoType = boffset6;
                    i = 0;
                    k = 8;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                }
                else
                {
                    negativeFlag = FALSE;
                    twoType = boffset6;
                    i = 0;
                    k = 7;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "LEA") == 0)
    {
        command |= (uint16_t)MASK_LEA;
        if (operandos[0] == 'R')
        {
            if (operandos[1] == '0' || operandos[1] == '1' || operandos[1] == '2' || operandos[1] == '3' || operandos[1] == '4' || operandos[1] == '5' || operandos[1] == '6' || operandos[1] == '7')
            {
                if (operandos[1] == '0')
                    command |= MASK_ADD_DR_R0;
                else if (operandos[1] == '1')
                    command |= MASK_ADD_DR_R1;
                else if (operandos[1] == '2')
                    command |= MASK_ADD_DR_R2;
                else if (operandos[1] == '3')
                    command |= MASK_ADD_DR_R3;
                else if (operandos[1] == '4')
                    command |= MASK_ADD_DR_R4;
                else if (operandos[1] == '5')
                    command |= MASK_ADD_DR_R5;
                else if (operandos[1] == '6')
                    command |= MASK_ADD_DR_R6;
                else if (operandos[1] == '7')
                    command |= MASK_ADD_DR_R7;
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
        }
        if (operandos[3] == '$')
        {
            if (operandos[4] == '-')
            {
                negativeFlag = TRUE;
                twoType = boffset6;
                i = 0;
                k = 5;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            else
            {
                negativeFlag = FALSE;
                twoType = boffset6;
                i = 0;
                k = 4;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
        
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
    }
    else if (strcmp(opcode, "STB") == 0)
    {
        command |= (uint16_t)MASK_STB;
        if (operandos[0] == 'R')
        {
            if (operandos[1] == '0' || operandos[1] == '1' || operandos[1] == '2' || operandos[1] == '3' || operandos[1] == '4' || operandos[1] == '5' || operandos[1] == '6' || operandos[1] == '7')
            {
                if (operandos[1] == '0')
                    command |= MASK_ADD_DR_R0;
                else if (operandos[1] == '1')
                    command |= MASK_ADD_DR_R1;
                else if (operandos[1] == '2')
                    command |= MASK_ADD_DR_R2;
                else if (operandos[1] == '3')
                    command |= MASK_ADD_DR_R3;
                else if (operandos[1] == '4')
                    command |= MASK_ADD_DR_R4;
                else if (operandos[1] == '5')
                    command |= MASK_ADD_DR_R5;
                else if (operandos[1] == '6')
                    command |= MASK_ADD_DR_R6;
                else if (operandos[1] == '7')
                    command |= MASK_ADD_DR_R7;
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[3] == 'R')
            {
                if (operandos[4] == '0' || operandos[4] == '1' || operandos[4] == '2' || operandos[4] == '3' || operandos[4] == '4' || operandos[4] == '5' || operandos[4] == '6' || operandos[4] == '7')
                {
                    if (operandos[4] == '0')
                        command |= MASK_ADD_SR1_R0;
                    else if (operandos[4] == '1')
                        command |= MASK_ADD_SR1_R1;
                    else if (operandos[4] == '2')
                        command |= MASK_ADD_SR1_R2;
                    else if (operandos[4] == '3')
                        command |= MASK_ADD_SR1_R3;
                    else if (operandos[4] == '4')
                        command |= MASK_ADD_SR1_R4;
                    else if (operandos[4] == '5')
                        command |= MASK_ADD_SR1_R5;
                    else if (operandos[4] == '6')
                        command |= MASK_ADD_SR1_R6;
                    else if (operandos[4] == '7')
                        command |= MASK_ADD_SR1_R7;
                    else
                    {
                        printf("Rutina erronea\n");
                        exit(1);
                    }
                }
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[6] == '#')
            {
                if (operandos[7] == '-')
                {
                    negativeFlag = TRUE;
                    twoType = boffset6;
                    i = 0;
                    k = 8;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                }
                else
                {
                    negativeFlag = FALSE;
                    twoType = boffset6;
                    i = 0;
                    k = 7;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "STW") == 0)
    {
        command |= (uint16_t)MASK_STW;
        if (operandos[0] == 'R')
        {
            if (operandos[1] == '0' || operandos[1] == '1' || operandos[1] == '2' || operandos[1] == '3' || operandos[1] == '4' || operandos[1] == '5' || operandos[1] == '6' || operandos[1] == '7')
            {
                if (operandos[1] == '0')
                    command |= MASK_ADD_DR_R0;
                else if (operandos[1] == '1')
                    command |= MASK_ADD_DR_R1;
                else if (operandos[1] == '2')
                    command |= MASK_ADD_DR_R2;
                else if (operandos[1] == '3')
                    command |= MASK_ADD_DR_R3;
                else if (operandos[1] == '4')
                    command |= MASK_ADD_DR_R4;
                else if (operandos[1] == '5')
                    command |= MASK_ADD_DR_R5;
                else if (operandos[1] == '6')
                    command |= MASK_ADD_DR_R6;
                else if (operandos[1] == '7')
                    command |= MASK_ADD_DR_R7;
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[3] == 'R')
            {
                if (operandos[4] == '0' || operandos[4] == '1' || operandos[4] == '2' || operandos[4] == '3' || operandos[4] == '4' || operandos[4] == '5' || operandos[4] == '6' || operandos[4] == '7')
                {
                    if (operandos[4] == '0')
                        command |= MASK_ADD_SR1_R0;
                    else if (operandos[4] == '1')
                        command |= MASK_ADD_SR1_R1;
                    else if (operandos[4] == '2')
                        command |= MASK_ADD_SR1_R2;
                    else if (operandos[4] == '3')
                        command |= MASK_ADD_SR1_R3;
                    else if (operandos[4] == '4')
                        command |= MASK_ADD_SR1_R4;
                    else if (operandos[4] == '5')
                        command |= MASK_ADD_SR1_R5;
                    else if (operandos[4] == '6')
                        command |= MASK_ADD_SR1_R6;
                    else if (operandos[4] == '7')
                        command |= MASK_ADD_SR1_R7;
                    else
                    {
                        printf("Rutina erronea\n");
                        exit(1);
                    }
                }
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[6] == '#')
            {
                if (operandos[7] == '-')
                {
                    negativeFlag = TRUE;
                    twoType = boffset6;
                    i = 0;
                    k = 8;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                }
                else
                {
                    negativeFlag = FALSE;
                    twoType = boffset6;
                    i = 0;
                    k = 7;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "JSR") == 0)
    {
        command |= (uint16_t)MASK_JSR;
        if (operandos[0] == '$')
        {
            if (operandos[1] == '-')
            {
                negativeFlag = TRUE;
                twoType = PCoffset11;
                i = 0;
                k = 2;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            else
            {
                negativeFlag = FALSE;
                twoType = PCoffset11;
                i = 0;
                k = 1;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "RET") == 0)
    {
        command |= MASK_TOTAL_RET;
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "LSHF") == 0)
    {
        command |= (uint16_t)MASK_LSHF;
        if (operandos[0] == 'R')
        {
            if (operandos[1] == '0' || operandos[1] == '1' || operandos[1] == '2' || operandos[1] == '3' || operandos[1] == '4' || operandos[1] == '5' || operandos[1] == '6' || operandos[1] == '7')
            {
                if (operandos[1] == '0')
                    command |= MASK_ADD_DR_R0;
                else if (operandos[1] == '1')
                    command |= MASK_ADD_DR_R1;
                else if (operandos[1] == '2')
                    command |= MASK_ADD_DR_R2;
                else if (operandos[1] == '3')
                    command |= MASK_ADD_DR_R3;
                else if (operandos[1] == '4')
                    command |= MASK_ADD_DR_R4;
                else if (operandos[1] == '5')
                    command |= MASK_ADD_DR_R5;
                else if (operandos[1] == '6')
                    command |= MASK_ADD_DR_R6;
                else if (operandos[1] == '7')
                    command |= MASK_ADD_DR_R7;
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[3] == 'R')
            {
                if (operandos[4] == '0' || operandos[4] == '1' || operandos[4] == '2' || operandos[4] == '3' || operandos[4] == '4' || operandos[4] == '5' || operandos[4] == '6' || operandos[4] == '7')
                {
                    if (operandos[4] == '0')
                        command |= MASK_ADD_SR1_R0;
                    else if (operandos[4] == '1')
                        command |= MASK_ADD_SR1_R1;
                    else if (operandos[4] == '2')
                        command |= MASK_ADD_SR1_R2;
                    else if (operandos[4] == '3')
                        command |= MASK_ADD_SR1_R3;
                    else if (operandos[4] == '4')
                        command |= MASK_ADD_SR1_R4;
                    else if (operandos[4] == '5')
                        command |= MASK_ADD_SR1_R5;
                    else if (operandos[4] == '6')
                        command |= MASK_ADD_SR1_R6;
                    else if (operandos[4] == '7')
                        command |= MASK_ADD_SR1_R7;
                    else
                    {
                        printf("Rutina erronea\n");
                        exit(1);
                    }
                }
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[6] == '#')
            {
                if (operandos[7] == '-')
                {
                    printf("Rutina erronea");
                    exit(1);
                }
                else
                {
                    negativeFlag = FALSE;
                    twoType = amount4;
                    i = 0;
                    k = 7;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "RSHFL") == 0)
    {
        command |= (uint16_t)MASK_RSHFL;
        if (operandos[0] == 'R')
        {
            if (operandos[1] == '0' || operandos[1] == '1' || operandos[1] == '2' || operandos[1] == '3' || operandos[1] == '4' || operandos[1] == '5' || operandos[1] == '6' || operandos[1] == '7')
            {
                if (operandos[1] == '0')
                    command |= MASK_ADD_DR_R0;
                else if (operandos[1] == '1')
                    command |= MASK_ADD_DR_R1;
                else if (operandos[1] == '2')
                    command |= MASK_ADD_DR_R2;
                else if (operandos[1] == '3')
                    command |= MASK_ADD_DR_R3;
                else if (operandos[1] == '4')
                    command |= MASK_ADD_DR_R4;
                else if (operandos[1] == '5')
                    command |= MASK_ADD_DR_R5;
                else if (operandos[1] == '6')
                    command |= MASK_ADD_DR_R6;
                else if (operandos[1] == '7')
                    command |= MASK_ADD_DR_R7;
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[3] == 'R')
            {
                if (operandos[4] == '0' || operandos[4] == '1' || operandos[4] == '2' || operandos[4] == '3' || operandos[4] == '4' || operandos[4] == '5' || operandos[4] == '6' || operandos[4] == '7')
                {
                    if (operandos[4] == '0')
                        command |= MASK_ADD_SR1_R0;
                    else if (operandos[4] == '1')
                        command |= MASK_ADD_SR1_R1;
                    else if (operandos[4] == '2')
                        command |= MASK_ADD_SR1_R2;
                    else if (operandos[4] == '3')
                        command |= MASK_ADD_SR1_R3;
                    else if (operandos[4] == '4')
                        command |= MASK_ADD_SR1_R4;
                    else if (operandos[4] == '5')
                        command |= MASK_ADD_SR1_R5;
                    else if (operandos[4] == '6')
                        command |= MASK_ADD_SR1_R6;
                    else if (operandos[4] == '7')
                        command |= MASK_ADD_SR1_R7;
                    else
                    {
                        printf("Rutina erronea\n");
                        exit(1);
                    }
                }
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[6] == '#')
            {
                if (operandos[7] == '-')
                {
                    printf("Rutina erronea");
                    exit(1);
                }
                else
                {
                    negativeFlag = FALSE;
                    twoType = amount4;
                    i = 0;
                    k = 7;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "RSHFA") == 0)
    {
        command |= (uint16_t)MASK_RSHFA;
        if (operandos[0] == 'R')
        {
            if (operandos[1] == '0' || operandos[1] == '1' || operandos[1] == '2' || operandos[1] == '3' || operandos[1] == '4' || operandos[1] == '5' || operandos[1] == '6' || operandos[1] == '7')
            {
                if (operandos[1] == '0')
                    command |= MASK_ADD_DR_R0;
                else if (operandos[1] == '1')
                    command |= MASK_ADD_DR_R1;
                else if (operandos[1] == '2')
                    command |= MASK_ADD_DR_R2;
                else if (operandos[1] == '3')
                    command |= MASK_ADD_DR_R3;
                else if (operandos[1] == '4')
                    command |= MASK_ADD_DR_R4;
                else if (operandos[1] == '5')
                    command |= MASK_ADD_DR_R5;
                else if (operandos[1] == '6')
                    command |= MASK_ADD_DR_R6;
                else if (operandos[1] == '7')
                    command |= MASK_ADD_DR_R7;
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[3] == 'R')
            {
                if (operandos[4] == '0' || operandos[4] == '1' || operandos[4] == '2' || operandos[4] == '3' || operandos[4] == '4' || operandos[4] == '5' || operandos[4] == '6' || operandos[4] == '7')
                {
                    if (operandos[4] == '0')
                        command |= MASK_ADD_SR1_R0;
                    else if (operandos[4] == '1')
                        command |= MASK_ADD_SR1_R1;
                    else if (operandos[4] == '2')
                        command |= MASK_ADD_SR1_R2;
                    else if (operandos[4] == '3')
                        command |= MASK_ADD_SR1_R3;
                    else if (operandos[4] == '4')
                        command |= MASK_ADD_SR1_R4;
                    else if (operandos[4] == '5')
                        command |= MASK_ADD_SR1_R5;
                    else if (operandos[4] == '6')
                        command |= MASK_ADD_SR1_R6;
                    else if (operandos[4] == '7')
                        command |= MASK_ADD_SR1_R7;
                    else
                    {
                        printf("Rutina erronea\n");
                        exit(1);
                    }
                }
                else
                {
                    printf("Rutina erronea\n");
                    exit(1);
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
            
            if (operandos[6] == '#')
            {
                if (operandos[7] == '-')
                {
                    printf("Rutina erronea");
                    exit(1);
                }
                else
                {
                    negativeFlag = FALSE;
                    twoType = amount4;
                    i = 0;
                    k = 7;
                    while (operandos[k] != '\0')
                    {
                        immVal[i] = operandos[k];
                        i++;
                        k++;
                    }
                    value = immValue(immVal, twoType, negativeFlag);
                    command |= value;
                }
            }
            else
            {
                printf("Rutina erronea\n");
                exit(1);
            }
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "BR") == 0 || strcmp(opcode, "BRnzp") == 0)
    {
        command |= (uint16_t)MASK_BR;
        if (operandos[0] == '$')
        {
            if (operandos[1] == '-')
            {
                negativeFlag = TRUE;
                twoType = PCoffset9;
                i = 0;
                k = 2;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            else
            {
                negativeFlag = FALSE;
                twoType = PCoffset9;
                i = 0;
                k = 1;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "BRn") == 0)
    {
        command |= (uint16_t)MASK_BRN;
        if (operandos[0] == '$')
        {
            if (operandos[1] == '-')
            {
                negativeFlag = TRUE;
                twoType = PCoffset9;
                i = 0;
                k = 2;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            else
            {
                negativeFlag = FALSE;
                twoType = PCoffset9;
                i = 0;
                k = 1;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "BRz") == 0)
    {
        command |= (uint16_t)MASK_BRZ;
        if (operandos[0] == '$')
        {
            if (operandos[1] == '-')
            {
                negativeFlag = TRUE;
                twoType = PCoffset9;
                i = 0;
                k = 2;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            else
            {
                negativeFlag = FALSE;
                twoType = PCoffset9;
                i = 0;
                k = 1;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "BRp") == 0)
    {
        command |= (uint16_t)MASK_BRP;
        if (operandos[0] == '$')
        {
            if (operandos[1] == '-')
            {
                negativeFlag = TRUE;
                twoType = PCoffset9;
                i = 0;
                k = 2;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            else
            {
                negativeFlag = FALSE;
                twoType = PCoffset9;
                i = 0;
                k = 1;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "BRzp") == 0)
    {
        command |= (uint16_t)MASK_BRZP;
        if (operandos[0] == '$')
        {
            if (operandos[1] == '-')
            {
                negativeFlag = TRUE;
                twoType = PCoffset9;
                i = 0;
                k = 2;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            else
            {
                negativeFlag = FALSE;
                twoType = PCoffset9;
                i = 0;
                k = 1;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "BRnp") == 0)
    {
        command |= (uint16_t)MASK_BRNP;
        if (operandos[0] == '$')
        {
            if (operandos[1] == '-')
            {
                negativeFlag = TRUE;
                twoType = PCoffset9;
                i = 0;
                k = 2;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            else
            {
                negativeFlag = FALSE;
                twoType = PCoffset9;
                i = 0;
                k = 1;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
    else if (strcmp(opcode, "BRnz") == 0)
    {
        command |= (uint16_t)MASK_BRNZ;
        if (operandos[0] == '$')
        {
            if (operandos[1] == '-')
            {
                negativeFlag = TRUE;
                twoType = PCoffset9;
                i = 0;
                k = 2;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            else
            {
                negativeFlag = FALSE;
                twoType = PCoffset9;
                i = 0;
                k = 1;
                while (operandos[k] != '\0')
                {
                    immVal[i] = operandos[k];
                    i++;
                    k++;
                }
                value = immValue(immVal, twoType, negativeFlag);
                command |= value;
            }
            
        }
        else
        {
            printf("Rutina erronea\n");
            exit(1);
        }
        primero = (uint8_t)(command >> 8);
        segundo = (uint8_t)command;
        fwrite(&primero, sizeof(uint8_t), 1, hex);
        fwrite(&segundo, sizeof(uint8_t), 1, hex);
    }
}

uint16_t immValue(uint8_t immVal[], enum twoCType type, uint8_t negativeFlag)
{
    uint16_t numero = strtoul(immVal, NULL, 0);
    switch (type)
    {
        case imm5:
            if (negativeFlag == TRUE)
            {
                if (numero <= 16 && numero > 0)
                {
                    numero = ~numero;
                    numero += 1;
                    numero &= MASK_IMM5;
                    return numero;
                }
                else
                {
                    printf("Valores invalidos\n");
                    exit(1);
                }
            }
            else
            {
                if (numero <= 15 && numero > 0)
                {
                    return numero;
                }
                else
                {
                    printf("Valores invalidos\n");
                    exit(1);
                }
            }
            break;
            
        case PCoffset11:
            if (negativeFlag == TRUE)
            {
                if (numero <= 1024 && numero >= 0)
                {
                    numero = ~numero;
                    numero += 1;
                    numero &= MASK_PCOFFSET11;
                    return numero;
                }
                else
                {
                    printf("Valores invalidos\n");
                    exit(1);
                }
            }
            else
            {
                if (numero <= 1023 && numero >= 0)
                {
                    return numero;
                }
                else
                {
                    printf("Valores invalidos\n");
                    exit(1);
                }
            }
            break;
            
        case boffset6:
            if (negativeFlag == TRUE)
            {
                if (numero <= 32 && numero >= 0)
                {
                    numero = ~numero;
                    numero += 1;
                    numero &= MASK_BOFFSET6;
                    return numero;
                }
                else
                {
                    printf("Valores invalidos\n");
                    exit(1);
                }
            }
            else
            {
                if (numero <= 31 && numero >= 0)
                {
                    return numero;
                }
                else
                {
                    printf("Valores invalidos\n");
                    exit(1);
                }
            }
            break;
            
        case PCoffset9:
            if (negativeFlag == TRUE)
            {
                if (numero <= 256 && numero >= 0)
                {
                    numero = ~numero;
                    numero += 1;
                    numero &= MASK_PCOFFSET9;
                    return numero;
                }
                else
                {
                    printf("Valores invalidos\n");
                    exit(1);
                }
            }
            else
            {
                if (numero <= 255 && numero >= 0)
                {
                    return numero;
                }
                else
                {
                    printf("Valores invalidos\n");
                    exit(1);
                }
            }
            break;
            
        case amount4:
            if (numero <= 15 && numero >= 0)
            {
                return numero;
            }
            else
            {
                printf("Valores invalidos\n");
                exit(1);
            }
            break;
            
        default:
            break;
    }
    return 0;
}