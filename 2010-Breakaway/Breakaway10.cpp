#include "Breakaway10.h"

Breakaway10::Breakaway10(void) : /*turnController(0.1, 0.00, 0.5, gyro, pidOutput, 0.005),*/ camera(AxisCamera::GetInstance()), dseio(DriverStation::GetInstance()->GetEnhancedIO())
{
	printf("Robot Constructor\b\n");
	
	//Autonomous Kicker Interface Initializers
	AutoInterface = new AutonomousKickerInterface; //struct, not class
	AutoInterface->AutoKickerShoot = false;
	AutoInterface->AutoKickerStow = false;
	
	//Robot Base Drive Initializers:
	base = new RobotDrive(FRONT_LEFT_TRANSMISSION_MOTOR_CHANNEL, REAR_LEFT_TRANSMISSION_MOTOR_CHANNEL, FRONT_RIGHT_TRANSMISSION_MOTOR_CHANNEL, REAR_RIGHT_TRANSMISSION_MOTOR_CHANNEL);                               
	base->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	base->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	base->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
	base->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	
	//Gamepad Initializers:
	printf("Robot Constructor -> Gamepads\b\n");
	driverStick = new Gamepad(GAMEPAD_DRIVER);
	operatorStick = new Gamepad(GAMEPAD_OPERATOR);
	
	//Gyro Initializers:
	printf("Robot Constructor -> Gyro\b\n");
	gyro = new Gyro(ANALOG_MODULE1, TURN_CONTROLLER_GYRO_CHANNEL);
	
	//PID Output Initializers:
	printf("Robot Constructor -> PID Output\b\n");
	pidOutput = new SamplePIDOutput(base);
	
	//TurnController Initializers USES PID OUTPUT, USES GYRO
	turnController = new PIDController(0.1, 0.00, 0.5, gyro, pidOutput, 0.005);	

	//Compressor Initializers:
	printf("Robot Constructor -> Compressor\b\n");
	compressor = new Compressor(COMPRESS_PRESSURE_SWITCH_CHANNEL, COMPRESS_RELAY_CHANNEL);
	
	//Encoder Initializers:
	printf("Robot Constructor -> Encoders\b\n");
	leftEncoder = new Encoder(DIO_MODULE1, LEFT_MOTOR_ENCODER_CHANNEL_A, DIO_MODULE1, LEFT_MOTOR_ENCODER_CHANNEL_B, true);
	leftEncoder->SetDistancePerPulse(ENCODER_DISTANCEPERPULSE);
	rightEncoder = new Encoder(DIO_MODULE1, RIGHT_MOTOR_ENCODER_CHANNEL_A, DIO_MODULE1, RIGHT_MOTOR_ENCODER_CHANNEL_B, false);
	rightEncoder->SetDistancePerPulse(ENCODER_DISTANCEPERPULSE);
	
	//Ultrasonic Initializers:
	printf("Robot Constructor -> Ultrasonic\b\n");
	ballDistanceUltrasonic = new Ultrasonic(DIO_MODULE1, ULTRASONIC_BALL_DIGOUT_CHANNEL, DIO_MODULE1, ULTRASONIC_BALL_DIGIN_CHANNEL);
	//Dash Sharing Initializers:
	DashData = new DashSharing();
	
	//Dashboard Initializers: USES DASH DATA
	printf("Robot Constructor -> Dashboard\b\n");
	dds = new DashboardDataSender(DashData);
	
	//Dribbler Initializers: USES DASH DATA
	dribbler = new Dribbler(DashData, leftEncoder, rightEncoder, driverStick);
    KLPot_Value = 0.0;
    KRPot_Value = 0.0;
	ALPot_Value = 0.0;
	ARPot_Value = 0.0;
	
	//KickerInitializers:
	ChaosKicker = new Kicker(driverStick, operatorStick, DashData, AutoInterface);
	
	//Ball Initializer
	Ball = new SoccerBall(ballDistanceUltrasonic, base, gyro);
	
	//Various Autonomous Objects
	AutoSafeGuardTimer = new Timer();
	AutonomousTargetDistance = 0.0;
	TargetHorizontalAngle = 0.0;
	AutonomousPot = 0.0;
	AutonomousExtendDistance = 0.0;
	
	ScanResult = SoccerBall::SCAN_SUCCESS__NO_SUCCESS;
	
	//Teleop Loop Timer
	TeleopLoopTimer = new Timer();
	
	//Auto Loop Timer
	AutoLoopTimer = new Timer();
	
	ChaosLogger = new Logger();
	ChaosLogger->openIfClosed();
	
 
	//Watchdog Initializers:
	printf("Robot Constructor -> Watchdog\b\n");
	GetWatchdog().SetExpiration(10.0);
	
	//Initializing Done, Constructor Completed
	printf("Robot Constructor -> Completed\b\n");

} //End Breakaway10 Constructor

