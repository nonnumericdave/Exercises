#include "Standard.h"

#include "FastExponentiation.h"

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
TestInteger()
{
	const int kiBase = 7;
	const size_t kuExponent = 5;

	int iExponentiationControl = 1;
	for (size_t uIndex = 0; uIndex < kuExponent; uIndex++)
		iExponentiationControl *= kiBase;

	int iExponentiation = ::FastExponentiation(kiBase, kuExponent);

	return iExponentiationControl == iExponentiation;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
TestReal()
{
	const double krEpsilon = 0.25;

	const double krBase = 7.5;
	const size_t kuExponent = 5;

	double rExponentiationControl = 1;
	for (size_t uIndex = 0; uIndex < kuExponent; uIndex++)
		rExponentiationControl *= krBase;

	double rExponentiation = ::FastExponentiation(krBase, kuExponent);

	return ::fabs(rExponentiationControl - rExponentiation) < krEpsilon;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static const UnitTest g_aUnitTest[] =
{
	DefineUnitTest(TestInteger),
	DefineUnitTest(TestReal),
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
