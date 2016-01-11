 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Misc.cpp                                       
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
#include "Misc.h"
Misc::Misc()
{
	
}

float Misc::fabs(float number)
{
	if(number >= 0.0)
	{
		return number;
	}
	else
	{
		return -number;
	}
}
