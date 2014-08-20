#ifndef CountingSort_h
#define CountingSort_h

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T>
std::vector<typename std::enable_if<std::is_integral<T>::value, T>::type>
CountingSort(const std::vector<T>& aValues)
{
	const size_t kuNumberOfElements = aValues.size();
	std::vector<T> aValuesCopy(aValues);

	if ( kuNumberOfElements == 0 )
		return aValuesCopy; 

	T tMinimumElement = aValues[0];
	T tMaximumElement = aValues[0];
	for (size_t uIndex = 0; uIndex < kuNumberOfElements; uIndex++)
	{
		const T ktElement = aValues[uIndex];
		
		if ( ktElement > tMaximumElement )
			tMaximumElement = ktElement;

		if ( ktElement < tMinimumElement )
			tMinimumElement = ktElement;
	}

	const size_t kuSizeOfRange = tMaximumElement - tMinimumElement + 1;
	std::vector<size_t> aCountingVector(kuSizeOfRange, 0);
	
	for (const auto tElement : aValues)
		aCountingVector[tElement - tMinimumElement]++;
	
	for (size_t uIndex = 1; uIndex < kuSizeOfRange; uIndex++)
		aCountingVector[uIndex] += aCountingVector[uIndex - 1]; 

	for (const auto tElement : aValues)
		aValuesCopy[aCountingVector[tElement - tMinimumElement]-- - 1] = tElement;

	return aValuesCopy;
}

#endif

