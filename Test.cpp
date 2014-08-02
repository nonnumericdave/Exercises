#include <stddef.h>
#include <stdio.h>
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
static const UnitTest g_aUnitTest[] =
{
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool TestDummy()
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
			::printf(" passed\n");
		else
			::printf(" failed\n");

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
