/*-------------------------------------------------------------**
 **                                                             
 **   Filename: Manipulator.cpp                                        
 **                                                             
 **   About:    The ReboundRumble Robot Class Manipulator
 **                                                             
 **   Property of Chaos, Copyright 2012
 **   Written by:  
 **               Josh Allard
 **               Ben Papp
 **               Zain Abbas
 **				  Eric Moy, Chaos.           
 **                                                                                           
 **   2012 1 28             
 **                                                             
 **-------------------------------------------------------------*/

#include "Manipulator.h"

Manipulator::Manipulator(Gamepad *OperatorGamepad)
	: mBuffer( 15, 0.0 )
{
	this->OperatorGamepad = OperatorGamepad;
	
	LightSensorIntake = new DigitalInput(DIGITAL_MODULE, LIGHT_SENSOR_INTAKE_PORT);
	LightSensorConveyor = new DigitalInput(DIGITAL_MODULE, LIGHT_SENSOR_CONVEYOR_PORT);
	LightSensorOutput = new DigitalInput(DIGITAL_MODULE, LIGHT_SENSOR_OUTPUT_PORT);
	NextState = MANIP_STATE_DISABLED;
	
	ConveyorMotor = new Victor(DIGITAL_MODULE, CONVEYOR_MOTOR_PORT);


	IntakeMotor = new Victor(DIGITAL_MODULE, INTAKE_MOTOR_PORT);
	TopShooterMotor = new Victor(DIGITAL_MODULE, TOP_SHOOTER_MOTOR_PORT);
	//BottomShooterMotor = new Victor(DIGITAL_MODULE, BOTTOM_SHOOTER_MOTOR_PORT);

	TopShooterEncoder = new Encoder(TOP_SHOOTER_ENCODER_PORT_1, TOP_SHOOTER_ENCODER_PORT_2, false, Encoder::k2X);
	TopShooterEncoder->SetDistancePerPulse(1);
	TopShooterEncoder->SetPIDSourceParameter(Encoder::kRate);
	TopShooterEncoder->Start();
	//BottomShooterEncoder = new Encoder(BOTTOM_SHOOTER_ENCODER_PORT_1, BOTTOM_SHOOTER_ENCODER_PORT_2);
	
	ProportionalConstant = PROP_CONST;
	IntervalConstant = INT_CONST;
	DerivativeConstant = DER_CONST;
	
	TopShooterMotorControl = new PIDController(ProportionalConstant, IntervalConstant, DerivativeConstant, TopShooterEncoder, TopShooterMotor);
	//BottomShooterMotorControl = new PIDController(ProportionalConstant, IntervalConstant, DerivativeConstant, BottomShooterEncoder, BottomShooterMotor);
	TopShooterMotorControl->SetInputRange(MIN_ENCODER_VALUE, MAX_ENCODER_VALUE);
	TopShooterMotorControl->SetOutputRange(MIN_SHOOTER_OUTPUT, MAX_SHOOTER_OUTPUT);
	TopShooterMotorControl->SetContinuous(true);
	
	TopShooterMotorControl->Disable();
	//BottomShooterMotorControl->Disable();
	
	
	BallCount = 3;
	
	ShootTimer = new Timer();
	
	CurrentState = MANIP_STATE_DISABLED;
	
}

