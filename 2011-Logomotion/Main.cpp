/*-------------------------------------------------------------**
**                                                             
**   Filename: Main.cpp                                        
**                                                             
**   About:    The Main Logomotion Robot Class
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Steven Kroh 
**               Josh Allard
**               Ben Papp
**               Zain Abbas, Chaos.           
**                                                                                           
**   2011 1 16             
**                                                             
**-------------------------------------------------------------*/

#include "Main.h"

Main::Main(void)
{
	printf("YOU ARE IN MAIN::MAIN");
	//wpi_stackTraceOnAssertEnable(true);
	printf("StackTraceOn::MAIN");
	
	//RobotDrive
	Base = new RobotDrive(FRONT_LEFT_DRIVE_PORT, REAR_LEFT_DRIVE_PORT, FRONT_RIGHT_DRIVE_PORT, REAR_RIGHT_DRIVE_PORT);                               
	
	//Line Trackers
	UpperLineTracker = new DigitalInput(DIO_MODULE1, UPPER_LINE_TRACKER_PORT);
	LowerLineTracker = new DigitalInput(DIO_MODULE1, LOWER_LINE_TRACKER_PORT);
	
	//Gamepads
	DriverGamepad = new Gamepad(DRIVER_GAMEPAD_PORT);
	OperatorGamepad = new Gamepad(OPERATOR_GAMEPAD_PORT);
	
	//Dashboard Sharing and Dashboard
	DashData = new DashSharing();
	Dash = new DashboardDataSender(DashData);
	
	//Uncomment to Enable the Logging Device
	//DataLogger = new Logger(DashData);
	
	//Setting up the Gyro
	LineFollowingGyro = new Gyro(ANALOG_MODULE1, TURN_CONTROLLER_GYRO_CHANNEL);
	LineFollowingGyro->Reset();
	
	//Compressor
	PneumaticCompressor = new Compressor(COMPRESSOR_PRESSURE_SWITCH_CHANNEL, COMPRESSOR_RELAY_CHANNEL);
	
	//Minibot
	MinibotPart = new Minibot();
	

	
	//Ultrasonics
	LeftUltrasonic = new Ultrasonic(LEFT_ULTRASONIC_PING, LEFT_ULTRASONIC_ECHO);
	RightUltrasonic = new Ultrasonic(RIGHT_ULTRASONIC_PING, RIGHT_ULTRASONIC_ECHO);
	
	MaxbotixUltrasonic = new AnalogChannel(ANALOG_MODULE1, MAXBOTIX_ULTRASONIC);
	
	//Make one ultrasonic Automatic to prevent multiple kernel errors
	LeftUltrasonic->SetAutomaticMode(true);
	
	//Wall Align Ultrasonic Averaging Engine
	WallAlign = new UltrasonicYAlign(LeftUltrasonic, RightUltrasonic);
	
	//Various timers
	TeleopLoopTimer = new Timer();
	AutoLoopTimer = new Timer();
	AutoTimeOut = new Timer();
	
	//Manipulator
	ManipulatorDevice = new Manipulator(DriverGamepad, OperatorGamepad, DashData);
	
	//Initialization of the Autonomous PegZSetting
	PegZSetting = Main::PEG_Z_NORMAL;
	
	//Limit Switch used to change the PegZSetting in Autonomous
	AutonomousLimitSwitch = new DigitalInput(DIO_MODULE1, AUTONOMOUS_PEG_HEIGHT_LIMIT_SWITCH_CHANNEL);
	
	//Edge detection for Manual Mode
	CurrentManualMode = false;
	PreviousManualMode = false;
	
	//Human Player Light Indicators
	IndicatorRedWhite = new Relay(DIO_MODULE1, INDICATOR_LIGHT_RELAY_REDWHITE, Relay::kBothDirections);
	IndicatorBlue = new Relay(DIO_MODULE1, INDICATOR_LIGHT_RELAY_BLUE, Relay::kForwardOnly);
	
	//Tube Shuttle
	ShuttleSolenoid = new Solenoid(SOLENOID_MODULE1, SHUTTLE_SOLENOID_PORT);
	ShuttleSolenoid->Set(false);

	//Setup Watchdog
	GetWatchdog().SetExpiration(10.0);
}
	
