
package org.usfirst.frc.team131.robot;

import edu.wpi.first.wpilibj.CameraServer;
import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.DoubleSolenoid.Value;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.command.Scheduler;
import edu.wpi.first.wpilibj.livewindow.LiveWindow;

import org.usfirst.frc.team131.robot.subsystems.ClawSubsystem;
import org.usfirst.frc.team131.robot.subsystems.DriveSubsystemQuick;
import org.usfirst.frc.team131.robot.subsystems.LinearLift;
import org.usfirst.frc.team131.robot.subsystems.PneumaticLift;

public class Robot extends IterativeRobot {

	public static final PneumaticLift pneumaticLift = new PneumaticLift ();
	public static final DriveSubsystemQuick driveSubsystemQuick = new DriveSubsystemQuick();
	public static final ClawSubsystem clawSubsystem = new ClawSubsystem();
	public static final LinearLift linearLift = new LinearLift();
	
	public static OI oi;

	private static int calcAuto = 0; 
	
	public static boolean smartDrive = true;
	public static boolean smartLifter = false;
	public static boolean fineTuning = false;
	
	public static long waitTime = 0;
	
	public static int preAutoState;
	public static int curAutoState;
	
    Command autonomousCommand;
    
    public void robotInit() {
		oi = new OI();
		
        smartDrive = true;
        
        if(RobotMap.CLAW && clawSubsystem.clawGetState() != Value.kForward) {
			clawSubsystem.clawOpen();
		}
        
        if(RobotMap.TILTER && pneumaticLift.tilterGetState() != Value.kForward) {
			pneumaticLift.tilterUp();
		}

        try {
        	CameraServer server = CameraServer.getInstance();
        	server.setQuality(75);
        	server.startAutomaticCapture("cam0");
        } catch (Exception e) {
    		e.printStackTrace();
        }
    }
	
	public void disabledPeriodic() {
		Scheduler.getInstance().run();
	}

    public void autonomousInit() {
        // schedule the autonomous command (example)
        if (autonomousCommand != null) autonomousCommand.start();
        
        int switchOne;
        int switchTwo;
        
        //if(RobotMap.TILTER && RobotMap.CLAW && RobotMap.DRIVE && RobotMap.LINEAR_LIFT){
			if(oi.autoSelector.getRawButton(6)) {
				switchOne = 1;
			}
			else {
				switchOne = 0;
			}
		//if(RobotMap.TILTER && RobotMap.CLAW && RobotMap.DRIVE && RobotMap.LINEAR_LIFT){
			if(oi.autoSelector.getRawButton(7)) {
				switchTwo = 2;
			}
			else {
				switchTwo = 0;
			}
			
			calcAuto = switchOne + switchTwo; 
			
	        driveSubsystemQuick.resetEncoders();
			driveSubsystemQuick.setPIDGains(0.25, 0.0, 0.001, 0.0, false); // @TODO more testing + gain tuning
			linearLift.setPIDGains(0.5, 0.0, 0, 0.0);
			
//	        if(RobotMap.LINEAR_LIFT) {
//				//linearLift.calibrateLifter();       	
//	        }
	        

			//}
        //}
			
	        
	        preAutoState = RobotMap.AUTO_INIT_STATE;
	        curAutoState = RobotMap.AUTO_CLOSE_CLAW;
    }

