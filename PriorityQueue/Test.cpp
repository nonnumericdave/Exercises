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
template<typename T, typename K>
using PFN_PriorityQueueFactory = std::unique_ptr<PriorityQueue<T,K>>(*)();

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PFN_PriorityQueueFactory<int, int> g_apfnPriorityQueueFactory[] =
{
	[] () -> std::unique_ptr<PriorityQueue<int, int>> 
	{ 
		return std::unique_ptr<PriorityQueue<int, int>>(new Heap<int, int>); 
	},
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
	
	for (PFN_PriorityQueueFactory<int, int> pfnPriorityQueueFactory : g_apfnPriorityQueueFactory)
	{
		std::vector<int> aTempValues(aValues);

		std::unique_ptr<PriorityQueue<int, int>> pPriorityQueue(pfnPriorityQueueFactory());
		for (const int& iValue : aTempValues)
			pPriorityQueue->InsertElementWithKey(iValue, iValue);

		std::sort(aTempValues.begin(), aTempValues.end());

		for (auto itValue = aTempValues.crbegin(); itValue != aTempValues.crend(); itValue++)
		{
			std::shared_ptr<PriorityQueue<int, int>::Element> pElement = pPriorityQueue->ExtractMaximumElement();

			if ( pElement == nullptr )
				return false;

			if ( pElement->Value() != *itValue )
				return false;
		}

		std::shared_ptr<PriorityQueue<int, int>::Element> pElement = pPriorityQueue->ExtractMaximumElement();
		if ( pElement != nullptr )
			return false;
	}

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool 
TestIncreaseElementKey()
{
	std::random_device randomDeviceGenerator;
	std::mt19937 mersenneTwisterGenerator(randomDeviceGenerator());
	std::uniform_int_distribution<int> uniformIntegerDistribution(1, 2500);
	
	constexpr size_t kuXValueCount = 4000;
	std::vector<int> aXValues(kuXValueCount);
	for (size_t uIndex = 0; uIndex < kuXValueCount; uIndex++)
		aXValues.push_back(uniformIntegerDistribution(mersenneTwisterGenerator));
	
	constexpr size_t kuYValueCount = 4500;
	std::vector<int> aYValues(kuYValueCount);
	for (size_t uIndex = 0; uIndex < kuYValueCount; uIndex++)
		aYValues.push_back(uniformIntegerDistribution(mersenneTwisterGenerator));

	for (PFN_PriorityQueueFactory<int, int> pfnPriorityQueueFactory : g_apfnPriorityQueueFactory)
	{
		std::unique_ptr<PriorityQueue<int, int>> pPriorityQueue(pfnPriorityQueueFactory());

		for (int iValue : aXValues)
			pPriorityQueue->InsertElementWithKey(iValue, iValue);

		std::shared_ptr<PriorityQueue<int, int>::Element> pInsertedElement =
			pPriorityQueue->InsertElementWithKey(1, 1);

		pPriorityQueue->IncreaseElementKey(pInsertedElement.get(), 2501);

		for (int iValue : aYValues)
			pPriorityQueue->InsertElementWithKey(iValue, iValue);

		std::shared_ptr<PriorityQueue<int, int>::Element> pMaximumElement = 
			pPriorityQueue->ExtractMaximumElement();
		
		if ( pInsertedElement != pMaximumElement )
			return false;
	}

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
	
	std::vector<int> aYValues(kuValueCount);
	for (size_t uIndex = 0; uIndex < kuValueCount; uIndex++)
		aYValues.push_back(uniformIntegerDistribution(mersenneTwisterGenerator));
	
	for (PFN_PriorityQueueFactory<int, int> pfnPriorityQueueFactory : g_apfnPriorityQueueFactory)
	{
		std::unique_ptr<PriorityQueue<int, int>> pXPriorityQueue(pfnPriorityQueueFactory());
		for (int iValue : aXValues)
			pXPriorityQueue->InsertElementWithKey(iValue, iValue);

		std::unique_ptr<PriorityQueue<int, int>> pYPriorityQueue(pfnPriorityQueueFactory());
		for (int iValue : aYValues)
			pYPriorityQueue->InsertElementWithKey(iValue, iValue);

		std::vector<int> aValues(aXValues);
		aValues.reserve(aXValues.size() + aYValues.size());
		aValues.insert(aValues.end(), aYValues.begin(), aYValues.end());

		std::sort(aValues.begin(), aValues.end());

		pXPriorityQueue->MergePriorityQueue(pYPriorityQueue.get());

		std::shared_ptr<PriorityQueue<int, int>::Element> pElement = pYPriorityQueue->ExtractMaximumElement();
		if ( pElement != nullptr )
			return false;

		for (auto itValue = aValues.crbegin(); itValue != aValues.crend(); itValue++)
		{
			std::shared_ptr<PriorityQueue<int, int>::Element> pElement = pXPriorityQueue->ExtractMaximumElement();

			if ( pElement == nullptr )
				return false;

			if ( pElement->Value() != *itValue )
				return false;
		}

		pElement = pXPriorityQueue->ExtractMaximumElement();
		if ( pElement != nullptr )
			return false;
	}

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
