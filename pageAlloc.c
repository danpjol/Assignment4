#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "pageAlloc.h"
#define PAGE_SIZE 1024
PAGE *pages[125];
PAGE *fullPg = NULL;

void *pgalloc(int size)
{
	void *temp;
	int index = size/8;
	int block = (index+1)*8;
	PAGE *ptr;
	ptr = pages[index];
	if(ptr == NULL)
	{
		ptr = _aligned_malloc(PAGE_SIZE, PAGE_SIZE);
		ptr->freePtr = NULL;
		ptr->nextPg = NULL;
		ptr->prevPg = NULL;
		ptr->size = block;
		ptr->blocks = 0;
		ptr->availPtr = (char*)ptr + PAGE_SIZE;
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
	int max;
	max = (PAGE_SIZE - 24)/ptr->size;
	if(ptr->blocks == max)
	{
		pages[index] = ptr->nextPg;
		if(fullPg == NULL)
		{
			fullPg = ptr;
		}
		else
		{
			ptr->prevPg = fullPg;
			fullPg->nextPg = ptr;
			fullPg = ptr;
		}
	}
	return temp;
}
void pgfree(void *mem)
{
	int pageMask = ~((unsigned int) (PAGE_SIZE-1));
	PAGE *page = (PAGE*) ((((unsigned int) mem) & pageMask));
	int index = (page->size)/8;
	PAGE *ptr = pages[index];
	if(page->blocks == page->size)
	{
		if(page->nextPg != NULL && page->prevPg != NULL)
		{
			page->nextPg->prevPg = page->prevPg;
			page->prevPg->nextPg = page->nextPg;
		}
		else if(page->nextPg == NULL)
		{
			page->prevPg->nextPg = NULL;
		}
		else
		{
			page->nextPg->prevPg = NULL;
		}
		page->nextPg = ptr;
		pages[index] = page;
	}
	
	page->blocks--;
	if(page->freePtr == NULL)
	{
		page->freePtr = mem;
	}
	else
	{
		page->freePtr->next = mem;
		page->freePtr = mem;
	}
}

void pgview()
{
	for(int i = 0; i<125; i++)
	{
		PAGE *ptr = pages[i];
		while(ptr != NULL)
		{
			FREE *free = ptr->freePtr;
			int max;
			max = (PAGE_SIZE - 24)/ptr->size;
			printf("Page at (%p) size(%d) max(%d) used(%d) avl(%p) free(", ptr, ptr->size, max, ptr->blocks, ptr->availPtr);
			while(free != NULL)
			{
				printf("%p ", free);
				free = free->next;
			}
			printf(")\n");
			ptr = ptr->nextPg;
		}
	}
	while(fullPg != NULL)
	{
		int max;
		max = (PAGE_SIZE - 24)/fullPg->size;
		printf("Page at (%p) size(%d) max(%d) used(%d) avl(%p) free()\n", fullPg, fullPg->size, max, fullPg->blocks, fullPg->availPtr);
		fullPg = fullPg->prevPg;
	}
}
