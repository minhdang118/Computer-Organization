#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int NP = 10;

int ask(void) {
    puts("Press CTRL+C to exit.");
    int a;
    while (true) {
        printf("Enter a positive integer for key size: ");
        
        if (scanf("%d", &a) == 0)
        {
            puts("Sorry, did not understand your input. Repeating question.");
            continue;
        }
        else if (a <= 4)
        {
            puts("Whoops! That's too small. Please enter a higher number!");
            continue;
        }
        else if (a > NP)
        {
            puts("Whoops! That's too big. Please enter a smaller number!");
            continue;
        } 
        else
        {
            printf("%d is just right!\n", a);
            break;
        }
    }
    return a;
}