#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "pageAlloc.h"
#include "pageAlloc.c"

int main()
{
/*	for(int i = 1; i<1000; i++)
	{
		pgalloc(i);
		i+=10;
	}*/
	int size = 100;
	pgalloc(size);
	pgalloc(size);
	pgalloc(size);
	void *mem = pgalloc(size);
	pgfree(mem);
	pgalloc(size);
	mem = pgalloc(size);
	pgfree(mem);
	mem = pgalloc(size);
	pgfree(mem);
	mem = pgalloc(size);
	pgfree(mem);
	pgview();
	return 0;
}
