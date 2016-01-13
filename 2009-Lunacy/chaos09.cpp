#include "stdlib.h"
#include "stdio.h"
#include "vxworkscommon.h"
#include "chaos09.h"
#include "logger.h"



#define PERIOD .2

#define HERTZ       2.0   // Should be really cleaned up throughout project
#define HERTZ_2     2.0
#define HERTZ_0_01  0.01
#define HERTZ_0_1   0.1

#define HERTZTURRET 10

//#define DISTANCEPERPULSE .0019156
#define DRIVE_POWER_FACTOR .99

#define DISTANCEPERPULSE 4.8656E-5
#define DISTANCEPERPULSE_DRAG 1.78488E-4//8.9244E-4
#define TURRET_DISTANCE_PER_PULSE .001 // TODO: Find actual values for this

#define NOTRACTION false
#define TRACTION true
#define DASHBOARD false

#define TURRETTIME 2
#define TURRETCALPOWER .2	// slew power when slamming into left and right to find ends

#define TURRETJOYTOSLEWPOWER .2 // multiplier from joystick control to slew power

#define TURRETJOYTOSHOOTPOWER (4.5/12)  // multiplier from joystick to shoot power
										// max distance has been seen at 4.5 volts
// Ratio of RPM to voltage
#define TURRETPOWERTOSHOOTSPEED (2500.0/5.0)
// KP for shooter
#define KP_SHOOTPOWER	0.01		// ratio / TURRETPOWERTOSHOOTSPEED to adjust by
// KI for shooter
#define KI_SHOOTPOWER	0.000	// ratio / TURRETPOWERTOSHOOTSPEED to adjust by

#define TURRETDISTANCETOMAXPOWER .002  // in power (range -1 to 1) over pulses
									// expecting 500 pulses per turret revolution
									// max power captain to avoid running into end.
									
#define SIZETOPOWER 2

#define MINHDFACTOR 1   

#define SLEWOPERATION true

#if SLEWOPERATION
#define TRACTIONCONTROL slewControl 
#else 
#define TRACTIONCONTROL func_drive
#endif	

//Dashboard

#if DASHBOARD
#define PRINTF dashboard.Printf
#else
#define PRINTF printf
#endif


Logger logger;




#if DRAGGING
#define LEFT_DRAG_ENCODER_A 11
#define LEFT_DRAG_ENCODER_B 14
#define RIGHT_DRAG_ENCODER_A 12
#define RIGHT_DRAG_ENCODER_B 13

//#warning "SET ENCODER CHANNELS TO REAL VALUES!!!"
#endif

#define SHOOTER_DIGITAL_CHANNEL 9
#define SHOOTER_ANALOG_CHANNEL 5

ChaosRobot::ChaosRobot(void): 
	//visiontask("vision", function_visiontask, 200),
	// Removed shooter2 - for dumper version - tbinns 053009
	pilot1(1), pilot2(2),
	motor1(1), motor2(2), turret(5), shooter1(3), /* shooter2(4), */ unjammer(1), shootRoller(2), lifter(6), intake(7),
//	shooterTrigger(SHOOTER_ANALOG_CHANNEL),
	shooterTach(SHOOTER_DIGITAL_CHANNEL),
//    hallSensorDI(SHOOTER_DIGITAL_CHANNEL),
	l_encoder(1, 2, DISTANCEPERPULSE), r_encoder(3, 4, DISTANCEPERPULSE),
	LPF1(HERTZ, PERIOD), LPF2(HERTZ, PERIOD), LPFT(HERTZTURRET, PERIOD),
#if DRAGGING
	leftDragger(LEFT_DRAG_ENCODER_A, LEFT_DRAG_ENCODER_B, DISTANCEPERPULSE_DRAG), rightDragger(RIGHT_DRAG_ENCODER_A, RIGHT_DRAG_ENCODER_B, DISTANCEPERPULSE_DRAG),
#endif
	turretencoder(5, 6, true, Encoder::k2X),
	leftRight_DI(8), additionalAngle_DI (7),
	additionalDirection_DI(10), thelight(3, Relay::kForwardOnly),
	/* tbinns 10/18 Removed dashData references */
	//dashData(m_ds->GetDashboardPacker()),
	
	lastShootPower(0), 
	integralErrorRPM(0)
    {
//		shooterTrigger.SetLimitsVoltage(.5, 2.0);
  		shooterTach.Start();
		m_turretLeftLimit = m_turretRightLimit = 0;
		GetWatchdog().SetExpiration(100);
		modeloops = 0;
		
		turretencoder.SetDistancePerPulse(TURRET_DISTANCE_PER_PULSE);
		turretencoder.Start();
		
		leftDragger.Start();
		rightDragger.Start();
		
		turret_error_i = 0.0;
		turret_centering = false;
		
		shooterIntegral = 0;
	}

void ChaosRobot::func_notraction(float rjoy, float ljoy)
{
	motor1.Set(ljoy); 
	motor2.Set(-rjoy);
}

