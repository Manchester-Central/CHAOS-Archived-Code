 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Main.h                                        
 **                                                             
 **   About:    The Main UltimateAscent Robot Class
 **                                                             
 **   Property of Chaos, Copyright 2013
 **   Written by:  
 **               Kathryn Ly-Bishop
 **               Eric Moy
 **               Ben Papp
 **               Harrison R.
 **				  CHAOS.           
 **                                                                                           
 **   2013 1 19             
 **                                                             
 **-------------------------------------------------------------*/

#ifndef MAIN_H_
#define MAIN_H_


#include "CHAOSDebug.h"
#include "WPILib.h"
#include "Refs.h"
#include "Gamepad.h"
#include "Manipulator.h"
#include "HardwareIO.h"


class Main : public IterativeRobot
{
public:
	
	//Function Prototypes
	Main(void);
	
/*	
	virtual void TeleopContinuous(void);
	virtual void AutonomousContinuous(void);
	virtual void DisabledContinuous(void);
	*/
	virtual void TeleopPeriodic(void);
	virtual void AutonomousPeriodic(void);	
	virtual void DisabledPeriodic(void);
	
	virtual void RobotInit(void);
	virtual void DisabledInit(void);
	virtual void AutonomousInit(void);
	virtual void TeleopInit(void);
//	void SendDashboard();
	
	/*typedef enum
	{
		NO_AUTO = 0,
		AUTO_STATE_1 = 1,
		AUTO_STATE_2 = 2,
		AUTO_STATE_3 = 3,
		AUTO_STATE_4 = 4
	}AUTO_STATES_X;
	*/
	int AutoState;
	
	
private:
	Manipulator *Mani;
	Chassis *ChassisPart;
	Timer *AutoTimer;
	SpeedController *TestController;
	Talon *ConveyorTalon;
	Relay *HPRollerSpike;
	
	Gamepad::DPadDirection LastDirection;
	
	
public:
	RobotDrive *Base;
	Gamepad *DriverGamepad;
	Gamepad *OperatorGamepad;
	
	
	
	Encoder *LeftDriveEncoder;
	Encoder *RightDriveEncoder;
	/*
	DigitalInput *IsBottomFrisbeeAbsent;
	DigitalInput *IsFrisbeeNotAtGate;
	DigitalInput *IsFrisbeeNotAtIntake;
	DigitalInput *IsTopFrisbeeAbsent;
	DigitalInput *IsShooterAligned;
	*/
	
	CHAOSDebug *CHAOSDebugger;
	
	SmartDashboard *smartDashboard;
};

#endif
