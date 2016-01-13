#ifndef LOGGER_H
#define LOGGER_H

#include "WPILib.h"
//GetRPM (int) desiredRPM (int)  integralErrorRPM (int)  adjustedShootPower (float)
#define LOG_HEADER "Time,Mark,LEncod,REncod,LWindup,RWindup,LDrvJoy,RDrvJoy,LDrvMot,RDrvMot,Period,Gyro,Accel,AccelF,VChassis,VChasL,VChasR, LWheelV, RWheelV, ShootRPM, DesiredRPM, ShootWindup, ShootVolts\r\n"
#define LOG_FORMAT "%1.2f,%d,%d,%d,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%f,%f,%f,%1.3f\r\n"

class Logger
{
public:
	Logger() : file(NULL) {}
	void openIfClosed();
	void flush();
	void post();
	void closeIfOpen();
	
	bool markButton;
	int chassisEncoders[2];
	
	float chassisWindup[2];
	float driverJoy[2];
	float driveMotorOut[2];
	float actualPeriod;
	float gyro;
	float accel;
	float accelf;
	float vChassis;
	float vChaSide[2];
	float chassisEncodersV[2];
	float KP[2];
	float KI[2];
	float switches[3];
	float shootRPM;
	float desiredRPM;
	float shootWindup;
	float shootVolts;
	float mailLoopTm1;
	float mailLoopTm2;
	float mailLoopTm3;
	float mailLoopTm4;
	
private:
	FILE* file;
};

extern Logger logger;

#endif //LOGGER_H