int ChaosRobot::sign(float x)
{
	if ( x < 0 ) return -1;
	if ( x > 0 ) return 1;
	return 0;
}

void ChaosRobot::MobileAutoTrack(void)
{
	
}

void ChaosRobot::func_drive(float rjoy, float ljoy)
{
	if (!pilot1.GetNumberedButton(6))
	{
		func_traction(rjoy, ljoy);
	}
	else
	{
		linear_y.accel_y.clear_vChassis();
		VerrorL_Integral = 0;
		VerrorR_Integral = 0;
		func_notraction(rjoy, ljoy);
	}
}

void ChaosRobot::func_traction(float rjoy, float ljoy)
{
	//float rjoy = pilot1.GetRightY();
	//float ljoy = pilot1.GetLeftY();
	
	logger.driverJoy[0] = ljoy;
	logger.driverJoy[1] = rjoy;
	logger.chassisEncoders[0] = l_encoder.GetRaw();
	logger.chassisEncoders[1] = r_encoder.GetRaw();
	
//	printf(" R: %d, L: %d\n", r_encoder.GetRaw(), l_encoder.GetRaw()); 
	
	float JoystickLChange;
	float JoystickRChange;
	
	JoystickLChange = ljoy - PreviousLJoyY;
    PreviousLJoyY = ljoy;
    
    JoystickRChange = rjoy - PreviousRJoyY;
    PreviousRJoyY = rjoy;
	
	double time = GetTime();
	
	//double lastperiod = time-lastGyroTime;
	double lastperiod = PERIOD;
	lastGyroTime = time;
	logger.actualPeriod = lastperiod;

#if !DRAGGING	
	linear_y.CalculateValue();
#endif	
	float r_encoder_val = -r_encoder.GetValue(); 
	float l_encoder_val =  l_encoder.GetValue();
	
	logger.chassisEncodersV[0] = l_encoder_val;
	logger.chassisEncodersV[1] = r_encoder_val;

#if DRAGGING
	float leftDragSpeed =  -leftDragger.GetValue();
	float rightDragSpeed = -rightDragger.GetValue();
	
	logger.vChaSide[0] = leftDragSpeed;
	logger.vChaSide[1] = rightDragSpeed;
	
	VerrorL = leftDragSpeed - l_encoder_val;
	VerrorR = rightDragSpeed - r_encoder_val;
	
	// printf("LDS: %2.3f, RDS: %2.3f, LEV: %2.3f, REV: %2.3f", leftDragSpeed, rightDragSpeed, l_encoder_val, r_encoder_val);
#else	
	VerrorL = linear_y.V_LeftChassis - l_encoder_val;
	VerrorR = linear_y.V_RightChassis - r_encoder_val;
#endif	
	VerrorL_Integral += (VerrorL*lastperiod)*KIL;
	
//	printf("JoystickLChange: %02.6f, VerrorL_Integral, %02.6f", JoystickLChange, VerrorL_Integral);
	
	if(sign(VerrorL_Integral) == sign(JoystickLChange))
	{
        if(fabs(JoystickLChange) > fabs(VerrorL_Integral))
        {
        	VerrorL_Integral = 0;
        }
        else
        {
        	VerrorL_Integral -= JoystickLChange;
        }
	}
//	if (ljoy==0)  VerrorL_Integral = 0;
	
	if(VerrorL_Integral >= 1)
	{
		VerrorL_Integral = 1;
	}
	else if(VerrorL_Integral <= -1)
	{
		VerrorL_Integral = -1;
	}
	
	VerrorR_Integral += (VerrorR*lastperiod)*KIR;
	
//    printf(" JoystickRChange: %02.6f, VerrorR_Integral, %02.6f\n", JoystickRChange, VerrorR_Integral);
	
	if(sign(VerrorR_Integral) == sign(JoystickRChange))
	{
		if(fabs(JoystickRChange) > fabs(VerrorR_Integral))
		{
			VerrorR_Integral = 0;
		}
		else
		{
			VerrorR_Integral -= JoystickRChange;
		}
	}
//	if (rjoy==0)  VerrorR_Integral = 0;
	
	//printf("PB VerrorR_Integral, %02.6f", VerrorR_Integral);
	
	if(VerrorR_Integral >= 1)
	{
		VerrorR_Integral = 1;
	}
	else if(VerrorR_Integral <= -1)
	{
		VerrorR_Integral = -1;
	}
	//printf("VerrorR_Integral, %02.6f\n", VerrorR_Integral);
	
	logger.chassisWindup[0] = VerrorL_Integral;
	logger.chassisWindup[1] = VerrorR_Integral;
	
	if  ( KIR < 0.0001)
	{
		VerrorR_Integral = 0.0;
		VerrorL_Integral = 0.0;
	}
	
	JoyLDelta = (KPL*VerrorL)+(VerrorL_Integral);
	float JoyLOut = JoyLDelta + ljoy;
	if(JoyLOut >= 1)
	{
		JoyLOut = 1;
	}
	else if(JoyLOut <= -1)
	{
		JoyLOut = -1;
	}
	
	JoyRDelta = (KPR*VerrorR)+(VerrorR_Integral);
	float JoyROut = JoyRDelta + rjoy;
    if(JoyROut >= 1)
	{
    	JoyROut = 1;
	}
	else if(JoyROut <= -1)
	{
		JoyROut = -1;
	}
	// printf("LJD: %2.3f, RJD: %2.3f\n", JoyLDelta, JoyRDelta);
	
//    printf("1: %02.2f, 2: %02.2f, 3: %02.2f, 4: %02.2f, 5: %02.2f, 6: %02.2f 7: %02.2f, 8: %02.2f\n", l_encoder_val, ljoy, JoyLDelta, VerrorL_Integral, r_encoder_val, rjoy, JoyRDelta, VerrorR_Integral );
    
//Motor1 Positive is +forward
//Motor2 Positive is reverse
motor1.Set((JoyLOut* DRIVE_POWER_FACTOR));
motor2.Set(-(JoyROut* DRIVE_POWER_FACTOR));
	logger.driveMotorOut[0] = JoyLOut;
	logger.driveMotorOut[1] = JoyROut;
}

