 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Conveyor.h                                       
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

#ifndef CONVEYOR_H_
#define CONVEYOR_H_

#include "WPILib.h"
#include "Refs.h"

class Conveyor
{
public:
	Conveyor();
	~Conveyor();
	
	//void Shooter();
	void Stop();
	void FeedTop();
	void FeedBottom();
	void Manual(float Speed);
	bool IsRunning();
	
private:
	Talon *ConveyorTalon;
	bool ConveyorIsRunning;
	
};

#endif 
