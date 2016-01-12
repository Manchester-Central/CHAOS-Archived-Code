package org.usfirst.frc.team131.robot.commands;

import org.usfirst.frc.team131.robot.Robot;
import edu.wpi.first.wpilibj.command.Command;

public class CalibrateLifter extends Command {

	public CalibrateLifter() {
	}

	public CalibrateLifter(String name) {
		super(name);
		// TODO Auto-generated constructor stub
	}

	public CalibrateLifter(double timeout) {
		super(timeout);
		// TODO Auto-generated constructor stub
	}

	public CalibrateLifter(String name, double timeout) {
		super(name, timeout);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void initialize() {

	}

	@Override
	protected void execute() {
		if(Robot.linearLift.lifterBottomLight() == false) {
			Robot.linearLift.moveLift(-0.1);
		}
		else{
		Robot.linearLift.moveLift(0.0);
		Robot.linearLift.calibrateEncoder();
		}
	}

	@Override
	protected boolean isFinished() {
		// TODO Auto-generated method stub
		return Robot.linearLift.lifterBottomLight();
	}

	@Override
	protected void end() {
		// TODO Auto-generated method stub

	}

	@Override
	protected void interrupted() {
		// TODO Auto-generated method stub

	}

}
