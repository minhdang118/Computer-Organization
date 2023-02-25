#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

unsigned int RM = 31;
unsigned int RMU = 29;
unsigned int RMI = 13;

unsigned int g(int a) {
    return (a * RMU + RMI) % RM;
}

void r(int *a, int b) {
    int c = 0;
    int d = g(b*b);
    c = 0;
    while (c < b)
    {   
        a[c] = d;
        d=g(a[c]);
        c++;
    }
    return;
}