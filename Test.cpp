#include "Standard.h"

#include "InsertionSort.h"

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

	std::vector<int> aVectorOfSortedIntegers(::InsertionSort<int>(aVectorOfUnsortedIntegers));
	
	return ::IsVectorSorted(aVectorOfSortedIntegers);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
TestBasicSorting()
{
	std::vector<int> aVectorOfUnsortedIntegers(::GenerateVectorOfUnsortedIntegersWithinRange(0, 1000, 250));

	std::vector<int> aVectorOfSortedIntegers(::InsertionSort<int>(aVectorOfUnsortedIntegers));
	
	return ::IsVectorSorted(aVectorOfSortedIntegers);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
TestEmptyArraySorting()
{
	std::vector<int> aVectorOfUnsortedIntegers(0);

	std::vector<int> aVectorOfSortedIntegers(::InsertionSort<int>(aVectorOfUnsortedIntegers));
	
	return aVectorOfSortedIntegers.size() == 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
TestSortedArraySorting()
{
	std::vector<int> aVectorOfIntegers(::GenerateVectorOfUnsortedIntegersWithinRange(0, 1000, 250));
	std::sort(aVectorOfIntegers.begin(), aVectorOfIntegers.end());

	std::vector<int> aVectorOfSortedIntegers(::InsertionSort<int>(aVectorOfIntegers));
	
	return ::IsVectorSorted(aVectorOfSortedIntegers);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
TestSortedArrayContainsSameElements()
{
	std::vector<int> aVectorOfUnsortedIntegers(::GenerateVectorOfUnsortedIntegersWithinRange(0, 1000, 250));

	std::vector<int> aVectorOfSortedIntegers(::InsertionSort<int>(aVectorOfUnsortedIntegers));
	
	assert( aVectorOfUnsortedIntegers.size() == aVectorOfSortedIntegers.size() );
	
	const int g_kiSentinel = 2000;

	for (int& iUnsortedValue : aVectorOfUnsortedIntegers )
	{
		size_t uBeginSearchIndex = 0;
		size_t uEndSearchIndex = aVectorOfSortedIntegers.size() - 1;

		while ( uBeginSearchIndex <= uEndSearchIndex )
		{
			const size_t uMiddleIndex = (uBeginSearchIndex + uEndSearchIndex) / 2;
			const int kiSortedValue	= aVectorOfSortedIntegers[uMiddleIndex];		

			if ( kiSortedValue == iUnsortedValue )
			{
				iUnsortedValue = g_kiSentinel;		
				break;
			}

			if ( kiSortedValue < iUnsortedValue )
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

	for (const int kiUnsortedValue : aVectorOfUnsortedIntegers )
	{
		if ( kiUnsortedValue != g_kiSentinel )
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
