/*-------------------------------------------------------------**
**                                                             
**   Filename: Filter.h                                        
**                                                             
**   About:    Filtering input.
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Steven Kroh 
**                                                               
**   2011 2 15             
**                                                             
**-------------------------------------------------------------*/

class Filter
{
public:
	// Ynow = Yprevious(1 - Fraction) + Xnow*Fraction
	Filter(double fraction, double previous = 0);
	double Result(double Input);
	void SetPrevious(double previous);
	
	double Fraction;
	
	double Yprevious;
	
};
