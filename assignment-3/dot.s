.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int vectors
# Arguments:
#   a0 is the pointer to the start of v0
#   a1 is the pointer to the start of v1
#   a2 is the length of the vectors
# Returns:
#   a0 is the dot product of v0 and v1
# =======================================================
dot:
     # Prologue
    addi sp,sp,-16
    sw ra,0(sp)
    sw s0,4(sp)
    sw s1,8(sp)
    sw s2,12(sp)

    #end prologue
    mv s0,a0
    mv s1,a1
    li s2,0 # set i
    li t1,0 # set result
loop_start:
    beq s2,a2,loop_end
    lw t3,0(s0)
    lw t4,0(s1)
    mul t2 t3,t4
    add t1,t1,t2
    addi s0,s0,4 # go to a0[next]
    addi s1,s1,4 # go to a1[next]
    addi s2,s2,1 # i++
    j loop_start




loop_end:
    mv a0,t1
    # Epilogue
    lw ra,0(sp)
    lw s0,4(sp)
    lw s1,8(sp)
    lw s2,12(sp)
    addi sp,sp,16
    #end epilogue
    ret
