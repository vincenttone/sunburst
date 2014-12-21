#ifndef SUNBUR_MEM_H
#define SUNBUR_MEM_H 1

void *vmalloc(size_t size);
void *vcalloc(size_t count, size_t size);
void vfree(void *ptr);

#endif