void ChaosRobot::TeleopInit(void)
{
 //   printf("teleopInit\b\n");
	Dashboard &dashboard = m_ds->GetDashboardPacker();
	func_tractioninit();
	lastShootPower = 0;
	integralErrorRPM = 0;
	dashboard.Printf("This is in the TeleopInit");
}
	
void ChaosRobot::func_tractioninit(void)
{
	linear_y.SetCoefficient_Accel_lpf((double )HERTZ_0_1, (double )PERIOD);
    linear_y.SetZero_Accel(1.5-0.011969388);
	linear_y.SetSensitivity_Accel(0.3);
	
	linear_y.Init_Gyro();
	
	linear_y.gyro.Reset();
	
	
	linear_y.accel_y.lpf.SetPrevious(linear_y.accel_y.GetValue());
	
	
	    
	l_encoder.SetMinRate(.01);
	l_encoder.SetCoefficient_lpf((double )HERTZ_2, (double )PERIOD);
	r_encoder.SetMinRate(.01);
	r_encoder.SetCoefficient_lpf((double )HERTZ_2, (double )PERIOD);
	
	leftDragger.SetMinRate(.01);
	leftDragger.SetCoefficient_lpf((double )HERTZ_2, (double )PERIOD);
	
	rightDragger.SetMinRate(.01);
	rightDragger.SetCoefficient_lpf((double )HERTZ_2, (double )PERIOD);
		
	VerrorL_Integral = 0;
	VerrorR_Integral = 0;
	   
}
	

	
bool ChaosRobot::AutoTrack(void)
{
	float encoderpos = turretencoder.Get();
	float slewpower;
	
//	if(chaosvision.getFoundColor() == true)
//	{
//		turretstate = ktrack;
//	}
//	else if(turretstate == ktrack)
//	{
//		turretstate = kslewleft; //Need to add ability to continue to slew in the 
//		                         //direction where the image broke up
//	}
	
	if(turretstate == kslewleft)
	{
		if(encoderpos <= m_turretLeftLimit)
		{
			turretstate = kslewright;
		}
	}
	if(turretstate == kslewright)
	{
		if(encoderpos <= m_turretRightLimit)
		{
			turretstate = kslewleft;
		}
	}
	
	if(turretstate == kslewright)
	{
		slewpower = .25;
	}
	if(turretstate == kslewleft)
	{
		slewpower = -.25;
	}
	if(turretstate == ktrack)
	{
//slewpower = chaosvision.getHorizontalDestination();
	}
	
	//Make sure that both turret movers do not break the turret
	int turretpos = turretencoder.Get();

	if(((turretpos <= m_turretLeftLimit)&&(slewpower < 0)) || 
	   ((turretpos >= m_turretRightLimit)&&(slewpower > 0)))
	{
		slewpower = 0;
	}
	turret.Set(LPFT.GetValue(slewpower));
		
//	if(chaosvision.getFoundColor() == true)
//	{
//		float shooterpower = SIZETOPOWER/chaosvision.getTargetSize();
//		shooter1.Set(shooterpower);
//		shooter2.Set(shooterpower);
//		
//		float minhd = chaosvision.getTargetSize()*MINHDFACTOR;
//		if(fabs(chaosvision.getHorizontalDestination()) <= minhd)
//		{
//			//servo actuated gate code
//		}
//		else
//		{
//			//gate down
//		}
//	}
//	else
//	{
//		//gate down
//	}
	
//	return chaosvision.getFoundColor();
	return true;
}

// static bool lastShoot = false; 

