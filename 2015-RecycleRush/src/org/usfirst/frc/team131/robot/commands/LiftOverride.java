package org.usfirst.frc.team131.robot.commands;

import org.usfirst.frc.team131.robot.Robot;
import edu.wpi.first.wpilibj.command.Command;

public class LiftOverride extends Command {
	boolean done;

	public LiftOverride() {
		// TODO Auto-generated constructor stub
	}

	public LiftOverride(String name) {
		super(name);
		// TODO Auto-generated constructor stub
	}

	public LiftOverride(double timeout) {
		super(timeout);
		// TODO Auto-generated constructor stub
	}

	public LiftOverride(String name, double timeout) {
		super(name, timeout);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void initialize() {
		done = false;
	}

	@Override
	protected void execute() {
		if(Robot.smartLifter) {
			Robot.smartLifter = false;
			Robot.linearLift.lifterPID.disable();
		}
		else {
			Robot.smartLifter = true;
			Robot.linearLift.setPIDTarget(Robot.linearLift.getLifterPosition());
			Robot.linearLift.lifterPID.reset();
			Robot.linearLift.lifterPID.enable();
		}
		done = true;
	}
	
	@Override
	protected boolean isFinished() {
		return done;
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
