
#include "inputtask.h"
#include "chaos09.h"
#include "chaosLinear.h"

#define SAMPLING_PERIOD  .001

chaosLinear linear_y(1, 2); 
int function_inputtask(...)
{
	
	while(1)
	{
		
		Wait(SAMPLING_PERIOD);
		
		
	}
	
	return 1;
}
