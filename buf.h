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

struct buffer* mkbuf(int cap);
void delbuf(struct buffer* buf);

/* insertion */

void bufset(struct buffer* buf, void* src, int off, int len);
void bufpush(struct buffer* buf, void* src, int len);
void bufadd(struct buffer* buf, void* src, int off, int len);

/* deletion */

void bufpop(struct buffer* buf, void* dst, int len);
void bufdel(struct buffer* buf, void* dst, int off, int len);

/* util */

int buflen(struct buffer* buf);
void bufget(struct buffer* buf, void* dst, int off, int len);
void bufdump(struct buffer* buf, void* dst);

#endif    /* VEC_H */
