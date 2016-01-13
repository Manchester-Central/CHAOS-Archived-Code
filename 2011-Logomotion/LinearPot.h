/*-------------------------------------------------------------**
**                                                             
**   Filename: LinearPot.h                                        
**                                                             
**   About:    Code to map the Voltage of a linear variable 
** 			   potentiometer to an angle in radians 
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Steven Kroh, Chaos.           
**                                                                                           
**   2011 1 29             
**                                                             
**-------------------------------------------------------------*/

#ifndef LINEAR_POT_H_
#define LINEAR_POT_H_

#include "WPILib.h"
#include "Refs.h"

class LinearPot : public PIDSource
{
public:
	
	LinearPot(int PotSlot, int PotChannel, float Voltage1, float Voltage2, float Angle1, float Angle2);
	
	float GetAngleDegrees(void);
	float GetAngleRadians(void);
	virtual double PIDGet(void);
	
private:
	
	float Voltage1; 
    float Voltage2; 
    float Angle1;
    float Angle2;
    float Slope;
    float Offset;
    
    AnalogChannel *Pot;
    
};

#endif
