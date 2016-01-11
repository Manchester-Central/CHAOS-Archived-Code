 /*-------------------------------------------------------------**
 **                                                             
 **   Filename: HardwareIO.h                                       
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
#ifndef HARDWARE_IO_H_
#define HARDWARE_IO_H_


#define X_BUTTON 1
#define A_BUTTON 2
#define B_BUTTON 3
#define Y_BUTTON 4
#define START_BUTTON 10
#define LEFT_BUMPER_BUTTON 5
#define RIGHT_BUMPER_BUTTON 6
#define LEFT_TRIGGER_BUTTON 7
#define RIGHT_TRIGGER_BUTTON 8

#define ENABLE_DEBUG 0
#define DISABLED 0
#define ENABLED 1



//-----------------DIGITAL MODULE-------------------------
#define DIGITAL_MODULE 1

//Wheels, Shooter side is the front of robot
#define LEFT_FRONT_DRIVE_PORT 3	//Port 3
#define LEFT_BACK_DRIVE_PORT 4	//port 4
#define RIGHT_FRONT_DRIVE_PORT 1	//port 1
#define RIGHT_BACK_DRIVE_PORT 2		//port 2

#define LEFT_DRIVE_ENCODER_PORT_A 1 
#define LEFT_DRIVE_ENCODER_PORT_B 2  
#define RIGHT_DRIVE_ENCODER_PORT_A 3 
#define RIGHT_DRIVE_ENCODER_PORT_B 4 
//intake
#define INTAKE_TALON_PORT_A 5 	
#define INTAKE_TALON_PORT_B 6
//shooter
#define SHOOTER_ENCODER_PORT 6 		
#define SHOOTER_TALON_PORT 7		

//HP Roller
//#define HPROLLER_TALON_PORT 6	
#define HPROLLER_SPIKE_PORT 1

//Conveyor
#define CONVEYOR_TALON_PORT 8		
#define BOTTOM_TRACKER_PORT 5		
#define FRISBEE_GATE_PORT 7		
#define FRISBEE_INTAKE_PORT 8		
#define HUMAN_PLAYER_PICKUP_PORT 9	

//Climber
#define RIGHT_CLIMB_TALON_PORT 9	
#define LEFT_CLIMB_TALON_PORT 10		

#define DRIVER_GAMEPAD_PORT 1
#define OPERATOR_GAMEPAD_PORT 2

//----------------- SECOND DIGITAL MODULE-------------------------
#define SECOND_DIGITAL_MODULE 2




//-----------------ANALOG MODULE-------------------------
#define ANALOG_MODULE 1



//----------------Solenoid MODULE-------------------------
#define SOLENOID_MODULE 1


#endif
