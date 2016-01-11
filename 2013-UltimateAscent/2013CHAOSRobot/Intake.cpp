 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Intake.cpp                                       
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
#include "Intake.h"

Intake::Intake()
{
	//IntakeTalonA = new Talon(INTAKE_TALON_PORT_A);
	//IntakeTalonB = new Talon(INTAKE_TALON_PORT_B);
	IntakeTalonA = new Victor(INTAKE_TALON_PORT_A);
	IntakeTalonB = new Victor(INTAKE_TALON_PORT_B);
}
Intake::~Intake()
{
	IntakeTalonA = NULL;
	IntakeTalonB = NULL;
}
void Intake::Feed()
{
	IntakeTalonA->Set(INTAKE_FEED_SPEED,0);
	IntakeTalonB->Set(INTAKE_FEED_SPEED, 0);
}
void Intake::Unjam()
{
	IntakeTalonA->Set(INTAKE_UNJAM_SPEED,0);
	IntakeTalonB->Set(INTAKE_UNJAM_SPEED, 0);
}
void Intake::Stop()
{
	IntakeTalonA->Set(0.0,0);
	IntakeTalonB->Set(0.0, 0);
}