void ChaosRobot::Shooter()
{
	bool Shoot = pilot2.GetNumberedButton(5);
	bool AntiShoot = pilot2.GetNumberedButton(2); // Edit for Riley, see below
	bool static FirstMultiCycle = true;
	int static FirstMultiCount = 0;
	static float shooterpower = 0.5;
	//float RightJoy = -pilot2.GetRightY();
	
	//Change Thursday Feb 26
	
	
	switch(pilot2.GetDPad())
	{
//	case Gamepad::kDown :
//        shooterpower = 0.99;
//	    break;
	case Gamepad::kLeft :
			if (shooterpower < 0.99)
			{
				shooterpower = shooterpower + 0.05;
			}
		    break;
	case Gamepad::kUp :
		    shooterpower = 0.5;
		    break;
	case Gamepad::kRight : 
		    if(shooterpower > 0.0)
		    {
		    	shooterpower = shooterpower - 0.05;
		    }
		    break;
		    
	default:
		break;
	}
	
//	if (RightJoy < 0) RightJoy = 0;

	//float shootPower   //= RightJoy * TURRETJOYTOSHOOTPOWER;
//#define USE_SHOOTERTACH	
//#ifndef USE_SHOOTERTACH
		if(Shoot)
		{
			if ((pilot2.GetDPad() == Gamepad::kDown) || (FirstMultiCycle && FirstMultiCount < 500))
			{
			shooter1.Set(-0.99); // consider LPF
			FirstMultiCount++;
			}
			else
			{
				FirstMultiCount = 0;
				FirstMultiCycle = false;
				shooter1.Set(-shooterpower); // consider LPF
			}
				
		}
		//Edit for Riley 9-24
				else if(AntiShoot)
				{
					if ((pilot2.GetDPad() == Gamepad::kDown) || (FirstMultiCycle && FirstMultiCount < 500))
					{
			     		shooter1.Set(0.99); // consider LPF
						FirstMultiCount++;
					}
					else
					{
						FirstMultiCount = 0;
						FirstMultiCycle = false;
						shooter1.Set(shooterpower); // consider LPF
					}
								
				}
				//end edit for Riley
		else
    	{
    		shooter1.Set(0); // consider LPF
    		if (shooterpower > 0.90)
    		{
    			shooterpower = 0.5;
    		}
    		FirstMultiCount = 0;
    		FirstMultiCycle = false;
    	}
    	// Removed shooter2 - for dumper version - tbinns 053009
	    // shooter2.Set(shooterpower); // consider LPF
/*
//	printf("Hall=%d", hallSensorDI.Get());
#else
	double desiredRPM = (shooterpower * TURRETPOWERTOSHOOTSPEED);
	shooterTach.AcquireSample();
	double currentRPM = shooterTach.GetRPM();
	double errorRPM = desiredRPM - currentRPM;
	double shooterProp = errorRPM*KP_SHOOTPOWER;
	shooterIntegral += errorRPM*KI_SHOOTPOWER;
//	double adjustedShootPower = lastShootPower + (errorRPM	/TURRETPOWERTOSHOOTSPEED * KP_SHOOTPOWER);

	if ( shooterIntegral > 1 )
	{
		shooterIntegral =  1;
	}
	else if ( shooterIntegral < 0.02 )
	{
		shooterIntegral = 0.02;
	}
	double adjustedShootPower = shooterpower + shooterIntegral + shooterProp;
	
	if ( adjustedShootPower > 1 )
	{
		adjustedShootPower =  1;
	}
	else if ( adjustedShootPower < -1.0 )
	{
		adjustedShootPower = -1.0;
	}

	shooter1.Set(-adjustedShootPower);
	// Removed shooter2 - for dumper version - tbinns 053009
	// shooter2.Set(adjustedShootPower);
	
	logger.shootRPM = currentRPM;
	logger.desiredRPM = desiredRPM;
	logger.shootWindup = integralErrorRPM;
	logger.shootVolts = adjustedShootPower;
	// printf("RPM=%2.3f", currentRPM);
#endif	
	*/
//	if ( shooterpower != lastShootPower )
//	{
//		printf("shopow=%1.3f\r\n", shooterpower);
//	}
	
/*
		// Control the top horizontal roller (not the shooter spinners)
	lastShoot = Shoot;
	if(Shoot == true)
	{
		shootRoller.Set(Relay::kReverse);
	}
	else if(pilot2.GetNumberedButton(2))
	{
		shootRoller.Set(Relay::kForward);
	}
	else
	{
		shootRoller.Set(Relay::kOff);
	}
	if (lastShoot != Shoot )
	{
		//printf("shoot=%d",Shoot);
		lastShoot = Shoot;
	}
	*/
}

// Do sign change here if encoder reads backward when finally working
// reads pulses
int ChaosRobot::readTurretEncoder()
{
	return turretencoder.Get();
}

