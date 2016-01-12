package org.usfirst.frc.team131.robot;

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
public class RobotMap {
	// boolean is for switching between raft and non-raft and whether or not subsystem exists 
	public static final boolean RAFT = false; 
	
	// booleans set false if we don't want respective code to run
	public static final boolean DRIVE = true; 
	public static final boolean LINEAR_LIFT = true; 
	public static final boolean CLAW = true; 
	public static final boolean TILTER = true; 
	public static final boolean POT_LIFTER = false; 
	public static final boolean APPROVAL = true;
	//public static boolean driveControl = false;
	//public static boolean manualLift = false;
	//public static boolean fineTuning = false;
	

	public static final int ENC_TICKS_PER_REV = 1000;
	public static final double ENC_WINCH_RADIUS = 2.0;
	public static final double ENC_WHEEL_RADIUS = 3.0;
	
	public static final double MECANUM_FORWARD_RATIO = 1 / Math.sqrt(2.0);
	public static final double MECANUM_SIDEWAYS_RATIO = 1 / Math.sqrt(2.0);
	public static final double MECANUM_ROTATION_RATIO = 1 / Math.sqrt(2.0);
	
	public static final double DIAGONAL_ROBOT_RADIUS = 24.0;
	
	public static final double MAX_SPEED = 24.0; //inches per second @ TODO testing
	public static final double MAX_HEIGHT = 64; 
	
	public static final double LIFT_POT_CONVERSION = 50000/10; //ohms per rotation
	public static final double LIFT_ENC_CONVERSION = 450/64; 
	
	public static final double LIFT_ONE_DISTANCE = 15.0; //Test!
	
	// Speed Controller PWM Ports
	public static final int FL_DRV_SC_PT = 0;
	public static final int FR_DRV_SC_PT= 2;	
	public static final int BL_DRV_SC_PT = 1;
	public static final int BR_DRV_SC_PT = 3;
	
	public static final int LIFT_SC = 4;	
	
	// Analog Inputs
	public static final int LIFT_POT = 0;
	
	//public static final SpeedController RFT_FL_DRV_SC = new Victor(FL_DRV_SC_PT);
	//public static final SpeedController RFT_FR_DRV_SC = new Victor(FR_DRV_SC_PT);
	//public static final SpeedController RFT_BL_DRV_SC = new Victor(BL_DRV_SC_PT);
	//public static final SpeedController RFT_BR_DRV_SC = new Victor(BR_DRV_SC_PT);
	
	//public static final SpeedController FNL_FL_DRV_SC = new Talon(FL_DRV_SC_PT);
	//public static final SpeedController FNL_FR_DRV_SC = new Talon(FR_DRV_SC_PT);
	//public static final SpeedController FNL_BL_DRV_SC = new Talon(BL_DRV_SC_PT);
	//public static final SpeedController FNL_BR_DRV_SC = new Talon(BR_DRV_SC_PT);
	
	// Encoder DIO Ports
	public static final int FL_DRV_ENC_A = 0; 
	public static final int FL_DRV_ENC_B = 1;
	public static final int FR_DRV_ENC_A = 2;
	public static final int FR_DRV_ENC_B = 3;
	public static final int BL_DRV_ENC_A = 4;
	public static final int BL_DRV_ENC_B = 5;
	public static final int BR_DRV_ENC_A = 6;
	public static final int BR_DRV_ENC_B = 7;
	
	public static final int LIFT_ENC_A = 8;
	public static final int LIFT_ENC_B = 9;
	
	// Boolean for Quadratic Encoder Direction
	public static final boolean LIFT_ENC_REV = true;
	
	
	// Light Sensor DIO Ports
	public static final int LIFT_CALIBRATOR = 13; 

	
	// Pneumatic Channels
	public static final int CLAW_OPEN_CH = 0;
	public static final int CLAW_CLOSE_CH = 1;	
	
	public static final int TILTER_UP_CH = 2;
	public static final int TILTER_DOWN_CH = 3;
	
	public static final int EXTRA_SOLENOID1_CH = 4;
	public static final int EXTRA_SOLENOID2_CH = 5;

	// Auto-States
	public static final int AUTO_INIT_STATE = 0;
	public static final int AUTO_CLOSE_CLAW = 1;
	public static final int AUTO_LIFT = 2;
	public static final int AUTO_DRIVE_FORWARD = 3;
	public static final int AUTO_LIFT_AGAIN = 4;
	public static final int AUTO_DRIVE_SIDEWAYS = 5;
	public static final int AUTO_DRIVE_BACK = 6;
	public static final int AUTO_DONE = 7;
	public static final int AUTO_TURN = 8;
	public static final int AUTO_BCK_ADJ = 9;
	public static final int AUTO_SIDE_ADJ = 10;
	public static final int AUTO_FWD_ADJ = 11;
	public static final int AUTO_SCORE = 12;
	public static final int AUTO_FWD_AGAIN = 13;
	public static final int AUTO_BCK_AGAIN = 14;
	public static final int AUTO_SIDE_AGAIN = 15;
	public static final int AUTO_FWD_FINAL = 16;
	public static final int AUTO_BACK_OFF = 17;
	public static final int AUTO_SIDE_FINAL = 18;
	public static final int AUTO_LIFT_THRICE = 19;
	public static final int AUTO_LIFT_FINAL = 20;
}
