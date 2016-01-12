package org.usfirst.frc.team131.robot;

import org.usfirst.frc.team131.robot.commands.ClawClose;
import org.usfirst.frc.team131.robot.commands.ClawOpen;
import org.usfirst.frc.team131.robot.commands.FineTuning;
import org.usfirst.frc.team131.robot.commands.LiftOne;
import org.usfirst.frc.team131.robot.commands.LiftOverride;
import org.usfirst.frc.team131.robot.commands.LowerAll;
import org.usfirst.frc.team131.robot.commands.ManualOverride;
import org.usfirst.frc.team131.robot.commands.Score;
import org.usfirst.frc.team131.robot.commands.TilterTiltDown;
import org.usfirst.frc.team131.robot.commands.TilterTiltUp;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.buttons.Button;
import edu.wpi.first.wpilibj.buttons.JoystickButton;

/**
 * This class is the glue that binds the controls on the physical operator
 * interface to the commands and command groups that allow control of the robot.
 */
public class OI {
	
	public final Joystick driver = new Joystick(0);
	public final Joystick operator = new Joystick(1);
	public final Joystick autoSelector = new Joystick(2);

	public OI (){
		
		
		
		if(RobotMap.TILTER){ //THIS WORKS TOO!!!
			Button tiltUp = new JoystickButton(operator, 2); //bottom button (A)
			tiltUp.whenPressed(new TilterTiltUp());
			
			Button tiltDownForWhat = new JoystickButton(operator, 4); //top button (Y)
			tiltDownForWhat.whenPressed(new TilterTiltDown());
		}
		
		if(RobotMap.CLAW){ //THIS WORKS!!!
			System.out.println("setting up robot claw");
			Button eternallyGrateful = new JoystickButton(operator, 5); // left bumper
			eternallyGrateful.whenPressed(new ClawOpen());
			
			Button firmlyGraspIt = new JoystickButton(operator, 7); // left trigger
			firmlyGraspIt.whenPressed(new ClawClose());		}
		
		// manual lifter is right y stick
		if(RobotMap.LINEAR_LIFT){
//			Button liftBro = new JoystickButton(operator, 6); // right bumper
//			liftBro.whenPressed(new LiftOne());			//We need Sensors!
//			
//			Button putThemDown = new JoystickButton(operator, 8); // right trigger
//			putThemDown.whenPressed(new LowerAll());			//We need Sensors!
			
			Button manualOperatorOverride = new JoystickButton(operator, 1); // left button (X)
			manualOperatorOverride.whenPressed(new LiftOverride());
		}
	
		if(RobotMap.DRIVE){			
			Button runForrestRun = new JoystickButton(driver, 3); //right button (B)
			runForrestRun.whenPressed(new ManualOverride());
			
			Button fineTuning = new JoystickButton(driver,6); // left button (X)
			fineTuning.whenPressed(new FineTuning());
		}
		
//		if(RobotMap.LINEAR_LIFT && RobotMap.CLAW && RobotMap.TILTER){
//			Button stacksOnStacks = new JoystickButton(driver, 2);
//			if(Robot.smartLifter) {
//				stacksOnStacks.whenPressed(new Score()); //bottom button (A)
//			}
//		}
	}
	
	
    //// CREATING BUTTONS
    // One type of button is a joystick button which is any button on a joystick.
    // You create one by telling it which joystick it's on and which button
    // number it is.
    // Joystick stick = new Joystick(port);
    // Button button = new JoystickButton(stick, buttonNumber);
    
    // There are a few additional built in buttons you can use. Additionally,
    // by subclassing Button you can create custom triggers and bind those to
    // commands the same as any other Button.
    
    //// TRIGGERING COMMANDS WITH BUTTONS
    // Once you have a button, it's trivial to bind it to a button in one of
    // three ways:
    
    // Start the command when the button is pressed and let it run the command
    // until it is finished as determined by it's isFinished method.
    // button.whenPressed(new ExampleCommand());
    
    // Run the command while the button is being held down and interrupt it once
    // the button is released.
    // button.whileHeld(new ExampleCommand());
    
    // Start the command when the button is released  and let it run the command
    // until it is finished as determined by it's isFinished method.
    // button.whenReleased(new ExampleCommand());
}

