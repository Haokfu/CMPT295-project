.import ../read_matrix.s
.import ../gemv.s
.import ../dot.s
.import ../utils.s

.data
output_step1: .asciiz "\n**Step result = gemv(matrix, vector)**\n"



.globl main

.text
main:
    # =====================================
    # COMMAND LINE ARGUMENTS
    # =====================================
    # Args:
    #   a0: int argc
    #   a1: char** argv
    #
    # Usage:
    #   main.s <VECTOR_PATH> <MATRIX_PATH> 

    # Exit if incorrect number of command line args
    li s1,3
    bne a0,s1,mismatched_arg
    mv s7,a1
# =====================================
# LOAD MATRIX and VECTOR. Iterate over argv.
# =====================================
# Load Vector
    addi s7,s7,4
    lw a0,0(s7)
    jal read_matrix #potential problem here

    mv s3,a0 # pointer to the matrix #need to be freed 
    lw s4,0(a1) # row #need to be freed
    lw s5,0(a2) # column #need to be freed

# Load Matrix   
    
    lw a0,4(s7)
    jal read_matrix #potential problem here

    mv s0,a0 # pointer to the matrix #need to be freed
    lw s1,0(a1) # row #need to be freed
    lw s2,0(a2) # column #need to be freed


# =====================================
# RUN GEMV
    mul t1,s1,s5
    slli t1,t1,2
    mv a0,t1
    jal malloc
    mv s6,a0
    
    
    mv a0,s0
    mv a3,s3
    mv a1,s1
    mv a2,s2
    mv a5,s6
    mv a4,s4
    jal gemv

# =====================================
# SPMV :    m * v

    la a1, output_step1
    jal print_str

    ## FILL OUT. Output is a dense vector.
    mv a0, a5# Base ptr
    mv a1, s1#rows
    mv a2, s5#cols
    jal print_int_array 

    #Print newline afterwards for clarity
    # li a1 '\n'
    # jal print_char

    

    jal exit
mismatched_arg:
    li a1 3
    jal exit2