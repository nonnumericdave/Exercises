#ifndef GenerateSequencePermutation_h
#define GenerateSequencePermutation_h

std::unique_ptr<size_t[]> GenerateSequencePermutation(size_t uStartOfRange, size_t uEndOfRange, std::function<double()> pfnRandomNumberGenerator);

#endif
