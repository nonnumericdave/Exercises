#ifndef HeapSort_h
#define HeapSort_h

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T>
std::vector<T>
HeapSort(const std::vector<T>& aValues)
{
	// Copy not necessary for heapsort, as it is in place.
	const size_t kuNumberOfElements = aValues.size();
	std::vector<T> aValuesCopy(aValues);

	auto lamdaHeapify = [&aValuesCopy] (const size_t kuIndex, const size_t kuNumberOfElements) -> void
	{
		assert( kuNumberOfElements <= aValuesCopy.size() );

		for (size_t uIndex = kuIndex; ; )
		{
			size_t uLargestIndex = uIndex;

			const size_t kuLeftChildIndex = (uIndex * 2) + 1;
			if ( kuLeftChildIndex < kuNumberOfElements && 
			     aValuesCopy[uLargestIndex] < aValuesCopy[kuLeftChildIndex] )
				uLargestIndex = kuLeftChildIndex;

			const size_t kuRightChildIndex = kuLeftChildIndex + 1;
			if ( kuRightChildIndex < kuNumberOfElements && 
			     aValuesCopy[uLargestIndex] < aValuesCopy[kuRightChildIndex] )
				uLargestIndex = kuRightChildIndex;

			if ( uLargestIndex == uIndex )
				break;

			T t = aValuesCopy[uIndex];
			aValuesCopy[uIndex] = aValuesCopy[uLargestIndex];
			aValuesCopy[uLargestIndex] = t;

			uIndex = uLargestIndex;
		}
	};

	for (size_t uIndex = kuNumberOfElements / 2; ; uIndex--)
	{
		lamdaHeapify(uIndex, kuNumberOfElements);

		if ( uIndex == 0 )
			break;
	}

	for (size_t uIndex = 0; uIndex < kuNumberOfElements; uIndex++)
	{
		const size_t kuLastIndex = kuNumberOfElements - uIndex - 1;
		
		T t = aValuesCopy[0];
		aValuesCopy[0] = aValuesCopy[kuLastIndex];
		aValuesCopy[kuLastIndex] = t;

		const size_t kuNewNumberOfElements = kuLastIndex;
		lamdaHeapify(0, kuNewNumberOfElements);
	}

	return aValuesCopy;
}

#endif
