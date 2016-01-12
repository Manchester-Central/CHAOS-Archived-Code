package org.usfirst.frc.team131.robot.subsystems;

import org.usfirst.frc.team131.robot.RobotMap;

import edu.wpi.first.wpilibj.AnalogInput;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDSource.PIDSourceParameter;
import edu.wpi.first.wpilibj.SpeedController;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.command.Subsystem;

public class LinearLift extends Subsystem {

	public final AnalogInput lifterPot;
	protected final SpeedController lifterSC;
	private final Encoder lifterEnc;
	private final DigitalInput lifterCal;
	public final PIDController lifterPID;
	
	protected double kP = 0;
	protected double kI = 0;
	protected double kD = 0;
	protected double kF = 0;
	
	public double potOffset;
	
	public LinearLift() {
	
		lifterSC = new Victor(RobotMap.LIFT_SC);
		lifterEnc = new Encoder(RobotMap.LIFT_ENC_A, RobotMap.LIFT_ENC_B, RobotMap.LIFT_ENC_REV);
		lifterCal = new DigitalInput(RobotMap.LIFT_CALIBRATOR);
		lifterPot = new AnalogInput(RobotMap.LIFT_POT);
		
		if(RobotMap.POT_LIFTER) {
			lifterPID = new PIDController(kP, kI, kD, kF, lifterPot, lifterSC);
		}
		else {
			lifterEnc.setSamplesToAverage(100);
			lifterEnc.setDistancePerPulse((2 * Math.PI * RobotMap.ENC_WINCH_RADIUS) / RobotMap.ENC_TICKS_PER_REV);
			lifterEnc.setPIDSourceParameter(PIDSourceParameter.kDistance);

			
			lifterPID = new PIDController(kP, kI, kD, kF, lifterEnc, lifterSC);
		}
		lifterPID.setContinuous(true);
		lifterPID.enable();
		lifterPID.setOutputRange(-1.0, 1.0);
		
		potOffset = 0.0;
	}

	@Override
	protected void initDefaultCommand() {
		// TODO Auto-generated method stub
	}
	
	public void manualLift(double speed) {
		lifterSC.set(speed);
	}
	
	public void moveLift(double speed) {
		lifterSC.set(speed * -1.0);
	}
	
	public void calibrateEncoder() {
		lifterEnc.reset();
	}
	
	public int readEncoder() {
		return lifterEnc.get() * -1;
	}
	
	public double readPot() {
		return lifterPot.getVoltage();
	}
	
	public boolean lifterBottomLight() {
		return lifterCal.get();
	}
	
	public void setSetpoint( double position ) {
		lifterPID.setSetpoint(position * -1.0);
	}
	
	public void calibrateLifter() {
		lifterPID.disable();
		System.out.println(lifterBottomLight());
		if(lifterBottomLight()) { //if everything is already collapsed, just zero the encoder
			calibrateEncoder();
			potOffset = lifterPot.getVoltage();
		}
		else { //if not, move down slowly until it is
			boolean calibrated = false;
			moveLift(-0.25);
			System.out.println(lifterBottomLight());
			
			while(calibrated == false) {
				if(lifterBottomLight()) { //once it is fully collapsed, stop it, zero the encoder, and exit loop
					moveLift(0.0);
					calibrateEncoder();
					potOffset = lifterPot.getVoltage();
					
					calibrated = true;
					System.out.println("we stopped");
					setSetpoint(getLifterPosition());
					lifterPID.enable();
				}
				System.out.println("moving down");
				System.out.println(lifterBottomLight());
				try {
					Thread.sleep(50);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}
	
	public void printLifterSensors() {
		System.out.print("Encoder: ");
		System.out.print(lifterEnc.get());
		System.out.print(", POT: ");
		System.out.print(lifterPot.getVoltage());
		System.out.print(", Calibrator " );
		System.out.print(lifterCal.get());
		System.out.print(", PID Setpoint: ");
		System.out.print(lifterPID.getSetpoint());
		System.out.print(", PID Output: ");
		System.out.print(lifterPID.get());
		System.out.print(", PID Enabled?: ");
		System.out.println(lifterPID.isEnable());
	}
	
	public void setPIDGains(double kPin, double kIin, double kDin, double kFin) {
			lifterPID.setPID(kPin, kIin, kDin, kFin);
	}
	
	public void setPIDTarget(double inches) {
		if(RobotMap.POT_LIFTER) {
			double pIDInput = inches * RobotMap.LIFT_POT_CONVERSION + potOffset;
			lifterPID.setSetpoint(pIDInput);
		}
		else {
			double pIDInput = inches * RobotMap.LIFT_ENC_CONVERSION;
			setSetpoint(pIDInput);
		}
	}
	
	public double getLifterPosition() {
		if(RobotMap.POT_LIFTER) {
			double position = (lifterPot.getVoltage() - potOffset) / RobotMap.LIFT_POT_CONVERSION;
			System.out.print(position);
			System.out.print(" ");
			System.out.print(lifterPID.getSetpoint());
			return position;
		}
		else {
			double position = (lifterEnc.get() / RobotMap.LIFT_ENC_CONVERSION);
			System.out.print(position);
			System.out.print(" ");
			System.out.println(lifterPID.getSetpoint());
			return position;
		}
	}
}
