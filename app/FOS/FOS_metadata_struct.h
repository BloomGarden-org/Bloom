#pragma once
#include<string.h>
#include<stdlib.h>
#ifndef HASH_STR_SIZE
#define HASH_STR_SIZE 41
#endif
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Structure qui represent un filesystem object en c
 * 
 * @param fostype type soit folder ou file
 * @param signature le hash de la fonction
 * @param fosname le nom + extension de la fonction
 */
typedef struct {
    char *fostype;
    char  hash[HASH_STR_SIZE];
    char *fosname; 
}metadataFOS_S;

metadataFOS_S *metadata_init(const char* fostype, const char (*hash)[HASH_STR_SIZE], const char *fosname);

void metadata_free(metadataFOS_S *FOS);
#ifdef __cplusplus
}
#endif



