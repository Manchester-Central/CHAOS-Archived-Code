#ifndef LOGGER_H
#define LOGGER_H

#include "WPILib.h"

#define LOG_HEADER "TimeStamp, AutoState\r\n"
#define LOG_FORMAT "%1.2f, %d\r\n"

class Logger
{
public:
	Logger() : file(NULL) {}
	void openIfClosed();
	void flush();
	void post();
	void closeIfOpen();
	
	int AutoStateEnum;
	
private:
	FILE* file;
};

extern Logger logger;

#endif //LOGGER_H
