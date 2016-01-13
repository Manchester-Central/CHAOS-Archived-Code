	/*----------------------------------------------------------------------------
* Copyright (c) Chaos 2009. All Rights Reserved.							  
*The program calculates the acceleration of the the chassis.
* The low pass filter is not used in this program.
* ---------------------------------------------------------------------------- */

#ifndef CHAOSACCEL_H_
#define CHAOSACCEL_H_

#include "LowPassFilter.h"
#include "WPILib.h"

/**
 *  
 */
class chaosAccel 
{
public:
	double coef_LPF;
	double Vprev;
	double period; 
	Accelerometer accel;
	LowPassFilter lpf;
	
	
	double vChassisStatic;
	void clear_vChassis(void);

	explicit chaosAccel(int Port);
	virtual ~chaosAccel();
	double GetValue();
	void SetCoefficient_lpf(double Coefficient);
	void SetCoefficient_lpf(double Hertz, double Period);
	void Reset_lpf();
	void SetSensitivity(float Sensitivity);
	void SetZero(double Zero);
	void SetPrevious_lpf(double previous);
};
#endif