static float oldSlewPower = 0;
void ChaosRobot::setSlewPower(float slewPower)
{
	turret.Set(slewPower);
	if ( slewPower != oldSlewPower)
	{
		// printf("turret slew = %01.3f\n", slewPower);
		oldSlewPower = slewPower;
	}
}
static bool warnedNoCal = false;
void ChaosRobot::TurretTrack(void)
{
    int turretpos = turretencoder.Get();
	//printf("encoder: %d", turretpos);
	bool calibrated = ( m_turretRightLimit != m_turretLeftLimit);
	// bool Calibrate;  //= pilot2.GetNumberedButton(1);

	// bool Center = pilot2.GetNumberedButton(3);
	float LeftJoy = pilot2.GetLeftX();
	float slewPower;
	// int error;
	// float KPTurret = .01;//.0016;
	// float KITurret = .003;
	
//	if (Calibrate )
//	{
//		TurretSelfCalibrate();
//	}
	
/*	if(Center)
	{
		if(!turret_centering)
		{
			turret_error_i = 0;
		}
		
		error = m_turretCenter - turretpos;
		if ( error == 0 ) turret_error_i = 0;
		turret_error_i += error;
		
		slewPower = KPTurret*(float )error + (turret_error_i*KITurret);
        turret_centering = true;
        
	}
	
	else
	{
		slewPower = LeftJoy * TURRETJOYTOSLEWPOWER; // consider LPF
	}
*/
	slewPower = LeftJoy * TURRETJOYTOSLEWPOWER; // consider LPF
	//bool somebutton = true;
	if ( !calibrated )
	{
		if ( !warnedNoCal)
		{
			// printf("TURRET SLEW DISABLED EXCEPT RAW MODE!  NO CALIBRATION\n");
			warnedNoCal=true;
		}
		
	}

	if ( slewPower > 0 && turretpos >= m_turretRightLimit )
	{
		slewPower = 0;
	}
	if ( slewPower < 0 && turretpos <= m_turretLeftLimit )
	{
		slewPower = 0;		
	}
    
    if ( slewPower > TURRETJOYTOSLEWPOWER )
    {
	   slewPower = TURRETJOYTOSLEWPOWER;
    }
    else if ( slewPower < -TURRETJOYTOSLEWPOWER )
    {
	   slewPower = -TURRETJOYTOSLEWPOWER;
    }
 
	turret.Set(slewPower);
}

void ChaosRobot::TurretSelfCalibrate(void)
{
    // printf("TURRET CALIBRATION initial position = %d\r\n", readTurretEncoder());
    turret.Set(-TURRETCALPOWER);
	Wait(TURRETTIME);
	turret.Set(0);
	
    m_turretLeftLimit = readTurretEncoder();
    
	turret.Set(TURRETCALPOWER);
	
	Wait(TURRETTIME);
	
	turret.Set(0);
	
	m_turretRightLimit = readTurretEncoder();
	
	range = m_turretRightLimit - m_turretLeftLimit;
	
	if ( abs(range) < 20 )
	{
		while ( !pilot2.GetNumberedButton(7)/*Shoot*/ )
		{
			// printf("Encoder FAILED - press SHOOT to continue\n");
		}
	}
	
	m_turretLeftLimit = m_turretLeftLimit + (range/20);
	m_turretRightLimit = m_turretRightLimit - (range/20);

	m_turretCenter = (m_turretLeftLimit + m_turretRightLimit)/2;
	
	// printf("Turret left limit=%d, right=%d, center: %d\r\n", m_turretLeftLimit, m_turretRightLimit, m_turretCenter);
	FILE* calFile = fopen("turretCalibration", "w");
	fwrite(&m_turretLeftLimit, sizeof m_turretLeftLimit, 1, calFile);
	fwrite(&m_turretRightLimit, sizeof m_turretLeftLimit, 1, calFile);
	fclose(calFile);
}

void ChaosRobot::TurretReadCalibration()
{
	FILE* calFile = fopen("turretCalibration", "r");
	if ( calFile == NULL )
	{
		// printf("Turret Cal File not found \n");
	}
	fread(&m_turretLeftLimit, sizeof m_turretLeftLimit, 1, calFile);
	fread(&m_turretRightLimit, sizeof m_turretLeftLimit, 1, calFile);
	printf("Turret cal file left limit=%d, right=%d\r\n", m_turretLeftLimit, m_turretRightLimit);
	fclose(calFile);
}

void ChaosRobot::RobotInit(void)
{

	lastGyroTime = GetTime();
	
	KPR = .3;
	KPL = .3;
	KIR = 0.0;//.04;
	KIL = 0.0;//.04;
	
	logger.KP[0] = KPL;
	logger.KP[1] = KPR;
	logger.KI[0] = KIL;
	logger.KI[1] = KIR;
	
	// logger.switches[0] = leftRight_DI;
	// additionalAngle_DI
	// additionalDirection_DI
	
	//shooterpower = 6.0/12.0;
	
	// if no file, default values above are used.
	readCalibrationFile();
	
	func_tractioninit();
	TurretReadCalibration();
	
	//Dashboard		
	if ( DASHBOARD )
	{
		/* tbinns 10/18 Removed dashData references */
		//dashData.PackAndSend();
		UpdateDashboard();
	}
}
	
