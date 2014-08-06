#ifndef BubbleSort_h
#define BubbleSort_h

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T>
std::vector<T>
BubbleSort(const std::vector<T>& aValues)
{
	const size_t kuNumberOfElements = aValues.size();

	// Copy not necessary for bubble sort, as it is in place.
	std::vector<T> aValuesCopy(aValues);

	bool bSwappedElementsInIteration;
	do
	{
		bSwappedElementsInIteration = false;

		for (size_t uIndexI = 1; uIndexI < kuNumberOfElements; uIndexI++)
		{
			if ( aValuesCopy[uIndexI] < aValuesCopy[uIndexI - 1] )
			{
				const T element = aValuesCopy[uIndexI];

				aValuesCopy[uIndexI] = aValuesCopy[uIndexI - 1];

				aValuesCopy[uIndexI - 1] = element;
		
				bSwappedElementsInIteration = true;
			}
		}
	}
	while ( bSwappedElementsInIteration );
	
	return aValuesCopy;
}

#endif
