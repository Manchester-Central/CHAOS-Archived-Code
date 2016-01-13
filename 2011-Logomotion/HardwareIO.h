/*-------------------------------------------------------------**
**                                                             
**   Filename: HardwareIO.h                                        
**                                                             
**   About:    Contians a hardware-software interface for slots
*              and channels
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Steven Kroh 
**               Josh Allard
**               Ben Papp
**               Zain Abbas, Chaos.           
**                                                                                           
**   2011 2 5   
**     
**   REV 2/21/2011       
**                                                             
**-------------------------------------------------------------*/

#ifndef HARDWARE_IO_H_
#define HARDWARE_IO_H_

#define DIO_MODULE1 1                         //DIGITAL SIDE CAR SLOT [4]
//---------------------------------------------------------------------

//PWM CHANNELS IN NUMERICAL ORDER
#define REAR_LEFT_DRIVE_PORT 2                //DRIVE MOTORS
#define REAR_RIGHT_DRIVE_PORT 1     
#define FRONT_LEFT_DRIVE_PORT 4
#define FRONT_RIGHT_DRIVE_PORT 3
#define ELBOW_VICTOR 7                        //ELBOW VICTOR
#define CHAINSAW_MOTOR_CHANNEL 5              //CHAINSAW MOTOR
#define MINIBOT_SERVO_PIN_CONTROL 10

//DIGITAL CHANNELS IN NUMERICAL ORDER
#define LEFT_DRIVE_ENCODER_A 1
#define LEFT_DRIVE_ENCODER_B 2
#define RIGHT_DRIVE_ENCODER_A 3
#define RIGHT_DRIVE_ENCODER_B 4
#define AUTONOMOUS_PEG_HEIGHT_LIMIT_SWITCH_CHANNEL 5                //CHAINSAW LIMIT SWITCH
#define UPPER_LINE_TRACKER_PORT 6              //LINE FOLLOWING SENSORS
#define LOWER_LINE_TRACKER_PORT 7
#define CHAINSAW_ULTRASONIC_SENSOR_PING 8
#define CHAINSAW_ULTRASONIC_SENOSR_ECHO 9
#define COMPRESSOR_PRESSURE_SWITCH_CHANNEL 10 //COMPRESSOR
#define LEFT_ULTRASONIC_PING 11               //ULTRASONIC
#define LEFT_ULTRASONIC_ECHO 12
#define RIGHT_ULTRASONIC_PING 13
#define RIGHT_ULTRASONIC_ECHO 14

//RELAY CHANNELS IN NUMERICAL ORDER
#define COMPRESSOR_RELAY_CHANNEL 1            //COMPRESSOR
#define INDICATOR_LIGHT_RELAY_REDWHITE 3
#define INDICATOR_LIGHT_RELAY_BLUE 2

//---END DIGITAL SIDE CAR----------------------------------------------



#define ANALOG_MODULE1 1                      //ANALOG MODULE [1]
//---------------------------------------------------------------------

//ANALOG CHANNELS IN NUMERICAL ORDER          
#define TURN_CONTROLLER_GYRO_CHANNEL 1        //GYRO
#define SHOULDER_POT 5                         //SHOULDER POT
#define ELBOW_POT 2                           //ELBOW POT
#define MAXBOTIX_ULTRASONIC 4

//---END ANALOG MODULE-------------------------------------------------




#define SOLENOID_MODULE1 1                   //SOLENOID MODULE [7]
//---------------------------------------------------------------------

//SOLENOID CHANNELS IN NUMERICAL ORDER
#define SHOULDER_SOLENOID_LEFT_PORT 1            //SHOULDER
#define SHOULDER_SOLENOID_RIGHT_PORT 2
#define DEPLOY_SOLENOID_PORT 3
#define FLAP_SOLENOID_PORT 4
#define SHUTTLE_SOLENOID_PORT 5

//---END SOLENOID MODULE-----------------------------------------------

#endif
