/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef CHAOSSERVO_H
#define CHAOSSERVO_H

//#include "PWM.h"
//#include "SpeedController.h"
#include "WPILib.h"

#define DISTANCEPERPULSE 4;

/**
 * Standard hobby style servo.
 * 
 * The range parameters default to the appropriate values for the Hitec HS-322HD servo provided
 * in the FIRST Kit of Parts in 2008.
 */
class chaosServo  //: public PWM, public SpeedController, public Encoder
{
public:
	explicit chaosServo(UINT32 channelEncoder, UINT32 channelJaguar );
	chaosServo(UINT32 slotEncoder, UINT32 channelEncoder,UINT32 slotPWM, UINT32 channelPWM);
	virtual ~chaosServo();
	void Set(float value);
	float Get();
	void SetAngle(float angle);
	float GetAngle();
	static float GetMaxAngle(){ return kMaxServoAngle; };
	static float GetMinAngle(){ return kMinServoAngle; };
	void SetSpeed(float speed){ SetSpeed(speed);} ;
	
	
	Encoder encoder;
	PWM turret;

private:
	void InitServo(void);
	void CalServo(void);
	float GetServoAngleRange(){return kMaxServoAngle - kMinServoAngle;};
	void Move(float angle);

	static const float kMaxServoAngle = 130.0;
	static const float kMinServoAngle = 0.0;
};

#endif

