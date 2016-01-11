 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Constants.h                                               
 **                                                                                           
 **   2014 2 08             
 **                                                             
 **-------------------------------------------------------------*/

#include "Shooter.h"
#include "Intake.h"

Shooter::Shooter(void)
{
	//Talons
	shooterTalonA = new Talon(SHOOTER_TALON_PORT_A);
	shooterTalonB = new Talon(SHOOTER_TALON_PORT_B);
	//shooterTalonC = new Talon(SHOOTER_TALON_PORT_C);

	
	shooterEncoder = new Encoder(SHOOTER_ENCODER_CHANNEL_A, SHOOTER_ENCODER_CHANNEL_B, 
			SHOOTER_ENCODER_DIRECTION, Encoder::k4X);
	shooterEncoder->SetDistancePerPulse(SHOOTER_DEGREES_PER_COUNT);
	shootEnable = false;
	
	shooterDownSensor = new DigitalInput(SHOOTER_DOWN_SENSOR_PORT);
	shooterUpSensor = new DigitalInput(SHOOTER_UP_SENSOR_PORT);
	
	calibrated = false;
	resetting = false;
	
	//troubleshooting section
	//shooterEncoder->Reset();
	//shooterEncoder->Start();
}

void Shooter::setShooterPower(double power)
{
	shooterTalonA->SetSpeed(power * SHOOTER_DIRECTION);
	shooterTalonB->SetSpeed(power * SHOOTER_DIRECTION);
	//shooterTalonC->SetSpeed(power * SHOOTER_DIRECTION);
}

// TODO: refactor to shooter

void Shooter::initShot(double shotAngle, double speed)
{
	Shooter::angle = shotAngle;
	Shooter::power = speed;
	

	shootEnable = true;
}

bool Shooter::isReset(void)
{
	bool IsReset = false;
	if(calibrated == true)
	{
		if(shooterDownSensor->Get() || shooterEncoder->GetDistance() <= RETRACTED_ANGLE)
		{
			IsReset = true;
		}
	}
	else 
	{
		if(shooterDownSensor->Get())
		{
			IsReset = true;
		}
	}
	return IsReset;
}

void Shooter::handle()
{
	if(shooterUpSensor->Get() == true)
	{
		shootEnable = false;
		//printf ("shooter safety switch detected \n");
	}
	
	if(intake->getCurrentPosition()<=INTAKE_SAFE_POSITION_FOR_SHOT)
	{
		Shooter::setShooterPower(STOP);
	}
	else
	{
		if(shootEnable == true && !resetting) //lettin' the shooter go
		{// we are supposed to be shooting
			if(fabs(shooterEncoder->GetDistance()) <= fabs(angle))//are we not there?
			{//lets go there
				Shooter::setShooterPower(power);
				//printf ("we have not reached target shooter angle %f\n", angle);
			}
			else 
			{//we are there
				Shooter::setShooterPower(STOP);
				shootEnable = false;
				//printf ("we have reched target shooter angle STOPPING \n");
				calibrated = false;
				resetting = true;
			}
		}
		else
		{//We are not supposed to be shooting
			if(Shooter::isReset()) //is the shooter in the home position?
			{//is in home position
				resetting = false;
				//printf("shooter is reset \n");
				
				Shooter::setShooterPower(STOP);
				if(!calibrated)
				{
					shooterEncoder->Reset();
					shooterEncoder->Start();
					calibrated = true;
					//printf("*shooter calibrated!!*\n");
				}
			}
			else
			{//we are not supposed to be shooting, so GO HOME
				Shooter::setShooterPower(SHOOTER_RESET_SPEED);
				//printf ("shooter going home \n");
				resetting = true;
			}
		}
	}
}
	
void Shooter::debug(void)
{
	if(shooterEncoder->GetStopped())
	{
		shooterEncoder->Start();
	}
	//printf("shooter encoder : %f, shooter down: %d, shooter up: %d \n", 
			//shooterEncoder->GetDistance(),(int )(shooterDownSensor->Get()), (int )(shooterUpSensor->Get()));
}

void Shooter::setIntake(Intake *intake)
{
	Shooter::intake = intake;
}

bool Shooter::isShooting(void)
{
	return shootEnable;
}
