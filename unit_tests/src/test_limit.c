#include "./test.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

void run_test_rlimit()
{
    char *t;
    struct rlimit rpl;

    rpl.rlim_cur = TINY_ZONE;
    rpl.rlim_max = TINY_ZONE;

    if (setrlimit(RLIMIT_DATA, &rpl) < 0)
        printf("setrlimit did not work\n");

    if (!(t = (char *)malloc(TINY_ZONE - sizeof(t_heap) - sizeof(t_heap))))
        printf("malloc() should return ptr\n");
    free(t);

    if ((t = (char *)malloc(TINY_ZONE)))
        printf("malloc() should return NULL\n");
    free(t);
}
