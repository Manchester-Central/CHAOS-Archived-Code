package org.usfirst.frc.team131.robot.subsystems;

import org.usfirst.frc.team131.robot.Robot;
import org.usfirst.frc.team131.robot.RobotMap;

import edu.wpi.first.wpilibj.CANJaguar;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDSource.PIDSourceParameter;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.SpeedController;
import edu.wpi.first.wpilibj.communication.UsageReporting;
import edu.wpi.first.wpilibj.communication.FRCNetworkCommunicationsLibrary.tInstances;
import edu.wpi.first.wpilibj.communication.FRCNetworkCommunicationsLibrary.tResourceType;

public class ChaosRobotDrive extends RobotDrive {
	
	
	public static class MotorType {

        /**
         * The integer value representing this enumeration
         */
		
        public final int value;
        static final int kFrontLeft_val = 0;
        static final int kFrontRight_val = 1;
        static final int kRearLeft_val = 2;
        static final int kRearRight_val = 3;
        /**
         * motortype: front left
         */
        public static final MotorType kFrontLeft = new MotorType(kFrontLeft_val);
        /**
         * motortype: front right
         */
        public static final MotorType kFrontRight = new MotorType(kFrontRight_val);
        /**
         * motortype: rear left
         */
        public static final MotorType kRearLeft = new MotorType(kRearLeft_val);
        /**
         * motortype: rear right
         */
        public static final MotorType kRearRight = new MotorType(kRearRight_val);

        private MotorType(int value) {
            this.value = value;
        }
    }
	
	protected Encoder frontLeftEncoder; 
	protected Encoder rearLeftEncoder;
	protected Encoder frontRightEncoder;
	protected Encoder rearRightEncoder;
	
	protected PIDController frontLeftController;
	protected PIDController rearLeftController;
	protected PIDController frontRightController;
	protected PIDController rearRightController;
	
	protected double kP;
	protected double kI;
	protected double kD;
	protected double kF;
	
	public ChaosRobotDrive(int leftMotorChannel, int rightMotorChannel) {
		super(leftMotorChannel, rightMotorChannel);
		
		frontLeftEncoder = null;
		rearLeftEncoder = null;
		frontRightEncoder = null;
		rearRightEncoder = null;
		
		frontLeftController= null;
		rearLeftController = null;
		frontRightController = null;
		rearLeftController = null;
	}

	public ChaosRobotDrive(SpeedController leftMotor, SpeedController rightMotor) {
		super(leftMotor, rightMotor);
		
		frontLeftEncoder = null;
		rearLeftEncoder = null;
		frontRightEncoder = null;
		rearRightEncoder = null;
		
		frontLeftController= null;
		rearLeftController = null;
		frontRightController = null;
		rearLeftController = null;
	}

	public ChaosRobotDrive(int frontLeftMotor, int rearLeftMotor,
			int frontRightMotor, int rearRightMotor) {
		super(frontLeftMotor, rearLeftMotor, frontRightMotor, rearRightMotor);
		
		frontLeftEncoder = null;
		rearLeftEncoder = null;
		frontRightEncoder = null;
		rearRightEncoder = null;
		
		frontLeftController= null;
		rearLeftController = null;
		frontRightController = null;
		rearLeftController = null;
	}

	public ChaosRobotDrive(SpeedController frontLeftMotor,
			SpeedController rearLeftMotor, SpeedController frontRightMotor,
			SpeedController rearRightMotor) {
		super(frontLeftMotor, rearLeftMotor, frontRightMotor, rearRightMotor);
		
		frontLeftEncoder = null;
		rearLeftEncoder = null;
		frontRightEncoder = null;
		rearRightEncoder = null;
		
		frontLeftController= null;
		rearLeftController = null;
		frontRightController = null;
		rearLeftController = null;	
	}

