/*----------------------------------------------------------------------------
* Copyright (c) Chaos 2009. All Rights Reserved.							  
*The Program calculates the velocity of the left and right sides of the chassis.
* The low pass filter is not in use at this time. 
* ---------------------------------------------------------------------------- */

#ifndef CHAOSLINEAR_H_
#define CHAOSLINEAR_H_

#include "chaosAccel.h"
#include "WPILib.h"
#include "LowPassFilter.h"



/**
 *  
 */
class chaosLinear
{
public:	
	double period; 
	float V_LeftChassis;
	float V_RightChassis;
	
	chaosAccel accel_y;
	Gyro gyro;
	LowPassFilter LPFG;

	explicit chaosLinear(int GyroPort, int AccelPort);
	virtual ~chaosLinear();
	void CalculateValue();
	void SetCoefficient_Accel_lpf(double Coefficient);
	void SetCoefficient_Accel_lpf(double Hertz, double Period);
	void Reset_Accel_lpf();
	void SetSensitivity_Accel(float Sensitivity);
//	void SetSensitivity_Gyro(int Sensitivity);
	void SetZero_Accel(double Zero);
	void SetPrevious_Accel_lpf(double previous);
	void Init_Gyro(void);
	
	float prevGyroValue;
	
};
#endif
