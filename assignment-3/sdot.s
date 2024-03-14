.globl sdot

.text
# =======================================================
# FUNCTION: Dot product of 1 sparse vectors and 1 dense vector
# Arguments:
#   a0 is the pointer to the start of v0 (sparse, coo format)
#   a1 is the pointer to the start of v1 (dense)
#   a2 is the number of non-zeros in vector v0
# Returns:
#   a0 is the sparse dot product of v0 and v1
# =======================================================
#
# struct coo {
#   int row;
#   int index;
#   int val;
# };   
# Since these are vectors row = 0 always for v0.
#for (int i = 0 i < nnz; i++) {
#    sum = sum + v0[i].value * v1[coo[i].index];
# }
sdot:
    # Prologue    
    addi sp,sp,-16
    sw ra,0(sp)
    sw s0,4(sp)
    sw s1,8(sp)
    sw s2,12(sp)
    # Save arguments
    mv s0,a0 #save a0 in s0 -> pointer to v0
    mv s1,a1 #save a1 in s1 -> pointer to v1
    mv s2,a1 
    # Set strides. Note that v0 is struct. v1 is array.
    li t0,12 # stride of v0 is 3 # stride of v1 is 1
    # Set loop index
    li t2,0 # i = t2
    # Set accumulation to 0
    li a0,0

loop_start:

    # Check outer loop condition
    bge t2,a2,loop_end
    # load v0[i].value. The actual value is located at offset  from start of coo entry
    lw t3,8(s0) # store v0.value in t3 
    # What is the index of the coo element?
    # Lookup corresponding index in dense vector
    lw t5,4(s0) # index
    slli t5,t5,2
    add t6,s1,t5
    lw t6,0(t6)

    # Load v1[coo[i].index]
    # Multiply and accumulate
    mul t4,t3,t6
    add a0,a0,t4
    # Bump ptr to coo entry
    add s0,s0,t0
    # Increment loop index
    addi t2,t2,1
    jal loop_start
loop_end:

    # Epilogue
    lw ra,0(sp)
    lw s0,4(sp)
    lw s1,8(sp)
    lw s2,12(sp)
    addi sp,sp,12
    
    ret
