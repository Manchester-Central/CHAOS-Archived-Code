 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Main.cpp                                        
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

#include "Main.h"

Main::Main(void)
{
	//RobotDrive
	DriverGamepad = new Gamepad(DRIVER_GAMEPAD_PORT);
	OperatorGamepad = new Gamepad(OPERATOR_GAMEPAD_PORT);
	
	//ChassisPart = new Chassis(Base, LeftDriveEncoder,RightDriveEncoder);
	
	
if(ENABLE_DEBUG)
	{
		CHAOSDebugger = new CHAOSDebug();
	}
else
	{
		Base = new RobotDrive(LEFT_FRONT_DRIVE_PORT, LEFT_BACK_DRIVE_PORT, RIGHT_FRONT_DRIVE_PORT, RIGHT_BACK_DRIVE_PORT);
		Base->SetSafetyEnabled(false);
	}

		
	//LeftDriveEncoder = new Encoder(LEFT_DRIVE_ENCODER_PORT_A, LEFT_DRIVE_ENCODER_PORT_B);
	//RightDriveEncoder = new Encoder(RIGHT_DRIVE_ENCODER_PORT_A, RIGHT_DRIVE_ENCODER_PORT_B);

	//ChassisPart = new Chassis();
	Mani = new Manipulator(Base);
	//Setup Watchdog
	
	
	GetWatchdog().SetExpiration(10.0);
	GetWatchdog().Feed();


}



