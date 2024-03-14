.globl gemv

.text
# =======================================================
# FUNCTION: Matrix Vector Multiplication
# 	d = gemv(m0, m1)
#   If the dimensions don't match, exit with exit code 2
# Arguments:
# 	a0 is the pointer to the start of m0
#	a1 is the # of rows (height) of m0
#	a2 is the # of columns (width) of m0
#	a3 is the pointer to the start of v
# 	a4 is the # of rows (height) of v
#	a5 is the pointer to the the start of d
# Returns:
#	None, sets d = gemv(m0, m1)
# =======================================================
gemv:

    # Error if mismatched dimensions
    bne a2,a4,mismatched_dimensions
    # Prologue
    addi sp,sp,-20
    sw ra,0(sp)
    sw s0,4(sp)
    sw s1,8(sp)
    sw s3,12(sp)
    sw s5,16(sp)

    #store variables
    mv s0,a0 
    mv s3,a3
    mv s5,a5
    li s1,0 #i
outer_loop_start_gemv:
    beq s1,a1,outer_loop_end_gemv # i < row of m0
    # prologue of func: 
    addi sp,sp,-28
    sw a0,0(sp)
    sw a1,4(sp)
    sw a2,8(sp)
    sw t1,12(sp)
    sw t2,16(sp)
    sw t3,20(sp)
    sw t4,24(sp)
    # set function parameter
    mv a0,s0
    mv a1,s3
    mv a2,a4
    # call function
    jal dot
    sw a0,0(s5)
    # epilogue of func
    lw a0,0(sp)
    lw a1,4(sp)
    lw a2,8(sp)
    lw t1,12(sp)
    lw t2,16(sp)
    lw t3,20(sp)
    lw t4,24(sp)
    addi sp,sp,28
    #end func
    #increment of adress
    slli t1,a2,2
    add s0,s0,t1
    addi s5,s5,4
    addi s1,s1,1
    j outer_loop_start_gemv


outer_loop_end_gemv:
    #Epilogue
    lw ra,0(sp)
    lw s0,4(sp)
    lw s1,8(sp)
    lw s3,12(sp)
    lw s5,16(sp) 
    addi sp,sp,20
    ret

mismatched_dimensions:
    li a1 2
    jal exit2