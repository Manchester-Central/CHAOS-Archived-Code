/*-------------------------------------------------------------**
**                                                             
**   Filename: Shoulder.h                                        
**                                                             
**   About:    Shoulder Object
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Everyone, Chaos.           
**                                                                                           
**   2011 1 27       
**                                                             
**-------------------------------------------------------------*/

#ifndef SHOULDER_H_
#define SHOULDER_H_

#include "WPILib.h"
#include "Refs.h"
#include "LinearPot.h"

class Shoulder
{

public:
	
	typedef enum
	{
		SHOULDER_VALVE_CMD_UP,
		SHOULDER_VALVE_CMD_DOWN,
		SHOULDER_VALVE_CMD_DISABLE
	}SHOULDER_VALVE_CMD_T;
	
	SHOULDER_VALVE_CMD_T ShoulderValveCmd;
	SHOULDER_VALVE_CMD_T PreviousShoulderValveCmd;
	
	typedef enum
	{
		SHOULDER_STATE_INIT = 0,
		SHOULDER_STATE_DISABLE = 1,
		SHOULDER_STATE_UP = 2,
		SHOULDER_STATE_DOWN = 3,
		SHOULDER_STATE_HOLD = 4
	}SHOULDER_STATES_T;
	
	SHOULDER_STATES_T NextState;
	SHOULDER_STATES_T CurrentState;
	
	Shoulder(void);
	void StateMachine(void);
	void SetValveStates(SHOULDER_VALVE_CMD_T ShoulderValveCmd);
	
	void Signal(SHOULDER_STATES_T NextState);
	SHOULDER_STATES_T Check(void);
	
	
	Solenoid *ShoulderSolenoidLeft;
	Solenoid *ShoulderSolenoidRight;
	
	LinearPot *ShoulderPot;
	
};

#endif
