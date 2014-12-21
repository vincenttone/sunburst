#include <stdlib.h>
#include "vmem.h"

void *vmalloc(size_t size)
{
  return malloc(size);
}

void *vcalloc(size_t count, size_t size)
{
  return calloc(count, size);
}

void vfree(void *ptr)
{
  return free(ptr);
}
