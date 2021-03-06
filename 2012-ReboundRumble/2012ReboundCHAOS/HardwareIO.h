#ifndef HARDWARE_IO_H_
#define HARDWARE_IO_H_


//-----------------DIGITAL MODULE-------------------------
#define DIGITAL_MODULE 1

//Drive Motors
//#define FRONT_LEFT_DRIVE_PORT 3
//#define REAR_LEFT_DRIVE_PORT 1
//#define FRONT_RIGHT_DRIVE_PORT 4
//#define REAR_RIGHT_DRIVE_PORT 2


//PWMS
#define RIGHT_DRIVE_PORT 1
#define LEFT_DRIVE_PORT 2
#define BRIDGE_TOGGLE_MOTOR_PORT 3
#define TOP_SHOOTER_MOTOR_PORT 4
#define CONVEYOR_MOTOR_PORT 5
#define INTAKE_MOTOR_PORT 6

//DIGITAL IOs

#define TOGGLE_UP_SWITCH_PORT 1
#define TOGGLE_DOWN_SWITCH_PORT 2

#define LIGHT_SENSOR_INTAKE_PORT 4
#define LIGHT_SENSOR_CONVEYOR_PORT 5
#define LIGHT_SENSOR_OUTPUT_PORT 6
#define TOP_SHOOTER_ENCODER_PORT_1 7
#define TOP_SHOOTER_ENCODER_PORT_2 8
#define FRONT_LIGHT_SENSOR_PORT 9

#define LEFT_ENCODER_PORT_1 11
#define LEFT_ENCODER_PORT_2 12
#define RIGHT_ENCODER_PORT_1 13
#define RIGHT_ENCODER_PORT_2 14

//RELAYS
#define LED_SIGNAL_RELAY_PORT 1
#define LED_SIGNAL_RELAY_TWO_PORT 2


//----------------- SECOND DIGITAL MODULE-------------------------
#define SECOND_DIGITAL_MODULE 2

#define DRIVING_RAMP_SWITCH 4


//-----------------ANALOG MODULE-------------------------
#define ANALOG_MODULE 1

#define GYRO_CHANNEL 1
#define DRIVING_GYRO_CHANNEL 2
#define ACCEL_CHANNEL 3
#define DISTANCE_SENSOR_PORT 4

//----------------Solenoid MODULE-------------------------
#define SOLENOID_MODULE 1


#endif
