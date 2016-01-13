/*
 * Shooter wheel tachometer
 * Looking for the .cpp file?
 * There isn't any!
 * 
 * */
#ifndef DRAGENCODER_H
#define DRAGENCODER_H

#include "WPILib.h"

#define DRAGGERYACK	// define to enable debug output
class DragEncoder
{
public:
	

	static const double DRAG_DIST_PER_TICK = .1;	// meters per encoder tick
	
	DragEncoder(char* name, UINT32 aChannel, UINT32 bChannel, bool direction)
	:	m_name(name), encoder(aChannel, bChannel, direction)
	{
		
		encoder.SetMaxPeriod(1000000 * 5); // stopped if we don't see anything for 5 secs 
		encoder.Start();
	}
	virtual ~DragEncoder()	{}

	// This should be idempotent, but has never been checked
	double GetSpeedMPS()  // revs per second
	{
		double speedMPS = 0;
		double period_sec = encoder.GetPeriod();	// period in seconds
		if ( !encoder.GetStopped() && period_sec != 0 )
		{
			speedMPS = DRAG_DIST_PER_TICK/period_sec;
		}
#ifdef DRAGGERYACK
		printf("DragEncoder: %f mps", speedMPS);
#endif
		return speedMPS;
	}

	const char* m_name;		// name, e.g. "left"

private:
	Encoder encoder;				// encoder object for 1x and 2x encoding
};

#endif

