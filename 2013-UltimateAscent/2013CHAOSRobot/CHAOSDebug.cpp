 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: CHAOSDebug.cpp                                       
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
#include "CHAOSDebug.h"
#include "Gamepad.h"
#include "WPILib.h"
#include "string.h"

CHAOSDebug::CHAOSDebug()
{

	ShooterTalon = new Talon(SHOOTER_TALON_PORT);
	ConveyorTalon = new Talon(CONVEYOR_TALON_PORT);
	IntakeTalonA = new Talon(INTAKE_TALON_PORT_A);
	IntakeTalonB = new Talon(INTAKE_TALON_PORT_B);
	LeftFrontDriveTalon = new Talon(LEFT_FRONT_DRIVE_PORT);
	LeftBackDriveTalon = new Talon(LEFT_BACK_DRIVE_PORT);
	RightFrontDriveTalon = new Talon(RIGHT_FRONT_DRIVE_PORT);
	RightBackDriveTalon = new Talon(RIGHT_BACK_DRIVE_PORT);
	
	HPRollerSpike = new Relay(HUMAN_PLAYER_PICKUP_PORT);
	
	LeftDriveEncoder = new Encoder(LEFT_DRIVE_ENCODER_PORT_A, LEFT_DRIVE_ENCODER_PORT_B, false);
	RightDriveEncoder = new Encoder(RIGHT_DRIVE_ENCODER_PORT_A, RIGHT_DRIVE_ENCODER_PORT_B, false);
	
	IsBottomFrisbeePresent = new DigitalInput(BOTTOM_TRACKER_PORT);
	IsFrisbeeAtGate = new DigitalInput(FRISBEE_GATE_PORT);
	IsFrisbeeAtIntake = new DigitalInput(FRISBEE_INTAKE_PORT);
	IsTopFrisbeePresent = new DigitalInput(HUMAN_PLAYER_PICKUP_PORT);
	
	
	ShooterEncoder = new DigitalInput(SHOOTER_ENCODER_PORT);
	ShooterTach = new Counter(ShooterEncoder);
	
	DriverGamepad = new Gamepad(DRIVER_GAMEPAD_PORT);
	//OperatorGamepad = new Gamepad(OPERATOR_GAMEPAD_PORT);
		
}
CHAOSDebug::~CHAOSDebug()
{
	ShooterTalon = NULL;
	ConveyorTalon = NULL;
	IntakeTalonA = NULL;
	IntakeTalonB = NULL;
	LeftFrontDriveTalon = NULL;
	LeftBackDriveTalon = NULL;
	RightFrontDriveTalon = NULL;
	RightBackDriveTalon = NULL;
	
	HPRollerSpike = NULL;
	
	LeftDriveEncoder = NULL;
	RightDriveEncoder = NULL;
	
	IsBottomFrisbeePresent = NULL;
	IsFrisbeeAtGate = NULL;
	IsFrisbeeAtIntake = NULL;
	IsTopFrisbeePresent = NULL;
	
	
	ShooterEncoder = NULL;
	ShooterTach = NULL;
	
	DriverGamepad = NULL;
	OperatorGamepad = NULL;
}

void CHAOSDebug::ControllerDebug()
{

	if(IsBottomFrisbeePresent->Get()==true){
		printf("Bottom Frisbee Found\n");
	}
	else
	{
		printf("No Bottom Frisbee");
	}
	
	if(IsFrisbeeAtIntake->Get()==true) {
		printf("Frisbee Is At Intake\n");
	}
	else
	{
		printf("No Frisbee At Intake\n");
	}
	
	if(IsFrisbeeAtGate->Get()==true) {
		printf("Frisbee Is At Gate\n");
	}
	else
	{
		printf("No Frisbee Is At Gate\n");
	}
	
	if(ShooterEncoder->Get()==true){
		printf("The Shooter Is Aligned\n");
	}
	else
	{
		printf("Shooter Is Not Aligned\n");
	}
	
	printf("ShooterTach %d \n", ShooterTach->Get());
	
	ShooterTalon->Set(Misc::fabs(DriverGamepad->GetLeftY()), 0);
	
	if(DriverGamepad->GetNumberedButton(A_BUTTON))//"A" button
	{
		printf("A-Button was pressed\n");
		//ShooterTalon->SetSpeed(1.0);
		ConveyorTalon->Set(1.0,0);
		IntakeTalonA->Set(1.0,0);
		IntakeTalonB->Set(1.0,0);
		LeftFrontDriveTalon->Set(1.0,0);
		LeftBackDriveTalon->Set(1.0,0);
		RightFrontDriveTalon->Set(1.0,0);
		RightBackDriveTalon->Set(1.0,0);
		HPRollerSpike->Set(HPRollerSpike->kForward);
		printf("    A-button ended\n");
	}
	else if(DriverGamepad->GetNumberedButton(B_BUTTON))//"B" button
	{
		printf("B-Button was pressed\n");
		//ShooterTalon->Set(1.0,0);
		ConveyorTalon->Set(-1.0,0);
		IntakeTalonA->Set(-1.0,0);
		IntakeTalonB->Set(-1.0,0);
		LeftFrontDriveTalon->Set(-1.0,0);
		LeftBackDriveTalon->Set(-1.0,0);
		RightFrontDriveTalon->Set(-1.0,0);
		RightBackDriveTalon->Set(-1.0,0);
		HPRollerSpike->Set(HPRollerSpike->kReverse);
		printf("    B-button ended\n");
	}
	else
	{
		printf("nothing was pressed\n");
		//ShooterTalon->Set(0.0,0);
		ConveyorTalon->Set(0.0,0);
		IntakeTalonA->Set(0.0,0);
		IntakeTalonB->Set(0.0,0);
		LeftFrontDriveTalon->Set(0.0,0);
		LeftBackDriveTalon->Set(0.0,0);
		RightFrontDriveTalon->Set(0.0,0);
		RightBackDriveTalon->Set(0.0,0);
		HPRollerSpike->Set(HPRollerSpike->kOff);
		printf("    no-button ended\n");
	}
}