void Breakaway10::TeleopContinuous(void) 
{
	// Called continuously while in the teleop part of the match.
	// Each time the program returns from this function, it is immediately
	// called again provided that the state hasn’t changed.
	printf("TeleopContinuous -> Begin\b\n");	
	
	// Keep track of the previous joystick trigger value
	bool lastTrigger = false;

	// ->->-> MAIN LOOP BEGINS HERE <-<-<-
	printf("TeleopContinuous -> Starting operator control loop\n");
	
	//We need to start these tasks before we begin the loop, to use the enable function
	ChaosKicker->Start();
	
	double TargetDistance = 0.0; //cm
	
	while(IsOperatorControl() && !IsDisabled()) 
	{ 
		TeleopLoopTimer->Start();
		    
		bool trigger;
		GetWatchdog().Feed();
		
		// if trigger is pulled, the robot will run with standard arcade drive
		// otherwise the robot will home towards the target.
		
		if (trigger = driverStick->GetTrigger())
		{
			dds->UpdateTimeIO = IO_UPDATE_TIME_SLOW;
			
			TargetDistance = TargetFunction(trigger, lastTrigger);
			
			DashData->TargetDistance_DashOut = TargetDistance;
			
			ChaosKicker->DoSetExtendDistanceManual(false);
			ChaosKicker->SetExtendDistance(GetTargetExtendDistance(TargetDistance));
		} 
		else 
		{
			dds->UpdateTimeIO = IO_UPDATE_TIME_NORMAL;
			
			// if the trigger is not pressed, do not track
			if (trigger != lastTrigger) turnController->Disable();
			
			// Do tank drive now
			base->TankDrive(driverStick->GetLeftY(), driverStick->GetRightY());
			ChaosKicker->DoSetExtendDistanceManual(true);
		}
		
		//Send Trigger Data to Dashboard
		lastTrigger = trigger;
		DashData->Trigger_DashOut = trigger;
		
		//Feed Watchdog Here
		GetWatchdog().Feed();
		
		// ->->-> KICKER SECTION BEGINS HERE <-<-<-
		DashData->KickerExtendEistance_DashOut = ChaosKicker->ExtendDistance;
		// END KICKER SECTION
		
		// ->->-> DRIBBLER SECTION BEGINS HERE <-<-<- 
		
		//Both the left and right sides of the dribbler are equal, so only look for 2 pots, not 4
		KLPot_Value = dseio.GetAnalogIn(KLPOT);
		ALPot_Value = dseio.GetAnalogIn(ALPOT);
		
		KLPot_Value = (KLPot_Value / 3.3) * 2.0;
		KRPot_Value = KLPot_Value;
		ALPot_Value = (ALPot_Value / 3.3);
		ARPot_Value = ALPot_Value;
		
		DashData->KLPot_Value_DashOut = KLPot_Value;
		DashData->ALPot_Value_DashOut = ALPot_Value;
		
		if(driverStick->GetNumberedButton(DRIBBLE_COMMAND))
		{
			dribbler->SetConstants(KLPot_Value, ALPot_Value, KRPot_Value, ARPot_Value);
			dribbler->Keep();
		}
		else
		{
			dribbler->Release();
		}
		dribbler->BallIsInDribbler();
		
		//END DRIBBLER SECTION
		
		// ->->-> COMPRESSOR SECTION <-<-<-
		DashData->PressureSwitch_DashOut = compressor->GetPressureSwitchValue();
		
		// ->->-> KICKER STOW SETTING SECTION <-<-<-
		ChaosKicker->SetWheelStowDistance(((dseio.GetAnalogIn(WHEEL_STOW_OFFSET_POT)/3.3)*(5))-2.5);
	
		// ->->-> DASHBOARD DATA SENDER BEGINS HERE <-<-<-
		dds->sendIOPortData();
		
		// ->->-> LOOP TIME REGULATION SECTION <-<-<-
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
		
		TeleopLoopTimer->Reset();
		// END LOOP TIME REGULATION
		
	} //END while Loop -> IsOperatorControl()
	
	//If we leave the main loop (ie !IsEnabled) we need to also disable the tasks.
	ChaosKicker->Stop();
	
} //End TeleopContinuous

