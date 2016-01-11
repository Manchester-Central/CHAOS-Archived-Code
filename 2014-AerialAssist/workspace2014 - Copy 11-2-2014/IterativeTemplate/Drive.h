 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Constants.h                                       
 **                                                             
 **   About:    
 **                                                                
 **   Property of Chaos, Copyright 2014
 **   Written by:  
 **              Ben Papp
 **              Eric Moy
 **               
 **				  CHAOS.           
 **                                                                                           
 **   2014 1 13             
 **                                                             
 **-------------------------------------------------------------*/

#include "HardwareIO.h"
#include "WPILib.h"
#include "Constants.h"
#include <math.h>

#define RIGHT_DRIVE_DIRECTION -1.0
#define LEFT_DRIVE_DIRECTION 1.0

#define DRIVE_TURN_GAIN 25.0
#define MAX_CORRECTION 0.3

#define LEFT_DRIVE_CHANNEL_A 1
#define LEFT_DRIVE_CHANNEL_B 2
#define RIGHT_DRIVE_CHANNEL_A 3
#define RIGHT_DRIVE_CHANNEL_B 4

#define DRIVE_INCHES_PER_COUNT 0.1257 //(revolution/100counts)*(4*pi)(inches/revolution) to inches/counts
#define RIGHT_ENCODER_DIRECTION true
#define LEFT_ENCODER_DIRECTION false


class Drive
{
public:
	Drive(void);
	//Function prototypes
	void TeleopDrive(double, double);
	void InitAutoDrive(double rightDistance, double leftDistance, double speed);
	bool autoDrive(void);
	double getSpeed(void);
	
private:
	
	Talon *LeftFrontDriveTalon;
	Talon *LeftMiddleDriveTalon;
	Talon *LeftBackDriveTalon;
	
	Talon *RightFrontDriveTalon;
	Talon *RightMiddleDriveTalon;
	Talon *RightBackDriveTalon;
	
	
	Encoder *RightDriveEncoder;
	Encoder *LeftDriveEncoder;
	
	float rightPower, leftPower;
	float rightDistance, leftDistance; 
	bool autoDriveEnable; 
};