	public ChaosRobotDrive(int d, SpeedController frontLeftSpeedController,	SpeedController rearLeftSpeedController, 
			SpeedController frontRightSpeedController, SpeedController rearRightSpeedController){
		super(frontLeftSpeedController, rearLeftSpeedController, frontRightSpeedController, rearRightSpeedController);
		
		if (d == 0) {
			System.out.println("why"); 
		}
		
		m_invertedMotors[MotorType.kRearRight_val] = -1;
		m_invertedMotors[MotorType.kFrontRight_val] = -1;
		
		frontLeftEncoder= new Encoder(RobotMap.FL_DRV_ENC_A, RobotMap.FL_DRV_ENC_B, true);
		rearLeftEncoder = new Encoder (RobotMap.BL_DRV_ENC_A, RobotMap.BL_DRV_ENC_B, true);
		frontRightEncoder= new Encoder (RobotMap. FR_DRV_ENC_A, RobotMap.FR_DRV_ENC_B, true);
		rearRightEncoder = new Encoder (RobotMap.BR_DRV_ENC_A, RobotMap.BR_DRV_ENC_B, true);
		
		frontLeftEncoder.setDistancePerPulse((2 * Math.PI * RobotMap.ENC_WHEEL_RADIUS) / RobotMap.ENC_TICKS_PER_REV); //inches per pulse
		frontRightEncoder.setDistancePerPulse((2 * Math.PI * RobotMap.ENC_WHEEL_RADIUS) / RobotMap.ENC_TICKS_PER_REV);
		rearLeftEncoder.setDistancePerPulse((2 * Math.PI * RobotMap.ENC_WHEEL_RADIUS) / RobotMap.ENC_TICKS_PER_REV);
		rearRightEncoder.setDistancePerPulse((2 * Math.PI * RobotMap.ENC_WHEEL_RADIUS) / RobotMap.ENC_TICKS_PER_REV);
		
//		frontLeftEncoder.setMinRate(0.1); 
//		rearLeftEncoder.setMinRate(0.1); 
//		frontRightEncoder.setMinRate(0.1);
//		rearRightEncoder.setMinRate(0.1);
		
		frontLeftController = new PIDController(0.0, 0.0, 0.0, 0.0, frontLeftEncoder, m_frontLeftMotor);
		rearLeftController = new PIDController (0.0, 0.0, 0.0, 0.0, rearLeftEncoder, m_rearLeftMotor);
		frontRightController= new PIDController (0.0, 0.0, 0.0, 0.0, frontRightEncoder, m_frontRightMotor);
		rearRightController= new PIDController (0.0,0.0,0.0,0.0, rearRightEncoder, m_rearRightMotor);	
				
		frontLeftController.setContinuous(true);
		rearLeftController.setContinuous(true);
		frontRightController.setContinuous(true);
		rearRightController.setContinuous(true);
		
//		frontLeftController.setPercentTolerance(0.1);
//		rearLeftController.setPercentTolerance(0.1);
//		frontRightController.setPercentTolerance(0.1);
//		rearRightController.setPercentTolerance(0.1);
		
		frontLeftEncoder.setSamplesToAverage(100);
		rearLeftEncoder.setSamplesToAverage(100);
		frontRightEncoder.setSamplesToAverage(100);
		rearRightEncoder.setSamplesToAverage(100);
		
		frontLeftController.enable();
		rearLeftController.enable();
		frontRightController.enable();
		rearRightController.enable();
		
		frontLeftController.setOutputRange(-0.5, 0.5);
		rearLeftController.setOutputRange(-0.5, 0.5);
		frontRightController.setOutputRange(-0.5, 0.5);
		rearRightController.setOutputRange(-0.5, 0.5);		
	}
	
	public void setPIDRange(double minimum, double maximum) {
		frontLeftController.setOutputRange(minimum, maximum);
		rearLeftController.setOutputRange(minimum, maximum);
		frontRightController.setOutputRange(minimum, maximum);
		rearRightController.setOutputRange(minimum, maximum);
	}
	
