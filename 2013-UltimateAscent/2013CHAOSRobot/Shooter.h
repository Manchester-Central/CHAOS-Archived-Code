 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Shooter.h                                       
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
#ifndef SHOOTER_H_
#define SHOOTER_H_

#include "WPILib.h"
#include "Refs.h"

class Shooter
{
public:
	//function protypes
	Shooter();
	bool IsShooterFast();
	void SpinUpShooter();
	void SpinUpShooter(float ShooterSpeed);
	
	float GetSpeed();
	void SetSpeed(float ShooterSpeed);
	void ResetSpeed();
	void AddToShooterSpeed(float DeltaShooterSpeed);
	void SubtractFromShooterSpeed(float DeltaShooterSpeed);
	void Off();
	double GetPeriod();
	void SpeedControl();
	void SetTargetSpeed(float Speed);
	void AddToTargetSpeed(float DeltaTargetSpeed);
	double GetTargetSpeed();
	
	void Test();
	~Shooter();
	
	
private:
	//objects
	Talon *ShooterTalon;
	DigitalInput *ShooterEncoder;
	Counter *ShooterTach;
	
	float InternalShooterSpeed;
	float TargetSpeed;
};


#endif