    public void autonomousPeriodic() {
        Scheduler.getInstance().run();
        //Robot.linearLift.printLifterSensors();

        
	    if(calcAuto == 0) { //Auto #1 (1 bin + 1 tote + robot) BYPASSES EVERYTHING AFTER LIFT
	    	if(curAutoState == RobotMap.AUTO_CLOSE_CLAW) {
	    		//System.out.println("Waiting");
	    		if(curAutoState != preAutoState) {
	    			Robot.clawSubsystem.clawClose();
		    		waitTime = System.currentTimeMillis() + 7000;
		    		preAutoState = curAutoState;	
	    		}
	    		if(Robot.clawSubsystem.clawGetState() == Value.kReverse && System.currentTimeMillis() > waitTime) {
	    			curAutoState = RobotMap.AUTO_LIFT; 
	    		}
	    	}
	    	
	    	if(curAutoState == RobotMap.AUTO_LIFT) {
	    		if (curAutoState != preAutoState)
	    		{
	    			linearLift.lifterPID.disable();
	    			waitTime = System.currentTimeMillis() + 750;
	    			System.out.println("Lifting");
	    					
	    			linearLift.moveLift(1.0);
	    			preAutoState = RobotMap.AUTO_LIFT;
	    		}
	    		else
	    		{
	    			System.out.println("still Lifting");
	    			if (System.currentTimeMillis() >= waitTime)
	    			{
	    				linearLift.moveLift(0.0);
	    				linearLift.setSetpoint(linearLift.getLifterPosition());
//	    				linearLift.lifterPID.enable();
	    				curAutoState = RobotMap.AUTO_DONE;
	    			}
	    		}
	    	}
	    	
		    if(curAutoState == RobotMap.AUTO_BCK_ADJ){
		    	if(curAutoState != preAutoState){
		    		Robot.driveSubsystemQuick.driveForward(-12.0);
		    		waitTime = System.currentTimeMillis() + 500;
		    		preAutoState = curAutoState;	    	
			    }
		    	if(System.currentTimeMillis() >= waitTime){
		    		curAutoState = RobotMap.AUTO_SIDE_ADJ;
		    	}
		    }
		    
		    if(curAutoState == RobotMap.AUTO_SIDE_ADJ){
		    	if(curAutoState != preAutoState){
		    		Robot.driveSubsystemQuick.driveStrafe(33.0);
		    		waitTime = System.currentTimeMillis() + 500;
		    		preAutoState = curAutoState;	    	
			    }
		    	if(System.currentTimeMillis() >= waitTime){
		    		curAutoState = RobotMap.AUTO_FWD_ADJ;
		    	}
		    }
		    
		    if(curAutoState == RobotMap.AUTO_FWD_ADJ){
		    	if(curAutoState != preAutoState){
		    		Robot.driveSubsystemQuick.driveForward(15.0);
		    		waitTime = System.currentTimeMillis() + 500;
		    		preAutoState = curAutoState;	    	
			    }
		    	if(System.currentTimeMillis() >= waitTime){
		    		curAutoState = RobotMap.AUTO_LIFT_AGAIN;
		    	}
		    }
		    
		    if(curAutoState == RobotMap.AUTO_LIFT_AGAIN){
	    		double setpoint = 0.0;
	    		if(preAutoState != curAutoState){
	    			Robot.linearLift.setSetpoint(Robot.linearLift.getLifterPosition() + RobotMap.LIFT_ONE_DISTANCE);
	    			setpoint = Robot.linearLift.getLifterPosition() + RobotMap.LIFT_ONE_DISTANCE;
	    			waitTime = System.currentTimeMillis() + 2000;
	    			preAutoState = curAutoState;
	    		}	
	    		if (Robot.linearLift.getLifterPosition() == setpoint || System.currentTimeMillis() >= waitTime) {
	    			curAutoState = RobotMap.AUTO_DRIVE_BACK;
	    		}
	    	}
	   
		    if(curAutoState == RobotMap.AUTO_DRIVE_BACK) {
	    		//System.out.println("Backing up");
	    		if(curAutoState != preAutoState) {
	    			Robot.driveSubsystemQuick.driveForward(-96.0); //TEST!!!
	    			preAutoState = curAutoState;
	    			waitTime = System.currentTimeMillis() + 1500;
	    		}
	    		if (System.currentTimeMillis()> waitTime){
	    			curAutoState = RobotMap.AUTO_TURN;
	    		}
	    	}
		    
		    if(curAutoState == RobotMap.AUTO_TURN) {
	    		//System.out.println("Turning");
	    		if(curAutoState != preAutoState) {
	    			Robot.driveSubsystemQuick.driveTurn(45.0);
	    			preAutoState = curAutoState;
	    			waitTime = System.currentTimeMillis() + 1000;
	    		}
	    		if (System.currentTimeMillis() > waitTime){
	    			curAutoState = RobotMap.AUTO_DONE;
	    		}
	    	}
		    
		    if(curAutoState == RobotMap.AUTO_DONE) {
	    		//System.out.println("Done");
	    		if(curAutoState != preAutoState) {
	    			//Robot.driveSubsystemQuick.simpleMechDrive(0.0, 0.0, 0.0);; //TEST!!!
	    			Robot.linearLift.moveLift(0.0);
	    			preAutoState = curAutoState;
	    		}
	    		else{
	    			//System.out.println("still done");
	    		}
    		}
	    	System.out.println("Commmunist");
	    	
	    	// CloseClaw
	    	// Wait 7 seconds
	    	// Start lift
	    	// Wait .75 seconds
	    	// Stop all
	    	
	    	//initial orientation: surrounding container in staging zone perpendicular to view from driver station
	    	// grab container with THE CLAW
	    	// move into auto zone - crabwalk left FIELD DIMENSIONS
	    }
	    else if(calcAuto == 1) { //Auto #2 (robot)
	    	//System.out.println("NASA Agent");
	    	if(preAutoState == RobotMap.AUTO_INIT_STATE) {
	    		driveSubsystemQuick.setPIDGains(0.5, 0.0, 0.001, 0.0, false);
	    		driveSubsystemQuick.drive.setPIDRange(-1.0, 1.0);
	    		Robot.driveSubsystemQuick.driveStrafe(60.0);
	    		preAutoState = curAutoState;
	    	}
//	    	if(Robot.driveSubsystemQuick.finishedStrafing(60.0)) {
//    			curAutoState = RobotMap.AUTO_DONE;
//	    	}
//	    	if(curAutoState == RobotMap.AUTO_DONE) {
//	    		if(curAutoState != preAutoState) {
//	    			Robot.driveSubsystemQuick.simpleMechDrive(0.0, 0.0, 0.0);; //TEST!!!
//	    			Robot.linearLift.moveLift(0.0);
//	    			preAutoState = curAutoState;
//	    		}
//    		}
	    }
	    else if(calcAuto == 2) { //Auto #3 (1 bin + back-up)
	    	if(curAutoState == RobotMap.AUTO_CLOSE_CLAW) {
	    		//System.out.println("Waiting");
	    		if(curAutoState != preAutoState) {
	    			Robot.clawSubsystem.clawClose();
		    		preAutoState = curAutoState;	
		    		
		    		waitTime = System.currentTimeMillis() + 7000;
		    	}
	    		if(Robot.clawSubsystem.clawGetState() == Value.kReverse && System.currentTimeMillis() > waitTime) {
	    			curAutoState = RobotMap.AUTO_LIFT;
	    		}
	    	}
	    	if(curAutoState == RobotMap.AUTO_LIFT) {
	    		if (curAutoState != preAutoState)
	    		{
	    			linearLift.lifterPID.disable();
	    			waitTime = System.currentTimeMillis() + 750;
	    			System.out.println("Lifting");
	    					
	    			linearLift.moveLift(1.0);
	    			preAutoState = RobotMap.AUTO_LIFT;
	    		}
	    		else
	    		{
	    			System.out.println("still Lifting");
	    			if (System.currentTimeMillis() >= waitTime)
	    			{
	    				linearLift.moveLift(0.0);
	    				linearLift.setSetpoint(linearLift.getLifterPosition());
//	    				linearLift.lifterPID.enable();
	    				curAutoState = RobotMap.AUTO_DRIVE_BACK;
	    			}
	    		}
	    		

//	    		linearLift.moveLift(0.0);
//	    		curAutoState = RobotMap.AUTO_DRIVE_BACK;
	    		
	    	}
	    	if(curAutoState == RobotMap.AUTO_DRIVE_BACK) {
	    		//System.out.println("Backing up");
	    		if(curAutoState != preAutoState) {
	    			linearLift.moveLift(0.0);
	    			Robot.driveSubsystemQuick.driveForward(-108.0); //TEST!!!
	    			preAutoState = curAutoState;
	    			waitTime = System.currentTimeMillis() + 1500;
	    		}
	    		if (System.currentTimeMillis()> waitTime){
	    			curAutoState = RobotMap.AUTO_DONE;		//Turning is weird
	    		}
	    	}
	    	if(curAutoState == RobotMap.AUTO_TURN) {
	    		//System.out.println("Turning");
	    		if(curAutoState != preAutoState) {
	    			Robot.driveSubsystemQuick.driveTurn(45.0);
	    			preAutoState = curAutoState;
	    			waitTime = System.currentTimeMillis() + 1500;
	    		}
	    		if (System.currentTimeMillis() > waitTime){
	    			curAutoState = RobotMap.AUTO_DONE;
	    		}
	    	}
	    	if(curAutoState == RobotMap.AUTO_DONE) {
	    		//System.out.println("Done");
	    		if(curAutoState != preAutoState) {
	    			//Robot.driveSubsystemQuick.simpleMechDrive(0.0, 0.0, 0.0);; //TEST!!!
	    			Robot.linearLift.moveLift(0.0);
	    			preAutoState = curAutoState;
	    		}
	    		else{
	    			//System.out.println("still done");
	    		}
    		}
	    	// System.out.println("the Hulk");
	    	System.out.println(linearLift.lifterBottomLight());
	    }
	    else if(calcAuto == 3) { //Auto #4 (3 totes + robot) //1st lift state must move to the 3rd to last hook
	    	if(curAutoState == RobotMap.AUTO_CLOSE_CLAW) {
	    		curAutoState = RobotMap.AUTO_DONE;
	       	}
	    	
	    	if(curAutoState == RobotMap.AUTO_LIFT){
	    		double setpoint = 0.0;
	    		if(preAutoState != curAutoState){
	    			Robot.linearLift.setSetpoint(Robot.linearLift.getLifterPosition() + RobotMap.LIFT_ONE_DISTANCE);
	    			setpoint = Robot.linearLift.getLifterPosition() + RobotMap.LIFT_ONE_DISTANCE;
	    			waitTime = System.currentTimeMillis() + 1000;
	    			preAutoState = curAutoState;
	    		}	
	    		if (Robot.linearLift.getLifterPosition() == setpoint || System.currentTimeMillis() >= waitTime) {
	    			curAutoState = RobotMap.AUTO_FWD_ADJ;
	    		}
	    	}
	    	
		    if(curAutoState == RobotMap.AUTO_FWD_ADJ){
		    	if(curAutoState != preAutoState){
		    		Robot.driveSubsystemQuick.driveForward(12.0);
		    		waitTime = System.currentTimeMillis() + 500;
		    		preAutoState = curAutoState;	    	
			    }
		    	if(System.currentTimeMillis() >= waitTime){
		    		curAutoState = RobotMap.AUTO_LIFT_AGAIN;
		    	}
		    }
		    
		    if(curAutoState == RobotMap.AUTO_LIFT_AGAIN){
	    		double setpoint = 0.0;
	    		if(preAutoState != curAutoState){
	    			Robot.linearLift.setSetpoint(Robot.linearLift.getLifterPosition() + RobotMap.LIFT_ONE_DISTANCE);
	    			setpoint = Robot.linearLift.getLifterPosition() + RobotMap.LIFT_ONE_DISTANCE;
	    			waitTime = System.currentTimeMillis() + 1000;
	    			preAutoState = curAutoState;
	    		}	
	    		if (Robot.linearLift.getLifterPosition() == setpoint || System.currentTimeMillis() >= waitTime) {
	    			curAutoState = RobotMap.AUTO_BCK_ADJ;
	    		}
	    	}
		    
		    if(curAutoState == RobotMap.AUTO_BCK_ADJ){
		    	if(curAutoState != preAutoState){
		    		Robot.driveSubsystemQuick.driveForward(-12.0);
		    		waitTime = System.currentTimeMillis() + 500;
		    		preAutoState = curAutoState;	    	
			    }
		    	if(System.currentTimeMillis() >= waitTime){
		    		curAutoState = RobotMap.AUTO_SIDE_ADJ;
		    	}
		    }
		    
		    if(curAutoState == RobotMap.AUTO_SIDE_ADJ){
		    	if(curAutoState != preAutoState){
		    		Robot.driveSubsystemQuick.driveStrafe(-41.0);
		    		waitTime = System.currentTimeMillis() + 2000;
		    		preAutoState = curAutoState;	    	
			    }
		    	if(System.currentTimeMillis() >= waitTime){
		    		curAutoState = RobotMap.AUTO_FWD_AGAIN;
		    	}
		    }
		    
		    if(curAutoState == RobotMap.AUTO_FWD_AGAIN){
		    	if(curAutoState != preAutoState){
		    		Robot.driveSubsystemQuick.driveForward(12.0);
		    		waitTime = System.currentTimeMillis() + 500;
		    		preAutoState = curAutoState;	    	
			    }
		    	if(System.currentTimeMillis() >= waitTime){
		    		curAutoState = RobotMap.AUTO_LIFT_THRICE;
		    	}
		    }
		    
		    if(curAutoState == RobotMap.AUTO_LIFT_THRICE){
	    		double setpoint = 0.0;
	    		if(preAutoState != curAutoState){
	    			Robot.linearLift.setSetpoint(Robot.linearLift.getLifterPosition() + RobotMap.LIFT_ONE_DISTANCE);
	    			setpoint = Robot.linearLift.getLifterPosition() + RobotMap.LIFT_ONE_DISTANCE;
	    			waitTime = System.currentTimeMillis() + 1000;
	    			preAutoState = curAutoState;
	    		}	
	    		if (Robot.linearLift.getLifterPosition() == setpoint || System.currentTimeMillis() >= waitTime) {
	    			curAutoState = RobotMap.AUTO_BCK_AGAIN;
	    		}
	    	}
		    
		    if(curAutoState == RobotMap.AUTO_BCK_AGAIN){
		    	if(curAutoState != preAutoState){
		    		Robot.driveSubsystemQuick.driveForward(-12.0);
		    		waitTime = System.currentTimeMillis() + 500;
		    		preAutoState = curAutoState;	    	
			    }
		    	if(System.currentTimeMillis() >= waitTime){
		    		curAutoState = RobotMap.AUTO_SIDE_FINAL;
		    	}
		    }
		    
		    if(curAutoState == RobotMap.AUTO_SIDE_FINAL){
		    	if(curAutoState != preAutoState){
		    		Robot.driveSubsystemQuick.driveStrafe(-41.0);
		    		waitTime = System.currentTimeMillis() + 2000;
		    		preAutoState = curAutoState;	    	
			    }
		    	if(System.currentTimeMillis() >= waitTime){
		    		curAutoState = RobotMap.AUTO_FWD_FINAL;
		    	}
		    }
		    
		    if(curAutoState == RobotMap.AUTO_FWD_FINAL){
		    	if(curAutoState != preAutoState){
		    		Robot.driveSubsystemQuick.driveForward(12.0);
		    		waitTime = System.currentTimeMillis() + 500;
		    		preAutoState = curAutoState;	    	
			    }
		    	if(System.currentTimeMillis() >= waitTime){
		    		curAutoState = RobotMap.AUTO_LIFT_FINAL;
		    	}
		    }
		    
		    if(curAutoState == RobotMap.AUTO_LIFT_FINAL){
	    		double setpoint = 0.0;
	    		if(preAutoState != curAutoState){
	    			Robot.linearLift.setSetpoint(Robot.linearLift.getLifterPosition() + RobotMap.LIFT_ONE_DISTANCE);
	    			setpoint = Robot.linearLift.getLifterPosition() + RobotMap.LIFT_ONE_DISTANCE;
	    			waitTime = System.currentTimeMillis() + 1000;
	    			preAutoState = curAutoState;
	    		}	
	    		if (Robot.linearLift.getLifterPosition() == setpoint || System.currentTimeMillis() >= waitTime) {
	    			curAutoState = RobotMap.AUTO_DRIVE_BACK;
	    		}
	    	}
		    
		    if(curAutoState == RobotMap.AUTO_DRIVE_BACK) {
	    		//System.out.println("Backing up");
	    		if(curAutoState != preAutoState) {
	    			Robot.driveSubsystemQuick.driveForward(-108.0); //TEST!!!
	    			preAutoState = curAutoState;
	    			waitTime = System.currentTimeMillis() + 1500;
	    		}
	    		if (System.currentTimeMillis()> waitTime){
	    			curAutoState = RobotMap.AUTO_TURN;
	    		}
	    	}
	    	
		    if(curAutoState == RobotMap.AUTO_TURN) {
	    		//System.out.println("Turning");
	    		if(curAutoState != preAutoState) {
	    			Robot.driveSubsystemQuick.driveTurn(45.0);
	    			preAutoState = curAutoState;
	    			waitTime = System.currentTimeMillis() + 1500;
	    		}
	    		if (System.currentTimeMillis() > waitTime){
	    			curAutoState = RobotMap.AUTO_SCORE;
	    		}
	    	}
	    	
		    if(curAutoState == RobotMap.AUTO_SCORE){
		    	double setpoint = 0.0;
		    	if(curAutoState != preAutoState){
		    		Robot.linearLift.setSetpoint(Robot.linearLift.getLifterPosition() - (3.25 * RobotMap.LIFT_ONE_DISTANCE));
		    		setpoint = Robot.linearLift.getLifterPosition() - (3.25 * RobotMap.LIFT_ONE_DISTANCE);
		    		waitTime = System.currentTimeMillis() + 3000;
		    		preAutoState = curAutoState;
		    	}
		    	if(System.currentTimeMillis() > waitTime || Robot.linearLift.getLifterPosition() <= setpoint){
		    		curAutoState = RobotMap.AUTO_BACK_OFF;
		    	}
		    }
		    
		    if(curAutoState == RobotMap.AUTO_BACK_OFF) {
	    		//System.out.println("Backing up");
	    		if(curAutoState != preAutoState) {
	    			Robot.driveSubsystemQuick.driveForward(-2.0); //TEST!!!
	    			preAutoState = curAutoState;
	    			waitTime = System.currentTimeMillis() + 500;
	    		}
	    		if (System.currentTimeMillis()> waitTime){
	    			curAutoState = RobotMap.AUTO_DONE;
	    		}
	    	}
		    
		    if(curAutoState == RobotMap.AUTO_DONE) {
	    		//System.out.println("Done");
	    		if(curAutoState != preAutoState) {
	    			//Robot.driveSubsystemQuick.simpleMechDrive(0.0, 0.0, 0.0);; //TEST!!!
	    			Robot.linearLift.moveLift(0.0);
	    			preAutoState = curAutoState;
	    		}
	    		else{
	    			//System.out.println("still done");
	    		}
    		}
	    }
	    else {
	    System.out.println("should never return");	//What?
	    	//communists
	    }
    }