	public void setPIDGains(double kPIn, double kIIn, double kDIn, double kFIn, boolean velocity){
		
		frontLeftController.disable();
		rearLeftController.disable();
		frontRightController.disable();
		rearRightController.disable();
		
		kP = kPIn;
		kI = kIIn;
		kD = kDIn;
		kF = kFIn;
		
		frontLeftController.setPID(kP, kI, kD, kF);
		rearLeftController.setPID(kP, kI, kD, kF);
		frontRightController.setPID(kP, kI, kD, kF);
		rearRightController.setPID(kP, kI, kD, kF);
		
		if(velocity){
			frontLeftEncoder.setPIDSourceParameter(PIDSourceParameter.kRate);
			rearLeftEncoder.setPIDSourceParameter(PIDSourceParameter.kRate);
			frontRightEncoder.setPIDSourceParameter(PIDSourceParameter.kRate);
			rearRightEncoder.setPIDSourceParameter(PIDSourceParameter.kRate);	
		}
		else {
			frontLeftEncoder.setPIDSourceParameter(PIDSourceParameter.kDistance);
			rearLeftEncoder.setPIDSourceParameter(PIDSourceParameter.kDistance);
			frontRightEncoder.setPIDSourceParameter(PIDSourceParameter.kDistance);
			rearRightEncoder.setPIDSourceParameter(PIDSourceParameter.kDistance);	
		}
		
		frontLeftController.enable();
		rearLeftController.enable();
		frontRightController.enable();
		rearRightController.enable();
	}
	
	public void mecanumDrive_CartesianPID(double x, double y, double rotation, double gyroAngle) {
		
//		frontLeftEncoder.reset();
//		rearLeftEncoder.reset();
//		frontRightEncoder.reset();
//		rearRightEncoder.reset();
	
		if(frontLeftEncoder == null ||  rearLeftEncoder == null || frontRightEncoder == null || rearRightEncoder == null) {
			mecanumDrive_Cartesian(x, y, rotation, gyroAngle);
		} else { 
			if(!kMecanumCartesian_Reported) {
				UsageReporting.report(tResourceType.kResourceType_RobotDrive, getNumMotors(), tInstances.kRobotDrive_MecanumCartesian);
				kMecanumCartesian_Reported = true;
			}
			double xIn = x;
			double yIn = y;
			
			// Negate y for the joystick.
			yIn = -yIn;
			
	    // Compenstate for gyro angle.
	        //double rotated[] = rotateVector(xIn, yIn, gyroAngle);
	        //xIn = rotated[0];
	        //yIn = rotated[1];
	
	        double wheelSpeeds[] = new double[kMaxNumberOfMotors];
	        wheelSpeeds[MotorType.kFrontLeft_val] = xIn + yIn + rotation;
	        wheelSpeeds[MotorType.kFrontRight_val] = -xIn + yIn - rotation;
	        wheelSpeeds[MotorType.kRearLeft_val] = -xIn + yIn + rotation;
	        wheelSpeeds[MotorType.kRearRight_val] = xIn + yIn - rotation;
	
	//        System.out.printf("%.2f, %.2f, %.2f, %.2f", wheelSpeeds[MotorType.kFrontLeft_val], wheelSpeeds[MotorType.kFrontRight_val], wheelSpeeds[MotorType.kRearLeft_val], wheelSpeeds[MotorType.kRearRight_val]);
	//        normalize(wheelSpeeds);
	//        m_frontLeftMotor.set(wheelSpeeds[MotorType.kFrontLeft_val] * m_invertedMotors[MotorType.kFrontLeft_val] * m_maxOutput, m_syncGroup);
	//        m_frontRightMotor.set(wheelSpeeds[MotorType.kFrontRight_val] * m_invertedMotors[MotorType.kFrontRight_val] * m_maxOutput, m_syncGroup);
	//        m_rearLeftMotor.set(wheelSpeeds[MotorType.kRearLeft_val] * m_invertedMotors[MotorType.kRearLeft_val] * m_maxOutput, m_syncGroup);
	//        m_rearRightMotor.set(wheelSpeeds[MotorType.kRearRight_val] * m_invertedMotors[MotorType.kRearRight_val] * m_maxOutput, m_syncGroup);
	
	        frontLeftController.setSetpoint(wheelSpeeds[MotorType.kFrontLeft_val] * m_invertedMotors[MotorType.kFrontLeft_val]);
	        rearLeftController.setSetpoint(wheelSpeeds[MotorType.kRearLeft_val] * m_invertedMotors[MotorType.kRearLeft_val]);
	        frontRightController.setSetpoint(wheelSpeeds[MotorType.kFrontRight_val] * m_invertedMotors[MotorType.kFrontRight_val]);
	        rearRightController.setSetpoint(wheelSpeeds[MotorType.kRearRight_val] * m_invertedMotors[MotorType.kRearRight_val]);
	         
	        if (m_syncGroup != 0) {
	            CANJaguar.updateSyncGroup(m_syncGroup);
	        }		
	        
	 //       System.out.printf("%.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f", frontLeftController.getSetpoint(), 
//	        frontLeftEncoder.getRate(), frontRightController.getSetpoint(), frontRightEncoder.getRate(),
//	        rearLeftController.getSetpoint(), rearLeftEncoder.getRate(), rearRightController.getSetpoint(),
//	        rearRightEncoder.getRate());
	 //      System.out.println();
		}
	}
	
