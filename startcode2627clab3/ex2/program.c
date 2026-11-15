#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "dplist.h"
/**
 * \author Bert Lagaisse
 *
 * main method that executes some test functions (without check framework)
 */

#include <stdio.h>
#include "dplist.h"

void ck_assert_msg(bool result, char * msg){
    if(!result) printf("%s\n", msg);
}
int main(void)
{
    dplist_t *numbers = NULL;
    numbers = dpl_create();

    ck_assert_msg(numbers != NULL, "numbers = NULL, List not created");
    ck_assert_msg(dpl_size(numbers) == 0, "Numbers may not contain elements.");

    dpl_insert_at_index(numbers, "apple", 0);

    dpl_insert_at_index(numbers, "banana", -1);

    dpl_insert_at_index(numbers, "cherry", 100);
     
    ck_assert_msg(
    strcmp(dpl_get_element_at_index(numbers, 1), "apple") == 0,
    "Wrong element at index 1"
);


    dpl_free(&numbers);

    return 0;
}