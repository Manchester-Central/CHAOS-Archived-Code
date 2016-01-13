/*-------------------------------------------------------------**
**                                                             
**   Filename: Refs.h                                     
**                                                             
**   About:    A central location for all robot constants
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Steven Kroh, Chaos.           
**                                                                                           
**   2011 1 16             
**                                                             
**-------------------------------------------------------------*/

#include "Buttons.h" 
#include "HardwareIO.h"
#include "Constants.h"

//DEBUG PRINTF

//#define printf if(true){//}else{printf}    				
//CRIO SLOTS

/*
#define DIGITAL_SIDECAR_1_SLOT 4
//Modules in cRIO
#define ANALOG_MODULE1 1	//Reference to the Analog module
#define ANALOG_MODULE2 2	//Reference to the Analog module
#define DIO_MODULE1 4       //Reference to the Digital Side Car on the first module (module 4)
#define DIO_MODULE2 6       //Reference to the Digital Side Car on the first module (module 4)
#define SOLENOID_MODULE1 7       //Reference to the Digital Side Car on the first module (module 4)

// Gyro Constants
#define TURN_CONTROLLER_GYRO_CHANNEL 1  //Reference to Gyro for Turn Controller 

//DRIVE MOTORS
#define REAR_LEFT_DRIVE_PORT 1
#define REAR_RIGHT_DRIVE_PORT 2
#define FRONT_LEFT_DRIVE_PORT 3
#define FRONT_RIGHT_DRIVE_PORT 4

//LINE FOLLOWING SENSORS
#define LEFT_LINE_TRACKER_PORT 5
#define BACK_LINE_TRACKER_PORT 6
#define RIGHT_LINE_TRACKER_PORT 7
*/

//GAMEPADS
/*
#define DRIVER_GAMEPAD_PORT 1
#define OPERATOR_GAMEPAD_PORT 2
*/

//TELEOP LOOP TIME REGULATION
/*
#define TELEOP_PERIOD .025 // (25ms)
#define AUTO_PERIOD .025

//SEMIAUTONOMOUS CONSTANTS
#define FULL_ON_FORWARD .5
#define TURNING_SPEED .15
#define BEGIN_TIME_OUT_TIME  0.5

//CHAINSAW
#define CHAINSAW_STOP 0
#define CHAINSAW_ACQUIRE 1
#define CHAINSAW_DROP -1
#define LIMIT_SWITCH_CHANNEL 4
#define CHAINSAW_MOTOR_CHANNEL 7
*/

//SHOULDER
/*
#define SHOULDER_SOLENOID_1_PORT 1
#define SHOULDER_SOLENOID_2_PORT 2
#define POT_CHANNEL 5 //TODO Find real values
*/

/*
#define SHOULDER_ANGLE_UP 30 //deg
#define SHOULDER_ANGLE_DOWN 0 //deg

//CONSTANTS
#define PI 3.14159

//LINEAR POT
#define MIN_VOLTAGE 0.0
#define MAX_VOLTAGE 10.0
*/
//COMPRESSOR
/*
#define COMPRESSOR_PRESSURE_SWITCH_CHANNEL 10
#define COMPRESSOR_RELAY_CHANNEL 1
*/

//Elbow Angles
/*
#define ANGLE_UP_CENTER_TOP 186.8
#define ANGLE_UP_SIDE_TOP 199.5
#define ANGLE_UP_CENTER_MIDDLE 249.0
#define ANGLE_UP_SIDE_MIDDLE 261.7
#define ANGLE_DOWN_CENTER_BOTTOM 96.9
#define ANGLE_DOWN_SIDE_BOTTOM 110.6
#define ANGLE_DOWN_PICKUP 158.7
#define ANGLE_DOWN_STOW 38.7
*/

/*
#define ELBOW_VICTOR 5
#define ELBOW_POT 2
*/
/*
#define HYSTERESIS_BAND 10 //degrees

//
#define AUTO_STATE_TIMEOUT 500.0 //loops
#define AUTO_TIMEOUT_ADDITION 1.0
#define SCORE_DISTANCE 24.0

//Ultrasonic Y Align Section
#define DIST_FROM_CENTER_TO_ULTRASONIC_INCHES 10.0
*/
/*
#define LEFT_ULTRASONIC_PING 11
#define LEFT_ULTRASONIC_ECHO 12
#define RIGHT_ULTRASONIC_PING 13
#define RIGHT_ULTRASONIC_ECHO 14
*/

