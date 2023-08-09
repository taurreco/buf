#include "vec.h"
#include "unity.h"

/*********************************************************************
 *                                                                   *
 *                          unity helpers                            *
 *                                                                   *
 *********************************************************************/

void 
setUp() 
{
    /* empty */
}

void 
tearDown() 
{
    /* empty */
}

/*********************************************************************
 *                                                                   *
 *                           basic tests                             *
 *                                                                   *
 *********************************************************************/

/**************
 * basic_push *
 **************/

void
basic_push()
{
    struct vector* vec;
    int one;
    int two;
    int tmp;

    vec = mkvec(2, sizeof(int));
    one = 1;
    two = 2;

    vecpush(vec, &one);
    vecpush(vec, &two);

    vecget(vec, 0, &tmp);
    TEST_ASSERT_EQUAL_INT(one, tmp);

    vecget(vec, 1, &tmp);
    TEST_ASSERT_EQUAL_INT(two, tmp);
    
    delvec(vec);
}

/**************
 * basic_grow *
 **************/

void
basic_grow()
{
    struct vector* vec;
    int one;
    int two;

    vec = mkvec(1, sizeof(int));
    one = 1;
    two = 2;

    vecpush(vec, &one);
    vecpush(vec, &two);

    TEST_ASSERT_TRUE(vec->cap > 1);
    TEST_ASSERT_EQUAL_INT(2, vec->len);

    delvec(vec);
}

/*************
 * basic_add *
 *************/

void
basic_add()
{
    struct vector* vec;
    int one;
    int two;
    int three;
    int tmp;

    vec = mkvec(4, sizeof(int));
    one = 1;
    two = 2;
    three = 3;

    vecpush(vec, &one);
    vecpush(vec, &one);
    vecpush(vec, &three);
    
    TEST_ASSERT_EQUAL_INT(3, vec->len);

    vecget(vec, 1, &tmp);
    TEST_ASSERT_EQUAL_INT(one, tmp);

    vecadd(vec, &two, 1);

    vecget(vec, 1, &tmp);
    TEST_ASSERT_EQUAL_INT(two, tmp);
    TEST_ASSERT_EQUAL_INT(4, vec->len);
    
    vecget(vec, 2, &tmp);
    TEST_ASSERT_EQUAL_INT(one, tmp);
    
    vecget(vec, 3, &tmp);
    TEST_ASSERT_EQUAL_INT(three, tmp);
    
    delvec(vec);
}

/*************
 * basic_pop *
 *************/

void
basic_pop()
{
    struct vector* vec;
    int one;
    int tmp;

    vec = mkvec(1, sizeof(int));
    one = 1;

    vecpush(vec, &one);

    vecget(vec, 0, &tmp); 
    TEST_ASSERT_EQUAL_INT(one, tmp);
    TEST_ASSERT_EQUAL_INT(1, vec->len);

    tmp = 0;

    vecpop(vec, &tmp);
    TEST_ASSERT_EQUAL_INT(one, tmp);
    TEST_ASSERT_EQUAL_INT(0, vec->len);

    delvec(vec);
}

/****************
 * basic_shrink *
 ****************/

void
basic_shrink()
{
    struct vector* vec;
    int one;

    vec = mkvec(4, sizeof(int));
    one = 1;

    vecpush(vec, &one);
    vecpush(vec, &one);
    vecpush(vec, &one);
    vecpush(vec, &one);

    TEST_ASSERT_EQUAL_INT(4, vec->cap);
    
    vecpop(vec, 0);
    vecpop(vec, 0);
    vecpop(vec, 0);

    TEST_ASSERT_EQUAL_INT(3, vec->cap);

    delvec(vec);
}

/*************
 * basic_del *
 *************/

void
basic_del()
{
    struct vector* vec;
    int one;
    int two;
    int tmp;

    vec = mkvec(4, sizeof(int));
    one = 1;
    two = 2;

    vecpush(vec, &one);
    vecpush(vec, &one);
    vecpush(vec, &two);
    
    TEST_ASSERT_EQUAL_INT(3, vec->len);

    vecget(vec, 1, &tmp);
    TEST_ASSERT_EQUAL_INT(one, tmp);

    vecdel(vec, 1, 0);
    TEST_ASSERT_EQUAL_INT(2, vec->len);
    
    vecget(vec, 1, &tmp);
    TEST_ASSERT_EQUAL_INT(two, tmp);
    
    delvec(vec);
}


/*********************************************************************
 *                                                                   *
 *                              main                                 *
 *                                                                   *
 *********************************************************************/

/********
 * main *
 ********/

int
main() 
{
    UNITY_BEGIN();
    RUN_TEST(basic_push);
    RUN_TEST(basic_grow);
    RUN_TEST(basic_add);
    RUN_TEST(basic_pop);
    RUN_TEST(basic_shrink);
    RUN_TEST(basic_del);
    return UNITY_END();
}

