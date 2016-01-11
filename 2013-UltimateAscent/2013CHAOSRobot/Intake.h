 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Intake.h                                       
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
#ifndef INTAKE_H_
#define INTAKE_H_

#include "WPILib.h"
#include "Refs.h"

class Intake
{
public:
	//function prototypes
	Intake();
	~Intake();
	void Feed();
	void Unjam();
	void Stop();
	
private:
	//objects
	//Talon *IntakeTalonA;
	//Talon *IntakeTalonB;
	Victor *IntakeTalonA;
	Victor *IntakeTalonB;
};

#endif
