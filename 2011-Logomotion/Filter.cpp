/*-------------------------------------------------------------**
**                                                             
**   Filename: Filter.cpp                                        
**                                                             
**   About:    Filtering input.
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Steven Kroh, Ben Papp
**                                                               
**   2011 2 15             
**                                                             
**-------------------------------------------------------------*/

#include "Filter.h"
// Ynow = Yprevious(1 - Fraction) + Xnow*Fraction


Filter::Filter(double fraction, double previous)
{
	Fraction = fraction;
	Yprevious = previous;
}

double Filter::Result(double Input)
{
	double result = (Yprevious*(1 - Fraction)) + (Input*Fraction);
	Yprevious = result;
	return result;
}

void Filter::SetPrevious(double previous)
{
	Yprevious = previous;
}