void ChaosRobot::DisabledInit(void)
{
	logger.closeIfOpen();
}
	
void ChaosRobot::DisabledContinuous(void)
{
		
}

bool ChaosRobot::autonomousWait(float secs)
{
	//printf("chaosAutonomous::autonomousWait() -> Entered"); 
	if ( !IsAutonomous() || IsDisabled() )
	{
		//printf("chaosAutonomous::autonomousWait() -> Antonomous Ends");
		TRACTIONCONTROL(0,0);
		return true;
	}
	if ( secs > 0 )	Wait(secs);
	//printf("chaosAutonomous::autonomousWait() -> Wait is done");
	return false;
}
void ChaosRobot::AutonomousContinuous(void)
{
	GetWatchdog().SetEnabled(false);
// Should be put in autonomous init function 
	func_tractioninit();
	//Angles from gyro are /2
	int turnangle = 45; // + (!additionalAngle_DI.Get()*45);
	float driveLength = 2.5 + (!additionalDirection_DI.Get()*2.5);
	float distanceTravelled  = 0.0;
	float averageVelocity;
	float totalTime;
	float time;
	float remainder;
	// True is Right
	bool leftRight = leftRight_DI.Get() == 0;
    if(!leftRight) turnangle = -turnangle;
	// Drive
	//printf("chaosAutonomous::drive -> drive forward");
	//		Motor
	TRACTIONCONTROL(1,1);
	//		Determine distance

	//printf("chaosAutonomous::drive -> Driving %d meters", driveLength);
	while(distanceTravelled < driveLength)
	{	
		timer.Reset();
		//startCycleTime=timer.Get() - previousTime;
		float r_encoder_val =  -r_encoder.GetValue(); 
		float l_encoder_val =   l_encoder.GetValue();
		
		//linear_y.CalculateValue();
		averageVelocity = (r_encoder_val + l_encoder_val) / 2;
		distanceTravelled += averageVelocity * PERIOD;
		// This cycle allows the low pass filter to get a new value each loop.
		time = timer.Get();
		remainder = PERIOD-time;
		if(remainder > 0)
		{
			if (autonomousWait(remainder))return;	
		}
		else
		{
			if (autonomousWait(0))return;
			// printf("chaosAutonomous::drive -> The loop takes longer than %f ms\n", PERIOD);
		}
		// printf("Dlength =  %2.3f, Dtravelled = %2.3f\n", driveLength,distanceTravelled);

		totalTime = totalTime + (timer.Get());
	}
	// printf("chaosAutonomous::drive ->  Stop");
	//		Stop
	TRACTIONCONTROL(0,0);

    
    
    
    // Determine direction to go
	// Turn 
	// printf("chaosAutonomous::start -> Turning %s\n", (leftRight?"Right":"Left"));
	// 		Motor comands
	float startangle = linear_y.gyro.GetAngle();
	float testangle = startangle;
	float goalangle = startangle + turnangle;
	
	
	
	if(leftRight)
	{
		TRACTIONCONTROL(-1,1);	
	}
	else 
	{
		TRACTIONCONTROL(1,-1);
	};
	// printf("chaosAutonomous::start -> Check the turn angle\n");
	
	
	
	while(((leftRight == true)&&(testangle < goalangle))||
		  ((leftRight != true)&&(testangle > goalangle)))
		 
	{
		if ( autonomousWait(.1) )return;
		
		testangle = linear_y.gyro.GetAngle();
		// printf("Test Angle: %02.3f\n", testangle);
		
	}
	// printf("chaosAutonomous::start -> Stop the turn:");
	//		Stop
	TRACTIONCONTROL(0,0); 

	// Drive
	// printf("chaosAutonomous::drive -> drive forward");
	//		Motor
	TRACTIONCONTROL(0.25, 0.25);
	//		Determine distance
	distanceTravelled = 0;
	// printf("chaosAutonomous::drive -> Driving %d meters", driveLength);
	while(distanceTravelled < driveLength)
	{	
		timer.Reset();
		//startCycleTime=timer.Get() - previousTime;
		float r_encoder_val = -r_encoder.GetValue(); 
		float l_encoder_val =  l_encoder.GetValue();
		
		//linear_y.CalculateValue();
		averageVelocity = (r_encoder_val + l_encoder_val) / 2;
		distanceTravelled += averageVelocity * PERIOD;
		// This cycle allows the low pass filter to get a new value each loop.
		time = timer.Get();
		remainder = PERIOD-time;
		if(remainder > 0)
		{
			if (autonomousWait(remainder))return;	
		}
		else
		{
			if (autonomousWait(0))return;
			// printf("chaosAutonomous::drive -> The loop takes longer than %f ms\n", PERIOD);
		}

		totalTime = totalTime + (timer.Get());
	}
	// printf("chaosAutonomous::drive ->  Stop");
	//		Stop
	TRACTIONCONTROL(0,0);

    
 	// Turn second
	// printf("chaosAutonomous::2nd turn -> Turning %s", (leftRight)?"Right": "Left"); 
	// 		Motor comands
	if(!leftRight)
	{
		TRACTIONCONTROL(-1,1);	
	}
	else 
	{
		TRACTIONCONTROL(1,-1);
	};
	// printf("chaosAutonomous::2nd turn -> determine angle:");
	// 		Determine angle
	while(linear_y.gyro.GetAngle() < (leftRight)?90:-90)
	{
		if (autonomousWait(.1))return;
	}
	// printf("chaosAutonomous::2nd turn -> Stop");
	//		Stop
	func_drive(0,0);
	// Backup 
	totalTime = 0;
	if(false)
	{
		// printf("chaosAutonomous::backup ->  go backwards"); 
		// Motor commands
		TRACTIONCONTROL(-1,-1);
		// Determine velocity until acceleration is none
		// Change the .2 later
		do 
		{	
			timer.Reset();
			//startCycleTime=timer.Get() - previousTime;
			linear_y.CalculateValue();
			averageVelocity = (linear_y.V_RightChassis + linear_y.V_LeftChassis) / 2;
			// This cycle allows the low pass filter to get a new value each loop.
			time = timer.Get();
			remainder = PERIOD-time;
			if(remainder > 0)
			{
				if (autonomousWait(remainder)) return;	
			}
			else
			{
				// printf("chaosAutonomous::backup -> The loop takes longer than %f ms\n", PERIOD);
			}

			totalTime = totalTime + (timer.Get());
		} while(fabs(averageVelocity) > .2);
		// printf("chaosAutonomous::backup ->  Stop");		
			// Stop
			func_drive(0,0);
		
	}
	// printf("chaosAutonomous::spin ->  Lets do a spin"); 
	// Wait motionless until end of period ????!!!
	while ( true )
	{
		TRACTIONCONTROL(1,-1);
		if ( autonomousWait(.01) ) return;
	}
//
//	// Tracking
//	printf("chaosAutonomous::start -> Finding Target");
//	//		Determine mobile or stationary tracking
//	if(mobileTracking_DI.Get())
//	{
//		AutoTrack();
//	}
//	else
//	{
//		MobileAutoTrack();
//	}
//	// 			Mobile: Start Camera Tracking
//	//					Connect Tracking to Motor Commands
}

