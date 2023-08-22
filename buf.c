#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "buf.h"

/*********************************************************************
 *                                                                   *
 *                    constructor / destructor                       *
 *                                                                   *
 *********************************************************************/

/*************
 * buf_alloc *
 *************/

struct buffer*
buf_alloc(int cap)
{
    struct buffer* buf;
    char* data;
    
    buf = malloc(sizeof(struct buffer));
    data = malloc(cap);

    buf->data = data;
    buf->cap = cap;
    buf->len = 0;

    return buf;
}

/************
 * buf_free *
 ************/

void
buf_free(struct buffer* buf)
{
    free(buf->data);
    free(buf);
}

/*********************************************************************
 *                                                                   *
 *                             utility                               *
 *                                                                   *
 *********************************************************************/

/**********
 * resize *
 **********/

/* changes size of buffer */

void
resize(struct buffer* buf, int new_cap)
{
    char* new_data;
    char* tmp;

    new_data = malloc(new_cap);
    tmp = buf->data;
    
    memcpy(new_data, buf->data, buf->len);
    buf->data = new_data;
    buf->cap = new_cap;
    
    free(tmp);
}

/***********
 * buf_len *
 ***********/

int
buf_len(struct buffer* buf)
{
    return buf->len;
}

/*********************************************************************
 *                                                                   *
 *                            insertion                              *
 *                                                                   *
 *********************************************************************/

/***********
 * buf_set *
 ***********/

/* updates existing chunk in buffer */

void
buf_set(struct buffer* buf, void* src, int off, int len)
{
    memcpy(buf->data + off, src, len);
}

/************
 * buf_push *
 ************/

/* pushes chunk to the back of the buffer */

void
buf_push(struct buffer* buf, void* src, int len)
{
    while (buf->len + len >= buf->cap)
        resize(buf, buf->cap * 2);    

    buf->len += len;

    buf_set(buf, src, buf->len - len, len);
}

/***********
 * buf_put *
 ***********/

/* inserts an chunk in the middle of the buffer */

void
buf_put(struct buffer* buf, void* src, int off, int len)
{
    char* start;
    
    while (buf->len + len >= buf->cap)
        resize(buf, buf->cap * 2);

    start = buf->data + off;

    memmove(start + len, start, buf->len - len);
    buf_set(buf, src, off, len);
    
    buf->len += len;
}

/*********************************************************************
 *                                                                   *
 *                             deletion                              *
 *                                                                   *
 *********************************************************************/

/***********
 * buf_pop *
 ***********/

/* removes chunk from back of buffer, copies it to dst */

void
buf_pop(struct buffer* buf, void* dst, int len)
{
    if (buf->len < 3 * buf->cap / 4)
        resize(buf, 3 * buf->cap / 4);
    
    memcpy(dst, buf->data + (buf->len - len), len);
    
    buf->len -= len;
}

/***********
 * buf_del *
 ***********/

/* deletes an chunk at an offset */

void
buf_del(struct buffer* buf, void* dst, int off, int len)
{
    char* start;
    
    if (buf->len < 3 * buf->cap / 4)
        resize(buf, 3 * buf->cap / 4);
   
    start = buf->data + off;
    
    memcpy(dst, start, len);

    memmove(start, start + len, buf->len - len);
    
    buf->len -= len;
}

/*********************************************************************
 *                                                                   *
 *                            retrieval                              *
 *                                                                   *
 *********************************************************************/

/***********
 * buf_get *
 ***********/

/* copies a chunk at an offset to dst */

void
buf_get(struct buffer* buf, void* dst, int off, int len)
{
    memcpy(dst, buf->data + off, len);
}

/************
 * buf_dump *
 ************/

/* copies the whole buffer to dst */

void
buf_dump(struct buffer* buf, void* dst)
{
    memcpy(dst, buf->data, buf->len);
}


