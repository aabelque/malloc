#include "include/malloc.h"
#include <errno.h>
#include <limits.h>

int main()
{
    char *s;
    void *new;
    char *s2;
    char *s3;
    char *s4;
    char *s5;

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
    if (!(s3 = (char *)ft_malloc(48)))
        return -1;
    if (!(s4 = (char *)ft_malloc(8)))
        return -1;
    ft_free(s2);
    if (!(s5 = (char *)ft_malloc(128)))
        return -1;
    ft_free(s3);
    if (!(s2 = (char *)ft_malloc(256)))
        return -1;
    ft_free(s4);
    if (!(s4 = (char *)ft_malloc(400)))
        return -1;
    if (!(s3 = (char *)ft_malloc(48)))
        return -1;
    ft_free(s);
    if (!(s = (char *)ft_malloc(5000)))
        return -1;
    if (!(s = (char *)ft_realloc(s, 7000)))
        return -1;
    /* printf("s: %s\n", s); */
    /* strcpy(s, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"); */
    /* printf("%s\n", s); */
    /* printf("s2: %p\n", s2); */
    /* strcpy(s2, "bonjour comment ca va?"); */
    /* printf("%s\n", s2); */
    /* if (!(s = (char *)ft_malloc(33))) */
    /*     return -1; */
    /* if (!(ss = (char *)ft_malloc(30))) */
    /* /1*     return -1; *1/ */
    /* ft_free(s3); */
    /* ft_free(s4); */
    /* printf("s3: %p\n", s3); */
    /* strcpy(s3, "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"); */
    /* printf("%s\n", s3); */
    /* printf("s4: %p\n", s4); */
    /* strcpy(s4, "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"); */
    /* printf("%s\n", s4); */
    show_alloc_mem();
    return (0);
}
