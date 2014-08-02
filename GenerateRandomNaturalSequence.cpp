#include "Standard.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
GenerateRandomNaturalSequence(size_t uStartOfRange, size_t uEndOfRange)
{
	assert( uStartOfRange <= uEndOfRange );

	size_t* puRandomNaturalSequenceArray = new size_t[uEndOfRange - uStartOfRange];

	for (size_t uIndex = uStartOfRange; uIndex <= uEndOfRange; uIndex++)
		puRandomNaturalSequenceArray[uIndex - uStartOfRange] = uIndex;

	delete [] puRandomNaturalSequenceArray;
}
