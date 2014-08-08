#include "Standard.h"

#include "AlignedMalloc.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void* 
AlignedMalloc(size_t uSize, size_t uAlignment)
{
	if ( uAlignment == 0 )
		return nullptr;

	constexpr size_t uSizeOfPointer = sizeof(void*);

	const size_t uExtraMemorySizeToAllocate = uAlignment + uSizeOfPointer;

	const size_t uMemorySizeToAllocate = uExtraMemorySizeToAllocate + uSize;
	uint8_t* pbMemory = reinterpret_cast<uint8_t*>(::malloc(uMemorySizeToAllocate));

	uint8_t* pbMemoryWithPointerStorageOffset = pbMemory + uSizeOfPointer;

	size_t uMemoryWithPointerStorageAlignment = 
		reinterpret_cast<size_t>(pbMemoryWithPointerStorageOffset) % uAlignment;

	size_t uOffsetForAlignment = uAlignment - (uMemoryWithPointerStorageAlignment % uAlignment);

	uint8_t* pbAlignedMemory = pbMemoryWithPointerStorageOffset + uOffsetForAlignment;

	uint8_t* pbPointerStorageMemory = pbAlignedMemory - uSizeOfPointer;
	void** ppvPointerStorageMemory = reinterpret_cast<void**>(pbPointerStorageMemory);

	*ppvPointerStorageMemory = pbMemory;

	return pbAlignedMemory;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void 
AlignedFree(void* pv)
{
	if ( pv == nullptr )
		return;

	constexpr size_t uSizeOfPointer = sizeof(void*);

	uint8_t* pbAlignedMemory = reinterpret_cast<uint8_t*>(pv);

	uint8_t* pbPointerStorageMemory = pbAlignedMemory - uSizeOfPointer;
	void** ppvPointerStorageMemory = reinterpret_cast<void**>(pbPointerStorageMemory);

	::free(*ppvPointerStorageMemory);
}

