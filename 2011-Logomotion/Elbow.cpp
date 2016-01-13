/*-------------------------------------------------------------**
**                                                             
**   Filename: Elbow.h                                        
**                                                             
**   About:    An object to control the elbow of the manipulator
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Josh & Ben, Chaos.           
**                                                                                           
**   2011 1 27       
**                                                             
**-------------------------------------------------------------*/

#include "Elbow.h"

Elbow::Elbow(void)
{
	ElbowPot = new LinearPot(ANALOG_MODULE1, ELBOW_POT, VOLTAGE_1, VOLTAGE_2, ANGLE_1, ANGLE_2);
	ElbowVictor = new Victor(DIO_MODULE1, ELBOW_VICTOR);
	
	ElbowProportionalConstant = ELBOW_PROPORTIONAL_CONSTANT_INIT;
    ElbowIntegralConstant = ELBOW_INTEGRAL_CONSTANT_INIT;
    ElbowDerivativeConstant = ELBOW_DERIVATIVE_CONSTANT_INIT;
	
	AngleCorrection = new PIDController(ElbowProportionalConstant, ElbowIntegralConstant, ElbowDerivativeConstant, ElbowPot, ElbowVictor);
	
	AngleCorrection->SetInputRange(ELBOW_INPUT_RANGE_MIN, ELBOW_INPUT_RANGE_MAX); //min and max angles
	AngleCorrection->SetOutputRange(ELBOW_OUTPUT_RANGE_MIN, ELBOW_OUTPUT_RANGE_MAX); //min and max output values
	AngleCorrection->Disable();
	
	CurrentState = ELBOW_STATE_DISABLE;
	NextState = ELBOW_STATE_DISABLE;
	StoreState = ELBOW_STATE_DISABLE;
}

void Elbow::SetGoalAngle(ELBOW_STATES NextAngle)
{
	switch(NextAngle)
	{
		case STATE_UP_CENTER_TOP: 
			 
			GoalAngle = ANGLE_UP_CENTER_TOP;
			break;
			
		case STATE_UP_SIDE_TOP:			
			
			GoalAngle = ANGLE_UP_SIDE_TOP;
			break;
			
		case STATE_UP_CENTER_MIDDLE:
			
			GoalAngle = ANGLE_UP_CENTER_MIDDLE;
			break;
			
		case STATE_UP_SIDE_MIDDLE:
			
			GoalAngle = ANGLE_UP_SIDE_MIDDLE;
			break;
			
		case STATE_DOWN_CENTER_BOTTOM:
			
			GoalAngle = ANGLE_DOWN_CENTER_BOTTOM;
			break;
			
		case STATE_DOWN_SIDE_BOTTOM:
			
			GoalAngle = ANGLE_DOWN_SIDE_BOTTOM;
			break;
			
		case STATE_DOWN_PICKUP:
			
			GoalAngle = ANGLE_DOWN_PICKUP;
			break;
			
		case STATE_DOWN_STOW:
			
			GoalAngle = ANGLE_DOWN_STOW;
			break;
			
		case STATE_DOWN_PICKUP_HP:
			
			GoalAngle = ANGLE_DOWN_PICKUP_HP;
			break;
		
		//TODO add default case!
	
	} //END SWITCH
}//END SET GOAL ANGLE

