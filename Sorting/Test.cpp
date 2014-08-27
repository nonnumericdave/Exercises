#include "Standard.h"

#include "BubbleSort.h"
#include "BucketSort.h"
#include "CountingSort.h"
#include "HeapSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "RadixSort.h"
#include "SelectionSort.h"
#include "QuickSort.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define DefineUnitTest(pfnTest) { pfnTest, #pfnTest }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef bool(*PFN_Test)();

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct UnitTest
{
	PFN_Test pfnTest;
	const char* szTest;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef std::vector<int> (*PFN_Sort)(const std::vector<int>&); 

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const PFN_Sort g_kapfnSort[] =
{
	&BubbleSort<int>,
	&BucketSort<int>,
	&CountingSort<int>,
	&HeapSort<int>,
	&InsertionSort<int>,
	&MergeSort<int>,
	&RadixSort<int>,
	&SelectionSort<int>,
	&QuickSort<int>,
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::vector<int>
GenerateVectorOfUnsortedIntegersWithinRange(const int kiStartOfRange, const int kiEndOfRange, const size_t kuSizeOfVector) 
{
        std::random_device randomDeviceGenerator;
        std::mt19937 mersenneTwisterGenerator(randomDeviceGenerator());
        std::uniform_int_distribution<int> uniformIntDistribution(kiStartOfRange, kiEndOfRange);

	std::vector<int> aVectorOfIntegers(kuSizeOfVector);
	for (size_t uIndex = 0; uIndex < kuSizeOfVector; uIndex++)
		aVectorOfIntegers[uIndex] = uniformIntDistribution(mersenneTwisterGenerator);

	return aVectorOfIntegers;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
IsVectorSorted(const std::vector<int>& aVectorOfIntegers)
{
	for (size_t uIndex = 1; uIndex < aVectorOfIntegers.size(); uIndex++)
	{
		if ( aVectorOfIntegers[uIndex - 1] > aVectorOfIntegers[uIndex] )
			return false;
	}	

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
TestReallyBasicSorting()
{
	std::vector<int> aVectorOfUnsortedIntegers({4, 10, 7, 1, 2, 5, 3, 9, 8, 4, 6, 7});

	for (PFN_Sort pfnSort : g_kapfnSort )
	{
		std::vector<int> aVectorOfSortedIntegers(pfnSort(aVectorOfUnsortedIntegers));
	
		if ( ! ::IsVectorSorted(aVectorOfSortedIntegers) )
			return false;
	}

	return true;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
TestBasicSorting()
{
	std::vector<int> aVectorOfUnsortedIntegers(::GenerateVectorOfUnsortedIntegersWithinRange(-1000, 1000, 250));

        for (PFN_Sort pfnSort : g_kapfnSort )
        {
                std::vector<int> aVectorOfSortedIntegers(pfnSort(aVectorOfUnsortedIntegers));

                if ( ! ::IsVectorSorted(aVectorOfSortedIntegers) )
                        return false;
        }

        return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
TestEmptyArraySorting()
{
	std::vector<int> aVectorOfUnsortedIntegers(0);

	for (PFN_Sort pfnSort : g_kapfnSort )
	{
		std::vector<int> aVectorOfSortedIntegers(pfnSort(aVectorOfUnsortedIntegers));
		
		if ( aVectorOfSortedIntegers.size() != 0 )
			return false;
	}

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
TestSortedArraySorting()
{
	std::vector<int> aVectorOfIntegers(::GenerateVectorOfUnsortedIntegersWithinRange(-1000, 1000, 250));
	std::sort(aVectorOfIntegers.begin(), aVectorOfIntegers.end());

	for (PFN_Sort pfnSort : g_kapfnSort )
	{
		std::vector<int> aVectorOfSortedIntegers(pfnSort(aVectorOfIntegers));
	
		if ( ! ::IsVectorSorted(aVectorOfSortedIntegers) )
			return false;
	}

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
TestSortedArrayContainsSameElements()
{
	std::vector<int> aVectorOfUnsortedIntegers(::GenerateVectorOfUnsortedIntegersWithinRange(-1000, 1000, 250));

	const size_t kuVectorSize = aVectorOfUnsortedIntegers.size();
	std::bitset<250> aBitsetOfMatchedIntegers;

	for (PFN_Sort pfnSort : g_kapfnSort )
	{
		aBitsetOfMatchedIntegers.reset();

		std::vector<int> aVectorOfSortedIntegers(pfnSort(aVectorOfUnsortedIntegers));
	
		assert( kuVectorSize == aVectorOfSortedIntegers.size() );
	
		const int g_kiSentinel = 2000;

		for (size_t uIndex = 0; uIndex < kuVectorSize; uIndex++)
		{
			int iUnsortedValue = aVectorOfUnsortedIntegers[uIndex];	
	
			size_t uBeginSearchIndex = 0;
			size_t uEndSearchIndex = aVectorOfSortedIntegers.size() - 1;

			while ( uBeginSearchIndex <= uEndSearchIndex )
			{
				const size_t uMiddleIndex = (uBeginSearchIndex + uEndSearchIndex) / 2;

				size_t uCurrentIndex = uMiddleIndex;
				bool bFoundMatch = false;
				while ( aVectorOfSortedIntegers[uCurrentIndex] == iUnsortedValue )
				{
					if ( ! aBitsetOfMatchedIntegers[uCurrentIndex] )
					{
						aBitsetOfMatchedIntegers[uCurrentIndex] = true;
						bFoundMatch = true;
						break;
					}
							
					if ( uCurrentIndex == 0 )
						break;

					uCurrentIndex--;
				}

				if ( ! bFoundMatch )
				{
					uCurrentIndex = uMiddleIndex;

					while ( aVectorOfSortedIntegers[uCurrentIndex] == iUnsortedValue )
					{
						if ( ! aBitsetOfMatchedIntegers[uCurrentIndex] )
						{
							aBitsetOfMatchedIntegers[uCurrentIndex] = true;
							bFoundMatch = true;
							break;
						}
							
						uCurrentIndex++;

						if ( uCurrentIndex == kuVectorSize )
							break;
					}

				}
				
				if ( bFoundMatch )
					break;
				
				if ( aVectorOfSortedIntegers[uMiddleIndex] < iUnsortedValue )
				{
					uBeginSearchIndex = uMiddleIndex + 1;
				}
				else
				{
					if ( uMiddleIndex == 0 )
						break;

					uEndSearchIndex = uMiddleIndex - 1;
				}
			}
		}

		if ( ! aBitsetOfMatchedIntegers.all() )
			return false;
	}

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static const UnitTest g_aUnitTest[] =
{
	DefineUnitTest(TestReallyBasicSorting),	
	DefineUnitTest(TestBasicSorting),	
	DefineUnitTest(TestEmptyArraySorting),	
	DefineUnitTest(TestSortedArraySorting),	
	DefineUnitTest(TestSortedArrayContainsSameElements),	
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool 
TestDummy()
{
	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
Test()
{
	::printf("\nRunning Unit Tests...\n");

	bool bAllTestsHavePassed = TestDummy();
	for (UnitTest unitTest : g_aUnitTest)
	{
		::printf(" %s ... ", unitTest.szTest);

		bool bTestPassed = unitTest.pfnTest();

		if ( bTestPassed )
			::printf("passed\n");
		else
			::printf("failed\n");

		bAllTestsHavePassed = bAllTestsHavePassed && bTestPassed;
	}

	if ( bAllTestsHavePassed )
		::printf("Passed\n\n");
	else
		::printf("Failed\n\n");

	return bAllTestsHavePassed;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int
main()
{
	return Test() ? 0 : 255;
}