void Main::TeleopPeriodic(void)
{
	//Feed Watchdog
	GetWatchdog().Feed();
	printf("in teleopContinuous\n");
	//smartDashboard->PutString("Location", "Main::TeleopContinuous()");
	//smartDashboard->PutNumber("Shooter Power", Mani->GetShooterSpeed());
	//printf("Slider 1's value is: %f",smartDashboard->GetNumber("Slider 1"));
	/*
	ConveyorTalon = new Talon(8);
	//HPRollerSpike = new Relay(1);
	IsShooterAligned = new DigitalInput(6);		//change this to test diferent light sensor
	*/
	
	
	//Main while loop of the Telop code
	
	//while(IsOperatorControl() && !IsDisabled()) 
	//{

		//Feed the watchdog every iteration of this while loop
		GetWatchdog().Feed();
		//smartDashboard->PutString("Location", "Main::TeleopContinuous->InMainLoop");
		
		
		if(ENABLE_DEBUG){
			printf("Main->CHAOSDebug");
			CHAOSDebugger->ControllerDebug();
			GetWatchdog().Feed();
		}
		else
		{
			CHAOSDebugger=NULL;
			
			smartDashboard->PutNumber("Shooter Power", Mani->GetShooterSpeed());
			smartDashboard->PutBoolean("light1", Mani->IsBottomFrisbeeAbsent->Get());
			smartDashboard->PutBoolean("light2", Mani->IsFrisbeeNotAtGate->Get());
			smartDashboard->PutBoolean("light3", Mani->IsFrisbeeNotAtIntake->Get());
			smartDashboard->PutBoolean("light4", Mani->IsShooterAligned->Get());
			smartDashboard->PutBoolean("light5", Mani->IsTopFrisbeeAbsent->Get());
			/*
			smartDashboard->PutBoolean("DIO6", Mani->DIO6->Get());
			smartDashboard->PutBoolean("DIO7", Mani->DIO7->Get());
			smartDashboard->PutBoolean("DIO8", Mani->DIO8->Get());//
			smartDashboard->PutBoolean("DIO9", Mani->DIO9->Get());
			smartDashboard->PutBoolean("DIO10", Mani->DIO10->Get());
			smartDashboard->PutBoolean("Encoder1", Mani->Encoder1A->Get());
			smartDashboard->PutBoolean("Encoder2", Mani->Encoder1B->Get());
			smartDashboard->PutBoolean("Encoder3", Mani->Encoder2A->Get());
			smartDashboard->PutBoolean("Encoder4", Mani->Encoder2B->Get());
			*/
			smartDashboard->PutNumber("Target Speed", Mani->GetTargetShooterSpeed());
			//smartDashboard->PutNumber("Encoder 1 Position", LeftDriveEncoder->GetDistance());
			//smartDashboard->PutNumber("Encoder 2 Position", RightDriveEncoder->GetDistance());
			smartDashboard->PutNumber("Shooter Period", Mani->GetShooterPeriod());
			
			smartDashboard->PutBoolean("Conveyor Running", Mani->ConveyorIsRunning());
			
			
			
			
			GetWatchdog().Feed();
			printf("Main->TankDrive\n");
			//Controls the chassis
			Base->SetSafetyEnabled(false);
			Base->TankDrive(DriverGamepad->GetLeftY(), DriverGamepad->GetRightY());
			GetWatchdog().Feed();
		
			//controls the shooter's speed
			
			printf("Main->ChangeShooterSpeed\n");
			
			if(OperatorGamepad->GetDPad() == Gamepad::kUp)
			{
				if (LastDirection != Gamepad::kUp)
				{
					//Mani->AddToShooterSpeed(SHOOTER_SPEED_NUDGE);
					Mani->AddToShooterTargetSpeed(-TARGET_SPEED_NUDGE);
					
				}
			}
			
			if(OperatorGamepad->GetDPad() == Gamepad::kDown)
			{
				if (LastDirection != Gamepad::kDown)
				{
					//Mani->SubtractFromShooterSpeed(SHOOTER_SPEED_NUDGE);
					Mani->AddToShooterTargetSpeed(TARGET_SPEED_NUDGE);
				}
			}
			
			LastDirection = OperatorGamepad->GetDPad();
			
			
			//ConveyorTalon->Set(1.0);
			//HPRollerSpike->Set(HPRollerSpike->kForward);
			
				//smartDashboard->PutNumber("DriverGamepadRY", DriverGamepad->GetRightY());
			//smartDashboard->PutNumber("DriverGamepadLY", DriverGamepad->GetLeftY());
			
			
			
			
			//printf("Manual Mode: %b\n",smartDashboard->GetBoolean("Manual Mode"));
			//if(!smartDashboard->GetBoolean("Manual Mode"))
			if(true)	
			{
				printf("Main->SpinShooter\n");				
				GetWatchdog().Feed();
				
				if(OperatorGamepad->GetNumberedButton(SHOOTER_SPIN_BUTTON))
				{
					printf("Mani->StartShooter();\n");
					Mani->StartShooter();
					
				}
				else if(!OperatorGamepad->GetNumberedButton(UNJAM_BUTTON)) //not jammed
				{
					printf("Mani->StopShooter();\n");
					Mani->StopShooter();
					
				}
				
				GetWatchdog().Feed();
				//controls the intake
				printf("Main->IntakeControl\n");
				
				if(OperatorGamepad->GetNumberedButton(INTAKE_BUTTON))
				{
					printf("Calling StartIntake()\n");
					Mani->StartIntake();
				}
				else if(OperatorGamepad->GetNumberedButton(UNJAM_BUTTON))
				{
					printf("Calling ClearIntake()\n");
					Mani->ClearIntake();
				}
				else
				{
					printf("Calling StopIntake\n");
					Mani->StopIntake();
					
				}
				GetWatchdog().Feed();
				
				
				

				//SHOOT!/ make my day...
				printf("Main->Make My Day\n");
				
				if(OperatorGamepad->GetNumberedButton(SHOOT_BUTTON))
				{
					Mani->Shoot();
				}
				else if(OperatorGamepad->GetNumberedButton(MANUAL_CONVEYOR_BUTTON))
				{
					Mani->ManualMode();
				}
				else if(!OperatorGamepad->GetNumberedButton(UNJAM_BUTTON) && !OperatorGamepad->GetNumberedButton(INTAKE_BUTTON))
				{
					Mani->DontShoot();
				
				}
				
				
				
				//GetWatchdog().Feed();
				
				
				
				// controls the reloading function
				printf("Main->Reloading\n");
				
				if(!OperatorGamepad->GetNumberedButton(UNJAM_BUTTON))
				{
					Mani->ReloadTop(); //only want to reload if not unjamming
				}
				
				Mani->ShooterSpeedControl();
			}
			else
			{
				//Mani->ManualMode(DriverGamepad,OperatorGamepad);
			}
		}
		printf("\n\n\n");
		GetWatchdog().Feed();
		

		
//	} //End of while

} //End of Teleop

