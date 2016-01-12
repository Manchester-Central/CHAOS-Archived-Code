package org.usfirst.frc.team131.robot.subsystems;

import org.usfirst.frc.team131.robot.Robot;
import org.usfirst.frc.team131.robot.RobotMap;

import edu.wpi.first.wpilibj.RobotDrive.MotorType;
import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.command.Subsystem;

public class DriveSubsystemQuick extends Subsystem {
	
	public DriveSubsystemQuick() {
	
	}

	public ChaosRobotDrive drive;

	@Override
	protected void initDefaultCommand() {
		
		Talon frontLeft = new Talon(RobotMap.FL_DRV_SC_PT);
		Talon frontRight = new Talon(RobotMap.FR_DRV_SC_PT);
		Talon backLeft = new Talon(RobotMap.BL_DRV_SC_PT);
		Talon backRight = new Talon(RobotMap.BR_DRV_SC_PT);
		
		//drive = new RobotDrive(frontLeft, backLeft, frontRight, backRight);
		drive = new ChaosRobotDrive(0, frontLeft, backLeft, frontRight, backRight);

		drive.setInvertedMotor(MotorType.kFrontRight, true);
		drive.setInvertedMotor(MotorType.kRearRight, true);
		
		drive.setPIDGains(1.0, 0.0, 0.0, 0.0, false);
		
		System.out.println("Init robot drive system quick");
	}
	
	public void simpleMechDrive(double x, double y, double rotation) {
		//System.out.println("joystick input x:" + x + " y:" + y);
		System.out.printf("joystick input x:%f y:%f rotation:%f \n", x, y, rotation);
		drive.mecanumDrive_Cartesian(x, y, rotation, 0.0);
		
//		double mag = Math.sqrt(x*x + y*y); 
//		double ang = Math.atan2(y, x)* 180.0/Math.PI;
//		drive.mecanumDrive_Polar(mag, ang, rotation);	
		
	}
	
	public void printDrive(){
		System.out.print("fl active: ");
		System.out.print(drive.frontLeftController.isEnable());
		System.out.print("fr active: ");
		System.out.print(drive.frontRightController.isEnable());
		System.out.print("bl active: ");
		System.out.print(drive.rearLeftController.isEnable());
		System.out.print("br active: ");
		System.out.println(drive.rearRightController.isEnable());
		
		System.out.print("fl output: ");
		System.out.print(drive.frontLeftController.get());
		System.out.print("fr output: ");
		System.out.print(drive.frontRightController.get());
		System.out.print("bl output: ");
		System.out.print(drive.rearLeftController.get());
		System.out.print("br output: ");
		System.out.println(drive.rearRightController.get());
		
		System.out.print("fl set: ");
		System.out.print(drive.frontLeftController.getSetpoint());
		System.out.print("fr set: ");
		System.out.print(drive.frontRightController.getSetpoint());
		System.out.print("bl set: ");
		System.out.print(drive.rearLeftController.getSetpoint());
		System.out.print("br set: ");
		System.out.println(drive.rearRightController.getSetpoint());
		
		System.out.print("fl enc: ");
		System.out.print(drive.frontLeftEncoder.getRate());
		System.out.print("fr enc: ");
		System.out.print(drive.frontRightEncoder.getRate());
		System.out.print("bl enc: ");
		System.out.print(drive.rearLeftEncoder.getRate());
		System.out.print("br enc: ");
		System.out.println(drive.rearRightEncoder.getRate());
	}
	
	public void enableDrivePID() {
		drive.frontLeftController.enable();
		drive.frontRightController.enable();
		drive.rearLeftController.enable();
		drive.rearRightController.enable();
	}
	
	public void disableDrivePID() {
		drive.frontLeftController.disable();
		drive.frontRightController.disable();
		drive.rearLeftController.disable();
		drive.rearRightController.disable();
	}
	
	public void resetPID() {
		drive.frontLeftController.reset();
		drive.frontLeftController.setSetpoint(0.0);
		drive.frontLeftController.enable();
		
		drive.frontRightController.reset();
		drive.frontRightController.setSetpoint(0.0);
		drive.frontRightController.enable();
		
		drive.rearLeftController.reset();
		drive.rearLeftController.setSetpoint(0.0);
		drive.rearLeftController.enable();
		      
		drive.rearRightController.reset();
		drive.rearRightController.setSetpoint(0.0);
		drive.rearRightController.enable();
	}
	
	public void pIDMechDrive(double x, double y, double rotation) {
		drive.mecanumDrive_CartesianPID(x, y, rotation, 0.0);
	}
	
	public void resetEncoders() {
		drive.resetEncoders();
	}

	public void driveForward(double inches) {
		drive.driveDistanceY(inches);
	}
	
	public void driveStrafe(double inches) {
		drive.driveDistanceX(inches);
	}
	
	public void driveTurn(double degrees) {
		drive.driveDistanceRotation(degrees);
	}
	
	public void setPIDGains(double kP, double kI, double kD, double kF, boolean vel){
		drive.setPIDGains(kP, kI, kD, kF, vel);
	}
	
	public int fLEncPosition() {
		return drive.frontLeftEncoder.get();
	}
	
	public int fREncPosition() {
		return drive.frontRightEncoder.get();
	}
	
	public int bLEncPosition() {
		return drive.rearLeftEncoder.get();
	}
	
	public int bREncPosition() {
		return drive.rearRightEncoder.get();
	}
	
	public boolean finishedDrivingStraight(double targetInches){
		boolean done = false;
		if(bLEncPosition() >= targetInches && bREncPosition() >= targetInches && fLEncPosition() >= targetInches && fREncPosition() >= targetInches) {
	    	done = true;
		}
		else{
			done = false;
		}
		return done;
	}
	
	public boolean finishedTurning(double targetDegrees){ //not sure if positive is left or right
		boolean done = false;
		double rotation_Rad = targetDegrees * Math.PI / 180;
		double rotation_Arc = (rotation_Rad * RobotMap.DIAGONAL_ROBOT_RADIUS / RobotMap.MECANUM_ROTATION_RATIO) / 2.25;

		if(bLEncPosition() <= (rotation_Arc * -1.0) && bREncPosition() >= rotation_Arc && fLEncPosition() <= (rotation_Arc * -1.0) && fREncPosition() >= rotation_Arc) {
	    	done = true;
		}
		else{
			done = false;
		}
		return done;
	}
	
	public boolean finishedStrafing(double targetDegrees){ //not sure if positive is left or right
		boolean done = false;
		double targetInches = targetDegrees * (Math.PI/180)  * RobotMap.DIAGONAL_ROBOT_RADIUS;
		
		if(bLEncPosition() <= (targetInches * -1.0) && bREncPosition() >= targetInches && fLEncPosition() >= targetInches && fREncPosition() <= (targetInches * -1.0)) {
	    	done = true;
		}
		else{
			done = false;
		}
		return done;
	}
}
