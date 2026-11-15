/**
 * \author Jeroen Van Aken, Bert Lagaisse, Ludo Bruynseels
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "dplist.h"
#include <string.h>


/*
 * The real definition of struct list / struct node
 */
struct dplist_node {
    dplist_node_t *prev, *next;
    element_t element;
};

struct dplist {
    dplist_node_t *head;
    // more fields will be added later
};

dplist_t *dpl_create() {
    dplist_t *list;
    list = malloc(sizeof(struct dplist));
    list->head = NULL;
  return list;
}

void dpl_free(dplist_t **list) {
    if(list==NULL){return ;}
    if(*list==NULL){return ;}
    dplist_node_t *huidig = (*list)->head;
    
    //TODO: add your code here
    //Do extensive testing with valgrind. 
 dplist_node_t *t;
   
    
    while(huidig != NULL){
        t=huidig->next;
        free(huidig );
        huidig = t;
    }
    free(*list);
    *list=NULL;
    return ;
}

/* Important note: to implement any list manipulation operator (insert, append, delete, sort, ...), always be aware of the following cases:
 * 1. empty list ==> avoid errors
 * 2. do operation at the start of the list ==> typically requires some special pointer manipulation
 * 3. do operation at the end of the list ==> typically requires some special pointer manipulation
 * 4. do operation in the middle of the list ==> default case with default pointer manipulation
 * ALWAYS check that you implementation works correctly in all these cases (check this on paper with list representation drawings!)
 **/


dplist_t *dpl_insert_at_index(dplist_t *list, element_t element, int index) {
    dplist_node_t *ref_at_index, *list_node;
    if (list == NULL) return NULL;

    list_node = malloc(sizeof(dplist_node_t));

    list_node->element = element;
    // pointer drawing breakpoint
    if (list->head == NULL) { // covers case 1
        list_node->prev = NULL;
        list_node->next = NULL;
        list->head = list_node;
        // pointer drawing breakpoint
    } else if (index <= 0) { // covers case 2
        list_node->prev = NULL;
        list_node->next = list->head;
        list->head->prev = list_node;
        list->head = list_node;
        // pointer drawing breakpoint
    } else {
        ref_at_index = dpl_get_reference_at_index(list, index);
        assert(ref_at_index != NULL);
        // pointer drawing breakpoint
        if (index < dpl_size(list)) { // covers case 4
            list_node->prev = ref_at_index->prev;
            list_node->next = ref_at_index;
            ref_at_index->prev->next = list_node;
            ref_at_index->prev = list_node;
            // pointer drawing breakpoint
        } else { // covers case 3
            assert(ref_at_index->next == NULL);
            list_node->next = NULL;
            list_node->prev = ref_at_index;
            ref_at_index->next = list_node;
            // pointer drawing breakpoint
        }
    }
    return list;
}

dplist_t *dpl_remove_at_index(dplist_t *list, int index) {
    if(list==NULL){return NULL;}
    if(list->head==NULL){return list;}
    dplist_node_t *removed = dpl_get_reference_at_index(list, index);
    dplist_node_t *rprev =removed->prev;
    dplist_node_t *rnext =removed->next;
    if(rprev==NULL){list->head = rnext;}
    else{rprev ->next = rnext; }
    if(rnext!=NULL){rnext->prev = rprev;}
   
     free(removed);
    //TODO: add your code here
    return list;
}

int dpl_size(dplist_t *list) {
     if(list==NULL){return -1;}
    dplist_node_t *huidig = list->head;
   
    int count =0;
    while(huidig != NULL){
        count++;
        huidig = huidig->next;
    }
    return count;
}

dplist_node_t *dpl_get_reference_at_index(dplist_t *list, int index) {
    if(list==NULL){return NULL;}
    if(list->head==NULL){return NULL;}
    dplist_node_t *huidig = list->head;
    dplist_node_t *dummy = NULL;
    for(int i=0;i<index&&huidig->next!=NULL;i++){
        huidig =huidig->next;
    }
    dummy = huidig;
    //TODO: add your code here
    return dummy;
}

element_t dpl_get_element_at_index(dplist_t *list, int index) {
    if(list==NULL){return NULL;}
    if(list->head==NULL){return NULL;}
    char *v=NULL;
    
    dplist_node_t *huidig = dpl_get_reference_at_index(list, index);
    v=huidig->element;
    //TODO: add your code here
    return v;
}

int dpl_get_index_of_element(dplist_t *list, element_t element) {
    if(list==NULL){return -1;}
    if(list->head==NULL){return -1;}
    int index = 0;
    dplist_node_t *huidig = list->head;
    
    while(huidig != NULL){
        if(strcmp(huidig->element, element)==0){return index;}
        huidig =huidig->next;
        index++;
    }
    
    //TODO: add your code here
    return -1;
}