void Breakaway10::TeleopPeriodic(void)
{
	// Called periodically during the teleoperation part of
	// the match based on a periodic timer for the class.
    printf("TeleopPeriodic\b\n");

} //End TeleopPeriodic

void Breakaway10::AutonomousContinuous(void)
{
	// Called continuously while the in the autonomous part of the match. 
	// Each time the program returns from this function, it is immediately 
	// called again provided that the state hasn’t changed.
	printf("AutonomousContinuous\b\n");		
	
	compressor->Start();
	
	//Find single ball using ultrasonic sensors
	//The robot has ball in dribbler
	
	AUTONOMOUS_STATES NextState = AUTO_STATE__BEGIN;
	AUTONOMOUS_STATES CurrentState = AUTO_STATE__BEGIN;
	
	GetWatchdog().Feed();
	ChaosKicker->Start() ;
	GetWatchdog().Feed();
	
	AutonomousPot = dseio.GetAnalogIn(AUTO_EXTEND_POT_CHANNEL);
	AutonomousExtendDistance = (AutonomousPot / 3.3) * 20;
	
	KLPot_Value = dseio.GetAnalogIn(KLPOT);
	ALPot_Value = dseio.GetAnalogIn(ALPOT);
	
	KLPot_Value = (KLPot_Value / 3.3) * 2.0;
	KRPot_Value = KLPot_Value;
	ALPot_Value = (ALPot_Value / 3.3);
	ARPot_Value = ALPot_Value;
	
	DashData->KLPot_Value_DashOut = KLPot_Value;
	DashData->ALPot_Value_DashOut = ALPot_Value;
	
	DashData->AutoExtendDistance_DashOut = AutonomousExtendDistance;
	
	while(IsEnabled() && IsAutonomous())
	{	
		AutoLoopTimer->Start();
		
		dribbler->SetConstants(KLPot_Value, ALPot_Value, KRPot_Value, ARPot_Value);
		dribbler->BallIsInDribbler();
		
		ChaosLogger->AutoStateEnum = CurrentState;
		ChaosLogger->post();
		
		switch(NextState)
		{
			
			case AUTO_STATE__BEGIN:
				CurrentState = AUTO_STATE__BEGIN;
				
				printf("AutoState -> BEGIN\n");
				
				dribbler->Keep();
				
				ChaosKicker->DoSetExtendDistanceManual(false);
				ChaosKicker->SetExtendDistance(AutonomousExtendDistance);
				
				NextState = AUTO_STATE__GET_BALL;
				GetWatchdog().Feed();
				break;
				
			case AUTO_STATE__FIND_BALL:
				CurrentState = AUTO_STATE__FIND_BALL;

				Ball->ScanFor();
				CurrentState = AUTO_STATE__FIND_BALL;
				
				printf("AutoState -> FIND BALL\n");
				
				if(Ball->IsFound() == SoccerBall::SCAN_SUCCESS__PARTIAL_SUCCESS || Ball->IsFound() == SoccerBall::SCAN_SUCCESS__FULL_SUCCESS)
				{
					Ball->StopScanFor();
					NextState = AUTO_STATE__GET_BALL;
					printf("NextState = AutoStateGetBall\n");
				}
				GetWatchdog().Feed();
				break;
				
			case AUTO_STATE__GET_BALL:
				CurrentState = AUTO_STATE__GET_BALL;
				
				printf("AutoState -> GET BALL\n");
				//Ball->StopRetrieve();
				
				Ball->GoRetrieve();
				NextState = AUTO_STATE__HOLD_BALL;
				
				GetWatchdog().Feed();
				
				break;
				
			case AUTO_STATE__HOLD_BALL:
				
				
				printf("AutoState -> HOLD BALL\n");
				
				if(CurrentState != NextState)
				{
					AutoSafeGuardTimer->Start();
					CurrentState = AUTO_STATE__HOLD_BALL;
				}
				
				
				if(dribbler->BallIsInDribbler())
				{
					AutoSafeGuardTimer->Stop();
					AutoSafeGuardTimer->Reset();
					Ball->StopRetrieve();
					//dribbler->Keep();
					
					//NextState = AUTO_STATE__TARGET;
					NextState = AUTO_STATE__PREPARE_FOR_KICK;
				}
				else if(!dribbler->BallIsInDribbler() && AutoSafeGuardTimer->Get() > SAFE_DRIBBLER_RETRIEVE_TIME)
				{
					AutoSafeGuardTimer->Stop();
					AutoSafeGuardTimer->Reset();
					
					//Added
					Ball->StopRetrieve();
					//dribbler->Keep();
					
					NextState = AUTO_STATE__PREPARE_FOR_KICK;
				}
				else
				{
					//Keep Retrieving, but beware, you might go endlessly forward
					//without the AutoSafeGuardTimer, which will throw the state mahcine
					//Back into Get Ball to be safe
				}
				GetWatchdog().Feed();
				break;
				
			case AUTO_STATE__TARGET:
				CurrentState = AUTO_STATE__TARGET;
				
				if(CurrentState != AUTO_STATE__TARGET)
				{
					AutonomousTargetDistance = TargetFunction(true, false);
				}
				else
				{
					AutonomousTargetDistance = TargetFunction(true, true);
				}
				
				printf("AutoState -> TARGET\n");
				
				if((TargetHorizontalAngle < (AUTO_HORIZONTAL_ANGLE_ALIGNED + HORIZONTAL_HYSTERISIS)) || (TargetHorizontalAngle > (AUTO_HORIZONTAL_ANGLE_ALIGNED - HORIZONTAL_HYSTERISIS)))
				{
					turnController->Disable();
					NextState = AUTO_STATE__PREPARE_FOR_KICK;
				}
					
				GetWatchdog().Feed();
				break;
				
			case AUTO_STATE__PREPARE_FOR_KICK:
				CurrentState = AUTO_STATE__PREPARE_FOR_KICK;
				
				DashData->AutoTargetDistance_DashOut = AutonomousTargetDistance;
				
				//ChaosKicker->SetExtendDistance(this->GetTargetExtendDistance(AutonomousTargetDistance));
				//Use this when targeting
				
				printf("AutoState -> PREPARE FOR KICK\n");
				
				if(ChaosKicker->GetKickerStateMachineState() == Kicker::KICK_STATE__SIT_FOR_SHOOT)
				{
					NextState = AUTO_STATE__KICK_BALL;
				}
				else
				{
					NextState = AUTO_STATE__PREPARE_FOR_KICK;
					//Wait for the dampner to be in the right position
				}
				
				GetWatchdog().Feed();
				break;
				
			case AUTO_STATE__KICK_BALL:
				CurrentState = AUTO_STATE__KICK_BALL;
				dribbler->Release();  
				
				AutoInterface->AutoKickerShoot = true;
				
				
				printf("AutoState -> KICK BALL\n");
				
				this->AutonomousWait(WAIT_FOR_WAIT_FOR_SHOOT_TIME);
				if(ChaosKicker->GetKickerStateMachineState() == Kicker::KICK_STATE__SIT_FOR_SHOOT)
				{
					NextState = AUTO_STATE__BEGIN;
				}

				GetWatchdog().Feed();
				break;
			
			default:
				NextState = AUTO_STATE__BEGIN;
				
				GetWatchdog().Feed();
				break;
		}//End of switch
		DashData->AutonomousCurrentState_DashOut = (int) CurrentState;
		dds->sendIOPortData();
		
		if(AutoLoopTimer->Get() < AUTO_PERIOD)
		{
			while(AUTO_PERIOD - AutoLoopTimer->Get() > 0.0)
			{
				GetWatchdog().Feed();
			}
		}
		else
		{
			printf("Auto Period NOT RESPECTED : CODE TAKES TOO LONG\n");
		}
		
		AutoLoopTimer->Reset();
		
	}
	ChaosKicker->Stop();
	ChaosLogger->closeIfOpen();
	
} // END AutonomousContinuous

