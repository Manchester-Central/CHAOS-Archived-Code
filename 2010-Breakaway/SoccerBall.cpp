#include "SoccerBall.h"

SoccerBall::SoccerBall(Ultrasonic *ScanUltrasonic, RobotDrive *base, Gyro *gyro)
{
	this->ScanUltrasonic = ScanUltrasonic;
	this->base = base;
	this->gyro = gyro;
	
	InitialGyroPosition = 0.0;
	StartedScan = false;
	
	ScanSuccess = SCAN_SUCCESS__NO_SUCCESS;
	ScanDistance = 0.0;
	
	InitialScanPath = true;
}

void SoccerBall::ScanFor()
{
	if(StartedScan == false)
	{
		InitialGyroPosition = gyro->GetAngle();
		StartedScan = true;
		printf("Init\n");
	}
	
	if(InitialScanPath == true && StartedScan == true)
	{
		base->TankDrive(AUTO_LEFT_DRIVE_SPEED_NORMAL, -AUTO_RIGHT_DRIVE_SPEED_NORMAL);
		printf("Scan true\n");
	}
	else if(InitialScanPath == false && StartedScan == true)
	{
		base->TankDrive(-AUTO_LEFT_DRIVE_SPEED_NORMAL, AUTO_RIGHT_DRIVE_SPEED_NORMAL);
		printf("Scan false\n");
		
	}
	
	printf("Gyro Angle %f\n", gyro->GetAngle());
	printf("InitialScanPath %d\n", (int) InitialScanPath);
	printf("InitGyroPos: %f\n", InitialGyroPosition);
	bool Condition = ((fabs(fabs(gyro->GetAngle()) - InitialGyroPosition)) >= (45.0));
	printf("Condition: %d\n", (int) Condition);
	
	if(Condition)    
	{	
		InitialScanPath = !InitialScanPath;

		StartedScan = false;
	}
}

void SoccerBall::StopScanFor(void)
{
	base->TankDrive(0.0, 0.0);
}

SoccerBall::SCAN_SUCCESS SoccerBall::IsFound(void)
{
	ScanDistance = ScanUltrasonic->GetRangeInches()*(2.0);
	
	if(ScanDistance < DISTANCE_SCAN_BALL_IS_IN_DRIBBLER_RANGE)
	{
	    ScanSuccess = SCAN_SUCCESS__FULL_SUCCESS;	
	}
	else if(ScanDistance < DISTANCE_SCAN_HAS_FOUND_BALL)
	{
		ScanSuccess = SCAN_SUCCESS__PARTIAL_SUCCESS;
	}	
	else
	{
		ScanSuccess = SCAN_SUCCESS__NO_SUCCESS;
	}

	printf("Scan Success: %d\n", ((int) ScanSuccess));
	return ScanSuccess;
}

void SoccerBall::GoRetrieve(void)
{
	//Go forward
	base->TankDrive(AUTO_LEFT_DRIVE_SPEED_NORMAL, AUTO_RIGHT_DRIVE_SPEED_NORMAL);
}

void SoccerBall::StopRetrieve(void)
{
	//Stop
	base->TankDrive(0.0, 0.0);
}

