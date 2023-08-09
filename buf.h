#ifndef VEC_H
#define VEC_H

/**********
 * vector *
 **********/

struct vector {
    char* data;
    int cap;
    int len;
    int stride;
};

/* construction / destruction */

struct vector* mkvec(int cap, int stride);
void delvec(struct vector* vec);

/* insertion */

void vecset(struct vector* vec, void* src, int idx);
void vecpush(struct vector* vec, void* src);
void vecadd(struct vector* vec, void* src, int idx);

/* deletion */

void vecpop(struct vector* vec, void* dst);
void vecdel(struct vector* vec, int idx, void* dst);

/* retrieval */

void vecget(struct vector* vec, int idx, void* dst);

/* utility */

int veclen(struct vector* vec);

#endif    /* VEC_H */