void Breakaway10::AutonomousPeriodic(void)
{
	// Called periodically during the autonomous part of
	// the match based on a periodic timer for the class.
	printf("AutonomousPeriodic\b\n");
	
} // END AutonomousContinuous

void Breakaway10::RobotInit(void)
{
	// Called when the robot is first turned on. This is a substitute for using the constructor
	// in the class for consistency. This method is only called once.
	printf("RobotInit -> Begin\b\n");
	
	//ENCODER SETUP:
	leftEncoder->Start();
	rightEncoder->Start();
	
	//TURN CONTROLLER SETUP:
	printf("Initializing PIDController\n");
	
	turnController->SetInputRange(-360.0, 360.0);
	turnController->SetOutputRange(-0.6, 0.6);
	turnController->SetTolerance(1.0 / 90.0 * 100);
	turnController->Disable();
	
	//CAMERA SETUP:
	printf("Setting camera parameters\n");
	
	camera.WriteResolution(AxisCameraParams::kResolution_320x240);
	camera.WriteBrightness(0);
	camera.WriteRotation(AxisCameraParams::kRotation_0);

	//GYRO SETUP:
	printf("Setting gyro parameters\n");
	gyro->SetSensitivity(0.007);
	
	//ULTRASONIC SETUP:
	ballDistanceUltrasonic->SetEnabled(true);
	ballDistanceUltrasonic->SetAutomaticMode(true);
	
	//WATCHDOG SETUP
	printf("Setting Watchdog parameters\n");
	GetWatchdog().SetExpiration(1.0);
	
	//COMPRESSOR SETUP:
	compressor->Start();
	
} //End RobotInit

