#include <stdio.h>
#include "strings.h"
#include "string.h"

int is_digit(char c) {
    return c >= '0' && c <= '9';
}

int is_upper(char c) {
    return c >= 'A' && c <= 'Z';
}

int is_lower(char c) {
    return c >= 'a' && c <= 'z';
}

int main(void) {
    char first[MAX];
    char second[MAX];
    char str[MAX];
    char name[MAX];

    printf("Enter first name: ");
    scanf("%99s", first);

    printf("Enter second name: ");
    scanf("%99s", second);

    printf("First: %s\n", first);
    printf("Second: %s\n", second);

    int i =0;
    
    while(second[i] != '\0'){
        char c = second[i];
        if(c>='a'&&c<='z'){
             c = c-('a'-'A');
        }

        printf("%c\n",c);
        str[i] = c;
        i++;
    }
    str[i] = '\0';
    printf("Uppercase name: %s\n", str);
    int comparison = strcmp(second, str);

printf("Comparison result: %d\n", comparison);
if (strcmp(second, str) == 0) {
    printf("The strings are equal!\n");
}

if (strlen(first) + strlen(second) + 2 > sizeof(name)) {
    printf("Combined name is too long!\n");
    return 1;
}

strcpy(name, first);
strcat(name, " ");
strcat(name, second);

printf("Full name: %s\n", name);

int year;

printf("Enter your birth year: ");

if (scanf("%d", &year) != 1) {
    printf("Invalid year!\n");
    return 1;
}

int written = snprintf(name, sizeof(name),
                       "%s %s %d", first, second, year);

if (written < 0 || written >= MAX) {
    printf("Combined information is too long or formatting failed!\n");
    return 1;
}

printf("Name and birth year: %s\n", name);

    return 0;
}
