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
	for (const int& iValue : aValues)
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
bool 
TestIncreaseElementKey()
{
	std::random_device randomDeviceGenerator;
	std::mt19937 mersenneTwisterGenerator(randomDeviceGenerator());
	std::uniform_int_distribution<int> uniformIntegerDistribution(1, 2500);

	Heap<int, int> heap;

	for (size_t uIndex = 0; uIndex < 4000; uIndex++)
	{
		const int iValue = uniformIntegerDistribution(mersenneTwisterGenerator);
		heap.InsertElementWithKey(iValue, iValue);
	}

	std::shared_ptr<PriorityQueue<int, int>::Element> pInsertedElement =
		heap.InsertElementWithKey(1, 1);

	heap.IncreaseElementKey(pInsertedElement.get(), 2501);

	for (size_t uIndex = 0; uIndex < 4500; uIndex++)
	{
		const int iValue = uniformIntegerDistribution(mersenneTwisterGenerator);
		heap.InsertElementWithKey(iValue, iValue);
	}

	std::shared_ptr<PriorityQueue<int, int>::Element> pMaximumElement = 
		heap.ExtractMaximumElement();
	
	if ( pInsertedElement != pMaximumElement )
		return false;

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool 
TestMerge()
{
	std::random_device randomDeviceGenerator;
	std::mt19937 mersenneTwisterGenerator(randomDeviceGenerator());
	std::uniform_int_distribution<int> uniformIntegerDistribution(1, 2500);

	constexpr size_t kuValueCount = 1000;

	std::vector<int> aXValues(kuValueCount);
	
	for (size_t uIndex = 0; uIndex < kuValueCount; uIndex++)
		aXValues.push_back(uniformIntegerDistribution(mersenneTwisterGenerator));
	
	Heap<int, int> heapX;
	for (const int& iValue : aXValues)
		heapX.InsertElementWithKey(iValue, iValue);

	std::sort(aXValues.begin(), aXValues.end());

	std::vector<int> aYValues(kuValueCount);
	
	for (size_t uIndex = 0; uIndex < kuValueCount; uIndex++)
		aYValues.push_back(uniformIntegerDistribution(mersenneTwisterGenerator));
	
	Heap<int, int> heapY;
	for (const int& iValue : aYValues)
		heapY.InsertElementWithKey(iValue, iValue);

	std::sort(aYValues.begin(), aYValues.end());

	std::vector<int> aValues;
	std::merge(aXValues.begin(), aXValues.end(), aYValues.begin(), aYValues.end(), std::back_inserter(aValues));

	heapX.MergePriorityQueue(&heapY);

	std::shared_ptr<PriorityQueue<int, int>::Element> pElement = heapY.ExtractMaximumElement();
	if ( pElement != nullptr )
		return false;

	for (auto itValue = aValues.crbegin(); itValue != aValues.crend(); itValue++)
	{
		std::shared_ptr<PriorityQueue<int, int>::Element> pElement = heapX.ExtractMaximumElement();

		if ( pElement == nullptr )
			return false;

		if ( pElement->Value() != *itValue )
			return false;
	}

	pElement = heapX.ExtractMaximumElement();
	if ( pElement != nullptr )
		return false;

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static const UnitTest g_aUnitTest[] =
{
	DefineUnitTest(TestSortedList),
	DefineUnitTest(TestIncreaseElementKey),
	DefineUnitTest(TestMerge),
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