void Main::AutonomousPeriodic(void)
{
	GetWatchdog().Feed();
	//smartDashboard->PutBoolean("IsEnabled", IsEnabled());
	//smartDashboard->PutBoolean("IsDisabled", IsDisabled());
	//smartDashboard->PutBoolean("IsAutonomous", IsAutonomous());
	printf("IsAutonomous %d\n" , IsAutonomous());
	//printf("IsDisabled %d\n" , IsDisabled());
	//printf("IsEnabled %d\n" , IsEnabled());
	//AutoTimer = new Timer();
	//AutoTimer->Start();
//	while(IsAutonomous() && !IsDisabled())
	//{
		
		GetWatchdog().Feed();
		printf("Auto State: %d\n", AutoState);
		
		//smartDashboard->PutString("Location", "Main::AutonomousContinuous()");
		
		
		
	
		printf("Auto->shooting\n");
		GetWatchdog().Feed();
		Mani->StartShooter();
		Mani->Shoot();
		Mani->ReloadTop();
		Mani->ShooterSpeedControl();
		
		smartDashboard->PutNumber("Shooter Power", Mani->GetShooterSpeed());
		smartDashboard->PutBoolean("light1", Mani->IsBottomFrisbeeAbsent->Get());
		smartDashboard->PutBoolean("light2", Mani->IsFrisbeeNotAtGate->Get());
		smartDashboard->PutBoolean("light3", Mani->IsFrisbeeNotAtIntake->Get());
		smartDashboard->PutBoolean("light4", Mani->IsShooterAligned->Get());
		smartDashboard->PutBoolean("light5", Mani->IsTopFrisbeeAbsent->Get());
		/*
		smartDashboard->PutBoolean("DIO6", Mani->DIO6->Get());
		smartDashboard->PutBoolean("DIO7", Mani->DIO7->Get());
		smartDashboard->PutBoolean("DIO8", Mani->DIO8->Get());//
		smartDashboard->PutBoolean("DIO9", Mani->DIO9->Get());
		smartDashboard->PutBoolean("DIO10", Mani->DIO10->Get());
		smartDashboard->PutBoolean("Encoder1", Mani->Encoder1A->Get());
		smartDashboard->PutBoolean("Encoder2", Mani->Encoder1B->Get());
		smartDashboard->PutBoolean("Encoder3", Mani->Encoder2A->Get());
		smartDashboard->PutBoolean("Encoder4", Mani->Encoder2B->Get());
		//*/
		smartDashboard->PutNumber("Target Speed", Mani->GetTargetShooterSpeed());
		//smartDashboard->PutNumber("Encoder 1 Position", LeftDriveEncoder->GetDistance());
		//smartDashboard->PutNumber("Encoder 2 Position", RightDriveEncoder->GetDistance());
		smartDashboard->PutNumber("Shooter Period", Mani->GetShooterPeriod());
		
		smartDashboard->PutBoolean("Conveyor Running", Mani->ConveyorIsRunning());
		printf("\n\n");
	
		/*printf("\n                Out of Auto->shoot\n\n");
		Mani->StopShooter();
		Mani->DontShoot();
		
		
		Mani->StartIntake();
		
		ChassisPart->EncoderDrive(AUTO_TARGET_DISTANCE, AUTO_TARGET_SPEED);
		
		ChassisPart->EncoderDrive(-AUTO_TARGET_DISTANCE, AUTO_TARGET_SPEED);
		Mani->StopIntake();*/
		//double SecondShotTime = AutoTimer->Get();
		/*
		while(AutoTimer->Get() < AUTO_SHOOT_TIME + SecondShotTime && (IsAutonomous() && !IsDisabled()))
		{
			printf("Auto->shooting again\n");
			GetWatchdog().Feed();
			Mani->StartShooter();
			Mani->Shoot();
			Mani->ReloadTop();
			Mani->ShooterSpeedControl();
			
			
			smartDashboard->PutNumber("Shooter Power", Mani->GetShooterSpeed());
			smartDashboard->PutBoolean("light1", Mani->IsBottomFrisbeeAbsent->Get());
			smartDashboard->PutBoolean("light2", Mani->IsFrisbeeNotAtGate->Get());
			smartDashboard->PutBoolean("light3", Mani->IsFrisbeeNotAtIntake->Get());
			smartDashboard->PutBoolean("light4", Mani->IsShooterAligned->Get());
			smartDashboard->PutBoolean("light5", Mani->IsTopFrisbeeAbsent->Get());
			//
			smartDashboard->PutBoolean("DIO6", Mani->DIO6->Get());
			smartDashboard->PutBoolean("DIO7", Mani->DIO7->Get());
			smartDashboard->PutBoolean("DIO8", Mani->DIO8->Get());//
			smartDashboard->PutBoolean("DIO9", Mani->DIO9->Get());
			smartDashboard->PutBoolean("DIO10", Mani->DIO10->Get());
			smartDashboard->PutBoolean("Encoder1", Mani->Encoder1A->Get());
			smartDashboard->PutBoolean("Encoder2", Mani->Encoder1B->Get());
			smartDashboard->PutBoolean("Encoder3", Mani->Encoder2A->Get());
			smartDashboard->PutBoolean("Encoder4", Mani->Encoder2B->Get());
			//
			smartDashboard->PutNumber("Target Speed", Mani->GetTargetShooterSpeed());
			//smartDashboard->PutNumber("Encoder 1 Position", LeftDriveEncoder->GetDistance());
			//smartDashboard->PutNumber("Encoder 2 Position", RightDriveEncoder->GetDistance());
			smartDashboard->PutNumber("Shooter Period", Mani->GetShooterPeriod());
			printf("\n\n");
		}
		Mani->StopShooter();
		Mani->DontShoot();
		//ChassisPart->DeadReckon(1,0,DRIVE_STRAIGHT_TIME);
		
		while(IsAutonomous() && !IsDisabled())
		{
			//Wait until teleop
		}
		
*/
//	}

}

