#ifndef MergeSort_h
#define MergeSort_h

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T>
std::vector<T>
MergeSort(const std::vector<T>& aValues)
{
	const size_t kuNumberOfElements = aValues.size();

	// Copy not necessary for bubble sort, as it is in place.
	std::vector<T> aValuesCopy(aValues);
	
	if ( kuNumberOfElements == 0 )
		return aValuesCopy;

	using PFN_MergeSortHelper = void(*)(std::vector<T>&, size_t, size_t);

	static PFN_MergeSortHelper pfnMergeSortHelper =
		[] (std::vector<T>& aValues, size_t uBeginIndex, size_t uEndIndex) -> void
		{
			if ( uBeginIndex == uEndIndex )
				return;

			const size_t kuMiddleIndex = (uBeginIndex + uEndIndex) / 2;
		
			size_t uFirstHalfIndex = uBeginIndex;
			size_t uSecondHalfIndex = kuMiddleIndex + 1;

			pfnMergeSortHelper(aValues, uFirstHalfIndex, kuMiddleIndex);			
			pfnMergeSortHelper(aValues, uSecondHalfIndex, uEndIndex);

			std::vector<T> aValuesMergeCopy;
			aValuesMergeCopy.reserve(uEndIndex - uBeginIndex + 1);
			
			for (;;)
			{
				if ( aValues[uFirstHalfIndex] < aValues[uSecondHalfIndex] )
				{
					aValuesMergeCopy.push_back(aValues[uFirstHalfIndex]);

					if ( ++uFirstHalfIndex > kuMiddleIndex )
					{
						while ( uSecondHalfIndex <= uEndIndex )
							aValuesMergeCopy.push_back(aValues[uSecondHalfIndex++]);
						
						break;
					}
				}
				else
				{
					aValuesMergeCopy.push_back(aValues[uSecondHalfIndex]);

					if ( ++uSecondHalfIndex > uEndIndex )
					{
						while ( uFirstHalfIndex <= kuMiddleIndex )
							aValuesMergeCopy.push_back(aValues[uFirstHalfIndex++]);
					
						break;
					}
				}
			}

			std::copy(aValuesMergeCopy.begin(), aValuesMergeCopy.end(), &aValues[uBeginIndex]);
		};

	pfnMergeSortHelper(aValuesCopy, 0, kuNumberOfElements - 1);

	return aValuesCopy;
}

#endif
