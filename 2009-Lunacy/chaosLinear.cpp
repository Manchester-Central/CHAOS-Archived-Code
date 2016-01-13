/*----------------------------------------------------------------------------*
* Copyright (c) CHAOS 2009
*----------------------------------------------------------------------------*/

#include "chaosLinear.h"
#include "logger.h"
#define L1 .6
#define L2 .45
#define RADIANSCONSTANT 0.032057067893773400392475952890607 // PI/Observed value for 180 turn
#define NUMBEROFACCUMULATIONS 3

void chaosLinear::SetSensitivity_Accel(float Sensitivity)
{ 
	accel_y.SetSensitivity(Sensitivity);
}

void chaosLinear::SetZero_Accel(double Zero)
{
	accel_y.SetZero(Zero);
}

void chaosLinear::SetPrevious_Accel_lpf(double previous)
{
	accel_y.SetPrevious_lpf(previous);
}

/**construct the chaosLinear object
 * @param int GyroPort
 * @param int AccelPort
 */

chaosLinear::chaosLinear(int GyroPort, int AccelPort):accel_y(AccelPort), gyro(GyroPort), LPFG(.01, .2)
{
	period = 0;
	V_LeftChassis = 0;
	V_RightChassis = 0;
}

void chaosLinear::Init_Gyro()
{
	gyro.SetSensitivity(.007);
	prevGyroValue = gyro.GetAngle()*RADIANSCONSTANT;
}

/**
 * Reset the chaosAccel that goes through the filter. 
 */
void chaosLinear::Reset_Accel_lpf()
{
	accel_y.Reset_lpf();
}

/**
 * Delete (free)  the chaosLinear.
 */
chaosLinear::~chaosLinear()
{
}

//calculates the linear acceleration of the chassis
void chaosLinear::CalculateValue()
{
	static int iterations = 0;
	float GyroSubtractor = 0.0;
	
	float V_EstChassis = accel_y.GetValue();
	
	float GyroValue = gyro.GetAngle()*RADIANSCONSTANT;
	logger.gyro = GyroValue;
	
	float deltaGyroValue = GyroValue - prevGyroValue;
	
	prevGyroValue = GyroValue;
	
	float GyroRate = deltaGyroValue/period;
	float RateAccumulated = 0;
	
	if(iterations < NUMBEROFACCUMULATIONS)
	{
		iterations++;
		GyroSubtractor = 0;
		RateAccumulated += GyroRate;
	}
	else if(iterations == NUMBEROFACCUMULATIONS)
	{
		RateAccumulated += GyroRate;
		LPFG.SetPrevious((double )GyroRate/NUMBEROFACCUMULATIONS);
		iterations++;
	}
	else
	{
		GyroSubtractor = LPFG.GetValue(GyroRate);
	}
	
	GyroRate -= GyroSubtractor;
	
//	printf("GR: %02.4f, GV: %02.6f, PGV: %02.6f, dGV: %02.6f\n", GyroRate, GyroValue, prevGyroValue, deltaGyroValue);
	V_RightChassis = V_EstChassis+(GyroRate*L2);
	V_LeftChassis = V_EstChassis-(GyroRate*L1);
	
	logger.vChaSide[0] = V_LeftChassis;
	logger.vChaSide[1] = V_RightChassis;
//	printf("5: %02.4f 6: %02.4f ", V_RightChassis, V_LeftChassis);
	
//	printf("LowPassFilter Coef: %02.6f, Vprev %02.6f\n", accel_y.lpf.coef_LPF, accel_y.lpf.Vprev);

}

/** 
*@param int Hertz Frequency of collecting data
*@param double Period
 */
void chaosLinear::SetCoefficient_Accel_lpf(double Hertz, double Period)
{
	period = Period;
	accel_y.SetCoefficient_lpf(Hertz, Period);

	//printf("Hertz: %02.6f, Period: %02.6f ", Hertz, Period);
//	printf("LowPassFilter Coef: %02.6f, Vprev %02.6f\n", accel_y.coef_LPF, accel_y.Vprev);
}
