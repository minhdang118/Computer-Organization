#include <stdio.h>
#include <stdint.h>

/* fill in return type */long fn1(void) {
  /* fill in body */
  int a = 1;
  int b = 5;
  long c = 4294967295;
  return a * b + c;
}

/* fill in return type */int fn2 (/* fill in parameter list */int p1, int p2, int p3) {
  /* fill in body */
  int max;
  if (p1 > p2) max = p1;
  else max = p2;
  if (p3 > max) {
    max = p3;
  }
  return max;
}

/* fill in return type */long fn3 (/* fill in parameter list */long p1) {
  /* fill in body */
  long a = 0;
  int b = 0;
  while (b < p1) {
    a += b;
    b++;
  }
  return a;
}

/*
   you can run `gcc -S a2_prep.c` to get the file `a2_prep.s` which
   should resemble `a2_prep.S` if your solution is correct on cycle1.
*/
