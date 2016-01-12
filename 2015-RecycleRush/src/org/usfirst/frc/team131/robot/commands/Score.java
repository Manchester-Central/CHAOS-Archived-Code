package org.usfirst.frc.team131.robot.commands;

import org.usfirst.frc.team131.robot.Robot;

import edu.wpi.first.wpilibj.DoubleSolenoid.Value;
import edu.wpi.first.wpilibj.command.Command;

public class Score extends Command {

	private boolean done = false;
	private boolean down = false;
	private double targetPosition;
	private double origionalPosition;
	private long waitTime;
	
	public Score() {
		// TODO Auto-generated constructor stub
	}

	public Score(String name) {
		super(name);
		// TODO Auto-generated constructor stub
	}

	public Score(double timeout) {
		super(timeout);
		// TODO Auto-generated constructor stub
	}

	public Score(String name, double timeout) {
		super(name, timeout);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void initialize() {	
		Robot.linearLift.lifterPID.disable();
		origionalPosition = Robot.linearLift.getLifterPosition();
		targetPosition = origionalPosition - 5.0; // @TODO We need to fine tune this
		waitTime = 0;
		if(targetPosition <= 0) {
			targetPosition = 0.0;
		}
		
		System.out.print(origionalPosition);
		System.out.println(targetPosition);
		
		//If the lift is down and the claw is open and the tilter is up then everything is done
		if(down && Robot.clawSubsystem.clawGetState() == Value.kForward && Robot.pneumaticLift.tilterGetState() == Value.kForward){ 
			done = true;
		}
		else{
			done = false; // if one or all of these things are not done then run while loop in execute() 
		}

	}

	@Override
	protected void execute() {	
		if(Robot.linearLift.readEncoder() <= 0 || Robot.linearLift.getLifterPosition() <= targetPosition) {
			down = true;
			System.out.print("down before we started");
		}
		
		if(Robot.pneumaticLift.tilterGetState() != Value.kForward && System.currentTimeMillis() >= waitTime){ // if the tilter is not up then move it up
			Robot.pneumaticLift.tilterUp();
			System.out.print("tilting up");
			waitTime = System.currentTimeMillis() + 100;
		}
		
		// if the tilter is up and the linear lift is up, then make the lift move down
		if(Robot.pneumaticLift.tilterGetState() == Value.kForward && down == false){ 
			Robot.linearLift.setPIDTarget(targetPosition);
			System.out.print("moving down");
		}
		
		// wait until the above are completed before opening the claw (if it isn't).
		if(Robot.pneumaticLift.tilterGetState() == Value.kForward && down && Robot.clawSubsystem.clawGetState() != Value.kForward){   
			Robot.clawSubsystem.clawOpen();
			System.out.print("opening claw");
		}
		if(down && Robot.clawSubsystem.clawGetState() == Value.kForward && Robot.pneumaticLift.tilterGetState() == Value.kForward){ 
			done = true; //if all of these things are finished then finish
			System.out.print("done");
		}
	}


	@Override
	protected boolean isFinished() {
		return done;
	}

	@Override
	protected void end() {
		Robot.linearLift.lifterPID.enable();

	}

	@Override
	protected void interrupted() {
		// TODO Auto-generated method stub

	}

}