void Elbow::StateMachine(void)
{	
	
	if(ElbowManualCheckInitial && !ElbowManualCheckSecondary)
	{
		NextState = ELBOW_STATE_MANUAL;
	}
	else if(!ElbowManualCheckInitial && ElbowManualCheckSecondary)
	{
		NextState = ELBOW_STATE_DISABLE;
	}
	
	ElbowManualCheckSecondary = ElbowManualCheckInitial;
	
	switch(NextState)
	{
		case ELBOW_STATE_DISABLE:
			
			AngleCorrection->Disable();
			ElbowVictor->Set(ELBOW_STOP);
			
			CurrentState = ELBOW_STATE_DISABLE;
			StoreState = ELBOW_STATE_DISABLE;
		
			break;
			
		case ELBOW_STATE_MANUAL_DISABLE_UP:
			
			if(NextState != CurrentState)
			{
				AngleCorrection->Disable();
				ElbowVictor->Set(ELBOW_STOP);
			}
			
			CurrentState = ELBOW_STATE_MANUAL_DISABLE_UP;
			
			if(ManualMotorValue < 0.0)
			{
				ManualMotorValue = 0.0;
			}
			
			ElbowVictor->Set(ManualMotorValue);
			
			if(ElbowPot->GetAngleDegrees() < ELBOW_MAXIMUM_ANGLE)
			{
				NextState = ELBOW_STATE_MANUAL;
			}
			
			break;
			
		case ELBOW_STATE_MANUAL_DISABLE_DOWN:
					
			if(NextState != CurrentState)
			{
				AngleCorrection->Disable();
				ElbowVictor->Set(ELBOW_STOP);
			}
			
			CurrentState = ELBOW_STATE_MANUAL_DISABLE_DOWN;
			
			if(ManualMotorValue > 0.0)
			{
				ManualMotorValue = 0.0;
			}
			
			if(ElbowPot->GetAngleDegrees() > ELBOW_MINIMUM_ANGLE)
			{
			     NextState = ELBOW_STATE_MANUAL;
			}
			
			ElbowVictor->Set(ManualMotorValue);
			
			break;
			
		case ELBOW_STATE_MANUAL:
			
			if(NextState != CurrentState)
			{
				AngleCorrection->Disable();
				ElbowVictor->Set(ELBOW_STOP);

			}
			
			ElbowVictor->Set(ManualMotorValue);
			CurrentState = ELBOW_STATE_MANUAL;
			
			if(ElbowPot->GetAngleDegrees() > ELBOW_MAXIMUM_ANGLE)
			{
				NextState = ELBOW_STATE_MANUAL_DISABLE_UP;
			}
			else if(ElbowPot->GetAngleDegrees() < ELBOW_MINIMUM_ANGLE)
			{
				NextState = ELBOW_STATE_MANUAL_DISABLE_DOWN;
			}
			
			break;
			
		case ELBOW_STATE_ENABLE:
			
			CurrentState = ELBOW_STATE_ENABLE;
			NextState = ELBOW_STATE_HOLD_MOTOR;
			
			AngleCorrection->Disable();
			
			StoreState = ELBOW_STATE_ENABLE;
			
			break;
		
		case ELBOW_STATE_HOLD_MOTOR:
					
			CurrentState = ELBOW_STATE_HOLD_MOTOR;
			StoreState = ELBOW_STATE_HOLD_MOTOR;
			
			PreviousAngle = ElbowPot->GetAngleDegrees();
			
			AngleCorrection->SetSetpoint(GoalAngle);
			AngleCorrection->Enable();
			
			
			//Elbow angle is not within Hysteresis Band, correct angle to goal angle
			if((PreviousAngle > (GoalAngle + HYSTERESIS_BAND)) || (PreviousAngle < (GoalAngle - HYSTERESIS_BAND)))
			{
				NextState = ELBOW_STATE_CORRECT_ANGLE;
			}	
			
			break;
			
		case ELBOW_STATE_CORRECT_ANGLE:
			
			CurrentState = ELBOW_STATE_CORRECT_ANGLE;
			
			//printf("Goal Angle %f, Previous Angle %f\n", GoalAngle, PreviousAngle); 

			//Determine velocity vector needed to home in on the Goal Angle
			
			PreviousAngle = ElbowPot->GetAngleDegrees();
			
			AngleCorrection->SetSetpoint(GoalAngle);
			AngleCorrection->Enable();
			//TODO: CHANGE HYSTERESIS BAND TO IN POSITION BAND
			//Elbow angle is within Hysteresis Band, go to the Hold Motor State
			
			if(PreviousAngle > ELBOW_MAXIMUM_ANGLE)
			{
				NextState = ELBOW_STATE_PID_DISABLE_UP;
			}
			else if(PreviousAngle < ELBOW_MINIMUM_ANGLE)
			{	
				NextState = ELBOW_STATE_PID_DISABLE_DOWN;
			}
			
			else if((PreviousAngle < (GoalAngle + HYSTERESIS_BAND)) && (PreviousAngle > (GoalAngle - HYSTERESIS_BAND)))
			{
				NextState = ELBOW_STATE_HOLD_MOTOR;
			}
			
			break;
			
		case ELBOW_STATE_PID_DISABLE_UP:
			
			CurrentState = ELBOW_STATE_PID_DISABLE_UP;
			
			AngleCorrection->Disable();
			
			ElbowVictor->Set(ELBOW_LIMIT_CORRECTION_POWER);
			
			if(ElbowPot->GetAngleDegrees() < ELBOW_MAXIMUM_ANGLE)
			{
				NextState = ELBOW_STATE_CORRECT_ANGLE;
			}
			break;
			
		case ELBOW_STATE_PID_DISABLE_DOWN:
			
			CurrentState = ELBOW_STATE_PID_DISABLE_DOWN;
			
			AngleCorrection->Disable();
			
			ElbowVictor->Set(-ELBOW_LIMIT_CORRECTION_POWER);
			
			if(ElbowPot->GetAngleDegrees() > ELBOW_MINIMUM_ANGLE)
			{
				NextState = ELBOW_STATE_CORRECT_ANGLE;
			}
			break;

			
		default:
			NextState = ELBOW_STATE_DISABLE;
			break;
	
	} //END SWITCH
	
	
} //END STATE MACHINE 

void Elbow::Signal(ELBOW_STATES_T NextState)
{
	this->NextState = NextState;
}

Elbow::ELBOW_STATES_T Elbow::Check(void)
{
	return this->CurrentState;
}

void Elbow::ManualSetMotor(float ManualMotorValue)
{
	this->ManualMotorValue = ManualMotorValue;
}
