#ifndef BUF_H
#define BUF_H

/**********
 * buffer *
 **********/

struct buffer {
    char* data;
    int cap;
    int len;
};

/* construction / destruction */

struct buffer* buf_alloc(int cap);
void buf_free(struct buffer* buf);

/* insertion */

void buf_set(struct buffer* buf, void* src, int off, int len);
void buf_push(struct buffer* buf, void* src, int len);
void buf_add(struct buffer* buf, void* src, int off, int len);

/* deletion */

void buf_pop(struct buffer* buf, void* dst, int len);
void buf_del(struct buffer* buf, void* dst, int off, int len);

/* util */

int buf_len(struct buffer* buf);
void buf_get(struct buffer* buf, void* dst, int off, int len);
void buf_dump(struct buffer* buf, void* dst);

#endif    /* VEC_H */
