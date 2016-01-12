package org.usfirst.frc.team131.robot.commands;

import org.usfirst.frc.team131.robot.Robot;

import edu.wpi.first.wpilibj.DoubleSolenoid.Value;
import edu.wpi.first.wpilibj.command.Command;

public class ToggleClaw extends Command {
	
	private boolean done = false;
	
	public ToggleClaw() {
		// TODO Auto-generated constructor stub
		
	}

	public ToggleClaw(String name) {
		super(name);
		// TODO Auto-generated constructor stub
	}

	public ToggleClaw(double timeout) {
		super(timeout);
		// TODO Auto-generated constructor stub
	}

	public ToggleClaw(String name, double timeout) {
		super(name, timeout);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void initialize() {
		done = false; 
		System.out.println("Starting out");
	}

	@Override
	protected void execute() {
		// check if solenoid is extended
		if(Robot.clawSubsystem.clawGetState() == Value.kForward) {
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
		}
		// check if solenoid is retracted
		else if (Robot.clawSubsystem.clawGetState() == Value.kReverse) {
			// If we aren't already, extend
			Robot.clawSubsystem.clawOpen();
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
			System.out.println("What?");
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
