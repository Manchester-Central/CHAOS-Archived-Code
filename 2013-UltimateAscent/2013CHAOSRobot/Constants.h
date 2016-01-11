 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: Constants.h                                        
 **                                                             
 **   About:    
 **                                                             
 **   Property of Chaos, Copyright 2013
 **   Written by:  
 **               Kathryn Ly-Bishop
 **               Eric Moy
 **               Ben Papp
 **               Harrison R.
 **				  CHAOS.           
 **                                                                                           
 **   2013 1 19             
 **                                                             
 **-------------------------------------------------------------*/
#ifndef CONSTANTS_H_
#define CONSTANTS_H_
 

#define INTAKE_FEED_SPEED 0.5 //untested
#define INTAKE_UNJAM_SPEED -0.5 //untested

#define GOOD_SHOOTER_SPEED 0.0222 //time between 2 ticks when running
#define SHOOTER_VOLTAGE 1.00 	//untested
#define SHOOTER_SPEED_NUDGE 0.05
#define SHOOTER_SPEED_DEADBAND 0.0002

#define TARGET_SPEED_NUDGE 0.0001 //untested

//#define HPROLLER_SPEED -0.1		//CHANGE?

#define CONVEYOR_SPEED_BOTTOM -0.6	//Switch?
#define CONVEYOR_SPEED_TOP 0.6		//Switch?
/*
#define L_CLIMBING_SPEED_UP 0.5		//untested
#define R_CLIMBING_SPEED_UP -0.5	//untested
#define L_CLIMBING_SPEED_DOWN -0.5	//untested
#define R_CLIMBING_SPEED_DOWN 0.5	//untested
*/
#define DRIVE_STRAIGHT_TIME 2 //untested
#define DRIVE_SPEED 148.8 //estimate of the robot speed in inches/second

#define ENCODER_DISTANCE_COEFFICIENT 29.5 //(256 Tick/1 Box Rev)*(1 Box Rev/8.66 Inches)

#define SPEED_HYSTERESIS 2 //inches/sec
#define DISTANCE_HYSTERESIS 2

#define AUTO_TARGET_DISTANCE 48 //inches
#define AUTO_TARGET_SPEED .8  

//PID Gains
#define P_GAIN 0.5
#define I_GAIN 0.05
#define D_GAIN 0.1

#define LEFT_DIRECTION -1 
#define RIGHT_DIRECTION 1

#define AUTO_SHOOT_TIME 8.0


#endif 
