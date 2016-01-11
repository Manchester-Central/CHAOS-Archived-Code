 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: HPRoller.cpp                                       
 **                                                             
 **   About:    
 **                                                                
 **   Property of Chaos, Copyright 2013
 **   Written by:  
 **               Kathryn Ly-Bishop
 **               Eric Moy
 **               Ben Papp
 **               Harrison Riddell
 **				  CHAOS.           
 **                                                                                           
 **   2013 1 19             
 **                                                             
 **-------------------------------------------------------------*/

#include "HPRoller.h"

HPRoller::HPRoller()
{
	HPRollerSpike = new Relay(HPROLLER_SPIKE_PORT);
}
HPRoller::~HPRoller()
{
	HPRollerSpike = NULL;
}
void HPRoller::AddDisc()
{
	//HPRollerSpike->Set(HPROLLER_SPEED);
	HPRollerSpike->Set(HPRollerSpike->kOff);
	HPRollerSpike->Set(HPRollerSpike->kReverse);
}
void HPRoller::Off()
{
	//HPRollerSpike->Set(0.0);
	HPRollerSpike->Set(HPRollerSpike->kOff);
	HPRollerSpike->Set(HPRollerSpike->kOff);
}
