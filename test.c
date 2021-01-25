#include "include/malloc.h"

int main()
{
    char *s;
    char *s2;

    if (!(s = (char *)ft_malloc(20)))
        return -1;
    printf("s: %p\n", s);
    strcpy(s, "salut");
    printf("%s\n", s);
    /* if (!(s2 = (char *)ft_malloc(64))) */
    /*     return -1; */
    /* printf("s2: %p\n", s2); */
    /* strcpy(s2, "bonjour comment ca va?"); */
    /* printf("%s\n", s); */
    return (0);
}
