#ifndef _REFERENCES_H
#define _REFERENCES_H

#include "Buttons.h"

#define MINIMUM_SCORE 0.01


//Configuration for inputs and output ports
// Game Pads
#define GAMEPAD_DRIVER 1                  //Reference to the Driver's USB port number
#define GAMEPAD_OPERATOR 2                //Reference to the Operator's USB port number

// Transmission motors
#define REAR_LEFT_TRANSMISSION_MOTOR_CHANNEL 1      //Reference to the Left motor's channel
#define REAR_RIGHT_TRANSMISSION_MOTOR_CHANNEL 2     //Reference to the Right motor's channel
#define FRONT_LEFT_TRANSMISSION_MOTOR_CHANNEL 3      //Reference to the Left motor's channel
#define FRONT_RIGHT_TRANSMISSION_MOTOR_CHANNEL 4     //Reference to the Right motor's channel


// Dribbling Motors
#define LEFT_DRIBBLING_MOTOR_CHANNEL 6 //Reference to Left driddling motor channel
#define RIGHT_DRIBBLING_MOTOR_CHANNEL 5 //Reference to Left driddling motor channel

//Motor Transmittion Encoders
#define RIGHT_MOTOR_ENCODER_CHANNEL_A 1 //Refernce to Right transmission encoder
#define RIGHT_MOTOR_ENCODER_CHANNEL_B 2 //Refernce to Right transmission encoder
#define LEFT_MOTOR_ENCODER_CHANNEL_A 3 //Refernce to Right transmission encoder
#define LEFT_MOTOR_ENCODER_CHANNEL_B 4 //Refernce to Right transmission encoder
#define ENCODER_DISTANCEPERPULSE 0.37  // cm/pulse

//Kicker
#define KICK_START_CHANNEL 14

//Modules in cROI
#define ANALOG_MODULE1 1	//Reference to the Analog module
#define ANALOG_MODULE2 2	//Reference to the Analog module
#define DIO_MODULE1 4       //Reference to the Digital Side Car on the first module (module 4)
#define DIO_MODULE2 6       //Reference to the Digital Side Car on the first module (module 4)
#define SOLENOID_MODULE1 7       //Reference to the Digital Side Car on the first module (module 4)

// Gyro Constants
#define TURN_CONTROLLER_GYRO_CHANNEL 1  //Reference to Gyro for Turn Controller 

// Compressor Constants
#define COMPRESS_PRESSURE_SWITCH_CHANNEL 13 //Reference to the Compressors pressure switch port
#define COMPRESS_RELAY_CHANNEL 1 //Reference to the Compressors relay port


//Solenoids
#define EXTENDER_A_CHANNEL 1
//#define EXTENDER_B_CHANNEL 8
#define RETRACTOR_A_CHANNEL 2
#define RETRACTOR_B_CHANNEL 6
#define LATCH_A_CHANNEL 3
#define LATCH_B_CHANNEL 7
#define VENT_A_CHANNEL 5
#define VENT_B_CHANNEL 4

//The Light
#define THE_LIGHT_CHANNEL 8

#define LINEAR_POT_CHANNEL 5

//Ultrasonic Sensor Constants
#define ULTRASONIC_BALL_DIGIN_CHANNEL 5
#define ULTRASONIC_BALL_DIGOUT_CHANNEL 6

//Inertial Sensors
#define ACCELEROMETER_CHANNEL_X 2
#define ACCELEROMETER_CHANNEL_Y 3
#define ACCELEROMETER_CHANNEL_Z 4

//Dribbler
//#define LEFT_DRIBBLING_MOTOR_CHANNEL 3 //Reference to Left driddling motor channel
//#define RIGHT_DRIBBLING_MOTOR_CHANNEL 4 //Reference to Left driddling motor channel
#define LEFT_DRIBBLING_ENCODER_CHANNEL_A 5
#define LEFT_DRIBBLING_ENCODER_CHANNEL_B 6
#define RIGHT_DRIBBLING_ENCODER_CHANNEL_A 7
#define RIGHT_DRIBBLING_ENCODER_CHANNEL_B 8

#define LEFT_DRIBBLER_LIMIT_SWITCH 9 //(sw1)
#define RIGHT_DRIBBLER_LIMIT_SWITCH 10 //(sw2)

//Cypres Board
#define KLPOT 1
//#define KRPOT 3
#define ALPOT 5
//#define ARPOT 7
#define WHEEL_STOW_OFFSET_POT 3
#define AUTO_EXTEND_POT_CHANNEL 7

//Tensioner Pot
#define POT_EXTEND_DISTANCE 5

#endif
