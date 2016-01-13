/*-------------------------------------------------------------**
**                                                             
**   Filename: Chainsaw.h                                        
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

#ifndef CHAINSAW_H_
#define CHAINSAW_H_

#include "Ultrasonic.h"
#include "WPILib.h"
#include "Refs.h"

class Chainsaw
{
public:
	//Typedef of the Chainsaw states for the state machine
	typedef enum
	{
		CHAINSAW_STATE_INIT = 0,
		CHAINSAW_STATE_DISABLE = 1,
		CHAINSAW_STATE_AUTO_ACQUIRE = 2,
		CHAINSAW_STATE_AUTO_DROP = 3,
		CHAINSAW_STATE_AUTO_HOLD = 4,
		CHAINSAW_STATE_MANUAL_ACQUIRE = 5,
		CHAINSAW_STATE_MANUAL_DROP = 6,
		CHAINSAW_STATE_IN_POSSESSION = 7,
		CHAINSAW_STATE_MANUAL = 8
		
	}CHAINSAW_STATES_T;
	
//	typedef struct
//	{
//		bool Request_Manual;
//		float Request_ChainsawMotorValue;
//	}CHAINSAW_INTERFACE_T;
//	
//  CHAINSAW_INTERFACE_T *ChainsawRequest;
//  CHAINSAW_INTERFACE_T *LastChainsawRequest;
	
	//Methods
	Chainsaw(void);
	void StateMachine(void);	
	void Signal(CHAINSAW_STATES_T NextState);
//	void Interface(CHAINSAW_INTERFACE_T *ChainsawRequest);
	
	CHAINSAW_STATES_T Check(void);
	//Objects
	//DigitalInput *LimitSwitch;
	
	Ultrasonic *ChainsawUltrasonic;
	
	//TODO Add Encoder Code Here
	
	Victor *ChainsawMotor;
	
	//Instantiation of the state typedef for use in the state machine
	CHAINSAW_STATES_T NextState;
	CHAINSAW_STATES_T CurrentState;
	
	//Ultrasonic Edge Detection
	double CurrentChainsawUltrasonic;
	double PreviousChainsawUltrasonic;
	
};

#endif
