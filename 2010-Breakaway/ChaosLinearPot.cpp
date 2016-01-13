
#include "ChaosLinearPot.h"

ChaosLinearPot::ChaosLinearPot(INT32 AnalogModule_Pass, INT32 AnalogChannel_Pass)
{
	LinearPot = new AnalogChannel(AnalogModule_Pass, AnalogChannel_Pass);
}

float ChaosLinearPot::GetDistance(void)
{
	float Distance = LinearPot->GetVoltage();
	Distance = (LinearPot->GetVoltage()) * SLOPE; //in cm
	Distance = fabs(Distance - MAX_POT_DISTANCE);
	return Distance;
}
