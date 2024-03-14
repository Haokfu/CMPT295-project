.import ../read_matrix.s
.import ../utils.s

.data
file_path: .asciiz "./test_files/test_input.bin"

.text
main:
   # Read matrix into memory
    la a0,file_path
    jal read_matrix
    lw a1,0(a1)
    lw a2,0(a2)


    jal print_int_array


    # Print out elements of matrix


    # Terminate the program
    addi a0, x0, 10
    ecall