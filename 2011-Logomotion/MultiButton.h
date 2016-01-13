/*-------------------------------------------------------------**
**                                                             
**   Filename: MultiButton.h                                        
**                                                             
**   About:    Looks for an edge in a digital signal
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Steven Kroh 
**                                                               
**   2011 2 11             
**                                                             
**-------------------------------------------------------------*/

#ifndef MULTI_BUTTON_H_
#define MULTI_BUTTON_H_

#include "WPILib.h"
#include "DashSharing.h"

class MultiButton
{
public:
	
	Timer *SuperTimer;
	DashSharing *DashData;
	
	MultiButton(DashSharing *DashData);
	bool IsSuper(bool NumberedButton, bool ToBooleanState, double SuperTime);
 
	bool LastDigitalState;
	bool DigitalState;
	bool SuperSequenceInitiated;
	bool Super;
};

#endif

