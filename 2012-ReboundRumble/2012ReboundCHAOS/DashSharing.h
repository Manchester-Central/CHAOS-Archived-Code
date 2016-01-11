
#ifndef _DASH_SHARING_H_
#define _DASH_SHARING_H_

#include "WPILib.h"

class DashSharing
{
public:	
	bool LightIntake;
	bool LightConveyor;
	bool LightOutput;
	float SensedDistance;

	DashSharing(void)
	{
		LightIntake = false;
		LightConveyor = false;
		LightOutput = false;
		SensedDistance = 0.0;
	}
};

#endif
