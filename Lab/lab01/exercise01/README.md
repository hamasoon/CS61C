# Exercise 1: See what you can C

```c
#include <stdio.h>

/* Only change any of these 4 values */
#define V0 3
#define V1 0
#define V2 1
#define V3 3

int main(void) {
    int a;
    char *s;

    /* This is a print statement. Notice the little 'f' at the end!
     * It might be worthwhile to look up how printf works for your future
     * debugging needs... */
    printf("Berkeley eccentrics:\n====================\n");

    /* for loop */
    for (a = 0; a < V0; a++)
    {
        printf("Happy ");
    }
    printf("\n");

    /* switch statement */
    switch (V1)
    {
    case 0:
        printf("Yoshua\n");
    case 1:
        printf("Triangle Man\n");
        break;
    case 2:
        printf("Chinese Erhu Guy\n");
    case 3:
        printf("Yoshua\n");
        break;
    case 4:
        printf("Dr. Jokemon\n");
        break;
    case 5:
        printf("Hat Lady\n");
    default:
        printf("I don't know these people!\n");
    }

    /* ternary operator */
    s = (V3 == 3) ? "Go" : "Boo";

    /* if statement */
    if (V2) {
        printf("%s BEARS!\n", s);
    } else {
        printf("%s CARDINAL!\n", s);
    }

    return 0;
}
```

#### V0
- V0 define the number of times the loop will run
- answer: 3

#### V1
- V1 define the case that will be executed
- answer: 0

#### V2
- V2 define T/F value of if statement
- answer: non-zero &rarr; in C, non-zero is true

#### V3
- V3 define the boolean value of ternary operator
- answer: non-zero &rarr; same as V2