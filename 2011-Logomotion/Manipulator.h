/*-------------------------------------------------------------**
**                                                             
**   Filename: Manipulator.h                                        
**                                                             
**   About:    Controlls all the sub-parts of the manipulator 
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Steven Kroh           
**                                                                                           
**   2011 1 30           
**                                                             
**-------------------------------------------------------------*/

#ifndef MANIPULATOR_H_
#define MANIPULATOR_H_

#include "WPILib.h"
#include "Chainsaw.h"
#include "Elbow.h"
#include "Shoulder.h"
#include "Refs.h"
#include "Gamepad.h"
#include "DashSharing.h"


class Manipulator
{
public:
	
	typedef enum
	{
		MANIP_STATE_DISABLED = 0,
		MANIP_STATE_INIT = 1,
		MANIP_STATE_PRE_STOW = 9,
		MANIP_STATE_STOW = 7,
		MANIP_STATE_GROUND_ACQUIRE_INIT = 2,
		MANIP_STATE_GROUND_ACQUIRE = 3,
		MANIP_STATE_HOLD = 4,
		MANIP_STATE_GO_TO_PEG_HEIGHT = 5,
		MANIP_STATE_SCORE = 6,
		MANIP_STATE_MANUAL = 8,
		MANIP_STATE_HP_PICKUP = 10,
		MANIP_STATE_MAINTAIN_PEG_HEIGHT = 11,
		MANIP_STATE_PAUSE_FOR_BACKUP = 12,
		MANIP_STATE_AUTO_SCORE = 13,
		MANIP_STATE_AUTO_PRE_SCORE = 14
		
	}MANIP_STATES_T;
	
	typedef enum
	{
		PEG_Z_STATE_BOTTOM_NORM = 0,
		PEG_Z_STATE_MIDDLE_NORM = 1,
		PEG_Z_STATE_TOP_NORM = 2,
		PEG_Z_STATE_BOTTOM_CENT = 3,
		PEG_Z_STATE_MIDDLE_CENT = 4,
		PEG_Z_STATE_TOP_CENT = 5,
		PEG_Z_STATE_PICKUP_FLOOR = 6,
		PEG_Z_STATE_PICKUP_HP = 7,
		PEG_Z_STATE_INIT = 8
	}PEG_Z_STATES;
	
	MANIP_STATES_T NextState;
	MANIP_STATES_T CurrentState;
	
	PEG_Z_STATES NextPegZ;
	PEG_Z_STATES CurrentPegZ;
	
//	Chainsaw::CHAINSAW_INTERFACE_T ChainsawRequest;
	
	Manipulator(Gamepad *DriverGamepad, Gamepad *OperatorGamepad, DashSharing *DashData);
	void StateMachine(void);
	void Signal(MANIP_STATES_T NextState);
	void ChangePegZ(PEG_Z_STATES NextPegZ);
	MANIP_STATES_T GetRestoreState(void);
	MANIP_STATES_T Check(void);
	
	
	Chainsaw *ChainsawPart;
	Elbow *ElbowPart;
	Shoulder *ShoulderPart;
	Gamepad *DriverGamepad;
	Gamepad *OperatorGamepad;
	DashSharing *DashData;
	Timer *ScoreTimeout;
	
	//MultiButton *EscapeButton;
	
private:
	MANIP_STATES_T RestoreState;
	
};

#endif