void ChaosRobot::slewControl(float rightDirection, float leftDirection)
{
	float step;
	for (step = 0.0; step < 11.0; step++)
	{
		func_drive((step * rightDirection)/10.0, (step * leftDirection)/10.0);
		Wait(.025);
	}
}



void ChaosRobot::TeleopContinuous(void)
{
	GetWatchdog().SetEnabled(false);
		
	//visiontask.Start();
		
	
	//TurretSelfCalibrate();
	func_tractioninit();
		
	timer.Start();
	logger.openIfClosed();
		
	while (IsOperatorControl() && !IsDisabled())
	{
		logger.markButton = pilot1.GetNumberedButton(1);
		GetWatchdog().Feed();
			
		timer.Reset();	
		logger.mailLoopTm1 = timer.Get();
/*		
  		if ( DASHBOARD )
		{
			UpdateDashboard();

		}
	*/
		logger.mailLoopTm4 = timer.Get();
		func_drive(-pilot1.GetRightY(), -pilot1.GetLeftY());
		
		// TurretTrack();
		Shooter();
		
		if(pilot2.GetNumberedButton(6))
		{
			intake.Set(-1); //Out
			//printf("INTAKE 1\n");
		}
		else
		{
			intake.Set(1); //In
			//printf("INTAKE -1\n");
		}
		
		
		if(pilot2.GetNumberedButton(7))
		{
			lifter.Set(1); //up
			shootRoller.Set(Relay::kForward);
			//printf("LIFTER 1\n");
		}
		else if(pilot2.GetNumberedButton(4))
		{
			lifter.Set(-1); //down
			shootRoller.Set(Relay::kOff);
			//printf("LIFTER -1\n");
		}
		else
		{
			lifter.Set(0); //NO
			shootRoller.Set(Relay::kOff);
		}
		
		if (pilot1.GetNumberedButton(8))
		{
			thelight.Set(Relay::kOn);
		}
		else
		{
			thelight.Set(Relay::kOff);
		}
		

/*		
		if(pilot1.GetNumberedButton(5))
		{
			modeloops++;
			if(modeloops >= 20)
			{
				while(modeloops>=1)
				{
					 //printf("KPR: %02.2f, KPL: %02.2f, KIR: %02.4f, KIL: %02.4f\n , KPR, KPL, KIR, KIL); 
					
					if(pilot1.GetNumberedButton(1))
					{
						if ( KPR == 0 )
						{
							KPR=.05;
						}
						KPR = KPR + KPR/10; 
					}
					if(pilot1.GetNumberedButton(3))
					{
						KPR = KPR - KPR/10;
					}
					if(pilot1.GetNumberedButton(4))
					{
						if ( KPL == 0 )
						{
							KPL = .05;
						}
						KPL = KPL + KPL/10;
				    }
					if(pilot1.GetNumberedButton(2))
				    {
						KPL = KPL - KPL/10;
					}
					if(pilot1.GetDPad() == Gamepad::kUp)
					{
						if ( KIR == 0 )
						{
							KIR=.05;
						}

					    KIR = KIR + KIR/10;
				    }
					if(pilot1.GetDPad() == Gamepad::kDown)
			        {
						KIR = KIR - KIR/10;
				    }
					if(pilot1.GetDPad () == Gamepad::kLeft)
					{
						if ( KIL == 0 )
						{
							KIL=.05;
						}

				        KIL = KIL + KIL/10;
					}
					if(pilot1.GetDPad() == Gamepad::kRight)
					{
						KIL = KIL - KIL/10;
			        }

					if(pilot1.GetNumberedButton(5))
					{
					   modeloops--;
					   if ( modeloops <= 0 )
					   {
						   // printf("Press 1 for ok, 3 for cancel\n");
						   while ( !pilot1.GetNumberedButton(3) && !pilot1.GetNumberedButton(1))
							   Wait(.01);
						   
						   if ( pilot1.GetNumberedButton(1) )
						   {
							   writeCalibrationFile();
						   }
					   }
					}

					
					logger.KP[0] = KPL;
					logger.KP[1] = KPR;
					logger.KI[0] = KIL;
					logger.KI[1] = KIR;
					
				}
			}
		}
*/
		
		float time = timer.Get();
		float remainder = PERIOD-time;
		//logger.mailLoopTm3 = time;	
		logger.post();
		//logger.mailLoopTm4 = timer.Get();
  		if (pilot1.GetNumberedButton(5))
  		{
			if ( DASHBOARD )
			{
				/* tbinns 10/18 Removed dashData references */
				//dashData.PackAndSend();
				UpdateDashboard();
	
			}
  		}
		
		if(remainder > 0)
		{
			 Wait(remainder);	
		}
		else
		{
			//DashPrintf("The loop takes longer than %f ms\n");
		}
	}
}

