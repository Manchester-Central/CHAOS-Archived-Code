 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Chassis.cpp                                       
 **                                                             
 **   About:    
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

#include "Chassis.h"


Chassis::Chassis(RobotDrive *Base)
{
	LeftFrontDriveTalon = new Talon(LEFT_FRONT_DRIVE_PORT);
	LeftBackDriveTalon = new Talon(LEFT_BACK_DRIVE_PORT);
	RightFrontDriveTalon = new Talon(RIGHT_FRONT_DRIVE_PORT);
	RightBackDriveTalon = new Talon(RIGHT_BACK_DRIVE_PORT);
	
	LeftDriveEncoder = new Encoder(LEFT_DRIVE_ENCODER_PORT_A, LEFT_DRIVE_ENCODER_PORT_B);
	RightDriveEncoder = new Encoder(RIGHT_DRIVE_ENCODER_PORT_A, RIGHT_DRIVE_ENCODER_PORT_B);
	
	DriveTimer = new Timer();
	
	//base = new RobotDrive(LEFT_FRONT_DRIVE_PORT, LEFT_BACK_DRIVE_PORT, RIGHT_FRONT_DRIVE_PORT, RIGHT_BACK_DRIVE_PORT);
	base = Base;
}

Chassis::~Chassis()
{
	LeftFrontDriveTalon = NULL;
	LeftBackDriveTalon = NULL;
	RightFrontDriveTalon = NULL;
	RightBackDriveTalon = NULL;		

	LeftDriveEncoder = NULL;
	RightDriveEncoder = NULL;
	base = NULL;
}


void Chassis::DeadReckon(float DriveForward, float TurnComponent, double Time)
{
	DriveTimer->Start();
	double StopTime = DriveTimer->Get() + Time;
	while(DriveTimer->Get() <StopTime);
	{
		LeftFrontDriveTalon->Set((DriveForward + TurnComponent) * LEFT_DIRECTION);
		LeftBackDriveTalon->Set((DriveForward + TurnComponent) * LEFT_DIRECTION);
		RightFrontDriveTalon->Set((DriveForward + TurnComponent) * RIGHT_DIRECTION);
		RightBackDriveTalon->Set((DriveForward + TurnComponent) * RIGHT_DIRECTION);
	}
	LeftFrontDriveTalon->Set(0.0,0);
	LeftBackDriveTalon->Set(0.0,0);
	RightFrontDriveTalon->Set(0.0,0);
	RightBackDriveTalon->Set(0.0,0);
	DriveTimer->Stop();
	DriveTimer->Reset();
}

/*
 * EncoderDrive 
 * float TargetDistance distance in inches to drive
 * float Speed scalar on output speed
 * return:true if no timeout
 */
bool Chassis::EncoderDrive(float TargetDistance, float Speed)
{
	Speed = Misc::fabs(Speed);
	LeftDriveEncoder->Start();
	RightDriveEncoder->Start();
	DriveTimer->Start();
	bool DidTimeoutHappen = false;
	double StartTime = DriveTimer->Get();
	bool NotThereYet = true;
	float AllPreviousErrors = 0.0;
	double PreviousTime = 0.0;
	float PreviousError = 0.0;
	float P = 0.0;
	float I = 0.0;
	float D = 0.0;
	
	double CurrentSpeed = 0.0;
	
	while(NotThereYet = true)
	{
		//calculates current speed in inches/sec based on (inch/tick)/current period
		CurrentSpeed = (1 / ENCODER_DISTANCE_COEFFICIENT) / ((LeftDriveEncoder->GetPeriod() + RightDriveEncoder->GetPeriod()) / 2);
		double Timer = DriveTimer->Get();
		//Encoder Distance in inches
		float EncoderDistance =(((LeftDriveEncoder->Get()+RightDriveEncoder->Get())/2) * ENCODER_DISTANCE_COEFFICIENT);
		float Error = TargetDistance - EncoderDistance; //distance to target distance in inches
		P = Error * P_GAIN;		//Proportional compontent of PID
		AllPreviousErrors += PreviousError;

		if(Timer > Misc::fabs(TargetDistance / (DRIVE_SPEED * 0.9)))
		{
			NotThereYet = false;
			DidTimeoutHappen = true;
		}
		if(Error == 0.0)
		{
			AllPreviousErrors = 0.0;
			StartTime = Timer;
		}
		I = I_GAIN * AllPreviousErrors * (Timer - StartTime);
		PreviousError = Error;
		if(P != 0)
		{
			D = D_GAIN * CurrentSpeed * (Timer - PreviousTime) * P/Misc::fabs(P);
		}
		else
		{
			D = 0.0;
		}
		PreviousTime = Timer;
		LeftFrontDriveTalon->Set((P+I+D) * Speed * LEFT_DIRECTION,0); 
		LeftBackDriveTalon->Set((P+I+D) * Speed * LEFT_DIRECTION,0);
		RightFrontDriveTalon->Set((P+I+D) * Speed * RIGHT_DIRECTION,0);
		RightBackDriveTalon->Set((P+I+D) * Speed * RIGHT_DIRECTION,0);
		if((CurrentSpeed < SPEED_HYSTERESIS)
			&& ((EncoderDistance < (TargetDistance + DISTANCE_HYSTERESIS))
			&& (EncoderDistance > (TargetDistance - DISTANCE_HYSTERESIS))))
		{
			NotThereYet = false;
		}
	}
	LeftDriveEncoder->Stop();
	LeftDriveEncoder->Reset();
	RightDriveEncoder->Stop();
	RightDriveEncoder->Reset();
	
	DriveTimer->Stop();
	DriveTimer->Reset();
	if(DidTimeoutHappen = true)
	{
		return false;
	}
	else 
	{
		return true;
	}
}

