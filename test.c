#include "include/malloc.h"
#include <errno.h>

int main()
{
    char *s;
    void *new;
    char *s2;
    char *s3;

    /* write(1, "A", 1); */
    /* write(1, "A", 1); */
    /* if (!(new = mmap(0, 409600, PROT, FLGS, -1, 0))) */
    /*     return -1; */
    /* printf("addr mmap: %p\n", new); */
    /* printf("addr mmap+48: %p\n", new + 48); */
    /* if (!(s = (char *)malloc(409600))) */
    /*     return -1; */
    /* printf("addr malloc: %p\n", s); */
    if (!(s = (char *)ft_malloc(20)))
        return -1;
    if (!(s2 = (char *)ft_malloc(64)))
        return -1;
    if (!(s3 = (char *)ft_malloc(5000)))
        return -1;
    printf("s: %p\n", s);
    strcpy(s, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    printf("%s\n", s);
    printf("s2: %p\n", s2);
    strcpy(s2, "bonjour comment ca va?");
    printf("%s\n", s2);
    printf("s3: %p\n", s3);
    strcpy(s3, "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
    printf("%s\n", s3);
    show_alloc_mem();
    return (0);
}