void Main::TeleopContinuous(void)
{
	//Feed Watchdog
	GetWatchdog().Feed();
	printf("You are in Main::Test:1\n");
	//Main while loop of the Telop code
	while(IsOperatorControl() && !IsDisabled()) 
	{ 
		//Feed the watchdog ever iteration of this while loop
		GetWatchdog().Feed();
		
		//Begin Loop Time Regulation
		TeleopLoopTimer->Start();
		printf("You are in Main::Test:2\n");
        //Highest Level Drive Controls
		//****************************
		
		DashData->LeftInches_D = (float )GetMaxbotixDistance();
		
		printf("You are in Main::Test:3\n");
		
		//Drive Code
		if(DriverGamepad->GetNumberedButton(BTN_SERVO_LEFT) == true)
		{
			//ServoLeft
			if((UpperLineTracker->Get() == true ) || (LowerLineTracker->Get() == true))
			{
				Base->TankDrive(SERVO_STOP_SPEED, SERVO_STOP_SPEED);	
			}
			else
			{
				Base->TankDrive(SERVO_TURNING_SPEED, -SERVO_TURNING_SPEED);
			}
		}
		else if(DriverGamepad->GetNumberedButton(BTN_SERVO_RIGHT) == true)
		{
			//ServoRight
			if((UpperLineTracker->Get() == true ) || (LowerLineTracker->Get() == true))
			{
				Base->TankDrive(SERVO_STOP_SPEED, SERVO_STOP_SPEED);
			}
			else
			{
				Base->TankDrive(-SERVO_TURNING_SPEED, SERVO_TURNING_SPEED);
			}
		}
		else
		{
			//Driver Joystick Commands
			Base->TankDrive((DriverGamepad->GetLeftY()), (DriverGamepad->GetRightY()));	
		}
		
//LinerTracker Display
		
//		if((UpperLineTracker->Get() == true) || (LowerLineTracker->Get() == true))
//		{
//			IndicatorRedWhite->Set(Relay::kForward);
//			IndicatorRedWhite->Set(Relay::kReverse);
//			IndicatorBlue->Set(Relay::kOn);
//		}
//		else
//		{
//	
//			if((OperatorGamepad->GetNumberedButton(BTN_INDICATE_RED)) && (DriverGamepad->GetNumberedButton(BTN_INDICATE_WHITE)))
//			{
//				//IndicatorRedWhite->Set(Relay::kOn);
//				RedLightStatus1 = true;
//				WhiteLightStatus1 = true;
//			}
//			else if(OperatorGamepad->GetNumberedButton(BTN_INDICATE_RED))
//			{
//				IndicatorRedWhite->Set(Relay::kForward);
//				RedLightStatus1 = true;
//			}
//			else if(OperatorGamepad->GetNumberedButton(BTN_INDICATE_WHITE))
//			{
//				IndicatorRedWhite->Set(Relay::kReverse);
//				WhiteLightStatus1 = true;
//			}
//			else
//			{
//				IndicatorRedWhite->Set(Relay::kOff);
//			}
//			
//			if(OperatorGamepad->GetNumberedButton(BTN_INDICATE_BLUE))
//			{
//				IndicatorBlue->Set(Relay::kForward);
//			}
//			else
//			{
//				IndicatorBlue->Set(Relay::kOff);
//			}
//			
//		}
		
		//Line Tracking Indicator Lights w/ Edge Detection
		if((OperatorGamepad->GetNumberedButton(BTN_INDICATE_RED) == true) && (RedLightLatch == false))
		{
			if(RedLightCommand == false)
			{
				RedLightCommand = true;
				RedLightLatch = true;

				WhiteLightCommand = false;
				BlueLightCommand = false;
			}
			else
			{
				RedLightCommand = false;
				RedLightLatch = true;	
			}
		}
		if((OperatorGamepad->GetNumberedButton(BTN_INDICATE_RED) != true))
		{
			RedLightLatch = false;
		}
		
		if((OperatorGamepad->GetNumberedButton(BTN_INDICATE_WHITE) == true) && (WhiteLightLatch == false))
		{
			if(WhiteLightCommand == false)
			{
				WhiteLightCommand = true;
				WhiteLightLatch = true;
				
				RedLightCommand = false;
				BlueLightCommand = false;
			}
			else
			{
				WhiteLightCommand = false;
				WhiteLightLatch = true;	
			}
		}
		if((OperatorGamepad->GetNumberedButton(BTN_INDICATE_WHITE) != true))
		{
			WhiteLightLatch = false;
		}
		if((OperatorGamepad->GetNumberedButton(BTN_INDICATE_BLUE) == true) && (BlueLightLatch == false))
		{
			if(BlueLightCommand == false)
			{
				BlueLightCommand = true;
				BlueLightLatch = true;
				
				RedLightCommand = false;
				WhiteLightCommand = false;
			}
			else
			{
				BlueLightCommand = false;
				BlueLightLatch = true;	
			}
		}
		if((OperatorGamepad->GetNumberedButton(BTN_INDICATE_BLUE) != true))
		{
			BlueLightLatch = false;
		}			
		if((UpperLineTracker->Get() == true) || (LowerLineTracker->Get() == true))
		{
			IndicatorRedWhite->Set(Relay::kForward);
			IndicatorRedWhite->Set(Relay::kReverse);
			IndicatorBlue->Set(Relay::kForward);
		}
		else
		{
			if(RedLightCommand == true)
			{
				IndicatorRedWhite->Set(Relay::kForward);	
				IndicatorBlue->Set(Relay::kOff);
			}
			else if(WhiteLightCommand == true)
			{
				IndicatorRedWhite->Set(Relay::kReverse);
				IndicatorBlue->Set(Relay::kOff);
			}
	
			else if(BlueLightCommand == true)
			{
				IndicatorBlue->Set(Relay::kForward);
				IndicatorRedWhite->Set(Relay::kOff);
			}
			else
			{
				IndicatorBlue->Set(Relay::kOff);
				IndicatorRedWhite->Set(Relay::kOff);
			}
		}
		
		//Minibot Deploy Code
		CurrentFlapButton = DriverGamepad->GetNumberedButton(BTN_FLAP_INDEX);		
		if((CurrentFlapButton == true) && (PreviousFlapButton == false))
		{
			MinibotPart->Signal(Minibot::MINIBOT_STATE_DEPLOY_FLAP_SERVO);
		}
		else if(DriverGamepad->GetNumberedButton(BTN_DEPLOY_MINIBOT) && (MinibotPart->AllowDeploy))
		{
			MinibotPart->Signal(Minibot::MINIBOT_STATE_DEPLOY_BOT);
		}
		PreviousFlapButton = CurrentFlapButton;
		
		//Manual Mode Edge Test
		CurrentManualMode = OperatorGamepad->GetNumberedButton(BTN_MANUAL_ACTIVATE);
		if(CurrentManualMode != PreviousManualMode)
		{
			if(CurrentManualMode == true)
			{
				ManipulatorDevice->Signal(Manipulator::MANIP_STATE_MANUAL);
			    ManipulatorDevice->ElbowPart->ElbowManualCheckInitial = true;
			}
			else if(CurrentManualMode == false)
			{
				ManipulatorDevice->ElbowPart->ElbowManualCheckInitial = false;
				ManipulatorDevice->Signal(Manipulator::MANIP_STATE_DISABLED);
				ManipulatorDevice->ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_DISABLE);
			}
		}
		PreviousManualMode = CurrentManualMode;
		
		//Set Center/Normal Positions for Manipulator State Machine
		if(OperatorGamepad->GetNumberedButton(BTN_CENTER_PEGS))
		{
			PegZSetting = PEG_Z_CENTER;
		}
		else if(OperatorGamepad->GetNumberedButton(BTN_NORMAL_PEGS))
		{
			PegZSetting = PEG_Z_NORMAL;
		}
		
		//Based on the above, set the row setting
		switch(PegZSetting)
		{
		    case PEG_Z_CENTER:
		    	
		    	if(OperatorGamepad->GetDPad() == Gamepad::kUp)
				{
					ManipulatorDevice->NextPegZ = Manipulator::PEG_Z_STATE_TOP_CENT;
				}
				else if(OperatorGamepad->GetDPad() == Gamepad::kLeft)
				{
					ManipulatorDevice->NextPegZ = Manipulator::PEG_Z_STATE_MIDDLE_CENT;
				}
				else if(OperatorGamepad->GetDPad() == Gamepad::kRight)
				{
					ManipulatorDevice->NextPegZ = Manipulator::PEG_Z_STATE_PICKUP_HP;
				}
				else if(OperatorGamepad->GetDPad() == Gamepad::kDown)
				{
					ManipulatorDevice->NextPegZ = Manipulator::PEG_Z_STATE_BOTTOM_CENT;
				}
		    	break;
		    
		    case PEG_Z_NORMAL:
		    	
				if(OperatorGamepad->GetDPad() == Gamepad::kUp)
				{
					ManipulatorDevice->NextPegZ = (Manipulator::PEG_Z_STATE_TOP_NORM);
				}
				else if(OperatorGamepad->GetDPad() == Gamepad::kLeft)
				{
					ManipulatorDevice->NextPegZ = (Manipulator::PEG_Z_STATE_MIDDLE_NORM);
				}
				else if(OperatorGamepad->GetDPad() == Gamepad::kRight)
				{
					ManipulatorDevice->NextPegZ = (Manipulator::PEG_Z_STATE_PICKUP_HP);
				}
				else if(OperatorGamepad->GetDPad() == Gamepad::kDown)
				{
					ManipulatorDevice->NextPegZ = (Manipulator::PEG_Z_STATE_BOTTOM_NORM);
				}
				break;
				
		    default:
		    	PegZSetting = PEG_Z_NORMAL;
		    	break;
		}
		
		CurrentShuttleButton = OperatorGamepad->GetNumberedButton(BTN_SHUTTLE);
		if((CurrentShuttleButton == true) && (PreviousShuttleButton == false))
		{
			if(ShuttleStatus == false)
			{
				ShuttleStatus = true;
				ShuttleSolenoid->Set(true);
			}
			else
			{
				ShuttleStatus = false;
				ShuttleSolenoid->Set(false);
			}
		}
		PreviousShuttleButton = CurrentShuttleButton;
		
		printf("You are in Main::Test:4\n");
		//Run the sub-state machines of Main
		ManipulatorDevice->StateMachine();
		MinibotPart->StateMachine();
			
		//Push Dash Data to the Dashboard 
		//DashData->LeftInches_D = LeftUltrasonic->GetRangeInches();
		DashData->RightInches_D = RightUltrasonic->GetRangeInches();
		DashData->AvgInches_D = WallAlign->GetAvgDistance();
		DashData->UltraAngle_D = WallAlign->GetAngle();
		DashData->UpperLineTracker_D = UpperLineTracker->Get();
		DashData->LowerLineTracker_D = LowerLineTracker->Get();
		
		printf("You are in Main::Test:5\n");
		
		//printf("LeftRightInches: %f, %f\n", DashData->LeftInches_D, DashData->RightInches_D);
		//printf("AvgDistance %f | Angle %f\n", WallAlign->GetAvgDistance(), WallAlign->GetAngle());
		DashData->LineFollowingGyroAngle_D = LineFollowingGyro->GetAngle();
		
		printf("You are in Main::Test:6\n");
		
		//Send Dashboard Data
		//Dash->sendIOPortData();
		
		printf("You are in Main::Test:7\n");
		
		//Regulate Loop Time
		if(TeleopLoopTimer->Get() < TELEOP_PERIOD)
		{
			while(TELEOP_PERIOD - TeleopLoopTimer->Get() > 0)
			{
				GetWatchdog().Feed();
			}
		}
		else
		{
			printf("Teleop Period NOT RESPECTED : CODE TAKES TOO LONG\n");
		}
		printf("You are in Main::Test:8\n");
		TeleopLoopTimer->Reset();

	} //End of while

} //End of Teleop

