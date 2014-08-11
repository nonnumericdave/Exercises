#include "Standard.h"

#include "Heap.h"
#include "PriorityQueue.h"

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
TestSortedList()
{
	std::random_device randomDeviceGenerator;
	std::mt19937 mersenneTwisterGenerator(randomDeviceGenerator());
	std::uniform_int_distribution<int> uniformIntegerDistribution(1, 2500);

	constexpr size_t kuValueCount = 1000;
	std::vector<int> aValues(kuValueCount);
	
	for (size_t uIndex = 0; uIndex < kuValueCount; uIndex++)
		aValues.push_back(uniformIntegerDistribution(mersenneTwisterGenerator));
	
	Heap<int, int> heap;
	for (const int& iValue : aValues )
		heap.InsertElementWithKey(iValue, iValue);

	std::sort(aValues.begin(), aValues.end());

	for (auto itValue = aValues.crbegin(); itValue != aValues.crend(); itValue++)
	{
		std::shared_ptr<PriorityQueue<int, int>::Element> pElement = heap.ExtractMaximumElement();

		if ( pElement == nullptr )
			return false;

		if ( pElement->Value() != *itValue )
			return false;
	}

	std::shared_ptr<PriorityQueue<int, int>::Element> pElement = heap.ExtractMaximumElement();
	if ( pElement != nullptr )
		return false;

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static const UnitTest g_aUnitTest[] =
{
	DefineUnitTest(TestSortedList),
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
