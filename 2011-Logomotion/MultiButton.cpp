/*-------------------------------------------------------------**
**                                                             
**   Filename: MultiButton.cpp                                        
**                                                             
**   About:    Looks for an edge in a digital signal
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Steven Kroh 
**                                                               
**   2011 2 11             
**                                                             
**-------------------------------------------------------------*/

#include "MultiButton.h"

MultiButton::MultiButton(DashSharing *DashData)
{
	LastDigitalState = false;
	DigitalState = false;
	SuperSequenceInitiated = false;
	Super = false;
	
	SuperTimer = new Timer();
	
	this->DashData = DashData;
}

bool MultiButton::IsSuper(bool NumberedButton, bool ToBooleanState, double SuperTime)
{
	DigitalState = NumberedButton;
	
	if((DigitalState != LastDigitalState) && (DigitalState == ToBooleanState))
	{
		SuperTimer->Start();
		SuperSequenceInitiated = true;
	}
	
	if(SuperSequenceInitiated)
	{
		DashData->EscapeTime_D = SuperTimer->Get();
		
		if((DigitalState != LastDigitalState) && (DigitalState != ToBooleanState))
		{
			SuperTimer->Stop();
			
			if(SuperTimer->Get() >= SuperTime)
			{
			    Super = true;	
			}
			if(SuperTimer->Get() < SuperTime)
			{
				Super = false;
			}
			
			SuperTimer->Reset();
			SuperSequenceInitiated = false;
		}
	}
	else
	{
		Super = false;
	}
	
	LastDigitalState = DigitalState;
	
	return Super;
} // end is super

