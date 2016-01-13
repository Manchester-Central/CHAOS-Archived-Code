#ifndef _MAIN_H
#define _MAIN_H

#include "WPILib.h"
#include "RobotDrive.h"
#include "Vision/AxisCamera.h"
#include "Vision/HSLImage.h"
#include "PIDController.h"
#include "Gyro.h"
#include "Gamepad.h"
#include "Target.h"
#include "DashboardDataSender.h"
#include "SamplePIDOutput.h"
#include "References.h"
#include "Dribbler.h"
#include "Kicker.h"
#include "DashSharing.h"
#include "DriverStationEnhancedIO.h"
#include "math.h"
#include "AutonomousKickerInterface.h"
#include "SoccerBall.h"
#include "Timer.h"
#include "DigitalInput.h"
#include "Logger.h"

#define EXTEND_POT_MULTIPLIER 7.3 //Changes potentiometer output of 0 - 3.3 v to a cm range equal to the range of the linear pot (0-24 cm) 
#define ULTRA_WIDTH 24 //inches

#define SAFE_DRIBBLER_RETRIEVE_TIME 2.5 //seconds
#define WAIT_FOR_WAIT_FOR_SHOOT_TIME 0.5 //seconds

#define TELEOP_PERIOD .025 //Seconds (25 ms)
#define AUTO_PERIOD .025 //Seconds (25 ms)

#define IO_UPDATE_TIME_NORMAL 0.1
#define IO_UPDATE_TIME_SLOW 0.4

#define AUTO_HORIZONTAL_ANGLE_ALIGNED 5//degrees
#define HORIZONTAL_HYSTERISIS 1//degree

double outputValue;

class Breakaway10 : public IterativeRobot 
{
public:
	AutonomousKickerInterface *AutoInterface;
	RobotDrive *base;
	Gamepad *driverStick;
	Gamepad *operatorStick;
	Gyro *gyro;
	PIDOutput *pidOutput;
	PIDController *turnController;
	AxisCamera &camera;
	Compressor *compressor;
	Encoder *rightEncoder;
	Encoder *leftEncoder;
	Ultrasonic *ballDistanceUltrasonic;
	DashSharing *DashData;
	DashboardDataSender *dds;
	Dribbler *dribbler;
	Kicker *ChaosKicker;
	DriverStationEnhancedIO &dseio;
	SoccerBall *Ball;
	Timer *AutoSafeGuardTimer;
	Timer *TeleopLoopTimer;
	Timer *AutoLoopTimer;
	Logger *ChaosLogger;

		Breakaway10(void); 
		
		virtual void TeleopContinuous(void);
		virtual void AutonomousContinuous(void);
		virtual void DisabledContinuous(void);
		
		virtual void TeleopPeriodic(void);
		virtual void AutonomousPeriodic(void);	
		virtual void DisabledPeriodic(void);
		
		virtual void RobotInit(void);
		virtual void DisabledInit(void);
		virtual void AutonomousInit(void);
		virtual void TeleopInit(void);
		
		bool AutonomousWait(float secs);
		
		double TargetFunction(bool trigger, bool lastTrigger);
		double GetTargetExtendDistance(double TargetDistance);
		
		double AutonomousTargetDistance;
		double TargetHorizontalAngle;
		
		double AutonomousPot;
		double AutonomousExtendDistance;
		
		double KLPot_Value;
		double KRPot_Value;
		double ALPot_Value;
		double ARPot_Value;
		
		double DistanceOffset;
		
		SoccerBall::SCAN_SUCCESS ScanResult;

};

typedef enum
{
	AUTO_STATE__BEGIN = 1,
	AUTO_STATE__FIND_BALL = 2,
	AUTO_STATE__GET_BALL = 3,
	AUTO_STATE__HOLD_BALL = 4,
	AUTO_STATE__TARGET = 5,
	AUTO_STATE__PREPARE_FOR_KICK = 6,
	AUTO_STATE__KICK_BALL = 7,
	
}AUTONOMOUS_STATES;



#endif

		
