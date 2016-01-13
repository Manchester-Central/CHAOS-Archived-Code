/*----------------------------------------------------------------------------
* Copyright (c) Chaos 2009. All Rights Reserved.							  
*The program gets the encoder value, making allowances for the chassis being stopped, 
* and passes it through the low pass filter.
* ---------------------------------------------------------------------------- */

#ifndef CHAOSENCODER_H_
#define CHAOSENCODER_H_

#include "LowPassFilter.h"
#include "WPILib.h"

/**
 *  
 */
class chaosEncoder 
{
public:
	double coef_LPF;
	double Vprev;
	double period; 
	Encoder encoder;
	LowPassFilter lpf;

	explicit chaosEncoder(int PortA, int PortB, float DistancePerPulse);
	virtual ~chaosEncoder();
	void SetCoefficient_lpf(double Coefficient);
	void SetCoefficient_lpf(double Hertz, double Period);
	void Reset_lpf();
	void SetPrevious_lpf(double previous);
	float GetValue ();
	
	void Start();
	INT32 Get();
	INT32 GetRaw();
	void Reset();
	void Stop();
	double GetPeriod();
	void SetMaxPeriod(double maxPeriod);
	bool GetStopped();
	bool GetDirection();
	float GetDistance();
	double GetRate();
	void SetMinRate(double minRate);
	void SetDistancePerPulse(double distancePerPulse);
	void SetReverseDirection(bool reverseDirection);
	
};
#endif
