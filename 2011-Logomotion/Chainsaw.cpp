/*-------------------------------------------------------------**
**                                                             
**   Filename: Chainsaw.cpp                                        
**                                                             
**   About:    An object to control the chainsaw manipulator to
**			   Acquire, Hold, and Deploy tubes
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Zain Abbas & Steven Kroh, Chaos.           
**                                                                                           
**   2011 1 27             
**                                                             
**-------------------------------------------------------------*/

#include "Chainsaw.h"

Chainsaw::Chainsaw(void)
{
	ChainsawUltrasonic = new Ultrasonic(CHAINSAW_ULTRASONIC_SENSOR_PING, CHAINSAW_ULTRASONIC_SENOSR_ECHO);
	ChainsawUltrasonic->SetAutomaticMode(true);
	
	ChainsawMotor = new Victor(DIO_MODULE1, CHAINSAW_MOTOR_CHANNEL);
	
	CurrentState = CHAINSAW_STATE_DISABLE;
	NextState = CHAINSAW_STATE_DISABLE;
	
	CurrentChainsawUltrasonic = 0.0;
	PreviousChainsawUltrasonic = 0.0;

	
}

void Chainsaw::StateMachine(void)
{
	
//	if((ChainsawRequest->Request_Manual == true) && (LastChainsawRequest->Request_Manual == false))
//	{
//		NextState = CHAINSAW_STATE_MANUAL;
//	}
	
	switch(NextState)
	{
		case CHAINSAW_STATE_INIT:
			//TODO Add sensor init code
			break;
	
		case CHAINSAW_STATE_DISABLE:
			
			CurrentState = CHAINSAW_STATE_DISABLE;
			
			ChainsawMotor->Set(CHAINSAW_STOP);
			
			break;
			
		case CHAINSAW_STATE_AUTO_ACQUIRE:
			
			CurrentState = CHAINSAW_STATE_AUTO_ACQUIRE;
			
			//TODO Fix mispellings
			ChainsawMotor->Set(CHAINSAW_ACQUIRE);
	
			CurrentChainsawUltrasonic = ChainsawUltrasonic->GetRangeInches();
			
			if(((PreviousChainsawUltrasonic - CurrentChainsawUltrasonic) <= CHAINSAW_ULTRASONIC_EDGE) && (CurrentChainsawUltrasonic < CHAINSAW_MINIMUM_IN_POSITION_BAND))
			{
				NextState = CHAINSAW_STATE_IN_POSSESSION;
			}
			
			PreviousChainsawUltrasonic = CurrentChainsawUltrasonic;
			
			break;
			
		case CHAINSAW_STATE_IN_POSSESSION:
			
			CurrentState = CHAINSAW_STATE_IN_POSSESSION;
			break;
			
		case CHAINSAW_STATE_AUTO_DROP:
			
			CurrentState = CHAINSAW_STATE_AUTO_DROP;
						
			ChainsawMotor->Set(CHAINSAW_DROP);
			
			//TODO Add encoder code here, or whatever sensor gets feedback from the chainsaw
			
			break;
			
		case CHAINSAW_STATE_AUTO_HOLD:
			
			CurrentState = CHAINSAW_STATE_AUTO_HOLD;
			
			ChainsawMotor->Set(CHAINSAW_STOP);
			
			break;
			
		//TODO: Add manual states please!
		case CHAINSAW_STATE_MANUAL_ACQUIRE:
			
			ChainsawMotor->Set(CHAINSAW_ACQUIRE);
			
			break;
			
		case CHAINSAW_STATE_MANUAL_DROP:
			
			ChainsawMotor->Set(CHAINSAW_DROP);
			
			break;
			
		case CHAINSAW_STATE_MANUAL:
			
			if(CurrentState != NextState)
			{
				ChainsawMotor->Set(CHAINSAW_STOP);
			}
			
			CurrentState = CHAINSAW_STATE_MANUAL;
			
//			ChainsawMotor->Set(ChainsawRequest->Request_ChainsawMotorValue);
			
//			if((ChainsawRequest->Request_Manual == false) != (LastChainsawRequest->Request_Manual == true))
//			{
//				NextState = CHAINSAW_STATE_DISABLE;
//			}
			
            break;
			
		//TODO Add default case!
            	
			
	} //END SWITCH
	
//	LastChainsawRequest = ChainsawRequest;
	
} //END STATE MACHINE

void Chainsaw::Signal(CHAINSAW_STATES_T NextState)
{
	this->NextState = NextState; 
}

Chainsaw::CHAINSAW_STATES_T Chainsaw::Check(void)
{
	return this->CurrentState;
}

//void Chainsaw::Interface(Chainsaw::CHAINSAW_INTERFACE_T *ChainsawRequest)
//{
//	this->ChainsawRequest = ChainsawRequest;
//}
