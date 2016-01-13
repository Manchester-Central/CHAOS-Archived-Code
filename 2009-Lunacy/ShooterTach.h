/*
 * Shooter wheel tachometer
 * Looking for the .cpp file?
 * There isn't any!
 * 
 * */
#ifndef SHOOTERTACH_H
#define SHOOTERTACH_H

#include "WPILib.h"

#define SHOOTERYACK	// define to enable debug output
class ShooterTach
{
public:
	ShooterTach(AnalogTrigger &anal)
	:	pTrigger(&anal),counter(anal)
	{
		clearHistory();
		rpm = 0;
		
		counter.SetUpSourceEdge(true, false); // clock rising edge, not falling edge
		counter.SetMaxPeriod(1000000 * 5); // stopped if we don't see anything for 5 secs 
		counter.SetUpSource(pTrigger->CreateOutput(AnalogTriggerOutput::kState));
	}
	ShooterTach(UINT32 aChannel)
	:	counter(aChannel)
	{
		clearHistory();
		rpm = 0;
		counter.SetUpSourceEdge(true, false); // clock rising edge, not falling edge
		counter.SetMaxPeriod(1000000 * 1); // stopped if we don't see anything for 5 secs 
		counter.SetUpSource(aChannel);	
		
	}
	
	void Start()
	{
		
		counter.Start();
	}
	virtual ~ShooterTach()	{}

	
	double GetRPM()  // revs per second
	{
		return rpm;
	}
	
	// Must call this once per clock tick
	void AcquireSample()
	{
		INT32 count = counter.Get();
	
		double period_sec = 0;
#define USE_PERIOD
#ifdef USE_PERIOD		
		rpm = 0;
		period_sec = counter.GetPeriod();	// period in seconds
		if ( !counter.GetStopped() && period_sec != 0 )
		{
			rpm = 60.0/period_sec;
		}
		else
		{
			counter.Reset();
			rpm = 0;
		}
		
#else
		processCount(count);
#endif		
		
#ifdef SHOOTERYACK
		printf("ShooterTach: count=%d period=%f rpm=%f nowmin=%f\n", 
			count, period_sec, rpm, GetClock()/60.);

#endif
	}
	
private:
	
#define SHOOTERTACH_HISTORY_SIZE  5
#define SHOOTERTACH_MIN_TURNS 10	// want at least 10% accuracy	
	
	double rpm; 
	
	/**
	 * Set all of history to current value 
	 */
	void clearHistory()
	{
		const double nowMins = GetClock()/60.;
		const INT32 count = counter.Get();
		for ( int iHist = 0; iHist < SHOOTERTACH_HISTORY_SIZE; iHist++ )
		{
			counts[iHist] = count;
			recentTimes[iHist] = nowMins;
		}
	}
	void processCount(INT32 count)
	{
		// Get current time.
		const double nowMins = GetClock()/60.;
		
		// If we don't set it to anything else, we set the speed to 0
		rpm = 0;
		/* Look through the history for the first sample that has a difference 
		 * in the count of at least the minimum (resolution) desired.  
		 * Use the oldest sample if none qualify.
		 * */
		for ( int iHist = 0; iHist < SHOOTERTACH_HISTORY_SIZE; iHist++ )
		{
			INT32 diffCounts = count - counts[iHist]; 
			if ( diffCounts >= SHOOTERTACH_MIN_TURNS || iHist == SHOOTERTACH_HISTORY_SIZE-1 )
			{
				rpm = ((float)diffCounts)/(nowMins-recentTimes[iHist]);
				break;
			}
		}
		for ( int iHist = 0; iHist < SHOOTERTACH_HISTORY_SIZE-1; iHist++ )
		{
			counts[iHist+1] = counts[iHist];
			recentTimes[iHist+1] = recentTimes[iHist];
		}
		counts[0] = count;
		recentTimes[0] = nowMins;
		
	}
	AnalogTrigger* pTrigger;
	Counter counter;				// Counter object for 1x and 2x encoding
	double recentTimes[SHOOTERTACH_HISTORY_SIZE];
	INT32 counts[SHOOTERTACH_HISTORY_SIZE];
};

#endif

