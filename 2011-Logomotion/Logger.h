/*-------------------------------------------------------------**
**                                                             
**   Filename: Logger.h                                        
**                                                             
**   About:    An object to output a csv file of data with timestamp 
**                                                             
**   Property of Chaos, Copyright 2009
**   Written by: Mr. Staub, Chaos.           
**   
**   Edited:                                                                                      
**   2011 1 29             
**                                                             
**-------------------------------------------------------------*/

#ifndef LOGGER_H
#define LOGGER_H

#include "WPILib.h"
#include "DashSharing.h"

#define LOG_HEADER "TimeStamp, LeftLineTracker, MidLineTracker, RightLineTracker, GyroAngle, Speed, Heading\r\n"
#define LOG_FORMAT "%1.2f, %n, %n, %n, %3.2f, %f, %f\r\n"

class Logger
{
public:
	Logger(DashSharing *DashData);
	void openIfClosed();
	void flush();
	void post();
	void closeIfOpen();
	
	bool LeftLineTracker;
	bool MidLineTracker;
	bool RightLineTracker;
	
	float Speed;
	float Heading;
	
	float GyroAngle;
	 
	
	DashSharing *DashData;
	
private:
	FILE* file;
};

extern Logger logger;

#endif //LOGGER_H
