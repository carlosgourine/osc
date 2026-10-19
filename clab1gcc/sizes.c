#include <stdio.h>
#include "sizes.h"

int main(void){
ValuesOfTypes();
return 0;

}
void ValuesOfTypes(void){
printf("Size int:  %zu\n", sizeof(int));
printf("Size long int:  %zu\n", sizeof(long int));
printf("Size short int:  %zu\n", sizeof(short int));
printf("Size float:  %zu\n", sizeof(float));
printf("Size double:  %zu\n", sizeof(double));
char letter = 'A';
char *p = &letter;
printf("Size pointer char:  %zu\n", sizeof(p));
printf("Size void:  %zu\n",sizeof(void));
printf("Size pointer void:  %zu\n",sizeof(void*));
return;
}