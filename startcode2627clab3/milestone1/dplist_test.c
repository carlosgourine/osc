#define _GNU_SOURCE

#include "dplist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int id;
    char *name;
} my_element_t;

int copies=0;
int frees=0;
int errors=0;

void *element_copy(void *element) {
    my_element_t *copy = malloc(sizeof(my_element_t));
    assert(copy!=NULL);
    copy->id = ((my_element_t *)element)->id;
    int result = asprintf(&copy->name,"%s",((my_element_t *)element)->name); //asprintf requires _GNU_SOURCE
    assert(result!=-1);
    copies++;
    return copy;
}

void element_free(void **element) {
    my_element_t *v = *element;
    free(v->name);
    free(v);
    *element=NULL;
    frees++;
}

int element_compare(void *x, void *y) {
    int a = ((my_element_t *)x)->id;
    int b = ((my_element_t *)y)->id;
    if(a<b){return -1;}
    if(a>b){return 1;}
    return 0;
}

void ck_assert_msg(bool result, const char *msg) {
    if(!result){
        printf("%s\n",msg);
        errors++;
    }
}

void yourtest1() {
    dplist_t *list=NULL;
    my_element_t a={1,"one"};

    // Test free NULL, don't use callback
    dpl_free(&list,false);
    ck_assert_msg(list==NULL,"Free NULL list failed");
    // Test free NULL, use callback
    dpl_free(&list,true);
    dpl_free(NULL,true);

    ck_assert_msg(dpl_size(NULL)==-1,"Wrong size for NULL");
    ck_assert_msg(dpl_get_element_at_index(NULL,0)==NULL,"Wrong element for NULL");
    ck_assert_msg(dpl_get_reference_at_index(NULL,0)==NULL,"Wrong reference for NULL");
    ck_assert_msg(dpl_get_index_of_element(NULL,&a)==-1,"Wrong index for NULL");
    ck_assert_msg(dpl_insert_at_index(NULL,&a,0,false)==NULL,"Insert into NULL failed");
    ck_assert_msg(dpl_remove_at_index(NULL,0,true)==NULL,"Remove from NULL failed");

    // Test free empty list, don't use callback
    list=dpl_create(element_copy,element_free,element_compare);
    ck_assert_msg(dpl_size(list)==0,"New list should be empty");
    ck_assert_msg(dpl_get_element_at_index(list,0)==NULL,"Empty list returned an element");
    ck_assert_msg(dpl_get_reference_at_index(list,0)==NULL,"Empty list returned a node");
    ck_assert_msg(dpl_get_index_of_element(list,&a)==-1,"Empty list returned an index");
    ck_assert_msg(dpl_get_element_at_reference(list,NULL)==NULL,"NULL reference failed");
    dpl_remove_at_index(list,0,true);
    ck_assert_msg(dpl_size(list)==0,"Removing from empty list failed");
    dpl_free(&list,false);
    ck_assert_msg(list==NULL,"List was not set to NULL");

    // Test free empty list, use callback
    list=dpl_create(element_copy,element_free,element_compare);
    dpl_free(&list,true);
    ck_assert_msg(list==NULL,"Free empty list failed");

    // TODO : your test scenarios
}

