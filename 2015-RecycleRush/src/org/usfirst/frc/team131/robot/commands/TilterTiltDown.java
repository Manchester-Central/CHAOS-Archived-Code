package org.usfirst.frc.team131.robot.commands;

import org.usfirst.frc.team131.robot.Robot;

import edu.wpi.first.wpilibj.command.Command;

public class TilterTiltDown extends Command {
	
	private boolean done = false;
	public TilterTiltDown() {
	}

	public TilterTiltDown(String name) {
		super(name);
		// TODO Auto-generated constructor stub
	}

	public TilterTiltDown(double timeout) {
		super(timeout);
		// TODO Auto-generated constructor stub
	}

	public TilterTiltDown(String name, double timeout) {
		super(name, timeout);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void initialize() {
		done = false; 
		System.out.println("Starting out");
		//Scheduler.getInstance().removeAll(); // @todo: determine if this is the right way to go
	}

	@Override
	protected void execute() {
		// check to make sure solenoid isn't already "Reversed"
		
		// if it isn't already, set the solenoid to retract
		Robot.pneumaticLift.tilterDown();
		// try {
			//wait 5 seconds
			// System.out.println("Waiting and trying to move");
			// Thread.sleep(5000);											//Blocking Method @TODO replace with sensor/ nonblocking method
		//}  catch (InterruptedException e) {
			//e.printStackTrace();
		//} finally {
		//	System.out.println("Done");
			// done = true;
		//}
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
