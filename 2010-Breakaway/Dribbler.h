#ifndef _DRIBBLER_H_
#define _DRIBBLER_H_

//#include "Breakaway10.h"
#include "WPILib.h"
#include "Victor.h"
#include "References.h"
#include "DashSharing.h"
#include "Task.h"
#include "Encoder.h"
#include "Ultrasonic.h"
#include "RobotDrive.h"
#include "DigitalModule.h"
#include "DigitalInput.h"
#include "Gamepad.h"
#include "Solenoid.h"

#define RELEASE 0

#define PI 3.14159265
#define DRIVE_WHEEL_CIRCUMFERENCE 63.84 //cm
#define SKATE_WHEEL_CIRCUMFERENCE 7.2 * PI //cm
#define BALL_CIRCUMFERENCE 22.86 * PI //cm

#define BALL_IS_IN_DRIBBLER_DISTANCE 6 //inches

#define DRIBBLER_SET_OFF 0 


class Dribbler
{	
public:
		
		
		double m_KL;
		double m_AL;
		double m_KR;
		double m_AR;
		
		float LeftDriveRate;
		float LeftDriveRPM;
		float LeftBallRPM_Goal;
		float LeftSkateRPM_Goal;
		float LeftDribblerRPM_Goal;
		float LeftDribbler_Out;
		
		float RightDriveRate;
		float RightDriveRPM;
		float RightBallRPM_Goal;
		float RightSkateRPM_Goal;
		float RightDribblerRPM_Goal;
		float RightDribbler_Out;
		
		bool DribblerHasBall;
		
		Dribbler(DashSharing *DashDataPass);
		Dribbler(DashSharing *DashDataPass, Encoder *LeftEncoderPass, Encoder *RightEncoderPass, Gamepad *Driver);
		void Keep();
		void Release(void);
		void SetConstants(double KL, double AL, double KR, double AR);
		void DribblerStateMachine(void);
		void Start(void);
		void Stop(void);
		bool BallIsInDribbler(void);
		
		Victor *LeftDribbler;
		Victor *RightDribbler;
		DashSharing *DashData;
		
		Solenoid *TheLight;

		RobotDrive *base;
		
		DigitalInput *LeftDribblerLimitSwitch;
		DigitalInput *RightDribblerLimitSwitch;
		
		bool LeftSwitch;
		bool RightSwitch;
		int LimitSwitchStatus;
		
		Gamepad *Driver;
	
private:
		
	   double RateToScaledOutput(double rate);
	   ~Dribbler(void);
	   Task DribblerTask;
	   bool m_Enabled;
};

#endif
