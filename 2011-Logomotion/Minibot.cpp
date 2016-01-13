/*-------------------------------------------------------------**
**                                                             
**   Filename: Minibot.cpp                                        
**                                                             
**   About:    An object to control the Minibot functions.             
**   Property of Chaos, Copyright 2011
**   Written by: Jallard and Bpapp, Chaos.           
**                                                                                           
**   2011 2 8           
**                                                             
**-------------------------------------------------------------*/

#include "Minibot.h"

Minibot::Minibot(void)
{
	//Mini-Bot Solenoids
	DeploySolenoid = new Solenoid(SOLENOID_MODULE1, DEPLOY_SOLENOID_PORT);
	FlapSolenoid = new Solenoid(SOLENOID_MODULE1, FLAP_SOLENOID_PORT);	
	
	CurrentMinibotState = MINIBOT_STATE_INIT;
	NextMinibotState = MINIBOT_STATE_INIT;
	
	MinibotValveCmd = MINIBOT_VALVE_CMD_INIT;
	
	FlapPinServo = new Servo(DIO_MODULE1, MINIBOT_SERVO_PIN_CONTROL);
	//FlapPinServo->SetAngle(FLAP_PIN_INIT_ANGLE);
	
	FlapPinTimer = new Timer();
	FlapPinTimer->Reset();
	
	AllowDeploy = false;
}

void Minibot::StateMachine(void)
{
	printf("minibotstate %d", (int )CurrentMinibotState);
	
	
	
	switch(NextMinibotState)
	{
		case MINIBOT_STATE_INIT:
			if(CurrentMinibotState != NextMinibotState)
			{
				SetMinibotValveStates(MINIBOT_VALVE_CMD_INIT);
				AllowDeploy = false;
			}
			CurrentMinibotState = MINIBOT_STATE_INIT;
			NextMinibotState = MINIBOT_STATE_WAIT;
			break;
			
		case MINIBOT_STATE_WAIT:
			if(CurrentMinibotState != NextMinibotState)
			{
				SetMinibotValveStates(MINIBOT_VALVE_CMD_WAIT);
			}
			CurrentMinibotState = MINIBOT_STATE_WAIT;
//			if(Main::DriverGamepad->GetNumberedButton(FLAP_BUTTON))
//			{
//				NextMinibotState = MINIBOT_STATE_DEPLOY_FLAP;			
//			}
			break;
		
		case MINIBOT_STATE_DEPLOY_FLAP_SERVO:
			
			if(CurrentMinibotState != NextMinibotState)
			{
				FlapPinTimer->Start();
			}
			
			CurrentMinibotState = MINIBOT_STATE_DEPLOY_FLAP_SERVO;
		
			FlapPinServo->SetAngle(FLAP_PIN_DEPLOY_ANGLE);
						
			if(FlapPinTimer->Get() >= FLAP_PIN_TIME)
			{
				FlapPinTimer->Stop();
				FlapPinTimer->Reset();
				
				NextMinibotState = MINIBOT_STATE_DEPLOY_FLAP_PISTON;
				
			}
			
			break;
			
		case MINIBOT_STATE_DEPLOY_FLAP_PISTON:
			
			if(CurrentMinibotState != NextMinibotState)
			{
//				FlapPinTimer->Start();
			}
			SetMinibotValveStates(MINIBOT_VALVE_CMD_DEPLOY_FLAP);
		
			CurrentMinibotState = MINIBOT_STATE_DEPLOY_FLAP_PISTON;
			NextMinibotState = MINIBOT_STATE_WAIT_DEPLOY_PISTON;

//			if(FlapPinTimer->Get() >= FLAP_PIN_TIME * 3.0)
//			{
//				FlapPinTimer->Stop();
//				FlapPinTimer->Reset();
//				
//				NextMinibotState = MINIBOT_STATE_WAIT_DEPLOY_PISTON;
//				
//				AllowDeploy = true;
//			}
			break;
			
		case MINIBOT_STATE_WAIT_DEPLOY_PISTON:
			if(CurrentMinibotState != NextMinibotState)
			{
				SetMinibotValveStates(MINIBOT_VALVE_CMD_DEPLOY_FLAP);
			}
			CurrentMinibotState = MINIBOT_STATE_WAIT_DEPLOY_PISTON;
			AllowDeploy = true;

			break;
			
		case MINIBOT_STATE_DEPLOY_BOT:
			if(CurrentMinibotState != NextMinibotState)
			{
				SetMinibotValveStates(MINIBOT_VALVE_CMD_DEPLOY_BOT);
				AllowDeploy = false;
			}
			CurrentMinibotState = MINIBOT_STATE_DEPLOY_BOT;
			NextMinibotState = MINIBOT_STATE_DEPLOY_BOT;
			
			break;

	}
}

void Minibot::SetMinibotValveStates(MINIBOT_VALVE_CMDS MinibotValveCmd)
{
	switch(MinibotValveCmd)
	{
		case MINIBOT_VALVE_CMD_INIT:
			DeploySolenoid->Set(false);
			FlapSolenoid->Set(false);
			break;
			
		case MINIBOT_VALVE_CMD_WAIT:
			DeploySolenoid->Set(false);
			FlapSolenoid->Set(false);
			break;
			
		case MINIBOT_VALVE_CMD_DEPLOY_FLAP:
			DeploySolenoid->Set(false);
			FlapSolenoid->Set(true);
			break;
			
		case MINIBOT_VALVE_CMD_DEPLOY_BOT:
			DeploySolenoid->Set(true);
			FlapSolenoid->Set(true);
			break;
	}
}

Minibot::MINIBOT_STATES Minibot::Check(void)
{
	return this->CurrentMinibotState;
}

void Minibot::Signal(Minibot::MINIBOT_STATES NextState)
{
	this->NextMinibotState = NextState;
}
