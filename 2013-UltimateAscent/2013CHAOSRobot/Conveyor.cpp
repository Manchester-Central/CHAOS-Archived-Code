 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Conveyor.cpp                                       
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
 **-----------------------------------------------------------*/

#include "Conveyor.h"

Conveyor::Conveyor()
{
	//initial configuration of the components
	ConveyorTalon = new Talon(CONVEYOR_TALON_PORT);
	
}

Conveyor::~Conveyor()
{
	//anything created in construct delete
	ConveyorTalon = NULL;
}



void Conveyor::FeedTop()
{
	ConveyorTalon->Set(CONVEYOR_SPEED_TOP);
	ConveyorIsRunning = 1;
}

void Conveyor::FeedBottom()
{
	ConveyorTalon->Set(CONVEYOR_SPEED_BOTTOM);
	
}

void Conveyor::Stop()
{
	ConveyorTalon->Set(0.0);
	ConveyorIsRunning = 0;
}

void Conveyor::Manual(float Speed)
{
	ConveyorTalon->Set(Speed);
}

bool Conveyor::IsRunning()
{
	return ConveyorIsRunning;
}

