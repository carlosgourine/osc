#include <stdio.h>

#include <stdlib.h>

#include <string.h>
swap_pointers( void *x , void *y ){
int **px;
int **py;
px=x;
py=y;
}
int a = 1;
int b = 2;
// for testing we use pointers to integers
int *p = &a;
int *q = &b;
printf("address of p = %p and q = %p\n", p, q);
// prints p = &a and q = &b
swap_pointers( void *p , void *q );
printf("address of p = %p and q = %p\n", p, q);
// prints p = &b and q = &a


