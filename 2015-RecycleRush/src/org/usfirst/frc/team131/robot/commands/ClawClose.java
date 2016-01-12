package org.usfirst.frc.team131.robot.commands;

import org.usfirst.frc.team131.robot.Robot;

import edu.wpi.first.wpilibj.command.Command;

public class ClawClose extends Command {
	
	private boolean done = false;

	public ClawClose() {
		// TODO Auto-generated constructor stub
	}

	public ClawClose(String name) {
		super(name);
		// TODO Auto-generated constructor stub
	}

	public ClawClose(double timeout) {
		super(timeout);
		// TODO Auto-generated constructor stub
	}

	public ClawClose(String name, double timeout) {
		super(name, timeout);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void initialize() {
		// TODO Auto-generated method stub
		done = false;
	}

	@Override
	protected void execute() {
		//if(Robot.clawSubsystem.clawGetState() == Value.kForward) {
			// If we aren't already, retract
		Robot.clawSubsystem.clawClose();
		try {
				// wait 5 seconds
			System.out.println("Waiting and trying to move");
				//Thread.sleep(5000);									//Blocking Method @TODO replace with sensor/ nonblocking method
		} finally {
			System.out.println("Done");
			done = true;
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