void ChaosRobot::writeCalibrationFile()
{
//	FILE* csvfile = fopen("chaos_calibration.csv", "w");
//	if ( csvfile != NULL )
//	{
//		fprintf(csvfile,"KPL, KIL, KPR, KIR\r\n");
//		fprintf(csvfile,"%f,%f,%f,%f\r\n",
//				KPL, KIL, KPR, KIR);
//		fclose(csvfile);
//	}
//	FILE* binFile = fopen("chaos_calibration.csv", "w");
//	if ( binFile != NULL )
//	{
//		fwrite(&KPL, sizeof KPL, 1, binFile );
//		fwrite(&KIL, sizeof KPL, 1, binFile );
//		fwrite(&KPR, sizeof KPL, 1, binFile );
//		fwrite(&KIR, sizeof KPL, 1, binFile );
//		fclose(binFile);
//	}
}

void ChaosRobot::readCalibrationFile()
{
//	FILE* binFile = fopen("chaos_calibration.csv", "r");
//	fread(&KPL, sizeof KPL, 1, binFile );
//	fread(&KIL, sizeof KPL, 1, binFile );
//	fread(&KPR, sizeof KPL, 1, binFile );
//	fread(&KIR, sizeof KPL, 1, binFile );
//	fclose(binFile);
}

/**
	 * Send data to the dashboard
	 * Just sending a few values to show the data changing.
	 * These values could be read from hardware.
	 */
/* tbinns 10/18 Added processing code */
void ChaosRobot::UpdateDashboard(void)
	{
		static float num = 0.0;
		dashboardDataFormat.m_AnalogChannels[0][0] = num;
		dashboardDataFormat.m_AnalogChannels[0][1] = 5.0 - num;
		dashboardDataFormat.m_DIOChannels[0]++;
		dashboardDataFormat.m_DIOChannelsOutputEnable[0]--;
		num += 0.01;
		if (num > 5.0) num = 0.0;
		dashboardDataFormat.PackAndSend();
	}

void ChaosRobot::DashPrintf(char* txt)
	{
		Dashboard &dashboard = m_ds->GetDashboardPacker();
	// 10/22/09 tbinns This needs to be uncommented and above removed 
	//&dashboard = m_ds->GetDashboardPacker();
		dashboard.Printf(txt);
	}

START_ROBOT_CLASS(ChaosRobot);

