## AlignedMalloc

Introduce AlignedMalloc(...) and AlignedFree(...), which effectively act like malloc(...) and free(...), respectively, with one additional feature -- a developer
can specify a requested memory address alignment for AlignedMalloc(...), such that the returned pointer is allocated on that boundary.
