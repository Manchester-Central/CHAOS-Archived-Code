/*----------------------------------------------------------------------------*/
/* Copyright (c) Chaos 2009. All Rights Reserved.							  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef LOWPASSFILTER_H_
#define LOWPASSFILTER_H_

#include "WPILib.h"

/**
 *  
 */
class LowPassFilter 
{
public:
	double coef_LPF;
	double Vprev;

	LowPassFilter();
	explicit LowPassFilter(double Coefficient);
	LowPassFilter(double Hertz, double Period);
	virtual ~LowPassFilter();
	double GetValue(double Vin);
	void SetCoefficient(double Coefficient);
	void SetCoefficient(double Hertz, double Period);
	void SetPrevious(double Previous);
	void Reset();

private:
	void InitLowPassFilter(double Coefficient);
	void InitLowPassFilter (double Hertz, double Period);
};
#endif
