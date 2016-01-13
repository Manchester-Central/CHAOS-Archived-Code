#include "Logger.h"


void Logger::openIfClosed()
{
	if ( file ) return;
	file = fopen("chaos.csv", "w");
	if ( file!= NULL)
	{
		fprintf(file,LOG_HEADER);
	}
	else
	{
		printf("Can't open log file\n");
	}
}
void Logger::flush()
{
	/*
	if ( file!= NULL)
	fflush(file);
	*/
}
void Logger::post()
{
	/*
	if ( file!=NULL)
		 fprintf(file, LOG_FORMAT,
				GetTime(), markButton,
				chassisEncoders[0],chassisEncoders[1],
				chassisWindup[0], chassisWindup[1],
				driverJoy[0], driverJoy[1],
				driveMotorOut[0], driveMotorOut[1],
				actualPeriod, gyro,
				accel, accelf, 
				vChassis, vChaSide[0], vChaSide[1], chassisEncodersV[0], chassisEncodersV[1], 
				shootRPM, desiredRPM, shootWindup, shootVolts
		);
	flush(); */
	
}
void Logger::closeIfOpen()
{
	//tbinns-20-26-09 Added flush, remove, rename to 
	// store the file so when closed it is store to get when turned on.
	if ( !file ) return;
	int result = fflush(file);
	fclose(file);
	file = NULL;
	result = remove("chaosHold.csv"); 
	result = rename("chaos.csv", "chaosHold.csv");
}

