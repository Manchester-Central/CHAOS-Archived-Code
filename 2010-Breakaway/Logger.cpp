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
	if ( file!= NULL)
	fflush(file);
}
void Logger::post()
{
	if ( file!=NULL)
		fprintf(file, LOG_FORMAT,
				GetTime(), AutoStateEnum
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

