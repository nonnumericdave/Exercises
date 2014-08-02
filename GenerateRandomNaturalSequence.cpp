#include "Standard.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::unique_ptr<size_t[]>
GenerateRandomNaturalSequence(size_t uStartOfRange, size_t uEndOfRange, std::function<double()> pfnRandomNumberGenerator)
{
	assert( uStartOfRange > 0 );
	assert( uStartOfRange <= uEndOfRange );

	std::unique_ptr<size_t[]> puRandomNaturalSequenceArray(new size_t[uEndOfRange - uStartOfRange]);

	for (size_t uIndex = uStartOfRange; uIndex <= uEndOfRange; uIndex++)
		puRandomNaturalSequenceArray[uIndex - uStartOfRange] = uIndex;
	
	const size_t kuNumberOfElements = uEndOfRange - uStartOfRange + 1;
	for (size_t uIndex = 0; uIndex < kuNumberOfElements; uIndex++)
	{
		const size_t kuNumberOfSelectableElements = kuNumberOfElements - uIndex;

		const double krRandomNumber = pfnRandomNumberGenerator();
		assert( krRandomNumber >= 0 && krRandomNumber < 1 );

		const size_t kuSelectedElementIndex = static_cast<size_t>(kuNumberOfSelectableElements*krRandomNumber) + uIndex;
		assert( kuSelectedElementIndex < kuNumberOfElements );
			
		size_t uCurrentElement = puRandomNaturalSequenceArray[uIndex];
		puRandomNaturalSequenceArray[uIndex] = puRandomNaturalSequenceArray[kuSelectedElementIndex];
		puRandomNaturalSequenceArray[kuSelectedElementIndex] = uCurrentElement;
	}

	return puRandomNaturalSequenceArray;
}
