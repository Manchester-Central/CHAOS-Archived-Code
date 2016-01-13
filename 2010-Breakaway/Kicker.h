#ifndef _KICKER_H_
#define _KICKER_H_


#define SET_VALVE_TRUE_DELAY 0.1
#define SET_VALVE_FALSE_DELAY 0.01
#define SET_AFTER_KICK_DELAY 1

#define SINGLE_COIL_VALVE true

#define LOWER_HYSTERETIC_BAND 1.0  //cm
#define UPPER_HYSTERETIC_BAND 1.0 //cm

#define STOW_DISTANCE 17 //cm
#define FULL_ON_DISTANCE 2.0//cm

#define WHEEL_STOW_DISTANCE_GOAL 17.0 //cm

#define EXTEND_DISTANCE_INCRIMENT 1.0 //cm
#define EXTEND_DISTANCE_INCRIMENT_LARGE 5.0 //cm
#define EXTEND_DISTANCE_MAX 19.0 //cm
#define EXTEND_DISTANCE_MIN 0.0 //cm

#define NEAR_DISTANCE 11.0 //cm
#define MID_DISTANCE 15.0 //cm
#define FAR_DISTANCE 19.0 //cm

#define DISTANCE_OFFSET_DECRIMENT 1.0 //cm
#define DISTANCE_OFFSET_INCREMENT 1.0 //cm

#include "References.h"
#include "Buttons.h"
#include "ChaosLinearPot.h"
#include "Solenoid.h"
#include "Timer.h"
#include "Buttons.h"
#include "Gamepad.h"
#include "Task.h"
#include "RobotBase.h"
#include "DashSharing.h"
#include "AutonomousKickerInterface.h"

class Kicker
{
	public:
		Solenoid *ExtenderA;
		Solenoid *ExtenderB;
		Solenoid *RetractorA;
		Solenoid *RetractorB;
		Solenoid *LatchA;
		Solenoid *LatchB;
		Solenoid *VentA; //temp using double solenoid for vent, cant comment out this code though
		Solenoid *VentB; //same here
		
		ChaosLinearPot *LinearPot;
		DashSharing *DashData;

		double RetractDistance;
		double ExtendDistance;
		double SitForShootDistance;
		
		double SavedManualExtendDistance;
		bool SaveExtendDistance;
		bool ReadExtendDistance;
		
		double WheelStowDistanceGoal;
		
		bool ExtendActionManual;
		
		void DoSetExtendDistanceManual(bool ExtendActionManual);
		
		void SetExtendDistance(double ExtendDistancePass);
		void SetWheelStowDistance(double WheelStowDistancePass);
		
		bool IsDistanceExtended();
		
		
		typedef enum
		{
			VALVE_CMD__TENSIONER_EXTEND,
			VALVE_CMD__TENSIONER_EXTEND_ON, 
			VALVE_CMD__TENSIONER_EXTEND_PAUSE, 
			VALVE_CMD__TENSIONER_CLEAR_ALL_VALVES,
			VALVE_CMD__TENSIONER_RETRACT_TO_LOAD, 
			VALVE_CMD__LATCH_SHOOT,
			VALVE_CMD__RELEASE_LATCH_AND_HOLD_RETRACT,
			VALVE_CMD__RETRACT_PLUGGED,
			VALVE_CMD__RETRACT_HOLD_PLUGGED,
		}VALVE_CMD;
			
		typedef enum
		{
			KICK_STATE__RETRACT = 1,
			KICK_STATE__EXTEND_ON = 2,
			KICK_STATE__EXTEND_PAUSE = 3,
			KICK_STATE__SIT_FOR_SHOOT = 4,
			KICK_STATE__SHOOT = 5,
			KICK_STATE__SET_RETRACT = 6,
			KICK_STATE__RETRACT_ON = 7,
			KICK_STATE__RETRACT_PAUSE = 8,
			KICK_STATE__RETRACT_TO_STOW = 9,
			KICK_STATE__RELEASE_LATCH_STOW = 10,
			KICK_STATE__WAIT_STOW = 11,
			
			//Manual States
			KICK_STATE__MANUAL_RETRACT = 12,
			KICK_STATE__MANUAL_EXTEND = 13,
			KICK_STATE__MANUAL_LATCH = 14,
			KICK_STATE__MANUAL_WAIT = 15,
			
			//Stow States
			KICK_STATE__WHEEL_STOW_MOVE = 16,
			KICK_STATE__WHEEL_STOW_WAIT = 17,
			
		}KICK_STATE;
		
		typedef enum
		{
			BUMP_RETRACT__
		}BUMP_RETRACT;
		
		KICK_STATE NextState; 
		KICK_STATE CurrentState;
		
		KICK_STATE GetKickerStateMachineState(void);
		
		AutonomousKickerInterface *AutoInterface;
		
		Kicker(Gamepad *DriverPass, Gamepad *OperatorPass, DashSharing *DashData, AutonomousKickerInterface *AutoInterface);
		void InitKicker(void);
		void SetValveStates(VALVE_CMD valve_cmd);
		void ClearValveStates(void);
		//void KickerStateMachine(void);
		void Start(void);
		void Stop(void);
		bool Enabled(void);
		void KickerStateMachine(); //Want it started only by the task
		
		typedef enum
		{
			ZONE__NEAR,
			ZONE__MID,
			ZONE__FAR,
		}ZONE;
		ZONE zone;
		ZONE lastZone;
		
		double DistanceOffset;
		
	private:
		~Kicker();
		Gamepad *Driver;
		Gamepad *Operator;
		Task KickerTask;
		bool m_Enabled; //Controls if the loop is executed
		bool m_EnableProcess; //Controls if the statemachime is processed
};

#endif
