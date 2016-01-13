#ifndef CHAOSVISION_H
#define CHAOSVISION_H

#include <iostream.h>
#include "math.h"

#include "AxisCamera.h" 
#include "BaeUtilities.h"
#include "FrcError.h"
#include "TrackAPI.h" 
#include "Target.h" 
#include "WPILib.h"
//#include "PCVideoServer.h"

class ChaosVision {

	DriverStation *ds; // driver station object
	DigitalInput teamcolor_DI;
//	Servo *horizontalServo; // first servo object
//	Servo *verticalServo; // second servo object
	float horizontalDestination; // servo destination (0.0-1.0)
	float verticalDestination; // servo destination (0.0-1.0)
	float targetSize;  // distance between green and pink centers in pixels
	
//	float horizontalPosition, verticalPosition; // current servo positions
//	float servoDeadband; // percentage servo delta to trigger move
	int framesPerSecond; // number of camera frames to get per second
	//Video Update
	//int cameraRotation; // angle that camera is mounted
//	float panControl; // to slow down pan
//	double sinStart; // control where to start the sine wave input for pan
	TrackingThreshold td1, td2; // color thresholds

	ParticleAnalysisReport par1, par2; // particle analysis report

	// initialize pan variables
	// incremental tasking toward dest (-1.0 to 1.0)
//	float incrementH, incrementV;
	
	// pan needs a 1-up number for each call
//	int panIncrement;
	
	// for controlling loop execution time 
//	float loopTime;
	//float loopTime = 0.05;											
	double currentTime;
	double lastTime;

    // search variables 
	bool foundColor;
	double savedImageTimestamp;
    bool staleImage;
	
	
	
	
	int iterations;

//	enum // Driver Station jumpers to control program operation
//	{	ARCADE_MODE = 1, // Tank/Arcade jumper is on DS Input 1 (Jumper present is arcade)
//		ENABLE_AUTONOMOUS = 2, // Autonomous/Teleop jumper is on DS Input 2 (Jumper present is autonomous)
//	} jumpers;

public:
	/**
	 * Constructor for this robot subclass.
	 * Create an instance of a RobotDrive with left and right motors plugged into PWM
	 * ports 1 and 2 on the first digital module. The two servos are PWM ports 3 and 4.
	 * Tested with camera settings White Balance: Flurorescent1, Brightness 40, Exposure Auto
	 */
	ChaosVision(void); 
	void startteleop(void); 
	float getTargetSize(void)
	{
		return targetSize;
	}
	bool getFoundColor(void)
	{
		return foundColor;
	}
    float getHorizontalDestination(void)
    {
    	return horizontalDestination;
    }
	

	/**
	 * Set servo positions (0.0 to 1.0) translated from normalized values (-1.0 to 1.0). 
	 * 
	 * @param normalizedHorizontal Pan Position from -1.0 to 1.0.
	 * @param normalizedVertical Tilt Position from -1.0 to 1.0.
	 */
	//void setServoPositions(float normalizedHorizontal, float normalizedVertical); 

	/**
	 * Adjust servo positions (0.0 to 1.0) translated from normalized values (-1.0 to 1.0). 
	 * 
	 * @param normalizedHorizontal Pan adjustment from -1.0 to 1.0.
	 * @param normalizedVertical Tilt adjustment from -1.0 to 1.0.
	 */
	//void adjustServoPositions(float normDeltaHorizontal, float normDeltaVertical); 

	/**
	 * Adjusts the servo gimbal based on the color tracked.
	 * Driving the robot or operating an arm based on color input from gimbal-mounted 
	 * camera is currently left as an exercise for the teams.
	 */
	void VisionMain(void); 

};
#endif
