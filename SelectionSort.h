#ifndef SelectionSort_h
#define SelectionSort_h

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T>
std::vector<T>
SelectionSort(const std::vector<T>& aValues)
{
	const size_t kuNumberOfElements = aValues.size();

	// Copy not necessary for insertion sort, as it is in place.
	std::vector<T> aValuesCopy(aValues);

	for (size_t uIndexI = 0; uIndexI < kuNumberOfElements; uIndexI++)
	{
		size_t uLeastElementIndex = uIndexI;

		for (size_t uIndexJ = uIndexI + 1; uIndexJ < kuNumberOfElements; uIndexJ++)
		{
			if ( aValuesCopy[uIndexJ] < aValuesCopy[uLeastElementIndex] )
				uLeastElementIndex = uIndexJ;
		}

		T leastElement = aValuesCopy[uLeastElementIndex];
		aValuesCopy[uLeastElementIndex] = aValuesCopy[uIndexI];
		aValuesCopy[uIndexI] = leastElement;
	}
	
	return aValuesCopy;
}

#endif