void Main::DisabledPeriodic(void)
{
	Mani->StopReload();
	printf("You are in Main::DisabledContinuous\n");
	Base->TankDrive(0.0,0.0);
	
	smartDashboard->PutNumber("Shooter Power", Mani->GetShooterSpeed());
	smartDashboard->PutBoolean("light1", Mani->IsBottomFrisbeeAbsent->Get());
	smartDashboard->PutBoolean("light2", Mani->IsFrisbeeNotAtGate->Get());
	smartDashboard->PutBoolean("light3", Mani->IsFrisbeeNotAtIntake->Get());
	smartDashboard->PutBoolean("light4", Mani->IsShooterAligned->Get());
	smartDashboard->PutBoolean("light5", Mani->IsTopFrisbeeAbsent->Get());
	/*
	smartDashboard->PutBoolean("DIO6", Mani->DIO6->Get());
	smartDashboard->PutBoolean("DIO7", Mani->DIO7->Get());
	smartDashboard->PutBoolean("DIO8", Mani->DIO8->Get());//
	smartDashboard->PutBoolean("DIO9", Mani->DIO9->Get());
	smartDashboard->PutBoolean("DIO10", Mani->DIO10->Get());
	smartDashboard->PutBoolean("Encoder1", Mani->Encoder1A->Get());
	smartDashboard->PutBoolean("Encoder2", Mani->Encoder1B->Get());
	smartDashboard->PutBoolean("Encoder3", Mani->Encoder2A->Get());
	smartDashboard->PutBoolean("Encoder4", Mani->Encoder2B->Get());
	//*/
	smartDashboard->PutNumber("Target Speed", Mani->GetTargetShooterSpeed());
	//smartDashboard->PutNumber("Encoder 1 Position", LeftDriveEncoder->GetDistance());
	//smartDashboard->PutNumber("Encoder 2 Position", RightDriveEncoder->GetDistance());
	smartDashboard->PutNumber("Shooter Period", Mani->GetShooterPeriod());
	
	if(OperatorGamepad->GetDPad() == Gamepad::kUp)
	{
		if (LastDirection != Gamepad::kUp)
		{
			//Mani->AddToShooterSpeed(SHOOTER_SPEED_NUDGE);
			Mani->AddToShooterTargetSpeed(-TARGET_SPEED_NUDGE);
			
		}
	}
	
	if(OperatorGamepad->GetDPad() == Gamepad::kDown)
	{
		if (LastDirection != Gamepad::kDown)
		{
			//Mani->SubtractFromShooterSpeed(SHOOTER_SPEED_NUDGE);
			Mani->AddToShooterTargetSpeed(TARGET_SPEED_NUDGE);
		}
	}
	
	LastDirection = OperatorGamepad->GetDPad();
	
}

/*void Main::TeleopContinuous(void)
{
	//smartDashboard->PutString("Location", "Main::TeleopPeriodic()");
}*/
/*void Main::AutonomousPeriodic(void)
{

}*/
/*void Main::DisabledPeriodic(void)
{

}*/
void Main::RobotInit(void)
{
	


}
void Main::DisabledInit(void)
{
	//This code will run once every time the robot is brought back into Disabled
	printf("You are in Main::DisabledInit\n");
	//Misc::SystemDisabled = true;
	
}

