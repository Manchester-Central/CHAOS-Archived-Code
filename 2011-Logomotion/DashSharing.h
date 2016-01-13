/*-------------------------------------------------------------**
**                                                             
**   Filename: DashSharing.h                                        
**                                                             
**   About:    The interface for sharing variables with the 
**             Dashboard and Logger system
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Steven Kroh, Chaos.           
**                                                                                           
**   2011 1 20             
**                                                             
**-------------------------------------------------------------*/

#ifndef _DASH_SHARING_H_
#define _DASH_SHARING_H_

#include "WPILib.h"
#include "LineFollowingStates.h"

class DashSharing
{
public:	
	
	//Line Following Sensors
	bool UpperLineTracker_D;
	bool LowerLineTracker_D;

	
	//Line Following States
	//LINE_FOLLOWING_STATES_T LineFollowingStates_D;
	int LineFollowingStates_D;
	
	//Gyro
	float LineFollowingGyroAngle_D;
	
	//Line Following Robot Driving Variables
	float Speed_D;
	float Heading_D;
	
	//Ultrasonic
	double LeftInches_D;
	double RightInches_D;
	double AvgInches_D;
	double UltraAngle_D;
	
	//Elbow Data
	float ElbowProportionalConstant_D;
	float ElbowIntegralConstant_D;
	float ElbowDerivativeConstant_D; 
	
	float ElbowPreviousAngle_D;
	float ElbowPidGet_D;
	float ElbowPidSetpoint_D;
	
	//Escape Button
	bool EscapeBTN_D;
	double EscapeTime_D;
	
	int CurrentAutoState_D;
	
	float ElbowPot_D;
	
	int ManipStates_D;
	int ElbowStates_D;
	int ShoulderStates_D;
	
	float ShoulderAngle_D;
	

	DashSharing(void)
	{
		UpperLineTracker_D = true;
		LowerLineTracker_D = false;
		
		LineFollowingStates_D = 0;
		LineFollowingGyroAngle_D = 0.0;
		Speed_D = 0.0;
	    Heading_D = 0.0;
	    
	    LeftInches_D = 0.0;
    	RightInches_D = 0.0;
    	AvgInches_D = 0.0;
    	UltraAngle_D = 0.0;
    	
    	ElbowProportionalConstant_D = 0.0;
		ElbowIntegralConstant_D = 0.0;
		ElbowDerivativeConstant_D = 0.0; 
		
		ElbowPreviousAngle_D = 0.0;
		ElbowPidGet_D = 0.0;
		ElbowPidSetpoint_D = 0.0;
		
		EscapeBTN_D = false;
		EscapeTime_D = 0.0;
		
		CurrentAutoState_D = 0;
		
		ElbowPot_D = 0.0;
		
		ManipStates_D = 0;
		ElbowStates_D = 0;
		ShoulderStates_D = 0;
		
		ShoulderAngle_D = 0.0;
	}
};

#endif

