/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "chaosServo.h"

int direction = 0;
float curAngle = 0;
float encoderCount = 0;
double encoderValue = 0;

/**
 * Common initialization code called by all constructors.
 *
 * InitServo() assigns defaults for the period multiplier for the servo PWM control signal, as
 * well as the minimum and maximum PWM values supported by the servo.
 */
void chaosServo::InitServo()
{
	//SetBounds(245, 0, 0, 0, 11);
	//SetPeriodMultiplier(kPeriodMultiplier_4X);
	INT32 max = 251; 
	INT32 deadbandMax = 135; 
	INT32 center = 128; 
	INT32 deadbandMin = 120;
	INT32 min = 4;
	turret.SetBounds(max, deadbandMax, center, deadbandMin, min);
	turret.SetPeriodMultiplier(turret.kPeriodMultiplier_1X);
	turret.SetRaw(center);
	encoder.Start();
	CalServo();
}

/**
 * Constructor that assumes the default digital module.
 *
 * @param channel The PWM channel on the digital module to which the servo is attached.
 */
chaosServo::chaosServo(UINT32 channelEncoder, UINT32 channelJaguar):
	encoder(channelEncoder, channelEncoder + 1 , false,  Encoder::k2X), 
	turret(channelJaguar)
{
	InitServo();
}

/**
 * Constructor that specifies the digital module.
 *
 * @param slot The slot in the chassis that the digital module is plugged into.
 * @param channel The PWM channel on the digital module to which the servo is attached.
 */
chaosServo::chaosServo(UINT32 slotEncoder, UINT32 channelEncoder,UINT32 slotJaguar, UINT32 channelJaguar):
	encoder(slotEncoder, channelEncoder, channelEncoder + 1, false , Encoder::k2X), 
	turret(slotJaguar, channelJaguar)
{
	InitServo();
}

chaosServo::~chaosServo()
{
}

/*
 * Calibrate the angle of the turret travel
*
* Test for encoder moving and start jaguar, read until encoder starts and then stops
*
* Record count, then start jaguar in oposite direction at the 
* slowest posible speed, stop when encoder starts to change
*
* Reset count on encoder this is zero
*
* Drive jaguar in oposite direction until encoder stops, then reverse direction and stop when encoder changes.
*
* Record this as the max angle and divide by 2 for middle position
 * 
 */
void chaosServo::CalServo()
{
	float encoderValue;
	//float kMaxServoAngle = 130.0;
	encoder.Reset();
	// Need to calculate the angle to pulse so we can get angle from the encoder, somewhat???
	// 1440 pulses per revolution (reads all the highs)
	// 360/1140 = 4 pulses per degree
	encoder.SetDistancePerPulse(4);
	
	// Move it to one side and reset the encoder
	SetSpeed(.01);
	do
	{
		encoderValue = encoder.GetDistance();
	}while (encoder.GetStopped());
	SetSpeed(0);
	// Now reset the encoder to get the complete swing number of pulses
	encoder.Reset();
	SetSpeed(-.01);
	do
	{
		encoderValue = encoder.GetDistance();
	}while (encoder.GetStopped());
	// Now we now how many count from stop to stop
	// Reduce it by 10 degees so we don't hit the stops
	encoderCount =  encoderValue - 10;
	//Move the turret to the center
	SetSpeed(.01);
	do
	{
		encoderValue = encoder.GetDistance();
	}while (encoderValue >= (encoderCount/2)+5); // Need to add in half of the reduction so it is centered
	SetSpeed(0);

	
	//We were moving positive was the encoder. if not set it so it counts the same as the motor
	bool encoderDir = encoder.GetDirection();
	if (!encoderDir)
	{
		encoder.SetReverseDirection(true);
	}
	//kMaxServoAngle = curAngle = encoderValue;
	curAngle = encoderValue;
}

/**
 *  Drive the motor to the angle passed 
 * 
 * 
 * 
 */
void chaosServo::Move(float angle)
{
	float difAngle = 0;
	int direction = 1;
	float speed = 0;
	if (angle > kMaxServoAngle) angle = kMaxServoAngle;
	do
	{
		encoderValue = encoder.GetDistance();
		if(angle > curAngle)
		{
			difAngle = angle - encoderValue;
			direction = 1;
		}else{
			difAngle = encoderValue - angle;
			direction = -1;
		}
		// need to slope the motor to slow as the number gets lower
		// as the angle difference decrease we want to slow the motor to almost 0
		speed = difAngle/180;
		SetSpeed(speed * direction);
	}while (difAngle < 0  ); // Stop when we get to the new location
	curAngle = encoder.GetDistance();
	SetSpeed(0);
}


/**
 * Set the servo position.
 *
 * Servo values range from 0.0 to 1.0 corresponding to the range of full left to full right.
 *
 * @param value Position from 0.0 to 1.0.
 */
void chaosServo::Set(float value)
{
	// SetPosition(value);
	Move(value * 180);	// use 180 since the track is only a half circle
}

/**
 * Get the servo position.
 *
 * Servo values range from 0.0 to 1.0 corresponding to the range of full left to full right.
 *
 * @return Position from 0.0 to 1.0.
 */
float chaosServo::Get()
{
	// return GetPosition();
	return curAngle/180;	// use 180 since the track is only a half circle
}

/**
 * Set the servo angle.
 *
 * Assume that the servo angle is linear with respect to the PWM value (big assumption, need to test).
 *
 * Servo angles that are out of the supported range of the servo simply "saturate" in that direction
 * In other words, if the servo has a range of (X degrees to Y degrees) than angles of less than X
 * result in an angle of X being set and angles of more than Y degrees result in an angle of Y being set.
 *
 * @param degrees The angle in degrees to set the servo.
 */
void chaosServo::SetAngle(float degrees)
{
	if (degrees < kMinServoAngle)
	{
		degrees = kMinServoAngle;
	}
	else if (degrees > kMaxServoAngle)
	{
		degrees = kMaxServoAngle;
	}
	//SetPosition(((float) (degrees - kMinServoAngle)) / GetServoAngleRange());
	Move(degrees);
}

/**
 * Get the servo angle.
 *
 * Assume that the servo angle is linear with respect to the PWM value (big assumption, need to test).
 * @return The angle in degrees to which the servo is set.
 */
float chaosServo::GetAngle()
{
	// return (float)GetPosition() * GetServoAngleRange() + kMinServoAngle;
	return curAngle;
}
