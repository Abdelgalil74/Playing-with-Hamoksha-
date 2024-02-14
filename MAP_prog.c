
#include "STD_TYPES.h"

sint32 MAP(sint32 InputRangeMin ,sint32 InputRangeMax ,sint32 OutputRangeMin ,sint32 OutputRangeMax, sint32 InputValue)
{
	
	return (((InputValue-InputRangeMin)* (OutputRangeMax-OutputRangeMin))/(InputRangeMax-InputRangeMin))+OutputRangeMin ;
	
}
