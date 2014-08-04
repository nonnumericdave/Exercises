#ifndef InsertionSort_h
#define InsertionSort_h

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T>
std::vector<T>
InsertionSort(const std::vector<T>& aValues)
{
	const size_t kuNumberOfElements = aValues.size();

	// Copy not necessary for bubble sort, as it is in place.
	std::vector<T> aValuesCopy(aValues);

	for (size_t uIndexI = 1; uIndexI < kuNumberOfElements; uIndexI++)
	{
		const T element = aValuesCopy[uIndexI];

		size_t uIndexJ = uIndexI - 1;

		for (;;)
		{
			if ( element < aValuesCopy[uIndexJ] )
			{
				aValuesCopy[uIndexJ + 1] = aValuesCopy[uIndexJ];
			}
			else
			{
				uIndexJ++;
				break;
			}		

			if ( uIndexJ == 0 )
				break;

			uIndexJ--;
		}

		aValuesCopy[uIndexJ] = element;
	}
	
	return aValuesCopy;
}

#endif
