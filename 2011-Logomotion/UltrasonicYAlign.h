/*-------------------------------------------------------------**
**                                                             
**   Filename: UltrasonicYAlign.h                                        
**                                                             
**   About:    An object to y-align the robot with the wall
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Zain Abbas & Steven Kroh, Chaos.           
**                                                                                           
**   2011 2 5           
**                                                             
**-------------------------------------------------------------*/

#ifndef ULTRASONIC_Y_ALIGN_H_
#define ULTRASONIC_Y_ALIGN_H_

#include "WPILib.h"
#include "Refs.h"
#include <math.h>

class UltrasonicYAlign : public PIDSource
{
public: 
	
	UltrasonicYAlign(Ultrasonic *LeftUltrasonic, Ultrasonic *RightUltrasonic);
	double GetAvgDistance(void);
	double GetAngle(void);
	virtual double PIDGet(void);
	
	Ultrasonic *LeftUltrasonic;
	Ultrasonic *RightUltrasonic;

	double AvgDistance;
	double Angle;
};

#endif
