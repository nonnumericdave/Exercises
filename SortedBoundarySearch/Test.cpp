#include "Standard.h"

#include "SortedBoundarySearch.h"

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
bool 
TestBasicBoundarySearch()
{
	std::vector<int> aValues({2, 4, 4, 5, 6, 7, 7, 7, 9, 9, 9, 11, 11});

	size_t uStartBoundary = 0;
	size_t uEndBoundary = 0;

	if ( ! ::SortedBoundarySearch(aValues, 7, uStartBoundary, uEndBoundary) )
		return false;

	return uStartBoundary == 5 && uEndBoundary == 7;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool 
TestBoundarySearchForSingleElement()
{
	std::vector<int> aValues({2, 4, 4, 5, 6, 7, 9, 9, 9, 11, 11});

	size_t uStartBoundary = 0;
	size_t uEndBoundary = 0;

	if ( ! ::SortedBoundarySearch(aValues, 7, uStartBoundary, uEndBoundary) )
		return false;

	return uStartBoundary == 5 && uEndBoundary == 5;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool 
TestBoundarySearchForElementNotPresent()
{
	std::vector<int> aValues({2, 4, 4, 5, 6, 9, 9, 9, 11, 11});

	size_t uStartBoundary = 0;
	size_t uEndBoundary = 0;

	return ! ::SortedBoundarySearch(aValues, 7, uStartBoundary, uEndBoundary); 
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool 
TestBoundarySearchForOnlyElementPresent()
{
	std::vector<int> aValues({8, 8, 8, 8, 8});

	size_t uStartBoundary = 0;
	size_t uEndBoundary = 0;

	if ( ! ::SortedBoundarySearch(aValues, 8, uStartBoundary, uEndBoundary) )
		return false;

	return uStartBoundary == 0 && uEndBoundary == 4; 
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool 
TestBoundarySearchForNoElementsPresent()
{
	std::vector<int> aValues({});

	size_t uStartBoundary = 0;
	size_t uEndBoundary = 0;

	return ! ::SortedBoundarySearch(aValues, 9, uStartBoundary, uEndBoundary); 
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool 
TestBoundarySearchForSingleElementPresent()
{
	std::vector<int> aValues({8});

	size_t uStartBoundary = 0;
	size_t uEndBoundary = 0;

	if ( ! ::SortedBoundarySearch(aValues, 8, uStartBoundary, uEndBoundary) )
		return false;

	return uStartBoundary == 0 && uEndBoundary == 0; 
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool 
TestBoundarySearchOnLeftEdge()
{
	std::vector<int> aValues({2, 2, 2, 3, 6, 7, 7});

	size_t uStartBoundary = 0;
	size_t uEndBoundary = 0;

	if ( ! ::SortedBoundarySearch(aValues, 2, uStartBoundary, uEndBoundary) )
		return false;

	return uStartBoundary == 0 && uEndBoundary == 2; 
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool 
TestBoundarySearchOnRightEdge()
{
	std::vector<int> aValues({2, 2, 2, 3, 6, 7, 7});

	size_t uStartBoundary = 0;
	size_t uEndBoundary = 0;

	if ( ! ::SortedBoundarySearch(aValues, 7, uStartBoundary, uEndBoundary) )
		return false;

	return uStartBoundary == 5 && uEndBoundary == 6; 
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static const UnitTest g_aUnitTest[] =
{
	DefineUnitTest(TestBasicBoundarySearch),
	DefineUnitTest(TestBoundarySearchForSingleElement),
	DefineUnitTest(TestBoundarySearchForElementNotPresent),
	DefineUnitTest(TestBoundarySearchForOnlyElementPresent),
	DefineUnitTest(TestBoundarySearchForNoElementsPresent),
	DefineUnitTest(TestBoundarySearchForSingleElementPresent),
	DefineUnitTest(TestBoundarySearchOnLeftEdge),
	DefineUnitTest(TestBoundarySearchOnRightEdge),
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
