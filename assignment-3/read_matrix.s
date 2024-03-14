.globl read_matrix


.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#   If any file operation fails or doesn't read the proper number of bytes,
#   exit the program with exit code 1.
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 is the pointer to string representing the filename
# Returns:
#   a0 is the pointer to the matrix in memory
#   a1 is a pointer to an integer, we will set it to the number of rows
#   a2 is a pointer to an integer, we will set it to the number of columns
# ==============================================================================
read_matrix:
   # prologue
    addi sp,sp,-24
    sw ra,0(sp)
    sw s0,4(sp)
    sw s1,8(sp)
    sw s2,12(sp)
    sw s3,16(sp)
    sw s4,20(sp)
    # check file path
    # set a1=file name, a2 = 0(r)
    mv a1,a0
    li a2,0
    jal fopen


    # a0 is the file descriptor, store it in s0
    mv s0,a0
    #check if there is error of file descriptor:
    mv a1,s0
    jal ferror
    bne a0,zero,eof_or_error

    # malloc row pointer
    # set a0 = number of byte of row
    li a0,4
    jal malloc
    #store a0 in s1(row)
    mv s1,a0

    # Malloc col pointer
    li a0,4
    jal malloc
    #store a0 in s2(column)
    mv s2,a0


    # Read number of rows
    #set variable:
    mv a1,s0
    mv a2,s1
    li a3,4
    jal fread
    li t1,4
    bne a0,t1,eof_or_error
    # Read number of cols
    mv a1,s0
    mv a2,s2
    li a3,4
    jal fread
    bne a0,t1,eof_or_error
    # potential error: not consecutive read bytes

    # Calculate bytes
    lw t1,0(s1)#get row
    lw t2,0(s2)#get column

    mul t3,t1,t2 #total number of bytes
    # Allocate space for matrix and read it.
    slli t3,t3,2
    mv a0,t3
    jal malloc
    mv s3,a0 #s3 holds the address of matrix

    mv a1,s0
    mv a2,s3
    mv a3,t3
    jal fread

    bne a0,t3,eof_or_error

    


    # Return value
    mv a0,s3
    mv a1,s1
    mv a2,s2
    #close file
    # Epilogue
    lw ra,0(sp)
    lw s0,4(sp)
    lw s1,8(sp)
    lw s2,12(sp)
    lw s3,16(sp)
    lw s4,20(sp)
    addi sp,sp,24
    

    
    
    ret

eof_or_error:
    li a1 1
    jal exit2