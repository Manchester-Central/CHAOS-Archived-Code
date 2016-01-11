 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Climb.cpp                                       
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

#include "Climb.h"

Climb::Climb()
{
	//initial configuration of the components
	LeftClimbTalon = new Talon(LEFT_CLIMB_TALON_PORT);
	RightClimbTalon = new Talon(RIGHT_CLIMB_TALON_PORT);
	
}

Climb::~Climb()
{
	LeftClimbTalon = NULL;
	RightClimbTalon = NULL;
}

void Climb::ClimbUp()
{
	RightClimbTalon->Set(L_CLIMBING_SPEED_UP);
	LeftClimbTalon->Set(R_CLIMBING_SPEED_UP);
}


void Climb::ClimbDown()
{
	RightClimbTalon->Set(L_CLIMBING_SPEED_DOWN);
	LeftClimbTalon->Set(R_CLIMBING_SPEED_DOWN);
}

void Climb::Stop()
{
	smartDashboard->PutString("Location", "Climb::Stop()");
	RightClimbTalon->Set(0.0);
	LeftClimbTalon->Set(0.0);
}
*/
