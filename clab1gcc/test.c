#include <stdio.h>
#include "test.h"

int main(void){
chartype();
chartest();
return 0;

}
void chartype(void){
char test = 'A';
char test1 = 'B';
char test3 = 4;
char test2 = -1;
printf("test:  %c\n", test);
printf("test:  %d\n", test);
printf("test1:  %c\n", test1);
printf("test1:  %d\n", test1);
printf("test2:  %c\n", test2);
printf("test2:  %d\n", test2);
printf("test3:  %c\n", test3);
printf("test3:  %d\n", test3);
return;
}

void chartest(void){
    char test4 = -1;
    if (test4 <0) {
        printf("test4 is" " negative\n");
    }
}