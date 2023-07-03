#include <stdio.h>

int *get_ptr() {
    int y;
    y = 3;
    return &y;
};

int main(int argc, char *argv[]) {
    int *stack_addr, content; 
    stack_addr = get_ptr();

    content = *stack_addr;
    printf("%d", content); /* 3 */

    content = *stack_addr;
    printf("%d", content); /* ? */
};