    public void teleopInit() {
        if (autonomousCommand != null) autonomousCommand.cancel();
        
        driveSubsystemQuick.setPIDGains(0.03, 0.0, 0.001, 1/12.0, true);
        driveSubsystemQuick.drive.setPIDRange(-1.0, 1.0);
        driveSubsystemQuick.drive.resetEncoders();
        driveSubsystemQuick.resetPID();
        
        linearLift.lifterPID.disable();
        linearLift.setPIDGains(0.3, 0.0, 0.0, 0.0);
        linearLift.lifterPID.reset();
    //    linearLift.lifterPID.enable();
    }

    public void disabledInit(){

    }

    public void teleopPeriodic() {
        Scheduler.getInstance().run();    
        
        if(RobotMap.DRIVE){  	//TODO test cubic input shaping
        	
        	double xDrive = oi.driver.getRawAxis(0) * oi.driver.getRawAxis(0) * oi.driver.getRawAxis(0) * RobotMap.MAX_SPEED;
        	double yDrive = oi.driver.getRawAxis(1) * oi.driver.getRawAxis(1) * oi.driver.getRawAxis(1) * RobotMap.MAX_SPEED;
        	double rDrive = oi.driver.getRawAxis(2) * oi.driver.getRawAxis(2) * oi.driver.getRawAxis(2) * RobotMap.MAX_SPEED; 
        
        	if(oi.driver.getRawAxis(1) > -0.01 && Robot.oi.driver.getRawAxis(1) < 0.01) {
        		yDrive = 0.0;
        	}
        	
        	if(fineTuning) {
    			xDrive = 0.25 * xDrive;
    			yDrive = 0.25 * yDrive;
    			rDrive = 0.25 * rDrive;
    		}
        	
        	if(RobotMap.APPROVAL) {
        		if(oi.driver.getRawButton(4)) { // the top or (Y) button
        			Robot.driveSubsystemQuick.simpleMechDrive(0.0, -0.1, 0.0); // y is inverted normally for joysticks
        		}
        		else {
        			if (smartDrive) {
                		driveSubsystemQuick.pIDMechDrive(xDrive, yDrive, rDrive);
                		
                		//System.out.printf("%.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f", driveSubsystemQuick.drive.)
                	}
                	else {
                		driveSubsystemQuick.simpleMechDrive(Robot.oi.driver.getRawAxis(0), Robot.oi.driver.getRawAxis(1), Robot.oi.driver.getRawAxis(2));
                	}
        		}
        	}
        	else {	
        		if (smartDrive) {
	        		driveSubsystemQuick.pIDMechDrive(xDrive, yDrive, rDrive);
	        		
	        		//System.out.printf("%.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f", driveSubsystemQuick.drive.)
	        	}
	        	else {
	        		driveSubsystemQuick.simpleMechDrive(Robot.oi.driver.getRawAxis(0), Robot.oi.driver.getRawAxis(1), Robot.oi.driver.getRawAxis(2));
	        	}
        	}	
        	driveSubsystemQuick.printDrive();
        }
        
        if(RobotMap.LINEAR_LIFT){
//        	if (!smartLifter){
//    			if(RobotMap.APPROVAL && Robot.oi.operator.getRawAxis(3) < 0.2) {
//    				linearLift.moveLift(0.1);
//    			}
//	    		else {
//	    			linearLift.manualLift(Robot.oi.operator.getRawAxis(3));
//	    		}
//        	linearLift.manualLift(Robot.oi.operator.getRawAxis(3));
//        	linearLift.printLifterSensors();
//        	}
    		if(oi.operator.getRawButton(6)) { // right bumper
    			Robot.linearLift.moveLift(0.3);
    		}
    		else if(oi.operator.getRawButton(8)) { // right trigger
    			Robot.linearLift.moveLift(-0.25);
    		}
    		else {
    			linearLift.manualLift(Robot.oi.operator.getRawAxis(1));
    		}
        }
    }
    
    public void testPeriodic() {
        LiveWindow.run();
    	//linearLift.manualLift(Robot.oi.operator.getRawAxis(1) *0.5);
    }
    
    public void testInit() {
    	//linearLift.calibrateLifter();
    }
    
    
}
