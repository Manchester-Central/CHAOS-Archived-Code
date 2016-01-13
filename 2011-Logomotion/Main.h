/*-------------------------------------------------------------**
**                                                             
**   Filename: Main.h                                        
**                                                             
**   About:    The Main Logomotion Robot Class
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Steven Kroh 
**               Josh Allard
**               Ben Papp
**               Zain Abbas, Chaos.           
**                                                                                           
**   2011 1 16             
**                                                             
**-------------------------------------------------------------*/

#ifndef MAIN_H_
#define MAIN_H_

#include "Ultrasonic.h"
#include "WPILib.h"
#include "Refs.h"
#include "Gamepad.h"
#include "DashSharing.h"
#include "DashboardDataSender.h"
#include "LineFollowingStates.h"
#include "DriverStation.h"
#include "Gyro.h"
#include "Logger.h"
#include "Compressor.h"
#include "Shoulder.h"
#include "Elbow.h"
#include "Chainsaw.h"
#include "UltrasonicYAlign.h"
#include "Minibot.h"
#include "Manipulator.h"

class Main : public IterativeRobot
{
public:
	
	//Function Prototypes
	Main(void);
	
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
	
	float GetMaxbotixDistance(void);
	
	//Robot Base
	RobotDrive *Base;
	
	//Line Trackers
	DigitalInput *UpperLineTracker;
	DigitalInput *LowerLineTracker;
	
	//Gamepads
	Gamepad *DriverGamepad;
	Gamepad *OperatorGamepad;
	
	//Timers
	Timer *TeleopLoopTimer;
	Timer *AutoLoopTimer;
	Timer *AutoTimeOut; 
	
	//Dashboard
	DashSharing *DashData;
	DashboardDataSender *Dash;
	
	//Gyro 
	float AngleCorrectionModification;
	
	Gyro *LineFollowingGyro;
	
	//Logger - Uncomment to enable
	//Logger *DataLogger;
	
	//Compressor
	Compressor *PneumaticCompressor;
	
	//Ultrasonics
	Ultrasonic *LeftUltrasonic;
	Ultrasonic *RightUltrasonic;
	UltrasonicYAlign *WallAlign;
	
	AnalogChannel *MaxbotixUltrasonic;
	
	//Minibot
	Minibot *MinibotPart;

	//Manipulator
	Manipulator *ManipulatorDevice;
	
	//Human Player Light Indicators
	Relay *IndicatorRedWhite;
	Relay *IndicatorBlue;
	

	
	//AutonomousSwitch
	DigitalInput *AutonomousLimitSwitch;
		
	//Autonomous States Enumeration Typedef
	typedef enum 
	{
		AUTO_STATE_BEGIN = 0,
		AUTO_STATE_FORWARD = 1,
		AUTO_STATE_ALLIGN_RIGHT = 2,
		AUTO_STATE_ALLIGN_LEFT = 3,
		AUTO_STATE_TARGETTED = 4,
		AUTO_STATE_INIT = 5,
		AUTO_STATE_SCORE = 7,
		AUTO_STATE_BACKUP = 8,
		AUTO_STATE_DEAD_RECKON = 9,
		AUTO_STATE_POSITION_ROBOT = 10,
		AUTO_STATE_POSITION_ROBOT_PAUSE = 11
		
	}AUTO_STATES;
	
	AUTO_STATES NextAutoState;
	AUTO_STATES CurrentAutoState;
	
	typedef enum
	{
		PEG_Z_CENTER = 0,
		PEG_Z_NORMAL = 1
	}PEG_Z_SETTING;
	
	PEG_Z_SETTING PegZSetting;
	
	//Autonomous Sloping
	float AutoStateTimeout;
	float PercentNumerator;
	float PercentDenominator;
	float PercentPower;
	
	//Minibot Deployment
	Solenoid *DeploySolenoid;
	Solenoid *FlapSolenoid;

	//Edge Detection for Manual Mode
	bool CurrentManualMode;
	bool PreviousManualMode;
	
	//Flow Variables for the Human Player Indicator Light System
	bool RedLightCommand;
	bool RedLightLatch;
	bool BlueLightCommand;
	bool BlueLightLatch;
	bool WhiteLightCommand;
	bool WhiteLightLatch;
	
	//Edge Detection
	bool CurrentFlapButton;
	bool PreviousFlapButton;
	
	double UltraSonicDistance;
	
	//Tube Shuttle
	Solenoid *ShuttleSolenoid;
	
	bool ShuttleStatus;
	bool CurrentShuttleButton;
	bool PreviousShuttleButton;
	
	int SonarGoodCount;
};

#endif
