#include "Standard.h"

#include "GenerateRandomNaturalSequence.h"

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
CheckForEveryNumberInRange(const size_t kuStartOfRange, const size_t kuEndOfRange, const std::unique_ptr<size_t[]>& kpuSequenceArray)
{
	const size_t kuNumberOfElements = kuEndOfRange - kuStartOfRange + 1;
	for (size_t uElement = kuStartOfRange; uElement <= kuEndOfRange; uElement++)
	{
		bool bElementNotFound = true;
		for (size_t uIndex = 0; uIndex < kuNumberOfElements; uIndex++)
		{
			if ( kpuSequenceArray[uIndex] == uElement )
			{
				bElementNotFound = false;
				break;
			}
		}

		if ( bElementNotFound )
			return false;
	}

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
TestBasic()
{
	const size_t kuStartOfRange = 7;
	const size_t kuEndOfRange = 101;

	auto pfnDummyRandomNumberGenerator = [] () -> double
	{
			return 0.5;
	};

	std::unique_ptr<size_t[]> puRandomNaturalSequenceArray =
		::GenerateRandomNaturalSequence(kuStartOfRange, kuEndOfRange, pfnDummyRandomNumberGenerator);

	if ( ! ::CheckForEveryNumberInRange(kuStartOfRange, kuEndOfRange, puRandomNaturalSequenceArray) )
		return false;

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
TestUniformRealDistribution()
{
	const size_t kuStartOfRange = 7;
	const size_t kuEndOfRange = 101;

	std::random_device randomDeviceGenerator;
	std::mt19937 mersenneTwisterGenerator(randomDeviceGenerator());
	std::uniform_real_distribution<double> uniformRealDistribution(0.0, 1.0);

	auto pfnRandomNumberGenerator = [&mersenneTwisterGenerator, &uniformRealDistribution] () -> double
	{	
		return uniformRealDistribution(mersenneTwisterGenerator);
	};

	std::unique_ptr<size_t[]> puRandomNaturalSequenceArray =
		::GenerateRandomNaturalSequence(kuStartOfRange, kuEndOfRange, pfnRandomNumberGenerator);

	if ( ! ::CheckForEveryNumberInRange(kuStartOfRange, kuEndOfRange, puRandomNaturalSequenceArray) )
		return false;

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static const UnitTest g_aUnitTest[] =
{
	DefineUnitTest(TestBasic),
	DefineUnitTest(TestUniformRealDistribution),
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