void Main::AutonomousInit(void)
{
	printf("You are in Main::AutoInit\n");

	//Autonomous1 = // add digital toggle switch here  express ?  true: false;
	
	smartDashboard->PutBoolean("IsEnabled", IsEnabled());
	smartDashboard->PutBoolean("IsDisabled", IsDisabled());
	smartDashboard->PutBoolean("IsAutonomous", IsAutonomous());
	printf("IsAutonomous %d\n" , IsAutonomous());
	printf("IsDisabled %d\n" , IsDisabled());
	printf("IsEnabled %d\n" , IsEnabled());
	//AutoState =(int) smartDashboard->GetNumber("Auto Mode");
	//AutoState = 0;
	smartDashboard->PutNumber("Shooter Power", Mani->GetShooterSpeed());
	smartDashboard->PutBoolean("light1", Mani->IsBottomFrisbeeAbsent->Get());
	smartDashboard->PutBoolean("light2", Mani->IsFrisbeeNotAtGate->Get());
	smartDashboard->PutBoolean("light3", Mani->IsFrisbeeNotAtIntake->Get());
	smartDashboard->PutBoolean("light4", Mani->IsShooterAligned->Get());
	smartDashboard->PutBoolean("light5", Mani->IsTopFrisbeeAbsent->Get());
	/*
	smartDashboard->PutBoolean("DIO6", Mani->DIO6->Get());
	smartDashboard->PutBoolean("DIO7", Mani->DIO7->Get());
	smartDashboard->PutBoolean("DIO8", Mani->DIO8->Get());//
	smartDashboard->PutBoolean("DIO9", Mani->DIO9->Get());
	smartDashboard->PutBoolean("DIO10", Mani->DIO10->Get());
	smartDashboard->PutBoolean("Encoder1", Mani->Encoder1A->Get());
	smartDashboard->PutBoolean("Encoder2", Mani->Encoder1B->Get());
	smartDashboard->PutBoolean("Encoder3", Mani->Encoder2A->Get());
	smartDashboard->PutBoolean("Encoder4", Mani->Encoder2B->Get());
	//*/
	smartDashboard->PutNumber("Target Speed", Mani->GetTargetShooterSpeed());
	//smartDashboard->PutNumber("Encoder 1 Position", LeftDriveEncoder->GetDistance());
	//smartDashboard->PutNumber("Encoder 2 Position", RightDriveEncoder->GetDistance());
	smartDashboard->PutNumber("Shooter Period", Mani->GetShooterPeriod());
	//Misc::SystemDisabled = false;
	
	
	//Main::AutonomousContinuous();  //IterativeRobot appears not to call the continous functions
	
	
}

void Main::TeleopInit(void)
{


	printf("You are in Main::TeleopInit\n");

	smartDashboard->PutString("Location", "Main::TeleopInit()");

	smartDashboard->PutBoolean("IsEnabled", IsEnabled());
	smartDashboard->PutBoolean("IsDisabled", IsDisabled());
	smartDashboard->PutBoolean("IsOperatorControl", IsOperatorControl());
	printf("IsOperatorControl %d\n" , IsOperatorControl());
	printf("IsDisabled %d\n" , IsDisabled());
	printf("IsEnabled %d\n" , IsEnabled());
	
	//Misc::SystemDisabled = false;
	//Main::TeleopContinuous();  //IterativeRobot appears not to call the continous functions
	
}
/*
void Main::SendDashboard()
{
	smartDashboard->PutNumber("Shooter Power", Mani->GetShooterSpeed());
	smartDashboard->PutBoolean("light1", Mani->IsBottomFrisbeeAbsent->Get());
	smartDashboard->PutBoolean("light2", Mani->IsFrisbeeNotAtGate->Get());
	smartDashboard->PutBoolean("light3", Mani->IsFrisbeeNotAtIntake->Get());
	smartDashboard->PutBoolean("light4", Mani->IsShooterAligned->Get());
	smartDashboard->PutBoolean("light5", Mani->IsTopFrisbeeAbsent->Get());
	//
	smartDashboard->PutBoolean("DIO6", Mani->DIO6->Get());
	smartDashboard->PutBoolean("DIO7", Mani->DIO7->Get());
	smartDashboard->PutBoolean("DIO8", Mani->DIO8->Get());//
	smartDashboard->PutBoolean("DIO9", Mani->DIO9->Get());
	smartDashboard->PutBoolean("DIO10", Mani->DIO10->Get());
	smartDashboard->PutBoolean("Encoder1", Mani->Encoder1A->Get());
	smartDashboard->PutBoolean("Encoder2", Mani->Encoder1B->Get());
	smartDashboard->PutBoolean("Encoder3", Mani->Encoder2A->Get());
	smartDashboard->PutBoolean("Encoder4", Mani->Encoder2B->Get());
	//
	smartDashboard->PutNumber("Target Speed", Mani->GetTargetShooterSpeed());
	//smartDashboard->PutNumber("Encoder 1 Position", LeftDriveEncoder->GetDistance());
	//smartDashboard->PutNumber("Encoder 2 Position", RightDriveEncoder->GetDistance());
	smartDashboard->PutNumber("Shooter Period", Mani->GetShooterPeriod());
}
*/

START_ROBOT_CLASS(Main);
