#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"

void print_rtype(char *, Instruction);
void print_itype_except_load(char *, Instruction, int);
void print_load(char *, Instruction);
void print_store(char *, Instruction);
void print_branch(char *, Instruction);
void print_lui(Instruction);
void print_jal(Instruction);
void print_ecall(Instruction);
void write_rtype(Instruction);
void write_itype_except_load(Instruction); 
void write_load(Instruction);
void write_store(Instruction);
void write_branch(Instruction);
void write_custom(Instruction);

void decode_instruction(uint32_t instruction_bits) {
    Instruction instruction = parse_instruction(instruction_bits);
    switch(instruction.opcode) {
        case 0x0b:
            write_custom(instruction);
            break;
        case 0x33:
            write_rtype(instruction);
            break;
        case 0x13:
            write_itype_except_load(instruction);
            break;
        case 0x3:
            write_load(instruction);
            break;
        case 0x23:
            write_store(instruction);
            break;
        case 0x63:
            write_branch(instruction);
            break;
        case 0x37:
            print_lui(instruction);
            break;
        case 0x6F:
            print_jal(instruction);
            break;
        case 0x73:
            print_ecall(instruction);
            break;
        default: // undefined opcode
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_custom(Instruction instruction){
    
    //printf("%d, %d", instruction.rtype.funct3 , instruction.rtype.funct7);
    if(instruction.rtype.funct3 == 0x2 && instruction.rtype.funct7 == 0x0){
        //custom

        print_rtype("gep", instruction);
    }
    else{
        handle_invalid_instruction(instruction);
    }
}
void write_rtype(Instruction instruction) {
    switch (instruction.rtype.funct3) {
        case 0x0:
            switch (instruction.rtype.funct7) {
                case 0x0:
                    print_rtype("add", instruction);
                    break;
                case 0x1:
                    print_rtype("mul", instruction);
                    break;
                case 0x20:
                    print_rtype("sub", instruction);
                    break;
                default:
                    handle_invalid_instruction(instruction);
                break;      
            }
            break;
        case 0x1:
            switch (instruction.rtype.funct7) {
                case 0x0:
                print_rtype("sll", instruction);
                break;
                case 0x1:
                print_rtype("mulh", instruction);
                break;
                default:
                handle_invalid_instruction(instruction);
                break;
            }
            break;
        case 0x2:
            print_rtype("slt", instruction);
            break;
        case 0x4:
            switch (instruction.rtype.funct7) {
                case 0x0:   
                print_rtype("xor", instruction);
                break;
                case 0x1:
                print_rtype("div", instruction);
                break;
                default:
                handle_invalid_instruction(instruction);
                break;
            }
            break;
        case 0x5:
            switch (instruction.rtype.funct7) {
                case 0x0:
                print_rtype("srl", instruction);
                break;
                case 0x20:
                print_rtype("sra", instruction);
                break;
                default:
                handle_invalid_instruction(instruction);
                break;
            }
            break;
        case 0x6:
            switch (instruction.rtype.funct7) {
                case 0x0:
                print_rtype("or", instruction);
                break;
                case 0x1:
                print_rtype("rem", instruction);
                break;
                default:
                handle_invalid_instruction(instruction);
                break;
            }
            break;
        case 0x7:
            print_rtype("and", instruction);
            break;
        default:
            handle_invalid_instruction(instruction);
        break;
    }
}

void write_itype_except_load(Instruction instruction) {
    int shiftOp;
    switch (instruction.itype.funct3) {
        case 0x0:
            print_itype_except_load("addi", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        case 0x1:
            print_itype_except_load("slli", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        case 0x2:
            print_itype_except_load("slti", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        case 0x4:
            print_itype_except_load("xori", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        case 0x5:
            shiftOp = instruction.itype.imm >> 10;
            switch(shiftOp) {
                case 0x0:
                    print_itype_except_load("srli", instruction, instruction.itype.imm & 0x1F);
                    break;
                case 0x1:
                    print_itype_except_load("srai", instruction, sign_extend_number(instruction.itype.imm, 12) & 0x1F);
                    break;
                default:
                    handle_invalid_instruction(instruction);
                    break;
            }
            break;
        case 0x6:
            print_itype_except_load("ori", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        case 0x7:
            print_itype_except_load("andi", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        default:
            handle_invalid_instruction(instruction);
            break;  
    }
}

void write_load(Instruction instruction) {
    switch (instruction.itype.funct3) {
        case 0x0:
            print_load("lb", instruction);
            break;
        case 0x1:
            print_load("lh", instruction);
            break;
        case 0x2:
            print_load("lw", instruction);
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_store(Instruction instruction) {
    switch (instruction.stype.funct3) {
        case 0x0:
            print_store("sb", instruction);
            break;
        case 0x1:
            print_store("sh", instruction);
            break;
        case 0x2:
            print_store("sw", instruction);
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_branch(Instruction instruction) {
    switch (instruction.sbtype.funct3) {
        case 0x0:
            print_branch("beq", instruction);
            break;
        case 0x1:
            print_branch("bne", instruction);
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void print_lui(Instruction instruction) {
    /* YOUR CODE HERE */
    printf(LUI_FORMAT, instruction.utype.rd, instruction.utype.imm);
}

void print_jal(Instruction instruction) {
    /* YOUR CODE HERE */
    printf(JAL_FORMAT, instruction.ujtype.rd, get_jump_offset(instruction));
}

void print_ecall(Instruction instruction) {
    /* YOUR CODE HERE */
    printf(ECALL_FORMAT);
}

void print_rtype(char *name, Instruction instruction) {
  printf(RTYPE_FORMAT, name, instruction.rtype.rd, instruction.rtype.rs1,
         instruction.rtype.rs2);
  /* YOUR CODE HERE */
}

void print_itype_except_load(char *name, Instruction instruction, int imm) {
    /* YOUR CODE HERE */
    printf(ITYPE_FORMAT, name, instruction.itype.rd, instruction.itype.rs1,imm);
}

void print_load(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    printf(MEM_FORMAT, name, instruction.itype.rd, sign_extend_number(instruction.itype.imm, 12),
         instruction.itype.rs1);
}

void print_store(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    printf(MEM_FORMAT, name, instruction.stype.rs2, get_store_offset(instruction),
        instruction.stype.rs1);
}

void print_branch(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    printf(BRANCH_FORMAT, name, instruction.sbtype.rs1, instruction.sbtype.rs2,
        get_branch_offset(instruction));
}
