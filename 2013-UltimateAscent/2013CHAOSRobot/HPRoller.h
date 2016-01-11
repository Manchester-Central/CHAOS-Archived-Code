 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: HPRoller.h                                       
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

#ifndef HPROLLER_H_
#define HPROLLER_H_

#include "WPILib.h"
#include "Refs.h"

class HPRoller
{
	public:
	
	HPRoller();
	~HPRoller();
	void AddDisc();
	void Off();
	
	private:
	
	Relay *HPRollerSpike;
	
};
#endif
