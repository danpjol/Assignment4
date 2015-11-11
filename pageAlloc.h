#include <stdlib.h>
#include <stdio.h>
#ifndef PAGEALLOC_H_
#define PAGEALLOC_H_
typedef struct FREE{
	struct FREE *next;
} FREE;
typedef struct PAGE{
	int size;
	int blocks;
	void *availPtr;
	struct PAGE *nextPg, *prevPg;
	FREE *freePtr;
} PAGE;

void *pgalloc(int size);
void pgfree(void *ptr);
void pgview();
#endif
