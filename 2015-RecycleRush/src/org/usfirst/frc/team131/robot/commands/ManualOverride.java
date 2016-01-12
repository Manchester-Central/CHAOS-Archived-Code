package org.usfirst.frc.team131.robot.commands;

import org.usfirst.frc.team131.robot.Robot;
import edu.wpi.first.wpilibj.command.Command;

public class ManualOverride extends Command {
	boolean done;

	public ManualOverride() {
		// TODO Auto-generated constructor stub
	}

	public ManualOverride(String name) {
		super(name);
		// TODO Auto-generated constructor stub
	}

	public ManualOverride(double timeout) {
		super(timeout);
		// TODO Auto-generated constructor stub
	}

	public ManualOverride(String name, double timeout) {
		super(name, timeout);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void initialize() {
		done = false;
	}

	@Override
	protected void execute() {
		//RobotMap.driveControl = !RobotMap.driveControl;
		if(Robot.smartDrive) {
			Robot.driveSubsystemQuick.disableDrivePID();
			Robot.smartDrive = false;
		}
		else {
			Robot.smartDrive = true;
			Robot.driveSubsystemQuick.enableDrivePID();			
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
