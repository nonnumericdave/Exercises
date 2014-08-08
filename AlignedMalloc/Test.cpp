#include "Standard.h"

#include "AlignedMalloc.h"

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
TestBasicAlignedMalloc()
{
	constexpr size_t kuSize = 256;
	constexpr size_t kuAlignment = 7;

	void* pv = ::AlignedMalloc(kuSize, kuAlignment);
	if ( (reinterpret_cast<size_t>(pv) % kuAlignment) != 0 )
		return false;

	::AlignedFree(pv);

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool 
TestSmallAlignedMalloc()
{
	constexpr size_t kuSize = 127;
	constexpr size_t kuAlignment = 2;

	void* pv = ::AlignedMalloc(kuSize, kuAlignment);
	if ( (reinterpret_cast<size_t>(pv) % kuAlignment) != 0 )
		return false;

	::AlignedFree(pv);

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool 
TestSmallerAlignedMalloc()
{
	constexpr size_t kuSize = 1227;
	constexpr size_t kuAlignment = 1;

	void* pv = ::AlignedMalloc(kuSize, kuAlignment);
	if ( (reinterpret_cast<size_t>(pv) % kuAlignment) != 0 )
		return false;

	::AlignedFree(pv);

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool 
TestZeroAlignment()
{
	constexpr size_t kuSize = 1227;
	constexpr size_t kuAlignment = 0;

	void* pv = ::AlignedMalloc(kuSize, kuAlignment);
	if ( pv != nullptr )
		return false;

	::AlignedFree(pv);

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool 
TestAlignmentLargerThanSize()
{
	constexpr size_t kuSize = 7;
	constexpr size_t kuAlignment = 256;

	void* pv = ::AlignedMalloc(kuSize, kuAlignment);
	if ( (reinterpret_cast<size_t>(pv) % kuAlignment) != 0 )
		return false;

	::AlignedFree(pv);

	return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static const UnitTest g_aUnitTest[] =
{
	DefineUnitTest(TestBasicAlignedMalloc),
	DefineUnitTest(TestSmallAlignedMalloc),
	DefineUnitTest(TestSmallerAlignedMalloc),
	DefineUnitTest(TestZeroAlignment),
	DefineUnitTest(TestAlignmentLargerThanSize),
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
