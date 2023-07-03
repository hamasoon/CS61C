#include <stdio.h>

// 1. Using Unititialized Memory
void foo1(int *p) {
    int j; // declared but not initialized, so j contain garbage value
    *p = j;
}

void bar() {
    int i=10;
    foo1(&i);
    printf("i = %d\n", i); // so, now i contain garbage value also
}

// 2. Using Memory You Don't Own(1)
typedef struct node {
    struct node* next;
    int val;
} Node;

int findLastNodeValue(Node* head) 
{
    while (head->next != NULL) // What if head is NULL?
        head = head->next;

    return head->val; 
}

// 3. Using Memory You Don't Own(2)
char *append(const char* s1, const char *s2) {
    const int MAXSIZE = 128;
    char result[MAXSIZE];

    int i=0, j=0;

    for (; i<MAXSIZE-1 && j<strlen(s1); i++,j++)
        result[i] = s1[j];

    for (j=0; i<MAXSIZE-1 && j<strlen(s2); i++,j++)
        result[i] = s2[j];

    result[++i] = '\0';

    return result; // return local variable!!!!
}

// 4. Using Memory You Don't Own(3)
typedef struct {
    char *name;
    int age;
} Profile;

int doSomething() {
    Profile *person =(Profile *)malloc(sizeof(Profile));
    char *name = getName();
    person->name = malloc(sizeof(char)*strlen(name)); // you have to consider null termination
    // so, it should be person->name = malloc(sizeof(char)*(strlen(name)+1));
    strcpy(person->name,name);

    //... -> Do stuff (that isn’t buggy)

    free(person);
    free(person->name);
}

// 5. Using Memory You Haven’t Allocated
void StringManipulate() {
    const char *name = "Safety Critical";
    char *str = malloc(sizeof (char) * 10);
    strncpy(str, name, 10);
    str[10] = '\0'; // str length == 10, so str[10] is out of bound
    printf("%s\n", str); // read beyond bound
    // printf function actually print until meet null character
}

char buffer[1024]; /* global variable */

int foo2(char *str) {
    strcpy(buffer, str); // This is called BUFFER OVERRUN or BUFFER OVERFLOW and is a security flaw!!!

    // ...
}

// A Safer Version
#define ARR_LEN 1024
char buffer[ARR_LEN]; /* global variable for array length */

int foo3(char *str) {
    strncpy(buffer,str, ARR_LEN);
    // ...
}

// 6. Freeing Invalid Memory
void FreeMemX() {
    int fnh = 0;
    free(&fnh); // free stack variable
}

void FreeMemY() {
    int *fum = malloc(4*sizeof(int));

    free(fum+1); // free middle of block
    free(fum);
    free(fum); // double free
}

// 7. Memory Leaks
int *pi; // global pointer

void foo4() {
    pi = (int*)malloc(8*sizeof(int)); // pi is not freed, already occupied
    //...
    free(pi); 
}

void main() {
    pi = (int*)malloc(4*sizeof(int));
    foo4();
}
