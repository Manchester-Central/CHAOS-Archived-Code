/*----------------------------------------------------------------------------
 * Copyright (c) CHAOS 2009
 * ---------------------------------------------------------------------------- */

#include "LowPassFilter.h"


/**
 * setting Coefficient to a
 */
void LowPassFilter::InitLowPassFilter(double Coefficient)
{
	coef_LPF = 1;
	Vprev = 0;
	SetCoefficient(Coefficient);
}

/**
 * setting Coefficient to a
 */
void LowPassFilter::InitLowPassFilter(double Hertz, double Period)
{
	coef_LPF = 1;
	Vprev = 0;
	SetCoefficient(Hertz, Period);
}


//construct is using coef_LPF to init the class
LowPassFilter::LowPassFilter()
{
	
}
/**
 * LowPassFilter constructor 
 * 
 * @param double Coefficient
 */
LowPassFilter::LowPassFilter( double Coefficient)
{
	InitLowPassFilter(Coefficient);
}

/**
 * LowPassFilter constructor 
 * 
 * @param double Hertz
*@param doulbe Period
 */
LowPassFilter::LowPassFilter(double Hertz, double Period)
{
	InitLowPassFilter(Hertz, Period);
}

/**
 * Reset the LowPassFilter. 
*the previous value
 */
void LowPassFilter::Reset()
{
	Vprev = 0;
}

/**
 * Delete (free)  the LowPassFilter.
 */
LowPassFilter::~LowPassFilter()
{
	
}

/**
 * get value this calculates the Low pass filter here are the equations
* X = a(Xnew - Xprev) + Xprev
* X + aXnew + (1 - a)Xprev
* Xout += a(Xin - Xout) this is the equation being used
*
* @ param double Vin  Represents the value
 * @return double Vprev  The returned calculated value
 */

double LowPassFilter::GetValue(double Vin)
{
	
	Vprev += coef_LPF * (Vin - Vprev);
	
//  printf("coef_LPF: %02.6f, Vprev: %02.6f, Vin: %02.6f\n", coef_LPF, Vprev, Vin);
	
	return Vprev;
}


/**
 * Set the LowPassFilter type based on the sensitivity.
  * 
 * @param double coefficient  the coefficient is used in the get value to calculate the return value
 */
void LowPassFilter::SetCoefficient( double Coefficient)
{
	coef_LPF = Coefficient;
}

/**
 * Set the LowPassFilter type based on the sensitivity.
  * 
 * @param double Hertz Frequency of collecting data
*@param double Period ??
*The if statment assures that coef is never greater than 1, and if it is it resets it to 1.
 */
void LowPassFilter::SetCoefficient(double Hertz, double Period)
{
	double coef;
	coef = Hertz * Period;
	if (coef > 1) coef = .99;
	if (coef < 0) coef = .01;
	coef_LPF = coef;
	
//	printf("Hertz: %02.6f, Period: %02.6f, coef: %02.6f, coef_LPF: %02.6f\n", Hertz, Period, coef, coef_LPF);
}

void LowPassFilter::SetPrevious(double Previous)
{
	Vprev = Previous;
}

