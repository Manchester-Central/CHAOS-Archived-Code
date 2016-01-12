package org.usfirst.frc.team131.robot.commands;

import org.usfirst.frc.team131.robot.Robot;
import org.usfirst.frc.team131.robot.RobotMap;
import edu.wpi.first.wpilibj.command.Command;

public class LiftOne extends Command {

	private boolean done = false;
	private double targetPosition;
	private double origionalPosition;
	
	public LiftOne() {

	}

	public LiftOne(String name) {
		super(name);
		// TODO Auto-generated constructor stub
	}

	public LiftOne(double timeout) {
		super(timeout);
		// TODO Auto-generated constructor stub
	}

	public LiftOne(String name, double timeout) {
		super(name, timeout);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void initialize() {
		done = false;
		origionalPosition = Robot.linearLift.getLifterPosition();
		targetPosition = origionalPosition + RobotMap.LIFT_ONE_DISTANCE; // @TODO We need to fine tune this
	}

	@Override
	protected void execute() {
		if(targetPosition > RobotMap.MAX_HEIGHT) {
			targetPosition = RobotMap.MAX_HEIGHT;	
		}
		Robot.linearLift.setPIDTarget(targetPosition);
		Robot.linearLift.lifterPID.enable();
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
