#ifndef SortedBoundarySearch_h
#define SortedBoundarySearch_h

template<typename T>
bool
SortedBoundarySearch(const std::vector<T>& aValues, const T& t, size_t& uStartBoundaryIndex, size_t& uEndBoundaryIndex)
{	
	const size_t kuSize = aValues.size();
	if ( kuSize == 0 )
		return false;

	size_t uSearchStartIndex = 0;
	size_t uSearchEndIndex = kuSize - 1;

	while ( uSearchStartIndex <= uSearchEndIndex )
	{
		size_t uSearchMiddleIndex = (uSearchStartIndex + uSearchEndIndex) / 2;

		if ( aValues[uSearchMiddleIndex] < t )
		{
			uSearchStartIndex = uSearchMiddleIndex + 1;
		}
		else
		{
			if ( uSearchMiddleIndex == 0 )
			{
				uSearchEndIndex = 0;
				break;
			}		
			
			uSearchEndIndex = uSearchMiddleIndex - 1;
		}
	}

	uStartBoundaryIndex = uSearchStartIndex;

	uSearchStartIndex = 0;
	uSearchEndIndex = kuSize - 1;

	while ( uSearchStartIndex <= uSearchEndIndex )
	{
		size_t uSearchMiddleIndex = (uSearchStartIndex + uSearchEndIndex) / 2;

		if ( aValues[uSearchMiddleIndex] > t )
		{
			if ( uSearchMiddleIndex == 0 )
			{
				uSearchEndIndex = 0;
				break;
			}	
			
			uSearchEndIndex = uSearchMiddleIndex - 1;
		}
		else
		{
			uSearchStartIndex = uSearchMiddleIndex + 1;
		}
	}

	uEndBoundaryIndex = uSearchEndIndex;

	return uStartBoundaryIndex <= uEndBoundaryIndex;
}

#endif
