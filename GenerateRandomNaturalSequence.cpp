#include "Standard.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::unique_ptr<size_t[]>
GenerateRandomNaturalSequence(size_t uStartOfRange, size_t uEndOfRange)
{
	assert( uStartOfRange > 0 );
	assert( uStartOfRange <= uEndOfRange );

	std::unique_ptr<size_t[]> puRandomNaturalSequenceArray(new size_t[uEndOfRange - uStartOfRange]);

	for (size_t uIndex = uStartOfRange; uIndex <= uEndOfRange; uIndex++)
		puRandomNaturalSequenceArray[uIndex - uStartOfRange] = uIndex;

	return puRandomNaturalSequenceArray;
}
