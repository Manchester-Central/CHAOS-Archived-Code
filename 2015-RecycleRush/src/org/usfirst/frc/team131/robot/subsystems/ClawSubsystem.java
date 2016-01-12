package org.usfirst.frc.team131.robot.subsystems;

import org.usfirst.frc.team131.robot.RobotMap;

import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.DoubleSolenoid.Value;
import edu.wpi.first.wpilibj.command.Subsystem;

public class ClawSubsystem extends Subsystem {

	private final DoubleSolenoid claw; 
	
	public ClawSubsystem() {
		
		claw = new DoubleSolenoid(RobotMap.CLAW_OPEN_CH,RobotMap.CLAW_CLOSE_CH); 
		// TODO Auto-generated constructor stub
	}

//	public PneumaticLift(String name) {
//		super(name);
//		// TODO Auto-generated constructor stub
//	}

	@Override
	protected void initDefaultCommand() {
		// TODO Auto-generated method stub

	}
	
	public void clawOpen() {
		if(claw.get() != Value.kForward) {
			claw.set(Value.kForward);
			try {
				Thread.sleep(250);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	public void clawClose() {
		if(claw.get() != Value.kReverse) {
			claw.set(Value.kReverse);
			try {
				Thread.sleep(250);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	public Value clawGetState() {
		return claw.get();
	}
}

