/*-------------------------------------------------------------**
**                                                             
**   Filename: LinearPot.cpp                                        
**                                                             
**   About:    Code to map the voltage a linear variable 
** 		       potentiometer to an angle in radians 
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Steven Kroh, Chaos.           
**                                                                                           
**   2011 1 29             
**                                                             
**-------------------------------------------------------------*/

#include "LinearPot.h"

LinearPot::LinearPot(int PotSlot, int PotChannel, float Voltage1, float Voltage2, float Angle1, float Angle2)
{
	this->Pot = new AnalogChannel(PotSlot, PotChannel);
	this->Voltage1 = Voltage1;
	this->Voltage2 = Voltage2;
	this->Angle1 = Angle1;
	this->Angle2 = Angle2;
	
	this->Slope = ((this->Angle1 - this->Angle2)/(this->Voltage1 - this->Voltage2));
	this->Offset = (this->Angle1 - (this->Slope * this->Voltage1));
}

float LinearPot::GetAngleDegrees()
{
	return ((Pot->GetVoltage() * Slope) + Offset);
}

float LinearPot::GetAngleRadians()
{
	//Value of PI found in Refs.h
	return (GetAngleDegrees() * (PI/180));
}

double LinearPot::PIDGet(void)
{
	return ((double )this->GetAngleDegrees());
}

