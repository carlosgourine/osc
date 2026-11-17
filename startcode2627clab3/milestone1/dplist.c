

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dplist.h"




/*
 * The real definition of struct list / struct node
 */

struct dplist_node {
    dplist_node_t *prev, *next;
    void *element;
};

struct dplist {
    dplist_node_t *head;

    void *(*element_copy)(void *src_element);

    void (*element_free)(void **element);

    int (*element_compare)(void *x, void *y);
};


dplist_t *dpl_create(// callback functions
        void *(*element_copy)(void *src_element),
        void (*element_free)(void **element),
        int (*element_compare)(void *x, void *y)
) {
    dplist_t *list;
    list = malloc(sizeof(struct dplist));
    assert(list != NULL);
    list->head = NULL;
    list->element_copy = element_copy;
    list->element_free = element_free;
    list->element_compare = element_compare;
    return list;
}

void dpl_free(dplist_t **list, bool free_element) {
    if(list==NULL){return ;}
    if(*list==NULL){return ;}
    dplist_node_t *huidig = (*list)->head;
    
    //TODO: add your code here 
    dplist_node_t *t;
   
    
    while(huidig != NULL){
        t=huidig->next;
         if (free_element == true) {
        (*list)->element_free(&huidig->element);}
        free(huidig );
        huidig = t;
    }
    free(*list);
    *list=NULL;
    return ;
    //TODO: add your code here

}

dplist_t *dpl_insert_at_index(dplist_t *list, void *element, int index, bool insert_copy) {
dplist_node_t *ref_at_index, *list_node;
    if (list == NULL) return NULL;

    list_node = malloc(sizeof(dplist_node_t));
    assert(list_node != NULL);
    if (insert_copy == true) {
    list_node->element = list->element_copy(element);
     }
    else {
    list_node->element = element;
    }
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
    //TODO: add your code here

}

dplist_t *dpl_remove_at_index(dplist_t *list, int index, bool free_element) {
    if(list==NULL){return NULL;}
    if(list->head==NULL){return list;}
    dplist_node_t *removed = dpl_get_reference_at_index(list, index);
    dplist_node_t *rprev =removed->prev;
    dplist_node_t *rnext =removed->next;
    if(rprev==NULL){list->head = rnext;}
    else{rprev ->next = rnext; }
    if(rnext!=NULL){rnext->prev = rprev;}
     if (free_element == true) {
    list->element_free(&removed->element);
     }
     free(removed);
    //TODO: add your code here
    return list;
    //TODO: add your code here

}

int dpl_size(dplist_t *list) {
    if(list==NULL){return -1;}
    if(list->head==NULL){return 0;}
    dplist_node_t *huidig = list->head;
   
    int count =0;
    while(huidig != NULL){
        count++;
        huidig = huidig->next;
    }
    return count;

    //TODO: add your code here

}

void *dpl_get_element_at_index(dplist_t *list, int index) {
    if(list==NULL){return NULL;}
    if(list->head==NULL){return NULL;}
    void *v ;
    dplist_node_t *huidig = dpl_get_reference_at_index(list, index);
    v=huidig->element;
    //TODO: add your code here
    return v;
    //TODO: add your code here

}

int dpl_get_index_of_element(dplist_t *list, void *element) {
      if(list==NULL){return -1;}
    if(list->head==NULL){return -1;}
    int index = 0;
    dplist_node_t *huidig = list->head;
    
    while(huidig != NULL){
        if(list->element_compare(huidig->element, element)==0){return index;}
        huidig =huidig->next;
        index++;
    }
    
    //TODO: add your code here
    return -1;
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

    //TODO: add your code here

}

void *dpl_get_element_at_reference(dplist_t *list, dplist_node_t *reference) {
    if(list==NULL){return NULL;}
    if(reference==NULL){return NULL;}
    if(list->head==NULL){return NULL;}
    dplist_node_t *huidig = list->head;
    
    while(huidig != NULL){
       if(huidig == reference){return huidig->element;}
        huidig =huidig->next;
        
    }
    return NULL;
    
    //TODO: add your code here

}


