#ifndef GenerateRandomNaturalSequence_h
#define GenerateRandomNaturalSequence_h

std::unique_ptr<size_t[]> GenerateRandomNaturalSequence(size_t uStartOfRange, size_t uEndOfRange, std::function<double()> pfnRandomNumberGenerator);

#endif
