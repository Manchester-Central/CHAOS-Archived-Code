package org.usfirst.frc.team131.robot.subsystems;

import org.usfirst.frc.team131.robot.RobotMap;

import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.DoubleSolenoid.Value;
import edu.wpi.first.wpilibj.command.Subsystem;

public class PneumaticLift extends Subsystem {

	private final DoubleSolenoid tilter; 
	
	public PneumaticLift() {	
		tilter = new DoubleSolenoid(RobotMap.TILTER_UP_CH,RobotMap.TILTER_DOWN_CH); 
	}

	@Override
	protected void initDefaultCommand() {
		// TODO Auto-generated method stub
	}
	
	public void tilterUp() {
		if(tilter.get() != Value.kForward) {
			tilter.set(Value.kForward);
			try {
				Thread.sleep(250);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	public void tilterDown() {
		if(tilter.get() != Value.kReverse) {
			tilter.set(Value.kReverse);
			try {
				Thread.sleep(250);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	public Value tilterGetState() {
		return tilter.get();
	}
}
