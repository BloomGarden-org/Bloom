#define _POSIX_C_SOURCE 200809L
#include "FOS_metadata_struct.h"
#include <string.h>
#include <stdlib.h>


metadataFOS_S *metadata_init(const char* fostype, const char (*hash)[HASH_STR_SIZE], const char *fosname){
    metadataFOS_S *fos = malloc(sizeof(metadataFOS_S));
    if (!fos) return NULL;

    fos->fostype = strdup(fostype);
    fos->fosname = strdup(fosname);

    if (!fos->fostype || !fos->fosname) {
        free(fos->fostype);
        free(fos->fosname);
        free(fos);
        return NULL;
    }

    strncpy(fos->hash,*hash,HASH_STR_SIZE);
    return fos;
}

void metadata_free(metadataFOS_S *fos){
    free(fos->fosname);
    free(fos->fostype);
    fos->hash[0] = '\0';
    free(fos);
}