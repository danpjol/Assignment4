#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "pageAlloc.h"

PAGE *pages[125];

void *pgalloc(int size)
{
	void *temp;
	int index = size/8;
	int block = (index+1)*8;
	PAGE *ptr;
	ptr = pages[index];
	if(ptr == NULL)
	{
		ptr = _aligned_malloc(1024, 1024);
		ptr->freePtr = NULL;
		ptr->nextPg = NULL;
		ptr->prevPg = NULL;
		ptr->size = block;
		ptr->blocks = 0;
		ptr->availPtr = (char*)ptr + 1024;
		pages[index] = ptr;
		temp = ptr->availPtr;
	}
	else
	{
		if(ptr->freePtr == NULL)
		{
			ptr->availPtr -= ptr->size;
			temp = ptr->availPtr;
		}
		else
		{
			temp = ptr->freePtr;
			ptr->freePtr = ptr->freePtr->next;
		}
	}
	ptr->blocks++;
	if(ptr->blocks == ptr->size)
	{
		pages[index] = ptr->nextPg;
	}
	return temp;
}
