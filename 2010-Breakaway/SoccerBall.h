#ifndef _SOCCER_BALL_H
#define _SOCCER_BALL_H

#include "Ultrasonic.h"
#include "RobotDrive.h"
#include "Gyro.h"
#include "math.h"

#define AUTO_LEFT_DRIVE_SPEED_NORMAL -0.5
#define AUTO_RIGHT_DRIVE_SPEED_NORMAL -0.5
#define AUTO_DRIVE_SPEED_STOP = 0.0

#define DISTANCE_SCAN_HAS_FOUND_BALL 36.0 // inches
#define DISTANCE_SCAN_BALL_IS_IN_DRIBBLER_RANGE 12.0 //inches

class SoccerBall
{
	public:
		
		typedef enum
		{
			SCAN_SUCCESS__PARTIAL_SUCCESS = 1,
			SCAN_SUCCESS__FULL_SUCCESS = 2,
			SCAN_SUCCESS__NO_SUCCESS = 3
		}SCAN_SUCCESS;
		SCAN_SUCCESS ScanSuccess;
		
		SoccerBall(Ultrasonic *ScanUltrasonic, RobotDrive *base, Gyro *gyro);
		void ScanFor(); //true is left
		void StopScanFor(void);
		SCAN_SUCCESS IsFound(void);
		void GoRetrieve(void);
		void StopRetrieve(void);
		
		Ultrasonic *ScanUltrasonic;
		RobotDrive *base;
		Gyro *gyro;
		
		double InitialGyroPosition;
		bool StartedScan;
		bool InitialScanPath;
		
		
	
	    double ScanDistance;
};


#endif
