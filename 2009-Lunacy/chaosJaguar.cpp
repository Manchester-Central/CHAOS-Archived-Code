/*----------------------------------------------------------------------------*/
/* This code was added to avoid burning out the Jaguars				  */
/*    */
/*   */
/*----------------------------------------------------------------------------*/


#include "chaosJaguar.h"

chaosJaguar::chaosJaguar(UINT32 channel) : Jaguar(channel)
{
	
}

/**
 * Set the PWM value.  
 * 
 * The PWM value is set using a range of -1.0 to 1.0, appropriately
 * scaling the value for the FPGA.
 * 
 * @param speed The speed value between -1.0 and 1.0 to set.
 */
void chaosJaguar::Set(float speed)
{
	// Early teams had Jaguars burn out when a value of 1 is passed
	if(speed >= 1)
	{
		speed = .99;
	}
	else if(speed <= -1)
	{
		speed = -.99;
	}
	
	
	SetSpeed(speed);
	
}

