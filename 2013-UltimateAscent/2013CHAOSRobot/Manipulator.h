 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Manipulator.h                                       
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
#ifndef MANIPULATOR_H_
#define MANIPUlATOR_H_

#include "WPILib.h"
#include "Gamepad.h"
#include "Refs.h"
#include "Conveyor.h"
#include "Shooter.h"
#include "HPRoller.h"
#include "Intake.h"
//#include "Climb.h"
#include "Chassis.h"


class Manipulator
{
	public:
	
	Manipulator(RobotDrive *Base);
	void Shoot();
	~Manipulator();
	void StartShooter();
	void StartShooter(float ShooterSpeed);
	float GetShooterSpeed();
	void SetShooterSpeed(float ShooterSpeed);
	void ResetShooterSpeed();
	void StopShooter();
	void AddToShooterSpeed(float DeltaShooterSpeed);
	void SubtractFromShooterSpeed(float DeltaShooterSpeed);
	void StartIntake();
	void StopIntake();
	void ClearIntake();
	void ReloadTop();
	void DontShoot();
	double GetShooterPeriod();
	void ShooterSpeedControl();
	void AddToShooterTargetSpeed(float DeltaTargetSpeed);
	double GetTargetShooterSpeed();
	
	bool ConveyorIsRunning();
	//void ClimbUp();
	//void ClimbDown();
	//void ClimbStop();
	void StopReload();
	//SmartDashboard *smartDashboard;
	void Test();
	void ManualMode();
	
	typedef enum
	{
		MANIP_STATE_DISABLED = 0,
		MANIP_STATE_INIT = 1,
		MANIP_STATE_RELOAD = 2,
		MANIP_STATE_SHOOT = 3,
		MANIP_STATE_AUTO_SHOOT = 4,
		MANIP_STATE_MANUAL = 5
	}MANIP_STATES_X;
	
	
	
	DigitalInput *IsBottomFrisbeeAbsent;
	DigitalInput *IsFrisbeeNotAtGate;
	DigitalInput *IsFrisbeeNotAtIntake;
	DigitalInput *IsTopFrisbeeAbsent;
	DigitalInput *IsShooterAligned;
	
	DigitalInput *DIO6;
	DigitalInput *DIO7;
	DigitalInput *DIO8;
	DigitalInput *DIO9;
	DigitalInput *DIO10;
	DigitalInput *Encoder1A;
	DigitalInput *Encoder1B;
	DigitalInput *Encoder2A;
	DigitalInput *Encoder2B;
	
private:

	
	Conveyor *ConveyorPart;
	Shooter *ShooterPart;
	HPRoller *HPRollerPart;
	Intake *IntakePart;
	//Climb *ClimbPart;
	
};

#endif
