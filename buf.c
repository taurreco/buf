#include "vec.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*********************************************************************
 *                                                                   *
 *                    constructor / destructor                       *
 *                                                                   *
 *********************************************************************/

/*********
 * mkvec *
 *********/

struct vector*
mkvec(int cap, int stride)
{
    struct vector* vec;
    char* data;
    
    vec = malloc(sizeof(struct vector));
    data = malloc(cap * stride);

    vec->data = data;
    vec->cap = cap;
    vec->len = 0;
    vec->stride = stride;

    return vec;
}

/**********
 * delvec *
 **********/

void
delvec(struct vector* vec)
{
    free(vec->data);
    free(vec);
}

/*********************************************************************
 *                                                                   *
 *                             utility                               *
 *                                                                   *
 *********************************************************************/

/**********
 * resize *
 **********/

/* changes size of vector */

void
resize(struct vector* vec, int new_cap)
{
    char* new_data;
    char* tmp;

    new_data = malloc(new_cap * vec->stride);
    tmp = vec->data;
    
    memcpy(new_data, vec->data, vec->len * vec->stride);
    vec->data = new_data;
    vec->cap = new_cap;
    
    free(tmp);
}

/**********
 * veclen *
 **********/

int
veclen(struct vector* vec)
{
    return vec->len;
}

/*********************************************************************
 *                                                                   *
 *                            insertion                              *
 *                                                                   *
 *********************************************************************/

/**********
 * vecset *
 **********/

/* updates existing item */

void
vecset(struct vector* vec, void* src, int idx)
{
    memcpy(vec->data + idx * vec->stride, src, vec->stride);
}

/***********
 * vecpush *
 ***********/

/* pushes item to the back of the vector */

void
vecpush(struct vector* vec, void* src)
{
    if (vec->len == vec->cap)
        resize(vec, vec->cap * 2);    

    vec->len++;

    vecset(vec, src, vec->len - 1);
}

/**********
 * vecadd *
 **********/

/* inserts an item at an index */

void
vecadd(struct vector* vec, void* src, int idx)
{
    int bytes;
    char* start;
    
    if (vec->len == vec->cap)
        resize(vec, vec->cap * 2);

    bytes = (vec->len - idx) * vec->stride;
    start = vec->data + idx * vec->stride;

    memmove(start + vec->stride, start, bytes);
    vecset(vec, src, idx);
    
    vec->len++;
}

/*********************************************************************
 *                                                                   *
 *                             deletion                              *
 *                                                                   *
 *********************************************************************/

/**********
 * vecpop *
 **********/

/* removes the last item in the vector, copies it to dst */

void
vecpop(struct vector* vec, void* dst)
{
    if (vec->len < 3 * vec->cap / 4)
        resize(vec, 3 * vec->cap / 4);
    
    if (dst)
    	memcpy(dst, vec->data + (vec->len - 1) * vec->stride, vec->stride);
    
    vec->len--;
}

/**********
 * vecdel *
 **********/

/* deletes an item at an index */

void
vecdel(struct vector* vec, int idx, void* dst)
{
    int bytes;
    char* start;
    
    if (vec->len < 3 * vec->cap / 4)
        resize(vec, 3 * vec->cap / 4);
        
    bytes = (vec->len - idx) * vec->stride;
    start = vec->data + idx * vec->stride;
    
    if (dst)
    	memcpy(dst, start, vec->stride);

    memmove(start, start + vec->stride, bytes);
    
    vec->len--;
}

/*********************************************************************
 *                                                                   *
 *                            retrieval                              *
 *                                                                   *
 *********************************************************************/

/**********
 * vecget *
 **********/

/* copies the item at an index to dst */

void
vecget(struct vector* vec, int idx, void* dst)
{
    memcpy(dst, vec->data + idx * vec->stride, vec->stride);
}

