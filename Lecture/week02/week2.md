- [Lecture 6, 7 : RISCV](#lecture-6-7--riscv)
  - [Assembly Code](#assembly-code)
      - [Instructions](#instructions)
      - [Psuedo-Insturcion](#psuedo-insturcion)
      - [more example](#more-example)
      - [C to RISC-V Practice](#c-to-risc-v-practice)
  - [Function in Assembly](#function-in-assembly)
      - [Steps of Calling a Function](#steps-of-calling-a-function)
      - [Function and branch](#function-and-branch)
      - [Divide Regsiter](#divide-regsiter)
      - [Basic Prologue and Epilogue of Function Call](#basic-prologue-and-epilogue-of-function-call)
      - [Example](#example)
- [Lecture 8 : Format of Instruction](#lecture-8--format-of-instruction)

# Lecture 6, 7 : RISCV

## Assembly Code
- Insturction Syntax `op dst, src1, src2`
  - 1 operator, 3 operands
  - keep hardware simple via regularity
  - there is some operation that doesn't need 3 operands
    - but there is pseudo instruction which construct with basic operation &rarr; and that basic operation is 3 operands 

- example assembly code
  ```r
  # Comment using # symbol
  main:   add     t0, x0, x0 # labels is section of code -> mark with :
    addi    t1, x0, 1
    la      t3, n
    lw      t3, 0(t3)
  fib:    beq     t3, x0, finish
    add     t2, t1, t0
    mv      t0, t1
    mv      t1, t2
    addi    t3, t3, -1
    j       fib
  finish: addi    a0, x0, 1
    addi    a1, t0, 0
    ecall # print integer ecall
    addi    a0, x0, 10
    ecall # terminate ecall
  ```

#### Instructions
1. Arithmetic:
  - add, sub, addi
  - mult, div
2. Data Transfer: 
  - lw, sw, lb, sb, lbu
3. Branching: 
  - beq, bne, bge, blt, bgeu, bltu &rarr; conditional jump
  - jal, j, jalr, jr &rarr; always jump
4. Bitwise
  - and,  or,  xor
  - andi, ori, xori
5. Shifting: 
  - sll,  srl,  sra 
    - arithmetic shift : sign bit is preserved(filled with sign bit)
    - logical shift : sign bit is not preserved(filled with 0)
  - slli, srli, srai

#### Psuedo-Insturcion
- additional instructions that aren’t really implemented by the hardware
  - Instead translated into real instructions
- example : `mv rd, rs1` &rarr; `add rd, rs1, x0`

#### more example
1. Load Immediate (li)
  - li dst, imm
  - Loads 32-bit immediate into dst
  - translates to: addi dst, x0, imm[0:3] and lui dst, imm[3:8]
2. Load Address (la)
  - la dst, label
  - Loads address of specified label into dst
  - translates to: auipc dst, <offset to label>
3. No Operation (nop)
  - Do nothing : skip cycle
  - translates to: addi x0, x0, 0

#### C to RISC-V Practice
- c code
```c
char *p, *q;
while((*p++ = *q++) != '\0');
```
- asmbelly code
```r
# p -> s0, q -> s1
loop: 
      lb    t0 0(s1)
      sb    t0 0(s0)
      addi  s0, s0, 1
      addi  s1, s1, 1
      bne   t0, x0, loop
      ret
```

## Function in Assembly

#### Steps of Calling a Function
1. Put arguments in a place where the function can access them(a0, a1, ..., a7)
2. Transfer control to the function
  - jal, jalr, jr
3. The function will acquire any (local) storage resources it needs
  - normally, we call that local storage as stack frame
4. The function performs its desired task
5. The function puts return value in an accessible place(a0, a1) and “cleans up”
6. Control is returned to you

#### Function and branch
1. Jump (j) : pseudo instruction
  - j label
  - j label is a pseudo-instruction for jal x0 label
2. Jump and Link (jal) : used to call function
  - jal dst label
  - label &rarr; function location
  - dst &larr; save return address(current PC + 4)
3. Jump and Link Register (jalr) : used to call function
  - jalr dst imm(src) &rarr; src + imm == function location
  - imm(src) &rarr; function location : R[src] + imm
  - dst &larr; save return address(current PC + 4)
4. Jump Register (jr) : used to return from function(src ra) / pseudo instruction
  - jr src
  - jalr x0, 0(ra) 

- ra = return address register, used to save where a function is called from so we can get back

#### Divide Regsiter
- Caller : procedure that calls a function
  - caller save the register before call function
  - caller restore the register after call function
  - t0-t6, a0-a7, ra : insinde this register, caller save that values in somewhere(stack frame, callee saved, etc...) before call function
- Callee : procedure that is called by another function
  - callee save the register before call function
  - callee restore the register after call function
  - s0-s11, sp : insinde this register, callee save that values in somewhere(stack frame, etc...) before start function and restore that values before return to original function

#### Basic Prologue and Epilogue of Function Call
```r
# Prologue
func_label:
      addi sp,sp, -framesize
      sw ra, <framesize-4>(sp) # save return address
      #store other callee saved registers
      #save other regs if need be
... # Body 
      #restore other regs if need be
      #restore other callee saved registers
# Epilogue
      lw ra, <framesize-4>(sp) # restore return address
      # restore other callee saved registers
      addi sp,sp, framesize # clean up stack
      jr ra
```

#### Example
```c
int Leaf(int g, int h, int i, int j) {
  int f;
  f = (g+h)-(i+j);
  return f;
}
```
```r
Leaf:
# Prologue
      addi sp,sp,-8
      # allocate stack
      sw s1,4(sp) # save s1
      sw s0,0(sp) # save s0
# Body
      add s0,a0,a1 # s0 = g+h
      add s1,a2,a3 # s1 = i+j
      sub a0,s0,s1
      # return value a0 = s0-s1
# Epilogue
      lw s0,0(sp) # restore s0
      lw s1,4(sp) # restore s1
      addi sp,sp,8 # free stack
      jr ra # return
```

# Lecture 8 : Format of Instruction