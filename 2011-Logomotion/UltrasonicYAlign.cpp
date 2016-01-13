/*-------------------------------------------------------------**
**                                                             
**   Filename: UltrasonicYAlign.cpp                                       
**                                                             
**   About:    An object to y-align the robot with the wall
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Zain Abbas & Steven Kroh, Chaos.           
**                                                                                           
**   2011 2 5           
**                                                             
**-------------------------------------------------------------*/

#include "Ultrasonic.h"
#include "UltrasonicYAlign.h"

UltrasonicYAlign::UltrasonicYAlign(Ultrasonic *LeftUltrasonic, Ultrasonic *RightUltrasonic)
{
	this->LeftUltrasonic = LeftUltrasonic;
	this->RightUltrasonic = RightUltrasonic;
	
	AvgDistance = 0.0;
	Angle = 0.0;
}

double UltrasonicYAlign::GetAvgDistance(void)
{
	AvgDistance = ((LeftUltrasonic->GetRangeInches() + RightUltrasonic->GetRangeInches())/2.0);
	return AvgDistance;
}

double UltrasonicYAlign::GetAngle(void)
{
	Angle = (180.0/PI)*(atan2((GetAvgDistance() - LeftUltrasonic->GetRangeInches()), DIST_FROM_CENTER_TO_ULTRASONIC_INCHES)); 
	return Angle;
}

double UltrasonicYAlign::PIDGet(void)
{
	return GetAvgDistance();
}
