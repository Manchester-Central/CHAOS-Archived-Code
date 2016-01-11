 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Chassis.h                                       
 **                                                             
 **   About:    
 **                                                                
 **   Property of Chaos, Copyright 2013
 **   Written by:  
 **               Kathryn Ly-Bishop
 **               Eric Moy
 **               Ben Papp
 **               Harrison Riddell
 **				  CHAOS.           
 **                                                                                           
 **   2013 1 19             
 **                                                             
 **-------------------------------------------------------------*/

#ifndef CHASSIS_H_
#define CHASSIS_H_

#include "WPILib.h"
#include "Refs.h"


class Chassis
{
public:
	//explicit Counter(DigitalSource *source);
	Chassis(RobotDrive *Base);
	~Chassis();
	void DeadReckon(float DriveForward, float TurnComponent, double Time);
	bool EncoderDrive(float TargetDistance, float Speed);
	void EncoderTurn(float Angle, float TargetSpeed);
	
private:
	Talon *LeftBackDriveTalon;
	Talon *RightBackDriveTalon;
	Talon *LeftFrontDriveTalon;
	Talon *RightFrontDriveTalon;
	Encoder *LeftDriveEncoder;
	Encoder *RightDriveEncoder;
	RobotDrive *base;
	Timer *DriveTimer;
};


#endif
