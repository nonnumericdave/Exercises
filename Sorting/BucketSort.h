#ifndef BucketSort_h
#define BucketSort_h

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T>
std::vector<typename std::enable_if<std::is_integral<T>::value, T>::type>
BucketSort(const std::vector<T>& aValues)
{
	const size_t kuNumberOfElements = aValues.size();

	// Copy not necessary for bucket sort, as it is in place.
	std::vector<T> aValuesCopy;
	aValuesCopy.reserve(kuNumberOfElements);

	if ( kuNumberOfElements == 0 )
		return aValuesCopy;

	struct ListElement
	{
		T t;
		ListElement* pNextElement;
	};

	std::vector<ListElement*> aBuckets(kuNumberOfElements);

	for (auto& pListElement : aBuckets )
		pListElement = nullptr;

	T tMaximumValue = aValues[0];
	T tMinimumValue = aValues[0];
	for (const auto& t : aValues)
	{
		if ( t > tMaximumValue )
		{
			tMaximumValue = t;
		}
		else if ( t < tMinimumValue )
		{
			tMinimumValue = t;
		}
	}

	double dBucketIncrement = 
		(tMaximumValue - tMinimumValue + 1) / static_cast<double>(kuNumberOfElements);

	for (const auto& t : aValues)
	{
		const size_t kuIndex = static_cast<size_t>((t - tMinimumValue) / dBucketIncrement);
		assert( kuIndex < kuNumberOfElements );
	
		aBuckets[kuIndex] = new ListElement{t, aBuckets[kuIndex]};
	}

	for (auto pListElement : aBuckets)
	{
		while ( pListElement != nullptr )
		{
			aValuesCopy.push_back(pListElement->t);

			ListElement* pTempListElement = pListElement;
			pListElement = pListElement->pNextElement;
			delete pTempListElement;
		}
	}

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
