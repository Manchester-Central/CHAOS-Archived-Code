/*-------------------------------------------------------------**
**                                                             
**   Filename: Shoulder.cpp                                        
**                                                             
**   About:    Shoulder Object
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Everyone, Chaos.           
**                                                                                           
**   2011 1 27       
**                                                             
**-------------------------------------------------------------*/

#include "Shoulder.h"

Shoulder::Shoulder(void)
{
	ShoulderSolenoidLeft = new Solenoid(SOLENOID_MODULE1, SHOULDER_SOLENOID_LEFT_PORT);
	ShoulderSolenoidRight = new Solenoid(SOLENOID_MODULE1, SHOULDER_SOLENOID_RIGHT_PORT);
	
	ShoulderPot = new LinearPot(ANALOG_MODULE1, SHOULDER_POT, SHOULDER_VOLTAGE_1, SHOULDER_VOLTAGE_2, SHOULDER_ANGLE_1, SHOULDER_ANGLE_2);
	
	CurrentState = SHOULDER_STATE_DISABLE;
	NextState = SHOULDER_STATE_DISABLE;
	
	ShoulderValveCmd = SHOULDER_VALVE_CMD_DISABLE;
	
	
}

void Shoulder::StateMachine(void)
{
	switch(NextState)
	{
		case SHOULDER_STATE_DISABLE:
			
			//printf("Shoulder StateM DISABLE\n");
			
			if(NextState != CurrentState)
			{
				SetValveStates(SHOULDER_VALVE_CMD_DISABLE);
				PreviousShoulderValveCmd = SHOULDER_VALVE_CMD_DISABLE;
			}
			
			CurrentState = SHOULDER_STATE_DISABLE;
			
			break;

		case SHOULDER_STATE_HOLD:
			
			CurrentState = SHOULDER_STATE_HOLD;
			
			SetValveStates(PreviousShoulderValveCmd);
			
			break;
			
		case SHOULDER_STATE_UP:
			
			//printf("Shoulder StateM UP\n");
					
		    SetValveStates(SHOULDER_VALVE_CMD_UP);
		    PreviousShoulderValveCmd = SHOULDER_VALVE_CMD_UP;
			
			CurrentState = SHOULDER_STATE_UP;
		
			if(ShoulderPot->GetAngleDegrees() >= SHOULDER_ANGLE_UP)
			{
				NextState = SHOULDER_STATE_HOLD;
			}	
			break;
			
		case SHOULDER_STATE_DOWN:
			
			//printf("Shoulder StateM DOWN\n");
							
			SetValveStates(SHOULDER_VALVE_CMD_DOWN);
			PreviousShoulderValveCmd = SHOULDER_VALVE_CMD_DOWN;
			
			CurrentState = SHOULDER_STATE_DOWN;
			
			if(ShoulderPot->GetAngleDegrees() <= SHOULDER_ANGLE_DOWN)
			{
				NextState = SHOULDER_STATE_HOLD;
			}	
			break;
			
		default:
			NextState = SHOULDER_STATE_DISABLE;
			break;
	}
}

void Shoulder::SetValveStates(SHOULDER_VALVE_CMD_T ShoulderValveCmd)
{
	
	switch(ShoulderValveCmd)
	{
		case SHOULDER_VALVE_CMD_UP:
			ShoulderSolenoidLeft->Set(true);
			ShoulderSolenoidRight->Set(true);
			break;
			
		case SHOULDER_VALVE_CMD_DOWN:
			ShoulderSolenoidLeft->Set(false);
			ShoulderSolenoidRight->Set(false);
			break;
			
		case SHOULDER_VALVE_CMD_DISABLE:
			ShoulderSolenoidLeft->Set(false);
			ShoulderSolenoidRight->Set(false);
			break;
			
		default:
			ShoulderValveCmd = SHOULDER_VALVE_CMD_DISABLE;
	}
}

void Shoulder::Signal(SHOULDER_STATES_T NextState)
{
	this->NextState = NextState;
}

Shoulder::SHOULDER_STATES_T Shoulder::Check(void)
{
	return this->CurrentState;
}
