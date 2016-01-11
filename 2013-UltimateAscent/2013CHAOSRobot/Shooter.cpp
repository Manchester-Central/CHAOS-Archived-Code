 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Shooter.cpp                                       
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

#include "Shooter.h"

Shooter::Shooter()
{
	ShooterEncoder = new DigitalInput(SHOOTER_ENCODER_PORT);
	ShooterTach = new Counter(ShooterEncoder);
	ShooterTalon = new Talon(SHOOTER_TALON_PORT);
	InternalShooterSpeed = SHOOTER_VOLTAGE;
	ShooterTach->Start();
	TargetSpeed = GOOD_SHOOTER_SPEED;
}

Shooter::~Shooter()
{
	ShooterEncoder = NULL;
	ShooterTach = NULL;
	ShooterTalon = NULL;
}

void Shooter::Test()
{
	printf("SHOOTER TESTING\n");
}

bool Shooter::IsShooterFast()
{
	
	if(Shooter::GetPeriod()<= TargetSpeed)
	{
		return true;
	}
	else
	{
		return false;
	}
	
	
}

void Shooter::SpinUpShooter()
{
	ShooterTalon->Set(InternalShooterSpeed);
}

void Shooter::SpinUpShooter(float ShooterSpeed)
{
	InternalShooterSpeed = ShooterSpeed;
	//ShooterTalon->Set(InternalShooterSpeed);
	SpinUpShooter();
}

void Shooter::Off()
{
	ShooterTalon->Set(0.0);
}
double Shooter::GetPeriod()
{
	printf("ShooterTach->GetPeriod %f\n", (float)ShooterTach->GetPeriod());
	return   ShooterTach->GetPeriod();
}

float Shooter::GetSpeed()
{
	return InternalShooterSpeed;
}

void Shooter::SetSpeed(float ShooterSpeed)
{
	InternalShooterSpeed = ShooterSpeed;
}

void Shooter::ResetSpeed()
{
	InternalShooterSpeed = SHOOTER_VOLTAGE;
}

void Shooter::AddToShooterSpeed(float DeltaShooterSpeed)
{
	InternalShooterSpeed = InternalShooterSpeed + DeltaShooterSpeed;
	if(InternalShooterSpeed > 1)
	{
		InternalShooterSpeed = 1;
	}
	else if(InternalShooterSpeed < 0)
	{
		InternalShooterSpeed = 0;
	}
}

void Shooter::SubtractFromShooterSpeed(float DeltaShooterSpeed)
{
	InternalShooterSpeed = InternalShooterSpeed - DeltaShooterSpeed;
	if(InternalShooterSpeed > 1)
	{
		InternalShooterSpeed = 1;
	}
	else if(InternalShooterSpeed < 0)
	{
		InternalShooterSpeed = 0;
	}
}

void Shooter::SpeedControl()
{
	if(ShooterTach->GetPeriod() > TargetSpeed - (SHOOTER_SPEED_DEADBAND/10))
	{
		InternalShooterSpeed = 1;
	}
	else if(ShooterTach->GetPeriod() < TargetSpeed - SHOOTER_SPEED_DEADBAND)
	{
		InternalShooterSpeed = 0;
	}
	else
	{
		InternalShooterSpeed = 0.8;
	}
}

void Shooter::SetTargetSpeed(float Speed)
{
	TargetSpeed = Speed;
}

void Shooter::AddToTargetSpeed(float DeltaTargetSpeed)
{
	TargetSpeed = TargetSpeed + DeltaTargetSpeed;
	if(TargetSpeed > 0.1)
	{
		TargetSpeed = 0.1;
	}
	else if(TargetSpeed < 0.001)
	{
		TargetSpeed = 0.001;
	}
}

double Shooter::GetTargetSpeed()
{
	return TargetSpeed;
}
