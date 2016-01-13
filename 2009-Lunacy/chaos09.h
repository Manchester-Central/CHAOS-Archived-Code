#ifndef CHAOS09_H
#define CHAOS09_H

#include "WPILib.h"
#include "ChaosVision.h"
#include "LowPassFilter.h"
#include "chaosAccel.h"
#include "chaosEncoder.h"
#include "chaosLinear.h"
#include "Gamepad.h"
#include "inputtask.h"
#include "math.h"
#include "chaosJaguar.h"
#include "DashboardDataFormat.h"
#include "ShooterTach.h"
//#include "Dashboard.h"

#define DRAGGING true		// define to false if not dragging (don't just comment out)
#if DRAGGING
#include "DragEncoder.h"
#endif


class ChaosRobot : public IterativeRobot
{
	/* Objects */
	
	//Task visiontask;
	Gamepad pilot1;
	Gamepad pilot2;
	chaosJaguar motor1;
	chaosJaguar motor2;
	Victor turret;
	chaosJaguar shooter1;
	// Removed shooter2 - for dumper version - tbinns 053009
	// chaosJaguar shooter2;
    Relay unjammer;
	Relay shootRoller;
    Victor lifter;
    Victor intake;
//  AnalogTrigger shooterTrigger;
    ShooterTach shooterTach;
//	DigitalInput hallSensorDI;
	//chaosLinear linear_y;
	chaosEncoder l_encoder;
	chaosEncoder r_encoder;
	Timer timer;
	LowPassFilter LPF1;
	LowPassFilter LPF2;
	LowPassFilter LPFT;
#if DRAGGING
	chaosEncoder leftDragger, rightDragger;
#endif	
	Encoder turretencoder;
	DigitalInput leftRight_DI;
	DigitalInput additionalAngle_DI;
	DigitalInput additionalDirection_DI;   
	Relay thelight;
	
	/* tbinns 10/18 removed the old reference and added in example */
	// DashboardDataFormat dashData;
	DashboardDataFormat dashboardDataFormat;
	// 10/22/09 tbinns this needs to be uncommented
	// Dashboard dashboard;
	
		
public:
	
	ChaosRobot(void);
	void func_drive(float rjoy, float ljoy);
	void func_notraction(float rjoy, float ljoy);
	void func_traction(float rjoy, float ljoy);
	void func_tractioninit(void);
	void RobotInit(void);
	void DisabledInit(void);
	void DisabledContinuous(void);
	void AutonomousContinuous(void);
	bool autonomousWait(float secs);

	void TeleopContinuous(void);
	void TurretTrack(void);
	void TurretSelfCalibrate(void);
	void Shooter(void);
	void setSlewPower(float power);
	void TurretReadCalibration();
	int readTurretEncoder();
	bool AutoTrack(void);
	void MobileAutoTrack(void);
	void slewControl(float rightDirection, float leftDirection);
	static int sign(float x);
	void TeleopInit(void);
	void readCalibrationFile(void);
	void writeCalibrationFile(void);
	/* tbinns 10/18 added referrence to match functions */
	void ChaosRobot::UpdateDashboard(void);
	void ChaosRobot::DashPrintf(char* txt);
	
	int m_turretLeftLimit; 
	int m_turretRightLimit;
	int range;
	int m_turretCenter;
	
    float VerrorL_Integral;
	float VerrorR_Integral;
	float VerrorL;
	float VerrorR;
	float JoyLDelta;
	float JoyRDelta;
	
	float PreviousLJoyY;
	float PreviousRJoyY;
	
	float lastGyroTime;
	//float shooterpower;
	float lastShootPower;
	float integralErrorRPM;
	double shooterIntegral;
	
	float turret_error_i;
	bool  turret_centering;
	
	// Caution - cal file is read directly into these...
	// don't change to doubles without changing cal file handling
	float KPL, dummy, KPR, KIL, KIR;
	
	int modeloops;
	
	enum{kslewleft, kslewright, ktrack} turretstate;
	
	static ChaosRobot& getChaosRobot()
	{
		return (ChaosRobot&) getInstance();
	}
	//Timer timer;
	/*
	static Dashboard& getDashboard()
	{
		return getChaosRobot().getMyDashboard();
	}
	Dashboard& getMyDashboard()
	{
		return m_ds->GetDashboardPacker();
	}
	*/

};

#endif