void Manipulator::StateMachine(void)
{

	if(LightSensorIntake->Get() == true && PreviousLightIntakeBool == false)
	{
		BallCount = (BallCount + 1);
	}
	PreviousLightIntakeBool = LightSensorIntake->Get();
	
	if(LightSensorOutput->Get() == false && PreviousLightOutputBool == true)
	{
		BallCount = (BallCount - 1);
	}
	PreviousLightOutputBool = LightSensorOutput->Get();
	
	if(OperatorGamepad->GetNumberedButton(BALL_RESET_BUTTON))
	{
		BallCount = 0;
	}
	CurrentEncoderValue = TopShooterEncoder->GetRate();
	if(CurrentEncoderValue > 5000)
	{
		CurrentEncoderValue = PreviousEncoderValue;
	}
	else
	{
		PreviousEncoderValue = CurrentEncoderValue;
	}
	
	
	mBuffer.push_back( CurrentEncoderValue );
	
	float AverageEncoderValue = 0.0;
	// foreach 'old' sample, from oldest to newest (in time)
	for( boost::circular_buffer< float >::iterator iter = mBuffer.begin(); 
		 iter != mBuffer.end();
		 iter++ )
	{
		AverageEncoderValue += *iter;
	}
	AverageEncoderValue = AverageEncoderValue / mBuffer.size();
	

	

	//printf("Encoder %f, AverageEncoderValue %f, \n", TopShooterEncoder->GetRate(), AverageEncoderValue);
	
	if(OperatorGamepad->GetNumberedButton(BUTTON_MANUAL))
	{
		NextState = MANIP_STATE_MANUAL;
	}


	switch(NextState)
	{
		case MANIP_STATE_DISABLED:
			CurrentState = MANIP_STATE_DISABLED;
			NextState = MANIP_STATE_DISABLED;
			TopShooterMotorControl->Disable();
			printf("MANIP_DISABLED MANIPCurrentState = %i, MANIPNextState = %i,", CurrentState, NextState);
			//printf("State Disabled");
			break;
			
		case MANIP_STATE_INIT:
			BallCount = 0;
			CurrentState = MANIP_STATE_INIT;
			NextState = MANIP_STATE_RELOAD;
			TopShooterMotorControl->Disable();
			printf("MANIP_INIT MANIPCurrentState = %i, MANIPNextState = %i,", CurrentState, NextState);
			//printf("State Init");
			break;
			
		case MANIP_STATE_RELOAD:
			//printf("State Reload");
			printf("MANIP_RELOAD MANIPCurrentState = %i, MANIPNextState = %i,", CurrentState, NextState);
			CurrentState = MANIP_STATE_RELOAD;

			TopShooterMotorControl->Disable();
			
			if(LightSensorOutput->Get() != true)
			{
				if(LightSensorIntake->Get() != true && LightSensorConveyor->Get() != true)
				{
					ConveyorMotor->Set(0.0);
				}
				else if(LightSensorIntake->Get() == true || LightSensorConveyor->Get() == true)
				{
					ConveyorMotor->Set(CONVEYOR_MOTOR_POWER);
				}
			}
			else
			{
				ConveyorMotor->Set(0.0);
			}
			
			if(OperatorGamepad->GetNumberedButton(BUTTON_SHOOT) != true)
			{
				if(OperatorGamepad->GetNumberedButton(BUTTON_INTAKE) == true)
				{
					//IntakeMotor->Set(INTAKE_MOTOR_INTAKE);
				}
				else if(OperatorGamepad->GetNumberedButton(BUTTON_OUTPUT) == true)
				{
					IntakeMotor->Set(INTAKE_MOTOR_OUTPUT);
				}
				else
				{
					IntakeMotor->Set(0.0);
				}
				
			}
			else if(OperatorGamepad->GetNumberedButton(BUTTON_SHOOT) == true)
			{
				NextState = MANIP_STATE_SHOOT;
			}

			break;
			
		case MANIP_STATE_SHOOT:
			printf("MANIP_SHOOT MANIPCurrentState = %i, MANIPNextState = %i,", CurrentState, NextState);
			CurrentState = MANIP_STATE_SHOOT;
			if(CurrentState != NextState)
			{
				TopShooterMotorControl->Disable();

			}
			CurrentState = MANIP_STATE_SHOOT;
			ShootTimer->Start();
			
//			ShootSpeed = SHOOT_SPEED + SHOOT_SPEED_HYSTERESIS;
//			TopShooterMotorControl->SetSetpoint(ShootSpeed);
//			TopShooterMotorControl->Enable();
			
//			ShooterProportionalPower = -.55  + (.45 * (((SHOOT_SPEED - AverageEncoderValue)/SHOOT_SPEED)* -1));
//			
//			if( ShooterProportionalPower <= 0)
//			{
//				TopShooterMotor->Set(ShooterProportionalPower);
//			}
			



			TopShooterMotor->Set(-0.37);
			
			//printf("ShooterValue %f, Raw %i, MotorValue %f,", TopShooterMotorControl->Get(), TopShooterEncoder->GetRaw(), TopShooterMotor->Get());
			//printf("ShootTimer %f,", ShootTimer->Get());
			
			if(ShootTimer->Get() > 1.0)
			{
				ConveyorMotor->Set(CONVEYOR_MOTOR_POWER);
			}
			else
			{
				ConveyorMotor->Set(0.0);
			}
			
			if(OperatorGamepad->GetNumberedButton(BUTTON_SHOOT) == true)				
			{
				NextState = MANIP_STATE_SHOOT;
			}
			else
			{
				NextState = MANIP_STATE_RELOAD;
				ShootTimer->Stop();
				ShootTimer->Reset();
			}
			
			
			
			//printf("State Shoot");
			break;
			
		case MANIP_STATE_AUTO_SHOOT:
			printf("MANIP_AUTO_SHOOT MANIPCurrentState = %i, MANIPNextState = %i,", CurrentState, NextState);
//			if(NextState != CurrentState)
//			{
//				BallCount = 2;
//			}
//			
			printf("BallCount %f.,", BallCount);
			CurrentState = MANIP_STATE_AUTO_SHOOT;
			
			TopShooterMotor->Set(-0.39);
			//if(TopShooterEncoder->GetRate() < (SHOOT_SPEED + SHOOT_SPEED_HYSTERESIS) && TopShooterEncoder->GetRate() > (SHOOT_SPEED - SHOOT_SPEED_HYSTERESIS))
			//{
				ConveyorMotor->Set(CONVEYOR_MOTOR_POWER);
			//}

			
			if(BallCount <= 0)
			{
				ShootTimer->Start();
				if(ShootTimer->Get() > 1.0)
				{
					NextState = MANIP_STATE_DISABLED;
					ConveyorMotor->Set(0.0);
					TopShooterMotor->Set(0.0);
					ShootTimer->Stop();
					ShootTimer->Reset();
				}

			}
			break;
			
		case MANIP_STATE_MANUAL:
			printf("MANIP_MANUAL MANIPCurrentState = %i, MANIPNextState = %i,", CurrentState, NextState);
			if(CurrentState != NextState)
			{
				TopShooterMotorControl->Disable();	
			}

			if(OperatorGamepad->GetNumberedButton(BUTTON_INTAKE) == true)
			{
				IntakeMotor->Set(INTAKE_MOTOR_INTAKE);
			}
			else if(OperatorGamepad->GetNumberedButton(BUTTON_OUTPUT) == true)
			{
				IntakeMotor->Set(INTAKE_MOTOR_OUTPUT);
			}
			else
			{
				IntakeMotor->Set(0.0);
			}
			
			
			if(OperatorGamepad->GetRightY() < 0.1 && OperatorGamepad->GetRightY() > -0.1)
			{
				TopShooterMotor->Set(0.0);
			}
			else
			{
				TopShooterMotor->Set(OperatorGamepad->GetRightY());
			}
			
			if(OperatorGamepad->GetLeftY() < 0.1 && OperatorGamepad->GetLeftY() > -0.1)
			{
				ConveyorMotor->Set(0.0);
			}
			else
			{
				ConveyorMotor->Set(-OperatorGamepad->GetLeftY());
			}			
			
			if(OperatorGamepad->GetNumberedButton(BUTTON_SHOOT))
			{
				NextState = MANIP_STATE_MANUAL;
			}
			else
			{
				NextState = MANIP_STATE_RELOAD;
			}

			CurrentState = MANIP_STATE_MANUAL;
			//printf("State Manual");
			break;
	}//end switch
	
}

void Manipulator::ChangeNextState(Manipulator::MANIP_STATES_X NextState)
{
	this->NextState = NextState;
}

Manipulator::MANIP_STATES_X Manipulator::CheckState(void)
{
	return this->CurrentState;
}
