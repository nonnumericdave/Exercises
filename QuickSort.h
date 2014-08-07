#ifndef QuickSort_h
#define QuickSort_h

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T>
std::vector<T>
QuickSort(const std::vector<T>& aValues)
{
	const size_t kuNumberOfElements = aValues.size();

	// Copy not necessary for quick sort, as it is in place.
	std::vector<T> aValuesCopy(aValues);
	
	if ( kuNumberOfElements == 0 )
		return aValuesCopy;

	using PFN_QuickSortHelper = void(*)(std::vector<T>&, size_t, size_t);

	static PFN_QuickSortHelper pfnQuickSortHelper =
		[] (std::vector<T>& aValues, size_t uBeginIndex, size_t uEndIndex) -> void
		{
			if ( uBeginIndex == uEndIndex )
				return;

			size_t uPartitionBeginIndex = uBeginIndex;
			size_t uPartitionEndIndex = uEndIndex - 1;

			T partitionElement = aValues[uEndIndex];

			while ( uPartitionBeginIndex != uPartitionEndIndex )
			{
				if ( aValues[uPartitionBeginIndex] < partitionElement )
				{
					uPartitionBeginIndex++;
				}
				else
				{
					T tempElement = aValues[uPartitionEndIndex];
					aValues[uPartitionEndIndex] = aValues[uPartitionBeginIndex];
					aValues[uPartitionBeginIndex] = tempElement;

					uPartitionEndIndex--;
				}

			}

			if ( aValues[uPartitionBeginIndex] < partitionElement )
			{
				uPartitionBeginIndex++;
				uPartitionEndIndex++;

				aValues[uEndIndex] = aValues[uPartitionBeginIndex];
				aValues[uPartitionBeginIndex] = partitionElement;
			}
			else
			{
				aValues[uEndIndex] = aValues[uPartitionBeginIndex];
				aValues[uPartitionBeginIndex] = partitionElement;
			}

			if ( uPartitionBeginIndex > uBeginIndex )
				pfnQuickSortHelper(aValues, uBeginIndex, uPartitionBeginIndex - 1);
		
			if ( uPartitionEndIndex < uEndIndex )
				pfnQuickSortHelper(aValues, uPartitionEndIndex + 1, uEndIndex);
		};

	pfnQuickSortHelper(aValuesCopy, 0, kuNumberOfElements - 1);

	return aValuesCopy;
}

#endif
