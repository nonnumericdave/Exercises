#ifndef AlignedMalloc_h
#define AlignedMalloc_h

void* AlignedMalloc(size_t uSize, size_t uAlignment);
void AlignedFree(void* pv);

#endif
