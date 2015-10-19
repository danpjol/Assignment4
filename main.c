#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
void *pgalloc(int size);
typedef struct PAGE{
  int size;
  int blocks;
  boid *freePtr, *availPtr, *nextPg, *prevPg;
} PAGE;
PAGE *pages[125];

int main()
{
  return 0;
}

void *pgalloc(int size)
{
  if(size<1 || size>1000)
  }
    printf("Size out of bounds.");
    return 0;
  }
  PAGE *ptr;
  ptr = memalign(1024, 1024);
  ptr = (PAGE*)malloc(1024, 1024);
  pagePtr->size = size;
  pagePtr->blocks = 0;
  pagePtr->freePtr = memalign(8, 1024);
  pagePtr-> NULL;
  pagePtr->availPtr = ((char*)PAGE)+1024;
}
