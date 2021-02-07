#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/malloc.h"

int main()
{
	char *str, *ptr;
	if (!(str = malloc(10)))
		exit (128);
	printf("Malloc OK\n");
	if (!(ptr = realloc(str, -17)))
		return 0;
	printf("Realloc OK\n");
}