void Breakaway10::DisabledInit(void)
{
	// Called when the robot is first disabled
	printf("DisabledInit\b\n");	
	
} //DisabledInit

void Breakaway10::AutonomousInit(void)
{
	// Called when the robot enters the autonomous period for the first time. 
	// This is called on a transition from any other state.
	printf("AutonomousInit\b\n");
	
} //AutonomousInit

void Breakaway10::TeleopInit(void)
{
	// Called when the robot enters the teleop period for the first time. 
	// This is called on a transition from any other state.
	printf("TeleopInit\b\n");
	
} // TeleopInit

void Breakaway10::DisabledContinuous(void)
{
	// Called continuously while the robot is disabled. 
	// Each time the program returns from this function, 
	// it is immediately called again provided that the state hasn’t changed.
	printf("DisabledContinuous\b\n");	
	
} //DisabledContinuous

void Breakaway10::DisabledPeriodic(void)
{
	// Called periodically during the disabled time based on a periodic 
	// timer for the class.
	printf("DisabledPeriodic\b\n");
	
} //DisabledPeriodic
		
bool Breakaway10::AutonomousWait(float secs)
{
	//printf("chaosAutonomous::autonomousWait() -> Entered"); 
	if ( !IsAutonomous() || IsDisabled() )
	{
		return true;
	}
	if ( secs > 0 )	Wait(secs);
	return false;
} //AutonomousWait

