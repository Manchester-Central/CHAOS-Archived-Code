/*-------------------------------------------------------------**
**                                                             
**   Filename: Minibot.h                                        
**                                                             
**   About:    An object to control the Minibot functions.             
**   
**   Property of Chaos, Copyright 2011
**   Written by: Jallard and Bpapp, Chaos.           
**                                                                                           
**   2011 2 8           
**                                                             
**-------------------------------------------------------------*/

#ifndef MINIBOT_H_
#define MINIBOT_H_

#include "WPILib.h"
#include "Refs.h"

class Minibot
{
	
public:
	
	typedef enum
	{
		MINIBOT_STATE_INIT = 0,
		MINIBOT_STATE_WAIT = 1,
		MINIBOT_STATE_DEPLOY_FLAP_PISTON = 2,
		MINIBOT_STATE_DEPLOY_BOT = 3,
		MINIBOT_STATE_DEPLOY_FLAP_SERVO = 4,
		MINIBOT_STATE_WAIT_DEPLOY_PISTON = 5
	}MINIBOT_STATES;
	
	typedef enum
	{
		MINIBOT_VALVE_CMD_INIT = 0,
		MINIBOT_VALVE_CMD_WAIT = 1,
		MINIBOT_VALVE_CMD_DEPLOY_FLAP = 2,
		MINIBOT_VALVE_CMD_DEPLOY_BOT = 3
	}MINIBOT_VALVE_CMDS;
	
	MINIBOT_VALVE_CMDS MinibotValveCmd;
	MINIBOT_STATES NextMinibotState;
	MINIBOT_STATES CurrentMinibotState;
	
	Minibot(void);
	void StateMachine(void);
	void SetMinibotValveStates(MINIBOT_VALVE_CMDS MinibotValveCmd);
	MINIBOT_STATES Check(void);
	void Signal(MINIBOT_STATES NextState);
	
	Solenoid *DeploySolenoid;
	Solenoid *FlapSolenoid;
	
	Servo *FlapPinServo;
	Timer *FlapPinTimer;
	
	bool AllowDeploy;

};

#endif 
