//
//  Assembler.h
//  LC-3b
//
//  Created by Ian Bravo on 7/2/14.
//  Copyright (c) 2014 Ibrarabay. All rights reserved.
//

#ifndef LC_3b_Assembler_h
#define LC_3b_Assembler_h

#define TRUE 1
#define FALSE 0

#define MASK_IMM5 0x001F
#define MASK_PCOFFSET11 0x07FF
#define MASK_PCOFFSET9 0x01FF
#define MASK_BOFFSET6 0x003F
#define MASK_BIT5_ADD 0x0020

#define MASK_BR 0x0E00
#define MASK_BRN 0x0800
#define MASK_BRZ 0x0400
#define MASK_BRP 0x0200
#define MASK_BRZP 0x0600
#define MASK_BRNP 0x0A00
#define MASK_BRNZ 0x0C00

#define MASK_ADD 0x1000
#define MASK_AND 0x5000
#define MASK_NOT 0xA000
#define MASK_JMP 0xC000
#define MASK_JSRR 0x4000
#define MASK_JSR 0x4800
#define MASK_LDB 0x2000
#define MASK_LDW 0x6000
#define MASK_LEA 0xE000
#define MASK_RET 0xC000
#define MASK_SHF 0xD000
#define MASK_STB 0x3000
#define MASK_STW 0x7000
#define MASK_TRAP 0xF000
#define MASK_XOR 0x9000

#define MASK_LSHF 0xD000
#define MASK_RSHFL 0xD020
#define MASK_RSHFA 0xD030

#define MASK_ADD_DR_R0 0x0000
#define MASK_ADD_DR_R1 0x0200
#define MASK_ADD_DR_R2 0x0400
#define MASK_ADD_DR_R3 0x0600
#define MASK_ADD_DR_R4 0x0800
#define MASK_ADD_DR_R5 0x0A00
#define MASK_ADD_DR_R6 0x0C00
#define MASK_ADD_DR_R7 0x0E00

#define MASK_ADD_SR1_R0 0x0000
#define MASK_ADD_SR1_R1 0x0040
#define MASK_ADD_SR1_R2 0x0080
#define MASK_ADD_SR1_R3 0x00C0
#define MASK_ADD_SR1_R4 0x0100
#define MASK_ADD_SR1_R5 0x0140
#define MASK_ADD_SR1_R6 0x0180
#define MASK_ADD_SR1_R7 0x01C0

#define MASK_ADD_SR2_R0 0x0000
#define MASK_ADD_SR2_R1 0x0001
#define MASK_ADD_SR2_R2 0x0002
#define MASK_ADD_SR2_R3 0x0003
#define MASK_ADD_SR2_R4 0x0004
#define MASK_ADD_SR2_R5 0x0005
#define MASK_ADD_SR2_R6 0x0006
#define MASK_ADD_SR2_R7 0x0007

#define MASK_LASTBITS_NOT 0x003F

#define MASK_JMP_BSR_0 0x0000
#define MASK_JMP_BSR_1 0x0040
#define MASK_JMP_BSR_2 0x0080
#define MASK_JMP_BSR_3 0x00C0
#define MASK_JMP_BSR_4 0x0100
#define MASK_JMP_BSR_5 0x0140
#define MASK_JMP_BSR_6 0x0180
#define MASK_JMP_BSR_7 0x01C0

#define MASK_TOTAL_RET 0xC1C0

typedef enum twoCType
{
    imm5 = 0,
    boffset6,
    offset6,
    PCoffset9,
    PCoffset11,
    amount4,
    trapvect8
}twoCTypeEnum;


void assembler(FILE *programa);
void assembleCommand(uint8_t instruction[]);
uint16_t immValue(uint8_t immVal[], enum twoCType type, uint8_t negativeFlag);

#endif
