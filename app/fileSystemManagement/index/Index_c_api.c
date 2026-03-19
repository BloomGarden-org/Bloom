#define _POSIX_C_SOURCE 200809L
#include "Index_struct.h"
#include <stdlib.h>
#include <string.h>
#define HASH_BYTES_SIZE 20
#define HASH_STR_SIZE (HASH_BYTES_SIZE * 2 + 1)

#define ERR_BAD_ALLOC 2
#define ERR_NULL_PTR 3
#define ERR_NONEXISTANTE_VALUE 4
#define ERR_INVALID_OPERATION 5


Branch *alloc_branch(const char *name, const char *hash){
    if (!name || !hash || strlen(hash) != HASH_STR_SIZE - 1) {
        return NULL;
    }

    Branch *branch = malloc(sizeof(Branch));
    if(!branch){
        return NULL;
    }
    branch->name = strdup(name);
    if (!branch->name) {
        free(branch);
        return NULL;
    }

    strncpy(branch->hash, hash, HASH_STR_SIZE);
    branch->hash[HASH_STR_SIZE] = '\0';
    branch->next = NULL;

    return branch;
}

/**
 * free the index
 * @throw ERR_NULL_PTR 3
 */
int free_Index(Index_s *index){
    if (!index) return ERR_NULL_PTR;

    Branch* current = index->list;

    while (current) {
        Branch* next = current->next;
        free(current->name);
        free(current);
        current = next;
    }

    index->list = NULL;
    index->current = NULL;
    return 1;
}


/**
 * adds a branch to the index if branch list to index is null then it creates the list
 * @throw ERR_BAD_ALLOC 2
 * @throw ERR_NULL_PTR  3
 */
int add_branch(Index_s *index, const char *name, const char *hash){
    if(!index || !name || !hash) return ERR_NULL_PTR;

    Branch** ptr = &index->list;
        
    while(*ptr != NULL){
        if(strcmp((*ptr)->name,name)==0)
            return ERR_INVALID_OPERATION;
            
        ptr = &(*ptr)->next;
    }
    *ptr=alloc_branch(name, hash);

    if(!*ptr)
        return ERR_BAD_ALLOC;
    return 1;
}

/**
 * set la branch current
 * @throw ERR_NULL_PTR  2
 * @throw ERR_NONEXISTANTE_VALUE  3
 */
int set_current(Index_s *index,const char *name){
    if(!name) return ERR_NULL_PTR;

    Branch *ptr = index->list;

    while(ptr && strcmp(ptr->name,name) != 0)// cherche si elle existe
        ptr =ptr->next;

    if(!ptr) return ERR_NONEXISTANTE_VALUE;

    index->current = ptr; //set la branche
    return 1;
}


/**
 * delete a branch from the index 
 * @throw ERR_NONEXISTANTE_VALUE 3
 * @throw ERR_INVALID_OPERATION 4
 */
int delete_branch(Index_s *index, const char *name){
    if(!index || !name) return ERR_NULL_PTR;

    if(strcmp(name, "main")==0) return ERR_INVALID_OPERATION;

    Branch **ptr = &index->list;

    while(*ptr && strcmp((*ptr)->name, name) != 0 )
        ptr = &(*ptr)->next;

    if(!*ptr)
        return ERR_NONEXISTANTE_VALUE;

    Branch* trash = *ptr;
    *ptr = trash->next;

    free(trash);
    return 1;
}
