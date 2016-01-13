#ifndef _CHAOS_LINEAR_POT_
#define _CHAOS_LINEAR_POT_

#include "AnalogChannel.h"
#include "math.h"

#define MAX_POT_DISTANCE 24.5
//Need to change to 20, but changing will change other numbers

#define SLOPE 4.8 //cm/v

class ChaosLinearPot
{
	public:
		AnalogChannel *LinearPot;
		
		ChaosLinearPot(INT32 AnalogModule_Pass, INT32 AnalogChannel_Pass);
		float GetDistance(void);
};



#endif
