#ifndef RadixSort_h
#define RadixSort_h

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T>
std::vector<typename std::enable_if<std::is_integral<T>::value, T>::type>
RadixSort(const std::vector<T>& aValues)
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

	constexpr size_t kuNumberOfBits = sizeof(T) * 8;
	const size_t kuLog2NumberOfElements = static_cast<size_t>(std::log2(kuNumberOfElements));
	const size_t kuDigitBitSize = 
		(kuNumberOfElements < kuLog2NumberOfElements) ? 
			kuNumberOfBits :
			kuLog2NumberOfElements;
	const size_t kuNumberOfDigits = std::ceil(static_cast<double>(kuNumberOfBits) / kuDigitBitSize);

	std::vector<T> aValuesTempCopy;

	const size_t kuSizeOfRange = 1 << kuDigitBitSize;
	std::vector<size_t> aCountingVector(kuSizeOfRange);
	
	const size_t kuBitMask = kuSizeOfRange - 1;
	for (size_t uDigitIndex = 0; uDigitIndex < kuNumberOfDigits; uDigitIndex++)
	{
		aValuesTempCopy = aValuesCopy;

		aCountingVector.assign(kuSizeOfRange, 0);

		const size_t kuShiftAmount = uDigitIndex * kuDigitBitSize;

		for (const auto tElement : aValuesTempCopy)
			aCountingVector[((tElement - tMinimumElement) >> kuShiftAmount) & kuBitMask]++;
		
		for (size_t uIndex = 1; uIndex < kuSizeOfRange; uIndex++)
			aCountingVector[uIndex] += aCountingVector[uIndex - 1]; 

		for (auto itElement = aValuesTempCopy.crbegin(); itElement != aValuesTempCopy.crend(); itElement++)
			aValuesCopy[aCountingVector[((*itElement - tMinimumElement) >> kuShiftAmount) & kuBitMask]-- - 1] = *itElement;
	}

	return aValuesCopy;
}

#endif

