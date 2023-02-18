.data # active the data section
.word 2, 4, 6, 8 # store four words
n: .word 9 # 0 1 1 2 3 5 8 13 21 34 55 89 144 233

.text
main:
    add t0, x0, x0
    addi t1, x0, 1
    la t3, n # Loads the label address n into register t3
    lw t3, 0(t3) # t3目前存储的n的地址, lw的作用是把n的值load到t3
fib:
    beq t3, x0, finish # jump if t3==x0
    add t2, t1, t0 # t2=1
    mv t0, t1 # copy t1 -> t0
    mv t1, t2 # copy t2 -> t1
    addi t3, t3, -1 # n--
    j fib
finish:
    addi a0, x0, 1
    addi a1, t0, 0
    ecall # print integer ecall
    addi a0, x0, 10
    ecall # terminate ecall
