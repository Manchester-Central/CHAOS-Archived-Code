/*-------------------------------------------------------------**
 **                                                             
 **   Filename: Manipulator.h                                        
 **                                                             
 **   About:    The ReboundRumble Robot Class Manipulator
 **                                                             
 **   Property of Chaos, Copyright 2012
 **   Written by:  
 **               Josh Allard
 **               Ben Papp
 **               Zain Abbas           
 **               Eric Moy, Chaos.                                                                            
 **   2012 1 28             
 **                                                             
 **-------------------------------------------------------------*/

#ifndef MANIPULATOR_H_
#define MANIPULATOR_H_


#include "WPILib.h"
#include "Gamepad.h"
#include "Refs.h"
#define NDEBUG
#include "boost/circular_buffer.hpp"

class Manipulator
{
	public:
	
	typedef enum
	{
		MANIP_STATE_DISABLED = 0,
		MANIP_STATE_INIT = 1,
		MANIP_STATE_RELOAD = 2,
		MANIP_STATE_SHOOT = 3,
		MANIP_STATE_AUTO_SHOOT = 4,
		MANIP_STATE_MANUAL = 5
	}MANIP_STATES_X;

	float BallCount;
	
	Timer *ShootTimer;

	MANIP_STATES_X NextState;
	MANIP_STATES_X CurrentState;
	
	Manipulator(Gamepad *OperatorGamepad);
	void StateMachine(void);
	void ChangeNextState(MANIP_STATES_X NextState);
	MANIP_STATES_X CheckState(void);
	
	Victor *BottomShooterMotor;
	Victor *TopShooterMotor;
	Victor *IntakeMotor;
	Victor *ConveyorMotor;
	Gamepad *OperatorGamepad;
	
	
	Encoder *TopShooterEncoder;
	Encoder *BottomShooterEncoder;
	
	PIDController *TopShooterMotorControl;
	PIDController *BottomShooterMotorControl;
	float ProportionalConstant;
	float IntervalConstant;
	float DerivativeConstant;
	float ShootSpeed;
	
	float PreviousEncoderValue;
	float CurrentEncoderValue;
	
	float ShooterProportionalPower;
	
	DigitalInput *LightSensorIntake;
	DigitalInput *LightSensorOutput;
	DigitalInput *LightSensorConveyor;
	bool PreviousLightIntakeBool;
	bool PreviousLightOutputBool;
	
private:
		boost::circular_buffer<float> mBuffer;
};

#endif