void Main::AutonomousContinuous(void)
{
	GetWatchdog().Feed();
	
	while(IsAutonomous() && !IsDisabled())
	{
		
		DashData->LeftInches_D = (float )GetMaxbotixDistance();
		MinibotPart->StateMachine();
		
		//Feed the watchdog
		GetWatchdog().Feed();
		
		//Star the Autonomous Loop Time Regulation
		AutoLoopTimer->Start();
		
		//printf("In Autonomous while loop\n");
		
		//Push Dash Data to the Dashboard
		//DashData->LeftInches_D = LeftUltrasonic->GetRangeInches();
		DashData->RightInches_D = RightUltrasonic->GetRangeInches();
		DashData->AvgInches_D = WallAlign->GetAvgDistance();
		DashData->UltraAngle_D = WallAlign->GetAngle();
		DashData->UpperLineTracker_D = UpperLineTracker->Get();
		DashData->LowerLineTracker_D = LowerLineTracker->Get();
		DashData->CurrentAutoState_D = CurrentAutoState;
		
		DashData->LineFollowingGyroAngle_D = LineFollowingGyro->GetAngle();
		
		//printf("LeftRightInches: %f, %f\n", DashData->LeftInches_D, DashData->RightInches_D);
		
		switch(NextAutoState)
		{ 
			case AUTO_STATE_BEGIN:
				
				if(CurrentAutoState != NextAutoState)
				{
					AutoTimeOut->Start();
					LineFollowingGyro->Reset();
				}
				
				CurrentAutoState = AUTO_STATE_BEGIN;
				
				if(AutoTimeOut->Get() >= BEGIN_TIME_OUT_TIME)
				{
					//NextAutoState = AUTO_STATE_FORWARD;
					NextAutoState = AUTO_STATE_DEAD_RECKON;
					AutoTimeOut->Stop();
					AutoTimeOut->Reset();
				}
				
				break;
				
			case AUTO_STATE_DEAD_RECKON:
				
				if(CurrentAutoState != NextAutoState)
				{
					AutoTimeOut->Reset();
					AutoTimeOut->Start();
					
					if(PegZSetting == Main::PEG_Z_CENTER)
					{
						ManipulatorDevice->NextPegZ = (Manipulator::PEG_Z_STATE_TOP_CENT);
						ManipulatorDevice->Signal(Manipulator::MANIP_STATE_GO_TO_PEG_HEIGHT);
					}
					else
					{
					
						ManipulatorDevice->NextPegZ = (Manipulator::PEG_Z_STATE_TOP_NORM);
						ManipulatorDevice->Signal(Manipulator::MANIP_STATE_GO_TO_PEG_HEIGHT);						
					}
				}
				
				CurrentAutoState = AUTO_STATE_DEAD_RECKON;
				
				AngleCorrectionModification = (LineFollowingGyro->GetAngle() * ANGLE_CORRECTION_PROPORTION);
				
				if(AutoTimeOut->Get() >= AUTO_DEAD_RECKON_TIME)
				{
					AutoTimeOut->Stop();
					AutoTimeOut->Reset();
					Base->TankDrive(AUTO_STOP, AUTO_STOP);
					NextAutoState = AUTO_STATE_POSITION_ROBOT;
				}
				else
				{
					Base->TankDrive((AUTO_DEAD_RECKON_SPEED + AngleCorrectionModification), (AUTO_DEAD_RECKON_SPEED - AngleCorrectionModification));
				}
				
			    break;
			    
			case AUTO_STATE_POSITION_ROBOT:
				if(CurrentAutoState != NextAutoState)
				{
					AutoTimeOut->Start();
				}
				

				CurrentAutoState = AUTO_STATE_POSITION_ROBOT;
				
				AngleCorrectionModification = (LineFollowingGyro->GetAngle() * ANGLE_CORRECTION_PROPORTION);
								

				if(AutoTimeOut->Get() >= POSITION_ROBOT_MOVE_TIMEOUT)
				{
					AutoTimeOut->Stop();
					NextAutoState =  AUTO_STATE_POSITION_ROBOT_PAUSE;
					AutoTimeOut->Reset();
					Base->TankDrive(AUTO_STOP, AUTO_STOP);
				}
				else
				{
					Base->TankDrive((AUTO_POSITION_ROBOT_SPEED + AngleCorrectionModification), (AUTO_POSITION_ROBOT_SPEED - AngleCorrectionModification));
				}
				
				
				break;
				
			case AUTO_STATE_POSITION_ROBOT_PAUSE:
				
				if(CurrentAutoState != NextAutoState)
				{
					AutoTimeOut->Start();
				}
				CurrentAutoState = AUTO_STATE_POSITION_ROBOT_PAUSE;
				if(AutoTimeOut->Get() >= POSITION_ROBOT_PAUSE_TIMEOUT)
				{
					
					AutoTimeOut->Stop();
					AutoTimeOut->Reset();
					
					//if(WallAlign->GetAvgDistance() <= UltraSonicDistance)
					if(GetMaxbotixDistance() <= UltraSonicDistance)
					{
						if(SonarGoodCount >= 3)
						{
							NextAutoState = AUTO_STATE_ALLIGN_LEFT;
							
						}
						else
						{
							SonarGoodCount++;
							NextAutoState = AUTO_STATE_POSITION_ROBOT_PAUSE;
							AutoTimeOut->Start();
						}
					}
					else
					{
						NextAutoState = AUTO_STATE_POSITION_ROBOT;
						SonarGoodCount = 0;
					}
				}
				break;
			    
			case AUTO_STATE_FORWARD:

				if(CurrentAutoState != NextAutoState)
				{
					if(PegZSetting == Main::PEG_Z_CENTER)
					{
						ManipulatorDevice->NextPegZ = (Manipulator::PEG_Z_STATE_TOP_CENT);
						ManipulatorDevice->Signal(Manipulator::MANIP_STATE_GO_TO_PEG_HEIGHT);
					}
					else
					{
						ManipulatorDevice->NextPegZ = (Manipulator::PEG_Z_STATE_TOP_NORM);
						ManipulatorDevice->Signal(Manipulator::MANIP_STATE_GO_TO_PEG_HEIGHT);						
					}
				}
				
				if(WallAlign->GetAvgDistance() <= SLOWING_DISTANCE)
				{
					PercentNumerator = (SLOWING_DISTANCE - WallAlign->GetAvgDistance());
					PercentDenominator = (SLOWING_DISTANCE - SCORE_DISTANCE);
					PercentPower = (INITIAL_AUTO_SPEED - ((PercentNumerator * AUTO_PROPORTION_FOR_END_SPEED)/ (PercentDenominator * 100)));
					Base->TankDrive(PercentPower, PercentPower);
				}
				else
				{
					Base->TankDrive(INITIAL_AUTO_SPEED, INITIAL_AUTO_SPEED);
					printf("In else\n");
				}
				CurrentAutoState = AUTO_STATE_FORWARD;
				
				if(WallAlign->GetAvgDistance() <= SCORE_DISTANCE)
				{
					NextAutoState = AUTO_STATE_ALLIGN_LEFT;
				}
				break;
				
			case AUTO_STATE_ALLIGN_RIGHT:
				
				if(CurrentAutoState != NextAutoState)
				{
					AutoTimeOut->Start();
				}
		
				Base->TankDrive(AUTO_TURNING_SPEED, -AUTO_TURNING_SPEED);
				CurrentAutoState = AUTO_STATE_ALLIGN_RIGHT;
				
//				Code to Detect only the Center or Normal peg
//				if(PegZSetting == Main::PEG_Z_CENTER)
//				{
//					if(UpperLineTracker->Get())
//					{
//						NextAutoState = AUTO_STATE_TARGETTED;
//					}
//				}
//				else
//				{
//					if(LowerLineTracker->Get())
//					{
//						NextAutoState = AUTO_STATE_TARGETTED;
//					}
//				}
				
				//Detect the Retroreflective tape on the peg
				if(UpperLineTracker->Get() || LowerLineTracker->Get())
				{
					NextAutoState = AUTO_STATE_TARGETTED;
				}
				
				//If timeout, switch back to the Left Direction
				if(AutoTimeOut->Get() >= (AUTO_STATE_TIMEOUT_RIGHT * 2.5))
				{				
					AutoTimeOut->Stop();
					NextAutoState =  AUTO_STATE_ALLIGN_LEFT;
					AutoTimeOut->Reset();
				}
				break;
				
			case AUTO_STATE_ALLIGN_LEFT:
				if(CurrentAutoState != NextAutoState)
				{
					AutoTimeOut->Start();

				}
			
				Base->TankDrive(-AUTO_TURNING_SPEED, AUTO_TURNING_SPEED);
				CurrentAutoState = AUTO_STATE_ALLIGN_LEFT;
			
//				Code to Detect only the Center or Normal peg
//				if(PegZSetting == Main::PEG_Z_CENTER)
//				{
//					if(UpperLineTracker->Get())
//					{
//						NextAutoState = AUTO_STATE_TARGETTED;
//					}
//				}
//				else
//				{
//					if(LowerLineTracker->Get())
//					{
//						NextAutoState = AUTO_STATE_TARGETTED;
//					}
//				}
				
				//Detect the Retroreflective tape on the peg
				if(UpperLineTracker->Get() || LowerLineTracker->Get())
				{
					NextAutoState = AUTO_STATE_TARGETTED;
				}
				
				//If timeout, switch back to the Left Direction
				if(AutoTimeOut->Get() >= (AUTO_STATE_TIMEOUT_LEFT))
				{				
					AutoTimeOut->Stop();
					NextAutoState =  AUTO_STATE_ALLIGN_RIGHT;
					AutoTimeOut->Reset();
				}
				break;
				
			case AUTO_STATE_TARGETTED:
				
				Base->TankDrive(AUTO_STOP, AUTO_STOP);
				NextAutoState = AUTO_STATE_SCORE;
				
				break;	
				
			case AUTO_STATE_SCORE:
				
				if(NextAutoState != CurrentAutoState)
				{
					ManipulatorDevice->Signal(Manipulator::MANIP_STATE_AUTO_PRE_SCORE);
				}
				
				if(ManipulatorDevice->Check() == Manipulator::MANIP_STATE_PAUSE_FOR_BACKUP)
				{
					NextAutoState = AUTO_STATE_BACKUP;
				}
				
				CurrentAutoState = AUTO_STATE_SCORE;
				break;
				
			case AUTO_STATE_BACKUP:
				
				if(ManipulatorDevice->Check() == Manipulator::MANIP_STATE_STOW)
				{
					Base->TankDrive(AUTO_STOP, AUTO_STOP);
				}
				else
				{
					Base->TankDrive(AUTO_BACKUP, AUTO_BACKUP);
				}
				
				CurrentAutoState = AUTO_STATE_BACKUP;
				
				break;
				
			case AUTO_STATE_INIT:
				break;
		}
		
		Dash->sendIOPortData();
		
		ManipulatorDevice->StateMachine();
		
		//Regulate Loop Time
		if(AutoLoopTimer->Get() < AUTO_PERIOD)
		{
			printf("AUTO PERIOD LOOP RESPECTED\n");
			
			while(AUTO_PERIOD - AutoLoopTimer->Get() > 0)
			{
				GetWatchdog().Feed();
			}
		}
		else
		{
			printf("AUTO Period NOT RESPECTED : CODE TAKES TOO LONG\n");
		}
		
		AutoLoopTimer->Reset();
	}
}