double Breakaway10::TargetFunction(bool trigger,  bool lastTrigger = false)
{
	double FinalTargetDistance = 0;
	
	if (trigger != lastTrigger) 
	{
		// check if trigger changed
		turnController->Enable();
	}
			
	// if there's a fresh and we're at the previous target heading then
	// get a camera image and process it    
	
	if (camera.IsFreshImage()) 
	{
		
		// get the gyro heading that goes with this image
		double gyroAngle = gyro->PIDGet();
		
		// get the camera image
		ColorImage *image = camera.GetImage();

		// find FRC targets in the image
		vector<Target> targets = Target::FindCircularTargets(image);
		delete image;
		if (targets.size() == 0 || targets[0].m_score < MINIMUM_SCORE)
		{
			// no targets found. Make sure the first one in the list is 0,0
			// since the dashboard program annotates the first target in green
			// and the others in magenta. With no qualified targets, they'll all
			// be magenta.
			Target nullTarget;
			nullTarget.m_majorRadius = 0.0;
			nullTarget.m_minorRadius = 0.0;
			nullTarget.m_score = 0.0;
			if (targets.size() == 0)
				targets.push_back(nullTarget);
			else
				targets.insert(targets.begin(), nullTarget);
			dds->sendVisionData(0.0, gyro->GetAngle(), 0.0, 0.0, targets);
			if (targets.size() == 0)
				printf("No target found\n\n");
			else
				printf("No valid targets found, best score: %f\n", targets[0].m_score);
		}
		else 
		{
			// We have some targets.
			// set the new PID heading setpoint to the first target in the list
			double horizontalAngle = targets[0].GetHorizontalAngle();
			double setPoint = gyroAngle + horizontalAngle;
			
			this->TargetHorizontalAngle = horizontalAngle;
			
			
			double Target1 = targets[0].Get_m_majorRadius();
			double Target2 = targets[1].Get_m_majorRadius();
			
			
			if(Target1 < Target2)
			{
				printf("Distance: %f\n", targets[0].GetDistance());
				FinalTargetDistance = targets[0].GetDistance();
			}
			else if(Target1 > Target2)
			{
				printf("Distance: %f\n", targets[1].GetDistance());
				FinalTargetDistance = targets[1].GetDistance();
			}
			else
			{
				//printf("Distance: %f\n", targets[1].GetDistance());
				FinalTargetDistance = targets[1].GetDistance();
			}
			
			//printf("Major Radius %f ... Distance %f\n", targets[0].Get_m_majorRadius(), targets[0].GetDistance());
        
			turnController->SetSetpoint(setPoint);
			
			// send dashbaord data for target tracking
			dds->sendVisionData(0.0, gyro->GetAngle(), 0.0, targets[0].m_xPos / targets[0].m_xMax, targets);
		}
		
	}
	
return FinalTargetDistance;	
}  //End TargetFunction

double Breakaway10::GetTargetExtendDistance(double TargetDistance)
{
	//70 degree wedge
	return ((0.023 * TargetDistance) + 9.17);
}

START_ROBOT_CLASS(Breakaway10);

