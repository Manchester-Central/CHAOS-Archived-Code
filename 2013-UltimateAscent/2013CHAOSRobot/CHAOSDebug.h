 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: CHAOSDebug.h                                       
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
#ifndef CHAOSDEBUG_H_
#define CHAOSDEBUG_H_

#include "WPILib.h"
#include "Refs.h"
#include "Gamepad.h"

class CHAOSDebug
{
public:
	CHAOSDebug();
	~CHAOSDebug();
	// PassiveDebug();
	void ControllerDebug();
	Gamepad *DriverGamepad;
	Gamepad *OperatorGamepad;
	 
private:
	Talon *ShooterTalon;
	Talon *ConveyorTalon;
	Talon *IntakeTalonA;
	Talon *IntakeTalonB;
	Talon *LeftFrontDriveTalon;
	Talon *LeftBackDriveTalon;
	Talon *RightFrontDriveTalon;
	Talon *RightBackDriveTalon;
	
	Relay *HPRollerSpike;
	
	Encoder *LeftDriveEncoder;
	Encoder *RightDriveEncoder;
	
	DigitalInput *IsBottomFrisbeePresent;
	DigitalInput *IsFrisbeeAtGate;
	DigitalInput *IsFrisbeeAtIntake;
	DigitalInput *IsTopFrisbeePresent;
	
	Counter *ShooterTach;
	DigitalInput *ShooterEncoder;

};

#endif
