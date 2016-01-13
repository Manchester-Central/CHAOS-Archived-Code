
#include "SamplePIDOutput.h"

SamplePIDOutput::SamplePIDOutput(RobotDrive *base) 
{
	m_base = base;
}

void SamplePIDOutput::PIDWrite(float output) 
{
	m_base->ArcadeDrive(0.0, output);
	outputValue = -output;
}
