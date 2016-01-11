 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Climb.h                                       
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
 **-------------------------------------------------------------
#ifndef CLIMB_H_
#define CLIMB_H_

#include "WPILib.h"
#include "Refs.h"

class Climb
{
public:
	Climb();
	~Climb();
		
	void ClimbUp();
	void ClimbDown();
	void Stop();
	SmartDashboard *smartDashboard;
	
private:
	Talon *LeftClimbTalon;
	Talon *RightClimbTalon;
	
};


#endif
*/
