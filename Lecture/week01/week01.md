# Lecture 01 : Number Representation

## Number Base System
- $abcd_{(x)} = a * x^3 + b * x^2 + c * x^1 + d * x^0$
- general form: $a_n a_{n-1} ... a_1 a_0 = a_{n-1} \times B^{n-1} + ... + a_{0} \times B^{0}$ 

## Binary
- Bits can represent ***ANYTHING***

## Integer Representation

# C Concepts

## Basic 
- compiled language

#### Compilation
- compiler map C code to architecture-specific machine code
  - note that this machine code depends on the hardware system(RISC-V, ARM, x86, etc.)
  - this is main difference from Java
- Keep concept is each code map to loe-level machine insturctions
- Advantage
  - Good run-time preformance
    - optimized for specific hardware
  - Fair compilation time
    - recompile only the modified code
- Disadvantage
  - Not portable
    - need to recompile for different hardware
  - Edit &rarr; Compile &rarr; Run
    - need to recompile for every change
#### Variable Types
1. Numeric - int, long, float, double, etc.(note that size of ***long*** depends on the word size)
2. Character
3. Typed Function
   - Note that C requires **Forward Declaration**
   - it is basically same as declaration of variable
4. Struct
5. Pointer

#### Type Casting
- *weakly* typed language : explicit type from any type to any other
  - even if it doesn't make sense (e.g. struct to int)
  - Because, everything is bits!
## C Syntax and Control Flow

#### Generic C Layout
```c
#include <system_files>
#include "local_files"

#define MACRO
#define CONSTANT 1      // Handled by preprocessor

/* declare functions */
/* declare global variables */

int main(int argc, char *argv[]) { // program start at main() and main() must return int(program exit status)
    /* implementation  */
}

/* define functions */
```

#### C Syntax : main
- argc : argument count, indicates number of arguments
- argv : argument values, array of strings(argument)
- e.g. 
```shell
$ ./foo hello 87
```
&rarr; argc = 3
&rarr; argv[0] = "./foo", argv[1] = "hello", argv[2] = "87"

#### True or False
- False : 0, NULL
- True : non-zero

#### Control Flow
- if-else if-else, switch-case
- while, do-while(basic loop in assembly level ), for

#### ANSI C 
- Declarations in for loops, like Java (#15)
- Java-like // comments (to end of line) (#10)
- Variable-length non-global arrays (#33)
- <inttypes.h> for explicit integer types (#38)
- <stdbool.h> for boolean logic definitions (#35)

# Lecture 3 : C Arrays, Strings, More Pointers

## Arrays

#### Accessing an Array
- Array size : Use separate variable for array declaration &  array bound to be reused (eg: no hard-coding)
- Bad Pattern
```c 
int ar[10];
for(int i=0; i<10; i++) {...}
```
- Better Pattern
```c
const int ARRAY_SIZE = 10;
int ar[ARRAY_SIZE];
for(int i=0; i<ARRAY_SIZE; i++) {...}
```

#### Array and Pointers
- Key Concept : An array variable looks like a pointer to the first (0th) element
  - ar[0] same as *ar; ar[2] same as *(ar+2)
- e.g.
```c
for (i=0; i<SIZE; i++) {ar[i] = 0;}
for (i=0; i<SIZE; i++) {*(ar+i) = 0;}
for (p=ar; p<ar+SIZE; p++) {*p = 0;}
```

#### Arrays Stored Differently Than Pointers
```c
void foo() {
    int *p, a[4], x;
    p = &x;

    *p = 1; // or p[0]
    printf("*p:%u, p:%u, &p:%u\n",*p,p,&p);

    *a = 2; // or a[0]
    printf("*a:%u, a:%u, &a:%u\n",*a,a,&a);
}
```
&rarr; *p:1, p:40, &p:20 &rarr; think about why &p != p<br> 
&rarr; *a:2, a:24, &a:24

#### Arrays and Functions
```c
int foo(int array[], unsigned int size) { // must explicitly pass size!
    ...
    printf(“%d\n”, sizeof(array));
}
```

## Strings
- A String in C is just an array of characters
- Note that string must end with null terminator '\0'

#### String Standard Functioins
1. int strlen(char *string);
   - Returns the length of string (not including null term)
2. int strcmp(char *str1, char *str2);
   - Return 0 if str1 and str2 are identical (how is this  different from str1 == str2?)
3. char *strcpy(char *dst, char *src);
   - Copy contents of string src to the memory at dst.  
   - Caller must ensure that dst has enough memory to hold the data to be copied
   - Note: dst = src only copies pointer(the address)

## More Pointers
