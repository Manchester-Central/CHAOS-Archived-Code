
#ifndef _SAMPLEPIDOUTPUT_H
#define _SAMPLEPIDOUTPUT_H

#include "WPILib.h"
#include "RobotDrive.h"
#include "PIDController.h"

class SamplePIDOutput : public PIDOutput 
{
	public:
		SamplePIDOutput(RobotDrive *base); 
		void PIDWrite(float output); 
		double outputValue;
	private:
		RobotDrive *m_base;
};

#endif

