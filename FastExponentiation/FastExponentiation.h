#ifndef FastExponentiation_h
#define FastExponentiation_h

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T>
T
FastExponentiation(T t, size_t uExponent)
{
	if ( uExponent == 0 )
		return 1;

	T tTemp = FastExponentiation(t, uExponent / 2);

	if ( (uExponent % 2) == 0 )
		return tTemp * tTemp;

	return t * tTemp * tTemp; 
}

#endif
