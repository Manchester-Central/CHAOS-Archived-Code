/*-------------------------------------------------------------**
**                                                             
**   Filename: Constants.h                                        
**                                                             
**   About:    A list of universal software constants
*              "No magic numbers"
*                       - Bill Larkins (2011)
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Steven Kroh 
**               Josh Allard
**               Ben Papp
**               Zain Abbas, Chaos.           
**                                                                                           
**   2011 1 16             
**                                                             
**-------------------------------------------------------------*/

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

//LOOP TIME REGULATION
#define TELEOP_PERIOD .025 // (25ms)
#define AUTO_PERIOD .025

//SEMIAUTONOMOUS CONSTANTS
#define FULL_ON_FORWARD .5
#define TURNING_SPEED .15
#define BEGIN_TIME_OUT_TIME  0.5
#define SERVO_TURNING_SPEED 0.7
#define SERVO_STOP_SPEED 0.0

//CHAINSAW
#define CHAINSAW_STOP 0.0
#define CHAINSAW_ACQUIRE -1.0
#define CHAINSAW_DROP 0.5
#define CHAINSAW_ULTRASONIC_EDGE 50.0
#define CHAINSAW_MINIMUM_IN_POSITION_BAND 3.0

//MANIPULATOR
#define SCORE_TIMEOUT 5.0
#define OPERATOR_SCORE_JOYSTICK_THRESHOLD .25

//SHOULDER
#define SHOULDER_ANGLE_UP 128.0 //deg
#define SHOULDER_ANGLE_DOWN 43.0 //deg

#define ELBOW_SERVO_OFFSET 20.0

//CONSTANTS
#define PI 3.14159

//LINEAR POT
#define VOLTAGE_1 2.82
#define VOLTAGE_2 2.42
#define ANGLE_1 90.0
#define ANGLE_2 180.0

//Elbow Angles
#define ANGLE_UP_CENTER_TOP 177.0
#define ANGLE_UP_SIDE_TOP 190.0
#define ANGLE_UP_CENTER_MIDDLE 237.0
#define ANGLE_UP_SIDE_MIDDLE 253.0
#define ANGLE_DOWN_CENTER_BOTTOM 86.0
#define ANGLE_DOWN_SIDE_BOTTOM 100.0
#define ANGLE_DOWN_PICKUP 155.0

#define ANGLE_DOWN_PICKUP_HP 56.0

#define ELBOW_MAXIMUM_ANGLE 260.0
#define ELBOW_MINIMUM_ANGLE 53.0

#define ANGLE_DOWN_STOW (ELBOW_MINIMUM_ANGLE + 1.0)

#define ELBOW_MAXIMUM_AT_SHOULDER_MAX 260.0

#define HYSTERESIS_BAND 5.0 //degrees
#define ELBOW_LIMIT_CORRECTION_POWER 0.25

//Elbow
#define ELBOW_STOP 0.0

//AUTONOMOUS
#define AUTO_STATE_TIMEOUT_RIGHT 1.5 //seconds
#define AUTO_STATE_TIMEOUT_LEFT 1.5 //seconds
#define AUTO_TIMEOUT_ADDITION 1.0
#define INITIAL_AUTO_SPEED -.4
#define AUTO_PROPORTION_FOR_END_SPEED -.2

#define ANGLE_CORRECTION_PROPORTION 0.01

#define SCORE_DISTANCE 63.0
#define SLOWING_DISTANCE 100.0
#define CENTER_PEG_DISTANCE 60.0
#define NORMAL_PEG_DISTANCE 65.0

#define AUTO_TURNING_SPEED -0.7
#define AUTO_BACKUP 0.5
#define AUTO_STOP 0.0
#define POSITION_ROBOT_MOVE_TIMEOUT 0.25
#define POSITION_ROBOT_PAUSE_TIMEOUT 0.25

#define MANIP_BACKUP_TIME_BEFORE_STOW 1.5

#define AUTO_DEAD_RECKON_TIME 2.0
#define AUTO_DEAD_RECKON_SPEED -.75
#define AUTO_POSITION_ROBOT_SPEED -.5

#define AUTO_PRE_SCORE_TIMEOUT 1.0

#define MAXBOTIX_MAX_DISTANCE 512.0 //inches
#define MAXBOTIX_MAX_VOLTAGE 5.0 //volts

//ULTRASONIC Y ALIGN
#define DIST_FROM_CENTER_TO_ULTRASONIC_INCHES 10.0

//ELBOW PID CONSTANTS
#define ELBOW_PROPORTIONAL_CONSTANT_INIT -0.02
#define ELBOW_INTEGRAL_CONSTANT_INIT -0.0
#define ELBOW_DERIVATIVE_CONSTANT_INIT -0.0

#define ELBOW_INPUT_RANGE_MAX 360.0   //max degrees of a circle
#define ELBOW_INPUT_RANGE_MIN 0.0     //min degrees of a circle

#define ELBOW_OUTPUT_RANGE_MAX 1.0  //max jag PWM signal
#define ELBOW_OUTPUT_RANGE_MIN -1.0 //min jag PWM signal

//SHOULDER
#define SHOULDER_VOLTAGE_1 2.70
#define SHOULDER_VOLTAGE_2 .10
#define SHOULDER_ANGLE_1 90.0
#define SHOULDER_ANGLE_2 37.0

//ULTRASONIC FILTER 
#define ULTRASONIC_FRACTION 0.2
#define ULTRASONIC_FILTER_INITIAL_VALUE 250.0

//MINIBOT DEPLOYMENT
#define FLAP_PIN_INIT_ANGLE 0.0
#define FLAP_PIN_DEPLOY_ANGLE 180.0
#define FLAP_PIN_TIME 1.0

//Autonomous PID Constants
#define AUTO_LEFT_PROPORTIONAL 0.1
#define AUTO_LEFT_DERIVATIVE 0.0
#define AUTO_LEFT_INTEGRAL 0.0
#define AUTO_LEFT_INPUT_RANGE_MAX 150.0   //max degrees of a circle

#define AUTO_LEFT_INPUT_RANGE_MIN 50.0     //min degrees of a circle
#define AUTO_LEFT_OUTPUT_RANGE_MAX 1.0  //max jag PWM signal
#define AUTO_LEFT_OUTPUT_RANGE_MIN 0.35 //min jag PWM signal

#define AUTO_RIGHT_PROPORTIONAL 0.1
#define AUTO_RIGHT_DERIVATIVE 0.0
#define AUTO_RIGHT_INTEGRAL 0.0
#define AUTO_RIGHT_INPUT_RANGE_MAX 150.0   //max degrees of a circle

#define AUTO_RIGHT_INPUT_RANGE_MIN 50.0     //min degrees of a circle
#define AUTO_RIGHT_OUTPUT_RANGE_MAX 1.0  //max jag PWM signal
#define AUTO_RIGHT_OUTPUT_RANGE_MIN 0.35 //min jag PWM signal

#endif
