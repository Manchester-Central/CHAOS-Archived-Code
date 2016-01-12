package org.usfirst.frc.team131.robot.commands;

import org.usfirst.frc.team131.robot.Robot;
import edu.wpi.first.wpilibj.command.Command;

public class LowerAll extends Command {
	
	private boolean done = false;
	
	public LowerAll() {
		// TODO Auto-generated constructor stub
	}

	public LowerAll(String name) {
		super(name);
		// TODO Auto-generated constructor stub
	}

	public LowerAll(double timeout) {
		super(timeout);
		// TODO Auto-generated constructor stub
	}

	public LowerAll(String name, double timeout) {
		super(name, timeout);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void initialize() {
		Robot.linearLift.lifterPID.disable();
		
		//if(Robot.linearLift.lifterBottomLight() || Robot.linearLift.readEncoder() <= 0 || Robot.linearLift.getLifterPosition() <= 0){
		if (Robot.linearLift.lifterBottomLight()) {
			done = true;
		}
		else{
			done = false;
		}
	}

	@Override
	protected void execute() {
		Robot.linearLift.moveLift(-0.25);
		//if(Robot.linearLift.lifterBottomLight() || Robot.linearLift.readEncoder() <= 0 || Robot.linearLift.getLifterPosition() <= 0) {
		if (Robot.linearLift.lifterBottomLight()) {
			Robot.linearLift.moveLift(0.0);
			Robot.linearLift.calibrateEncoder();
			Robot.linearLift.potOffset = 0.0;
			done = true;
		}
	}
	


	@Override
	protected boolean isFinished() {
		return done;
	}

	@Override
	protected void end() {
		Robot.linearLift.setSetpoint(Robot.linearLift.getLifterPosition());
		Robot.linearLift.lifterPID.enable();

	}

	@Override
	protected void interrupted() {
		// TODO Auto-generated method stub

	}

}
