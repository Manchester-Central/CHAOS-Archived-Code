 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Manipulator.cpp                                       
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

#include "Manipulator.h"

Manipulator::Manipulator(RobotDrive *Base)
{

	IsBottomFrisbeeAbsent = new DigitalInput(BOTTOM_TRACKER_PORT);
	IsFrisbeeNotAtGate = new DigitalInput(FRISBEE_GATE_PORT);
	IsFrisbeeNotAtIntake = new DigitalInput(FRISBEE_INTAKE_PORT);
	IsTopFrisbeeAbsent = new DigitalInput(HUMAN_PLAYER_PICKUP_PORT); //
	IsShooterAligned = new DigitalInput(SHOOTER_ENCODER_PORT);
	//
	DIO6 = new DigitalInput(10);
	DIO7 = new DigitalInput(11);
	DIO8 = new DigitalInput(12);
	DIO9 = new DigitalInput(13);
	DIO10 = new DigitalInput(14);
	Encoder1A = new DigitalInput(1);
	Encoder1B = new DigitalInput(2);
	Encoder2A = new DigitalInput(3);
	Encoder2B = new DigitalInput(4);
	
	//
	ShooterPart = new Shooter();

	ConveyorPart = new Conveyor();
	HPRollerPart = new HPRoller();
	IntakePart = new Intake();
	
	
}

Manipulator::~Manipulator()
{
	IsBottomFrisbeeAbsent = NULL;
	IsFrisbeeNotAtGate = NULL;
	IsFrisbeeNotAtIntake = NULL;
	IsTopFrisbeeAbsent = NULL;
}

void Manipulator::ReloadTop()
{
	/*
	printf("     IsTopFrisbeeAbsent->Get(): %d\n",IsTopFrisbeeAbsent->Get());
	printf("     IsBottomFrisbeeAbsent->Get(): %d\n",IsBottomFrisbeeAbsent->Get());
	printf("     IsFrisbeeNotAtGate->Get(): %d\n",IsFrisbeeNotAtGate->Get());
	printf("     IsFrisbeeNotAtIntake->Get(): %d\n",IsFrisbeeNotAtIntake->Get());
	printf("     ShooterEncoder->Get(): %d\n",IsShooterAligned->Get());
	*/	
	
	if(IsTopFrisbeeAbsent->Get()== true)
	{
		printf("			ADD DISC\n");
		HPRollerPart->AddDisc();
	}
	else
	{
		printf("			DO NOT ADD DISC\n");
		HPRollerPart->Off();
	}
}

void Manipulator::StopReload()
{
	HPRollerPart->Off();
}

void Manipulator::StartIntake()
{
	if(IsFrisbeeNotAtGate->Get()== true)
	{
		printf("Calling IntakePart->Feed\n");
		IntakePart->Feed();
		if(IsFrisbeeNotAtIntake->Get() == false)
		{
			ConveyorPart->FeedBottom();
		}
		else
		{
			ConveyorPart->Stop();
		}
	}
	else
	{
		printf("Calling IntakePart->Stop\n");
		IntakePart->Stop();
		ConveyorPart->Stop();
	}
}

void Manipulator::StopIntake()
{
	IntakePart->Stop();
}

void Manipulator::ClearIntake()
{
	if(IsTopFrisbeeAbsent->Get()== false)
	{
		ShooterPart->SpinUpShooter();
		if(ShooterPart->IsShooterFast())
		{
			IntakePart->Unjam();
			ConveyorPart->FeedTop();
		}
	}
	else
	{
		IntakePart->Unjam();
		ConveyorPart->FeedTop();
	}
}

void Manipulator::Test()
{
	printf("YO DAWG LETS TEST\n");
	ShooterPart->Test();
	//ConveyorPart->FeedTop();
}

void Manipulator::StartShooter()
{
	ShooterPart->SpinUpShooter();
}

void Manipulator::StartShooter(float ShooterSpeed)
{
	ShooterPart->SpinUpShooter(ShooterSpeed);
}

float Manipulator::GetShooterSpeed()
{
	return ShooterPart->GetSpeed();
}

void Manipulator::SetShooterSpeed(float ShooterSpeed)
{
	ShooterPart->SetSpeed(ShooterSpeed);
}

void Manipulator::ResetShooterSpeed()
{
	ShooterPart->ResetSpeed();
}

void Manipulator::AddToShooterSpeed(float DeltaShooterSpeed)
{
	ShooterPart->AddToShooterSpeed(DeltaShooterSpeed);
}

void Manipulator::SubtractFromShooterSpeed(float DeltaShooterSpeed)
{
	ShooterPart->SubtractFromShooterSpeed(DeltaShooterSpeed);
}

void Manipulator::ShooterSpeedControl()
{
	ShooterPart->SpeedControl();
}

void Manipulator::AddToShooterTargetSpeed(float DeltaTargetSpeed)
{
	ShooterPart->AddToTargetSpeed(DeltaTargetSpeed);
}

void Manipulator::StopShooter()
{
	ShooterPart->Off();
}

void Manipulator::Shoot()
{
	if (ShooterPart->IsShooterFast())
	{
		if ((IsBottomFrisbeeAbsent->Get() == false || IsFrisbeeNotAtGate->Get() == false || IsFrisbeeNotAtIntake->Get() == false))
		{
			ConveyorPart->FeedBottom();
		}
		else
		{
			ConveyorPart->FeedTop();
		}
	}
	else
	{
		ConveyorPart->Stop();
	}
}

bool Manipulator::ConveyorIsRunning()
{
	return ConveyorPart->IsRunning();
}

void Manipulator::DontShoot()
{
	ConveyorPart->Stop();
}

void Manipulator::ManualMode()
{
	ConveyorPart->FeedTop();
}

double Manipulator::GetShooterPeriod()
{
	return ShooterPart->GetPeriod();
}

double Manipulator::GetTargetShooterSpeed()
{
	return ShooterPart->GetTargetSpeed();
}

/*void Manipulator::ClimbUp()
{
	ClimbPart->ClimbUp();
}*/

/*void Manipulator::ClimbDown()
{
	ClimbPart->ClimbDown();
}*/

/*void Manipulator::ClimbStop()
{
	smartDashboard->PutString("Location", "Manipulator::ClimbStop()");
	ClimbPart->Stop();
}*/
