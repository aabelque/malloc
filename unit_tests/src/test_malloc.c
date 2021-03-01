#include "./test.h"
#include <stdio.h>
#include <unistd.h>

static void test_malloc_null()
{
    void *t = malloc(0);
    if (!t)
        printf("malloc(0) should return minimum size 16\n");
    free(t);
}

static void test_malloc_one()
{
    char *t = (char *)malloc(1);
    if (!t) {
        printf("malloc(1) should return ptr\n");
        return;
    }
    t[0] = 0xFF;
    t[1] = 0xFF;
    t[2] = 0xFF;
    t[3] = 0xFF;
    show_alloc_mem();

    t[0] = 0;
    free(t);
}

static void test_malloc_getpagesize()
{
    void *t = malloc(getpagesize());
    free(t);
}

static void test_malloc_limits()
{
	int *t0[1024];
	int i = 0;

	while (i++ < 1023)
	{
		t0[i] = (int *)malloc(TINY);
		*t0[i] = 42;
	}

    void	*t	= malloc(1);
    void	*t00	= malloc(TINY);
    void	*t000	= malloc(TINY);
    void	*t1	= malloc(SMALL + 1);
    void	*t2	= malloc(SMALL + 1);

    i = 511;
    while (i++ < 1023)
		free(t0[i]);
	i = 0;
    while (i++ < 511)
		free(t0[i]);
    
    void *f0 = malloc(TINY - sizeof(t_heap));
    show_alloc_mem();
    free(t);
    free(t00);
    free(t000);
    free(t1);
    free(t2);
    show_alloc_mem();
}

static void test_malloc_free_size()
{
    void *t = malloc(SMALL + 1);

    /* show_alloc_mem(); */
    free(t);
    /* show_alloc_mem(); */
}

void run_test_malloc(void)
{
    test_malloc_null();
    test_malloc_one();
    test_malloc_getpagesize();
    test_malloc_limits();
    test_malloc_free_size();

    /* show_alloc_mem(); */
}
