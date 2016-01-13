/*-------------------------------------------------------------**
**                                                             
**   Filename: Logger.cpp                                        
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

#include "Logger.h"

Logger::Logger(DashSharing *DashData) : file(NULL)
{
	this->DashData = DashData;
}

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
	if ( file!= NULL)
	fflush(file);
}
void Logger::post()
{
	if ( file!=NULL)
		fprintf(file, LOG_FORMAT,
				GetTime(),
				DashData->UpperLineTracker_D,
				DashData->LowerLineTracker_D,
				//DashData->RightLineTracker_D,
				DashData->LineFollowingGyroAngle_D,
				DashData->Speed_D,
				DashData->Heading_D
		);
  flush();
	
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