void Main::DisabledContinuous(void)
{
	//printf("You are in Main::DisabledContinuous\n");
}

void Main::TeleopPeriodic(void)
{
	
}
void Main::AutonomousPeriodic(void)
{
	
}
void Main::DisabledPeriodic(void)
{
	
}
void Main::RobotInit(void)
{
	//When robot is turned on, enable the compressor
	PneumaticCompressor->Start();
}
void Main::DisabledInit(void)
{
	//This code will run once every time the robot is brought back into Disabled
	
	//When you disable the robot, Disable the ManipulatorDevice
	ManipulatorDevice->Signal(Manipulator::MANIP_STATE_DISABLED);
	
	//Reset Edge Detection on the Autonomous States System
	NextAutoState = AUTO_STATE_BEGIN;
	CurrentAutoState = AUTO_STATE_INIT;
	
	//Reset Edge Detection on the ChangePegZ System
	ManipulatorDevice->CurrentPegZ = Manipulator::PEG_Z_STATE_INIT;
	
	//Disable the Minibot System
	MinibotPart->NextMinibotState = Minibot::MINIBOT_STATE_INIT;
}

void Main::AutonomousInit(void)
{
	MinibotPart->FlapPinServo->Set(FLAP_PIN_INIT_ANGLE);
	
	//This code will run once every time the robot is brought back into Autonomous
	
	//Reset Edge detection on the Autonomous States
	MinibotPart->Signal(Minibot::MINIBOT_STATE_INIT);
	
	NextAutoState = AUTO_STATE_BEGIN;
	CurrentAutoState = AUTO_STATE_INIT;
	
	ShuttleStatus = false;
	ShuttleSolenoid->Set(false);
	
	//Set the Autonomous PegZ Setting
	//It will always go to the top row, but change the center/normal positions
	if(!AutonomousLimitSwitch->Get())
	{
		PegZSetting = Main::PEG_Z_CENTER;
		UltraSonicDistance = CENTER_PEG_DISTANCE;
		
	}
	else
	{
		PegZSetting = Main::PEG_Z_NORMAL;
		UltraSonicDistance = NORMAL_PEG_DISTANCE;
	}
	
	SonarGoodCount = 0;
}

