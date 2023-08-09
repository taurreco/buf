#include "buf.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*********************************************************************
 *                                                                   *
 *                    constructor / destructor                       *
 *                                                                   *
 *********************************************************************/

/*********
 * mkbuf *
 *********/

struct buffer*
mkbuf(int cap)
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

/**********
 * delbuf *
 **********/

void
delbuf(struct buffer* buf)
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

/**********
 * buflen *
 **********/

int
buflen(struct buffer* buf)
{
    return buf->len;
}

/*********************************************************************
 *                                                                   *
 *                            insertion                              *
 *                                                                   *
 *********************************************************************/

/**********
 * bufset *
 **********/

/* updates existing chunk in buffer */

void
bufset(struct buffer* buf, void* src, int off, int len)
{
    memcpy(buf->data + off, src, len);
}

/***********
 * bufpush *
 ***********/

/* pushes chunk to the back of the buffer */

void
bufpush(struct buffer* buf, void* src, int len)
{
    while (buf->len + len >= buf->cap)
        resize(buf, buf->cap * 2);    

    buf->len += len;

    bufset(buf, src, buf->len - len, len);
}

/**********
 * bufadd *
 **********/

/* inserts an chunk in the middle of the buffer */

void
bufadd(struct buffer* buf, void* src, int off, int len)
{
    char* start;
    
    while (buf->len + len >= buf->cap)
        resize(buf, buf->cap * 2);

    start = buf->data + off;

    memmove(start + len, start, buf->len - len);
    bufset(buf, src, off, len);
    
    buf->len += len;
}

/*********************************************************************
 *                                                                   *
 *                             deletion                              *
 *                                                                   *
 *********************************************************************/

/**********
 * bufpop *
 **********/

/* removes chunk from back of buffer, copies it to dst */

void
bufpop(struct buffer* buf, void* dst, int len)
{
    if (buf->len < 3 * buf->cap / 4)
        resize(buf, 3 * buf->cap / 4);
    
    memcpy(dst, buf->data + (buf->len - len), len);
    
    buf->len -= len;
}

/**********
 * bufdel *
 **********/

/* deletes an chunk at an offset */

void
bufdel(struct buffer* buf, void* dst, int off, int len)
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
 * bufget *
 ***********/

/* copies a chunk at an offset to dst */

void
bufget(struct buffer* buf, void* dst, int off, int len)
{
    memcpy(dst, buf->data + off, len);
}

/***********
 * bufdump *
 ***********/

/* copies the whole buffer to dst */

void
bufdump(struct buffer* buf, void* dst)
{
    memcpy(dst, buf->data, buf->len);
}


