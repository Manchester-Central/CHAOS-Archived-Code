package org.usfirst.frc.team131.robot.commands;

import org.usfirst.frc.team131.robot.Robot;

import edu.wpi.first.wpilibj.DoubleSolenoid.Value;
import edu.wpi.first.wpilibj.command.Command;

public class TilterTilt extends Command {
	private boolean done = false;
	public TilterTilt() {
		// TODO Auto-generated constructor stub
		
	}

	public TilterTilt(String name) {
		super(name);
		// TODO Auto-generated constructor stub
	}

	public TilterTilt(double timeout) {
		super(timeout);
		// TODO Auto-generated constructor stub
	}

	public TilterTilt(String name, double timeout) {
		super(name, timeout);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void initialize() {
		// TODO Auto-generated method stub
		done = false; 
		System.out.println("Starting out");
	}

	@Override
	protected void execute() {
		// check if solenoid is extended
		if(Robot.pneumaticLift.tilterGetState() == Value.kForward) {
			// If we aren't already, retract
			Robot.pneumaticLift.tilterDown();
			try {
				// wait 5 seconds
				System.out.println("Waiting and trying to move");
				//Thread.sleep(5000);									//Blocking Method @TODO replace with sensor/ nonblocking method
			} finally {
				System.out.println("Done");
				done = true;
			}
		}
		// check if solenoid is retracted
		else if (Robot.pneumaticLift.tilterGetState() == Value.kReverse) {
			// If we aren't already, extend
			Robot.pneumaticLift.tilterUp();
			try {
				// wait 5 seconds
				System.out.println("Waiting and trying to move");
				//Thread.sleep(5000);									//Blocking Method @TODO replace with sensor/ nonblocking method
			} finally {
				System.out.println("Done");
				done = true;
			}
		}
		//If we are neither extended nor retracted, leave it alone
		else {
			Robot.pneumaticLift.tilterUp();
			System.out.println("Might as well do something");
			done = true;
		}	 
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