	public void resetEncoders() {
		frontLeftEncoder.reset();
		rearLeftEncoder.reset();
		frontRightEncoder.reset();
		rearRightEncoder.reset();
	}
	
	public void driveDistanceY(double y) {
		y = y *RobotMap.MECANUM_FORWARD_RATIO / 2.5;
		
		frontLeftController.setSetpoint(y);
		frontRightController.setSetpoint(-1 * y);
		rearLeftController.setSetpoint(y);
		rearRightController.setSetpoint(-1 * y);	
		
//		double fLTarget = y;
//		double bLTarget = y;
//		double fRTarget = y * -1.0;
//		double bRTarget = y * -1.0;
//		
//		if(frontLeftEncoder.get() >= fLTarget && rearLeftEncoder.get() >= bLTarget 
//			&& frontRightEncoder.get() >= fRTarget && rearRightEncoder.get() >= bRTarget) {
//			frontLeftEncoder.reset();
//			rearLeftEncoder.reset();
//			frontRightEncoder.reset();
//			rearRightEncoder.reset();
//		}
	}
	public void driveDistanceX(double x) { // @TODO record what is positive, left or right
		x = x *RobotMap.MECANUM_SIDEWAYS_RATIO / 1.8;
				
		frontLeftController.setSetpoint(-1 * x);
		frontRightController.setSetpoint(-1 * x);
		rearLeftController.setSetpoint(x);
		rearRightController.setSetpoint(x);
		
//		double fLTarget = x * -1.0;
//		double bLTarget = x;
//		double fRTarget = x * -1.0;
//		double bRTarget = x;
//		
//		if(frontLeftEncoder.get() >= fLTarget && rearLeftEncoder.get() >= bLTarget 
//			&& frontRightEncoder.get() >= fRTarget && rearRightEncoder.get() >= bRTarget) {
//			frontLeftEncoder.reset();
//			rearLeftEncoder.reset();
//			frontRightEncoder.reset();
//			rearRightEncoder.reset();
//		}
	}
	
	//rotation is in degrees, counter-clockwise is positive
	public void driveDistanceRotation(double rotation_DG) { 
		double rotation_Rad = rotation_DG * Math.PI / 180;
		double rotation_Arc = (rotation_Rad * RobotMap.DIAGONAL_ROBOT_RADIUS / RobotMap.MECANUM_ROTATION_RATIO) / 2.25;
		
		frontLeftController.setSetpoint(-1 * rotation_Arc);
		frontRightController.setSetpoint(-1 * rotation_Arc);
		rearLeftController.setSetpoint(-1 * rotation_Arc);
		rearRightController.setSetpoint(-1 * rotation_Arc);		
		
//		double fLTarget = -1 * rotation_Arc;
//		double bLTarget = -1 * rotation_Arc;
//		double fRTarget = -1 * rotation_Arc;
//		double bRTarget = -1 * rotation_Arc;
//		
//		if(frontLeftEncoder.get() >= fLTarget && rearLeftEncoder.get() >= bLTarget 
//			&& frontRightEncoder.get() >= fRTarget && rearRightEncoder.get() >= bRTarget) {
//			frontLeftEncoder.reset();
//			rearLeftEncoder.reset();
//			frontRightEncoder.reset();
//			rearRightEncoder.reset();
//		}
	}
}