void yourtest2() {
    my_element_t a={1,"one"};
    my_element_t b={2,"two"};
    my_element_t c={3,"three"};
    my_element_t d={4,"four"};
    my_element_t test={3,"other"};
    my_element_t missing={99,"missing"};
    dplist_t *list=dpl_create(element_copy,element_free,element_compare);

    dpl_insert_at_index(list,&b,0,true);
    dpl_insert_at_index(list,&d,100,true);
    dpl_insert_at_index(list,&a,-1,true);
    dpl_insert_at_index(list,&c,2,true);

    ck_assert_msg(dpl_size(list)==4,"Wrong size after inserting");
    my_element_t *v=dpl_get_element_at_index(list,0);
    ck_assert_msg(v!=NULL && v->id==1,"Wrong first element");
    v=dpl_get_element_at_index(list,1);
    ck_assert_msg(v!=NULL && v->id==2,"Wrong second element");
    v=dpl_get_element_at_index(list,2);
    ck_assert_msg(v!=NULL && v->id==3,"Wrong third element");
    v=dpl_get_element_at_index(list,3);
    ck_assert_msg(v!=NULL && v->id==4,"Wrong last element");

    ck_assert_msg(dpl_get_element_at_index(list,-10)==dpl_get_element_at_index(list,0),"Negative index failed");
    ck_assert_msg(dpl_get_element_at_index(list,100)==dpl_get_element_at_index(list,3),"Big index failed");
    ck_assert_msg(dpl_get_index_of_element(list,&test)==2,"Finding an element failed");
    ck_assert_msg(dpl_get_index_of_element(list,&missing)==-1,"Missing element should return -1");

    dplist_node_t *ref=dpl_get_reference_at_index(list,1);
    ck_assert_msg(dpl_get_element_at_reference(list,ref)==dpl_get_element_at_index(list,1),"Get element at reference failed");
    ck_assert_msg(dpl_get_element_at_reference(list,NULL)==NULL,"NULL reference failed");

    dpl_remove_at_index(list,1,true);
    ck_assert_msg(dpl_size(list)==3,"Removing middle element failed");
    v=dpl_get_element_at_index(list,1);
    ck_assert_msg(v!=NULL && v->id==3,"Wrong element after removing middle");

    dpl_remove_at_index(list,-1,true);
    ck_assert_msg(dpl_size(list)==2,"Removing first element failed");
    v=dpl_get_element_at_index(list,0);
    ck_assert_msg(v!=NULL && v->id==3,"Wrong first element after removal");

    dpl_remove_at_index(list,100,true);
    ck_assert_msg(dpl_size(list)==1,"Removing last element failed");

    dpl_remove_at_index(list,0,true);
    ck_assert_msg(dpl_size(list)==0,"Removing only element failed");
    dpl_free(&list,true);
    ck_assert_msg(list==NULL,"List not NULL after free");
}

void yourtest3() {
    my_element_t a={10,"ten"};
    my_element_t b={20,"twenty"};
    dplist_t *list=dpl_create(element_copy,element_free,element_compare);
    int oldcopies=copies;
    int oldfrees=frees;

    dpl_insert_at_index(list,&a,0,false);
    dpl_insert_at_index(list,&b,1,false);
    ck_assert_msg(copies==oldcopies,"Copy was called with false");
    ck_assert_msg(dpl_get_element_at_index(list,0)==&a,"Wrong pointer when not copying");

    dpl_remove_at_index(list,0,false);
    ck_assert_msg(frees==oldfrees,"Element was freed with false");
    dpl_free(&list,false);
    ck_assert_msg(frees==oldfrees,"Free callback was called with false");

    list=dpl_create(element_copy,element_free,element_compare);
    dpl_insert_at_index(list,&a,0,true);
    void *p=dpl_get_element_at_index(list,0);
    ck_assert_msg(p!=&a,"Element was not copied");
    oldfrees=frees;
    dpl_remove_at_index(list,0,false);
    ck_assert_msg(frees==oldfrees,"Removed element was freed with false");
    element_free(&p);
    dpl_free(&list,true);

    list=dpl_create(element_copy,element_free,element_compare);
    dpl_insert_at_index(list,&a,0,true);
    dpl_insert_at_index(list,&b,1,true);
    p=dpl_get_element_at_index(list,0);
    void *q=dpl_get_element_at_index(list,1);
    oldfrees=frees;
    dpl_free(&list,false);
    ck_assert_msg(frees==oldfrees,"Elements were freed with false");
    element_free(&p);
    element_free(&q);
}

int main(void) {
    yourtest1();
    yourtest2();
    yourtest3();
    ck_assert_msg(copies==frees,"Not all copied elements were freed");
    if(errors==0){printf("All tests passed\n");}
    return errors==0 ? 0 : 1;
}