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

#ifndef ELBOW_H_
#define ELBOW_H_

#include "WPILib.h"
#include "Refs.h"
#include "LinearPot.h"

class Elbow
{	
public:
	
	//Typedef of the various angle states of the Elbow
	typedef enum
	{
		STATE_UP_CENTER_TOP = 0,
		STATE_UP_SIDE_TOP = 1,
		STATE_UP_CENTER_MIDDLE = 2,
		STATE_UP_SIDE_MIDDLE = 3,
		STATE_DOWN_CENTER_BOTTOM = 4,
		STATE_DOWN_SIDE_BOTTOM = 5,
		STATE_DOWN_PICKUP = 6,
		STATE_DOWN_STOW = 7,
		STATE_DOWN_PICKUP_HP = 8
	}ELBOW_STATES;
	
	//Instantiation of the angle states
	ELBOW_STATES NextAngle;
	ELBOW_STATES CurrentAngle;
	
	//Typedef of the state machine which controls the Elbow
	typedef enum
	{
		ELBOW_STATE_INIT = 0,
		ELBOW_STATE_DISABLE = 1,
		ELBOW_STATE_HOLD_MOTOR = 2,
		ELBOW_STATE_CORRECT_ANGLE = 3,
		ELBOW_STATE_ENABLE = 4,
		ELBOW_STATE_MANUAL = 5,
		ELBOW_STATE_MANUAL_DISABLE_UP = 6,
		ELBOW_STATE_MANUAL_DISABLE_DOWN = 7,
		ELBOW_STATE_PID_DISABLE_UP = 8,
		ELBOW_STATE_PID_DISABLE_DOWN = 9
	}ELBOW_STATES_T;
	
	//Instantiation of the Elbow states
	ELBOW_STATES_T NextState;
	ELBOW_STATES_T CurrentState;
	ELBOW_STATES_T StoreState;
	
	
	//Methods
	Elbow(void);
	void StateMachine(void);
	ELBOW_STATES_T Check(void);
	
	void Signal(ELBOW_STATES_T NextState);
	void SetGoalAngle(ELBOW_STATES NextAngle);
	void ManualSetMotor(float ManualMotorValue);
	
	float ManualMotorValue;
	
	float GoalAngle;
	float PreviousAngle;
	
	//Objects
	Victor *ElbowVictor;
	LinearPot *ElbowPot;
	
	//PID Controller
	PIDController *AngleCorrection;
	
	float ElbowProportionalConstant;
	float ElbowIntegralConstant;
	float ElbowDerivativeConstant;
	
	bool ElbowManualCheckInitial;
	bool ElbowManualCheckSecondary;
	
};

#endif
