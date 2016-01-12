package org.usfirst.frc.team131.robot.commands;

import org.usfirst.frc.team131.robot.Robot;

import edu.wpi.first.wpilibj.command.Command;

public class TilterTiltUp extends Command {
	
	private boolean done = false;
	public TilterTiltUp() {
	}

	public TilterTiltUp(String name) {
		super(name);
		// TODO Auto-generated constructor stub
	}

	public TilterTiltUp(double timeout) {
		super(timeout);
		// TODO Auto-generated constructor stub
	}

	public TilterTiltUp(String name, double timeout) {
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
		// check to make sure solenoid isn't already "forward"
		
		// If we aren't already, extend
		Robot.pneumaticLift.tilterUp();
		//try {
			// wait 5 seconds
			//System.out.println("Waiting and trying to move");
			//Thread.sleep(5000);									//Blocking Method @TODO replace with sensor/ nonblocking method
		//} catch (InterruptedException e) {
			//e.printStackTrace();
		//} finally {
			//System.out.println("Done");
			//done = true;
		//}
		done = true;
	}
		//If we are already extended, leave it alone
			 

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
