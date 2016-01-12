package org.usfirst.frc.team131.robot.commands;

import org.usfirst.frc.team131.robot.Robot;
import edu.wpi.first.wpilibj.command.Command;

public class FineTuning extends Command {
	boolean done = false;

	public FineTuning() {
		// TODO Auto-generated constructor stub
	}

	public FineTuning(String name) {
		super(name);
		// TODO Auto-generated constructor stub
	}

	public FineTuning(double timeout) {
		super(timeout);
		// TODO Auto-generated constructor stub
	}

	public FineTuning(String name, double timeout) {
		super(name, timeout);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void initialize() {
		done = false;
		// TODO Auto-generated method stub

	}

	@Override
	protected void execute() {
		if(Robot.fineTuning) {
			Robot.fineTuning = false;
		}
		else {
			Robot.fineTuning = true;
		}
		done = true;
	}

	@Override
	protected boolean isFinished() {
		// TODO Auto-generated method stub
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