void Main::TeleopInit(void)
{
	//This code will run once every time the robot is brought back into Teleop
	
	//Turn off minibot valves
	MinibotPart->Signal(Minibot::MINIBOT_STATE_INIT);
	
	//Setup Elbow-Manual Requesting System
	ManipulatorDevice->ElbowPart->ElbowManualCheckInitial = false;
	ManipulatorDevice->ElbowPart->ElbowManualCheckSecondary = false;
	//ManipulatorDevice->ElbowPart->Signal(Elbow::ELBOW_STATE_CORRECT_ANGLE);
	
	//Initialize Flow Variables for the Human Player Indicator Light System
	RedLightCommand = false;
	RedLightLatch = false;
	BlueLightCommand = false;
	BlueLightLatch = false;
	WhiteLightCommand = false;
	WhiteLightLatch = false;

	//Initialize Edge Detection for the Minibot Deployment System
	CurrentFlapButton = false;
	PreviousFlapButton = false;
	
	ShuttleStatus = false;
	ShuttleSolenoid->Set(false);
	
	MinibotPart->FlapPinServo->Set(FLAP_PIN_INIT_ANGLE);
	
	printf("You are in Main::TeleopInit\n");
}

float Main::GetMaxbotixDistance(void)
{
	return (MaxbotixUltrasonic->GetVoltage() * (MAXBOTIX_MAX_DISTANCE / MAXBOTIX_MAX_VOLTAGE));
}



START_ROBOT_CLASS(Main);
