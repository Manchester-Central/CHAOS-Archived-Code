#include "Dribbler.h"
#include "Victor.h"

//A File Scope Function
static void AccessDribblerStateMachine(Dribbler *d)
{
	printf("Dribbler -> Access Dribbler State Machine1\n");
	//d->DribblerStateMachine();
	//printf("Dribbler -> Access Dribbler State Machine2<%f>\n", LeftDriveRate);
}

Dribbler::Dribbler(DashSharing *DashDataPass)
	: DribblerTask("Dribbler", (FUNCPTR) AccessDribblerStateMachine)
{
	LeftDribbler = new Victor(DIO_MODULE1, LEFT_DRIBBLING_MOTOR_CHANNEL);
	RightDribbler = new Victor(DIO_MODULE1, RIGHT_DRIBBLING_MOTOR_CHANNEL);
	
	DashData = DashDataPass;
	
	this->LeftDribblerLimitSwitch = new DigitalInput(DIO_MODULE1, LEFT_DRIBBLER_LIMIT_SWITCH);
	this->RightDribblerLimitSwitch = new DigitalInput(DIO_MODULE1, RIGHT_DRIBBLER_LIMIT_SWITCH);
	
    LeftSwitch = false;
    RightSwitch = false;
    LimitSwitchStatus = 0;
	
	printf("Dribbler -> Construct");
}

Dribbler::Dribbler(DashSharing *DashDataPass, Encoder *LeftEncoderPass, Encoder *RightEncoderPass, Gamepad *Driver)
    : DribblerTask("Dribbler", (FUNCPTR) AccessDribblerStateMachine)
{
	LeftDribbler = new Victor(DIO_MODULE1, LEFT_DRIBBLING_MOTOR_CHANNEL);
	RightDribbler = new Victor(DIO_MODULE1, RIGHT_DRIBBLING_MOTOR_CHANNEL);
	
	DashData = DashDataPass;

	TheLight = new Solenoid(SOLENOID_MODULE1, THE_LIGHT_CHANNEL);
	
	this->LeftDribblerLimitSwitch = new DigitalInput(DIO_MODULE1, LEFT_DRIBBLER_LIMIT_SWITCH);
	this->RightDribblerLimitSwitch = new DigitalInput(DIO_MODULE1, RIGHT_DRIBBLER_LIMIT_SWITCH);
	
	this->base = base;
	DribblerHasBall = false;
	this->Driver = Driver;
	
    LeftSwitch = false;
    RightSwitch = false;
    LimitSwitchStatus = 0;
	
	printf("Dribbler -> Construct");
}

void Dribbler::Keep()
{	
	/* Left Section ********************************************************/
	
	LeftDriveRate = DigitalModule::GetInstance(DIO_MODULE1)->GetPWM(FRONT_LEFT_TRANSMISSION_MOTOR_CHANNEL);
	LeftDriveRate = ((LeftDriveRate - 127.0) / 128.0);
	LeftDribbler_Out = ((-1.0)*(m_KL)*(LeftDriveRate)) + m_AL;
	
	if(LeftDribbler_Out > 1.0)
	{
		LeftDribbler_Out = 1.0;
	}
	else if(LeftDribbler_Out < -1.0)
	{
		LeftDribbler_Out = -1.0;
	}
	
	/* Right Section *******************************************************/
	
	RightDriveRate = DigitalModule::GetInstance(DIO_MODULE1)->GetPWM(FRONT_RIGHT_TRANSMISSION_MOTOR_CHANNEL);
	RightDriveRate = ((RightDriveRate - 127.0) / 128.0);
	RightDribbler_Out = ((m_KR)*(RightDriveRate)) + m_AR;
	RightDribbler_Out = (RightDribbler_Out)*0.8;
	
	if(RightDribbler_Out > 0.8)
	{
		RightDribbler_Out = 0.8;
	}
	else if(RightDribbler_Out < -0.8)
	{
		RightDribbler_Out = -0.8;

	}
	
    /* Set Dribbler Outs ***************************************************/
	
	LeftDribbler->Set(-LeftDribbler_Out);
	RightDribbler->Set(RightDribbler_Out);

} //END Keep

void Dribbler::SetConstants(double KL, double AL, double KR, double AR)
{
	m_KL = KL;
	m_AL = AL;
	m_KR = KR;
	m_AR = AR;
	
}

void Dribbler::Release(void)
{
	LeftDribbler->Set(RELEASE);
	RightDribbler->Set(RELEASE);
}

Dribbler::~Dribbler(void)
{
	delete LeftDribbler;
	delete RightDribbler;
}

double Dribbler::RateToScaledOutput(double rate)
{
	return rate;
}

void Dribbler::Start(void)
{
	DribblerTask.Start();
	printf("Dribbler -> Start");
	m_Enabled = true;
} // end of Start

void Dribbler::Stop(void)
{
	DribblerTask.Stop();
	printf("Dribbler -> Stop");
	m_Enabled = false;
} // end if Stop

void Dribbler::DribblerStateMachine(void)
{
	// Need to add the statemachine that will continue to run the dribber
	// This should be an endless task with start stop functions
	printf("Dribbler -> Do\n");
	do
	{
		if(m_Enabled)
		{
			Keep();
		} // end if
		Wait(0.5);
	}while(true);
	
} // end of DribberStateMachine

bool Dribbler::BallIsInDribbler(void)
{
	LeftSwitch = !LeftDribblerLimitSwitch->Get();
	RightSwitch = !RightDribblerLimitSwitch->Get();
	
	if(LeftSwitch || RightSwitch)
	{
		DribblerHasBall = true;
	}
	else
	{	
		DribblerHasBall = false;
	}
	
	if(LeftSwitch && RightSwitch)
	{
		LimitSwitchStatus = 3;
		TheLight->Set(true);
	}
	else if(LeftSwitch)
	{
		LimitSwitchStatus = 1;
		TheLight->Set(false);
	}
	else if(RightSwitch)
	{
		LimitSwitchStatus = 2;
		TheLight->Set(false);
	}
	else
	{
		LimitSwitchStatus = 0;
		TheLight->Set(false);
	}
	
	
	DashData->DribblerHasBall_DashOut = LimitSwitchStatus;
	
	return DribblerHasBall;
}

