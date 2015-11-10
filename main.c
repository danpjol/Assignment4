#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "pageAlloc.h"
#include "pageAlloc.c"

int main()
{
	int *ptr, *next;
	ptr = pgalloc(1000);
	next = pgalloc(7);
	pages[0] = NULL;
	printf("%p\n%p\n%p", ptr, next, pages[0]);
	return 0;
}
