/*-------------------------------------------------------------**
**                                                             
**   Filename: Manipulator.cpp                                        
**                                                             
**   About:    Controlls all the sub-parts of the manipulator 
**                                                             
**   Property of Chaos, Copyright 2011
**   Written by: Steven Kroh           
**                                                                                           
**   2011 1 30           
**                                                             
**-------------------------------------------------------------*/

#include "Manipulator.h"


Manipulator::Manipulator(Gamepad *DriverGamepad, Gamepad *OperatorGamepad, DashSharing *DashData)
{
	this->DriverGamepad = DriverGamepad;
	this->OperatorGamepad = OperatorGamepad;
	this->DashData = DashData;
	
	ChainsawPart = new Chainsaw();
	ElbowPart = new Elbow();
	ShoulderPart = new Shoulder();
	
	//No Escape Button Needed with new Driver and Operator Mappings
	//EscapeButton = new MultiButton(this->DashData);
	
	NextState = MANIP_STATE_INIT;
	CurrentState = MANIP_STATE_INIT;
	RestoreState = MANIP_STATE_INIT;
	
	ScoreTimeout = new Timer();
	ScoreTimeout->Reset();
	
}

void Manipulator::StateMachine(void)
{
	
	DashData->ElbowPot_D = ElbowPart->ElbowPot->GetAngleDegrees();
	DashData->ElbowProportionalConstant_D = ElbowPart->ElbowProportionalConstant;
	DashData->ElbowIntegralConstant_D = ElbowPart->ElbowIntegralConstant;
	DashData->ElbowDerivativeConstant_D = ElbowPart->ElbowDerivativeConstant;
	DashData->ElbowPidGet_D = ElbowPart->AngleCorrection->Get(); //ElbowPart->AngleCorrection->GetError();
	DashData->ElbowPidSetpoint_D = ElbowPart->AngleCorrection->GetSetpoint();
	DashData->ElbowPreviousAngle_D = ElbowPart->PreviousAngle;
	
	DashData->ElbowStates_D = ((int )ElbowPart->CurrentState);
	
	DashData->ManipStates_D = ((int )CurrentState);
	
	DashData->ShoulderStates_D = ((int )ShoulderPart->CurrentState);
	
	DashData->ShoulderAngle_D = ShoulderPart->ShoulderPot->GetAngleDegrees();
	
	
	if(OperatorGamepad->GetNumberedButton(BTN_STOW))
	{
		ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_DISABLE);
		NextState = MANIP_STATE_PRE_STOW;
	}
	
	switch(NextState)
	{
	    case MANIP_STATE_INIT:
	    	
	    	ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_DISABLE);
			ElbowPart->Signal(Elbow::ELBOW_STATE_DISABLE);
			ShoulderPart->Signal(Shoulder::SHOULDER_STATE_DISABLE);
			
			NextState = MANIP_STATE_DISABLED;
			
			break;
	    	
		case MANIP_STATE_DISABLED:
			
			if(NextState != CurrentState)
			{
				ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_DISABLE);
				ElbowPart->Signal(Elbow::ELBOW_STATE_DISABLE);
				ShoulderPart->Signal(Shoulder::SHOULDER_STATE_DISABLE);
			}
			CurrentState = MANIP_STATE_DISABLED;
			
			if(OperatorGamepad->GetNumberedButton(BTN_GO_TO_PEG_HEIGHT))
			{
				NextState = MANIP_STATE_GO_TO_PEG_HEIGHT;
			}
			
			break;
			
		case MANIP_STATE_STOW:
			
			if(NextState != CurrentState)
			{
				ShoulderPart->Signal(Shoulder::SHOULDER_STATE_DOWN);
				ElbowPart->SetGoalAngle(Elbow::STATE_DOWN_STOW);
				ElbowPart->Signal(Elbow::ELBOW_STATE_CORRECT_ANGLE);
				ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_DISABLE);
			}
			CurrentState = MANIP_STATE_STOW;
			
//   		if(OperatorGamepad->GetNumberedButton(BTN_GROUND_ACQUIRE_INIT))
//			{
//					NextState = MANIP_STATE_GROUND_ACQUIRE_INIT;	
//			}
			
			if(OperatorGamepad->GetNumberedButton(BTN_GO_TO_PEG_HEIGHT))
			{
				NextState = MANIP_STATE_GO_TO_PEG_HEIGHT;
			}
			
			if(OperatorGamepad->GetDPad() == Gamepad::kRight)
			{
				NextState = MANIP_STATE_HP_PICKUP;
			}
			
            break;
            
		case MANIP_STATE_GROUND_ACQUIRE_INIT:
			
			if(NextState != CurrentState)
			{
				ShoulderPart->Signal(Shoulder::SHOULDER_STATE_DOWN);
				ElbowPart->SetGoalAngle(Elbow::STATE_DOWN_PICKUP);
				ElbowPart->Signal(Elbow::ELBOW_STATE_CORRECT_ANGLE);
				ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_DISABLE);
			}
			
			CurrentState = MANIP_STATE_GROUND_ACQUIRE_INIT;
			
			if(ElbowPart->Check() == Elbow::ELBOW_STATE_HOLD_MOTOR && ShoulderPart->Check() == Shoulder::SHOULDER_STATE_HOLD)
			{
				if(OperatorGamepad->GetNumberedButton(BTN_GROUND_ACQUIRE))
				{
					NextState = MANIP_STATE_GROUND_ACQUIRE;
				}
			}
			
			break;
			
		case MANIP_STATE_GROUND_ACQUIRE:
			
			if(NextState != CurrentState)
			{
				ShoulderPart->Signal(Shoulder::SHOULDER_STATE_DOWN);
				ElbowPart->SetGoalAngle(Elbow::STATE_DOWN_PICKUP);
				ElbowPart->Signal(Elbow::ELBOW_STATE_CORRECT_ANGLE);
				ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_AUTO_ACQUIRE);
			}
			
			CurrentState = MANIP_STATE_GROUND_ACQUIRE;
			
			if(ChainsawPart->Check() == Chainsaw::CHAINSAW_STATE_IN_POSSESSION)
			{
				NextState = MANIP_STATE_PRE_STOW;
			}
			
			break;
			
		case MANIP_STATE_PRE_STOW:
			
			if(CurrentState != NextState)
			{
				ElbowPart->SetGoalAngle(Elbow::STATE_DOWN_STOW);
				ElbowPart->Signal(Elbow::ELBOW_STATE_CORRECT_ANGLE);
				ShoulderPart->Signal(Shoulder::SHOULDER_STATE_DOWN);
				
//				ChainsawRequest.Request_Manual = false;
//				ChainsawPart->Interface(Chainsaw::ChainsawRequest);
				ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_AUTO_ACQUIRE);
			}
			
			CurrentState = MANIP_STATE_PRE_STOW;
			
			if(ElbowPart->Check() == Elbow::ELBOW_STATE_HOLD_MOTOR)
			{
				NextState = MANIP_STATE_STOW;
			}
			else
			{
				NextState = MANIP_STATE_PRE_STOW;
			}
			
			break;
			
		case MANIP_STATE_GO_TO_PEG_HEIGHT:
			
			if(NextPegZ != CurrentPegZ)
			{
				ChangePegZ(NextPegZ);
//				ChainsawRequest.Request_Manual = false;
//				ChainsawPart->Interface(ChainsawRequest);
			}
			
			ElbowPart->GoalAngle = ((ShoulderPart->ShoulderPot->GetAngleDegrees()) + ELBOW_SERVO_OFFSET);
			
			if(ShoulderPart->Check() == Shoulder::SHOULDER_STATE_HOLD)
			{
			    NextState = MANIP_STATE_MAINTAIN_PEG_HEIGHT;	
			}
			
			CurrentState = MANIP_STATE_GO_TO_PEG_HEIGHT;
			
			if((OperatorGamepad->GetRightY() >= OPERATOR_SCORE_JOYSTICK_THRESHOLD) || (OperatorGamepad->GetRightY() <= -OPERATOR_SCORE_JOYSTICK_THRESHOLD))
			{
			    NextState = MANIP_STATE_SCORE;	
			}
		    
			//ELBOW SONG
			
			break;
			
		case MANIP_STATE_MAINTAIN_PEG_HEIGHT:
			
			if(NextPegZ != CurrentPegZ)
			{
				NextState = MANIP_STATE_GO_TO_PEG_HEIGHT;
//				ChainsawRequest.Request_Manual = false;
//				ChainsawPart->Interface(ChainsawRequest);
		    }
			
			CurrentState = MANIP_STATE_MAINTAIN_PEG_HEIGHT;
			
			ChangePegZ(NextPegZ);
			
			if((OperatorGamepad->GetRightY() >= OPERATOR_SCORE_JOYSTICK_THRESHOLD) || (OperatorGamepad->GetRightY() <= -OPERATOR_SCORE_JOYSTICK_THRESHOLD))
			{
				NextState = MANIP_STATE_SCORE;	
			}
			
			break;
			
		case MANIP_STATE_SCORE:
			
			if(NextState != CurrentState)
			{
				//ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_AUTO_DROP);
				//ScoreTimeout->Start();
//				ChainsawRequest.Request_Manual = true;
//				ChainsawRequest.Request_ChainsawMotorValue = OperatorGamepad->GetRightY();
//				ChainsawPart->Interface(ChainsawRequest);
				ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_MANUAL);
			}
			
			CurrentState = MANIP_STATE_SCORE;
			
			ChainsawPart->ChainsawMotor->Set(-OperatorGamepad->GetRightY());
			
			if(OperatorGamepad->GetNumberedButton(BTN_GO_TO_PEG_HEIGHT))
			{
				NextState = MANIP_STATE_GO_TO_PEG_HEIGHT;
			}
			
//			if(ScoreTimeout->Get() >= SCORE_TIMEOUT)
//			{
//				ScoreTimeout->Stop();
//				ScoreTimeout->Reset();
//				NextState = MANIP_STATE_PAUSE_FOR_BACKUP;
//			}
			
			break;
			
		case MANIP_STATE_AUTO_PRE_SCORE:
			
			if(NextState != CurrentState)
			{
				ScoreTimeout->Reset();
				ScoreTimeout->Start();
				ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_DISABLE);
			}
			
			CurrentState = MANIP_STATE_AUTO_PRE_SCORE;
			
			if(ScoreTimeout->Get() >= AUTO_PRE_SCORE_TIMEOUT)
			{
				NextState = MANIP_STATE_AUTO_SCORE;
			}
			
			break;
			
		case MANIP_STATE_AUTO_SCORE:
					
			if(NextState != CurrentState)
			{
				ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_AUTO_DROP);
				ScoreTimeout->Start();
			}
			
			CurrentState = MANIP_STATE_SCORE;
			
			if(ScoreTimeout->Get() >= SCORE_TIMEOUT)
			{
				ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_DISABLE);
				ScoreTimeout->Stop();
				ScoreTimeout->Reset();
				NextState = MANIP_STATE_PAUSE_FOR_BACKUP;
			}
			
			break;
			
		case MANIP_STATE_PAUSE_FOR_BACKUP:
			
			if(CurrentState != NextState)
			{
				ScoreTimeout->Reset();
				ScoreTimeout->Start();
			}
			
			CurrentState = MANIP_STATE_PAUSE_FOR_BACKUP;
			
			if(ScoreTimeout->Get() >= MANIP_BACKUP_TIME_BEFORE_STOW)
			{
				ScoreTimeout->Stop();
				ScoreTimeout->Reset();
				NextState = MANIP_STATE_PRE_STOW;
			}
			
	     	break;
			
		case MANIP_STATE_HP_PICKUP:
			
			if(CurrentState != NextState)
			{
				ShoulderPart->Signal(Shoulder::SHOULDER_STATE_DOWN);
				ElbowPart->SetGoalAngle(Elbow::STATE_DOWN_PICKUP_HP);
				ElbowPart->Signal(Elbow::ELBOW_STATE_CORRECT_ANGLE);
			}
			
			CurrentState = MANIP_STATE_HP_PICKUP;
			
			if(OperatorGamepad->GetNumberedButton(BTN_STOW))
			{
				NextState = MANIP_STATE_PRE_STOW;
			}
			
		    break;
		
		case MANIP_STATE_MANUAL:
			
			if(CurrentState != NextState)
			{
				RestoreState = CurrentState;
				ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_MANUAL);
			}
			CurrentState = MANIP_STATE_MANUAL;
			
			//Map the Operator Left Joystick's Y axis to the Elbow Victor
			printf("Elbow angle value %f\n", ElbowPart->ElbowPot->GetAngleDegrees());
		
			//TODO: Find bug and eliminate this redundant "if" statement below
			
			ElbowPart->ManualSetMotor(OperatorGamepad->GetLeftY());
			
			
			/*if((ElbowPart->ElbowPot->GetAngleDegrees() < ELBOW_MAXIMUM_ANGLE) && (ElbowPart->ElbowPot->GetAngleDegrees() > ELBOW_MINIMUM_ANGLE))
			{
				ElbowPart->ElbowVictor->Set(OperatorGamepad->GetLeftY());
			}
			else if(ElbowPart->ElbowPot->GetAngleDegrees() >= ELBOW_MAXIMUM_ANGLE)
			{
				if(OperatorGamepad->GetLeftY() < 0)
				{
					ElbowPart->ManualSetMotor(OperatorGamepad->GetLeftY());
				}
				else 
				{
					ElbowPart->ManualSetMotor(0.0);
				}
			}
			else if(ElbowPart->ElbowPot->GetAngleDegrees() <= ELBOW_MINIMUM_ANGLE)
			{
				if(OperatorGamepad->GetLeftY() > 0)
				{
					ElbowPart->ElbowVictor->Set(OperatorGamepad->GetLeftY());
				}
				else 
				{
					ElbowPart->ElbowVictor->Set(0.0);
				}
			}
			else
			{
				ElbowPart->ElbowVictor->Set(0.0);
			}
		*/
			
			//Map operator buttons to manual control of the shoulder
			if(OperatorGamepad->GetNumberedButton(BTN_MANUAL_SHOULDER_UP))
			{
				ShoulderPart->Signal(Shoulder::SHOULDER_STATE_UP);
			}
			else if(OperatorGamepad->GetNumberedButton(BTN_MANUAL_SHOULDER_DOWN))
			{
				ShoulderPart->Signal(Shoulder::SHOULDER_STATE_DOWN);
			}
			
			//Map operator buttons to manual control of the chainsaw
//			if(OperatorGamepad->GetNumberedButton(BTN_MANUAL_ACQUIRE))
//			{
//				ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_MANUAL_ACQUIRE);
//			}
//			else if(OperatorGamepad->GetNumberedButton(BTN_MANUAL_DROP))
//			{
//				ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_MANUAL_DROP);
//			}
//			else
//			{
//				ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_DISABLE);
//			}
			
			ChainsawPart->ChainsawMotor->Set(-OperatorGamepad->GetRightY());
			
			
			NextState = MANIP_STATE_MANUAL;
			
			
			
			break;
			
		default:
			NextState = MANIP_STATE_DISABLED;
			break;
            
    
	} // End Switch Statement
	
	ChainsawPart->StateMachine();
	ElbowPart->StateMachine();
	ShoulderPart->StateMachine();
}

void Manipulator::ChangePegZ(Manipulator::PEG_Z_STATES NextPegZ)
{
	switch(NextPegZ)
	{
		case PEG_Z_STATE_BOTTOM_NORM:
			ShoulderPart->Signal(Shoulder::SHOULDER_STATE_DOWN);
			ElbowPart->SetGoalAngle(Elbow::STATE_DOWN_SIDE_BOTTOM);
			ElbowPart->Signal(Elbow::ELBOW_STATE_CORRECT_ANGLE);
			ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_DISABLE);
			//ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_AUTO_ACQUIRE);
			CurrentPegZ = PEG_Z_STATE_BOTTOM_NORM;
			break;
			
		case PEG_Z_STATE_MIDDLE_NORM:
			ShoulderPart->Signal(Shoulder::SHOULDER_STATE_UP);
			ElbowPart->SetGoalAngle(Elbow::STATE_UP_SIDE_MIDDLE);
			ElbowPart->Signal(Elbow::ELBOW_STATE_CORRECT_ANGLE);
			ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_AUTO_ACQUIRE);
			CurrentPegZ = PEG_Z_STATE_MIDDLE_NORM;
			break;
			
		case PEG_Z_STATE_TOP_NORM:
			ShoulderPart->Signal(Shoulder::SHOULDER_STATE_UP);
			ElbowPart->SetGoalAngle(Elbow::STATE_UP_SIDE_TOP);
			ElbowPart->Signal(Elbow::ELBOW_STATE_CORRECT_ANGLE);	
			//ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_AUTO_ACQUIRE);
			ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_DISABLE);
			CurrentPegZ = PEG_Z_STATE_TOP_NORM;
			break;
			
		case PEG_Z_STATE_BOTTOM_CENT:
			ShoulderPart->Signal(Shoulder::SHOULDER_STATE_DOWN);
			ElbowPart->SetGoalAngle(Elbow::STATE_DOWN_CENTER_BOTTOM);
			ElbowPart->Signal(Elbow::ELBOW_STATE_CORRECT_ANGLE);	
			//ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_AUTO_ACQUIRE);
			ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_DISABLE);
			CurrentPegZ = PEG_Z_STATE_BOTTOM_CENT;
			break;
		
		case PEG_Z_STATE_MIDDLE_CENT:
			ShoulderPart->Signal(Shoulder::SHOULDER_STATE_UP);
			ElbowPart->SetGoalAngle(Elbow::STATE_UP_CENTER_MIDDLE);
			ElbowPart->Signal(Elbow::ELBOW_STATE_CORRECT_ANGLE);	
			ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_AUTO_ACQUIRE);
			CurrentPegZ = PEG_Z_STATE_MIDDLE_CENT;
			break;
			
		case PEG_Z_STATE_TOP_CENT:
			ShoulderPart->Signal(Shoulder::SHOULDER_STATE_UP);
			ElbowPart->SetGoalAngle(Elbow::STATE_UP_CENTER_TOP);
			ElbowPart->Signal(Elbow::ELBOW_STATE_CORRECT_ANGLE);
			//ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_AUTO_ACQUIRE);
			ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_DISABLE);
			CurrentPegZ = PEG_Z_STATE_TOP_CENT;
			break;
			
		case PEG_Z_STATE_PICKUP_FLOOR:
			ShoulderPart->Signal(Shoulder::SHOULDER_STATE_DOWN);
			ElbowPart->SetGoalAngle(Elbow::STATE_DOWN_PICKUP);
			ElbowPart->Signal(Elbow::ELBOW_STATE_CORRECT_ANGLE);	
			CurrentPegZ = PEG_Z_STATE_PICKUP_FLOOR;
			break;
			
		case PEG_Z_STATE_PICKUP_HP:
			ShoulderPart->Signal(Shoulder::SHOULDER_STATE_DOWN);
			ElbowPart->SetGoalAngle(Elbow::STATE_DOWN_PICKUP_HP);
			ElbowPart->Signal(Elbow::ELBOW_STATE_CORRECT_ANGLE);
			ChainsawPart->Signal(Chainsaw::CHAINSAW_STATE_AUTO_ACQUIRE);
			CurrentPegZ = PEG_Z_STATE_PICKUP_HP;
			break;
	} //End Switch
	
} //End ChangePegZ

Manipulator::MANIP_STATES_T Manipulator::GetRestoreState(void)
{
	return RestoreState;
}

void Manipulator::Signal(Manipulator::MANIP_STATES_T NextState)
{
	this->NextState = NextState;
}

Manipulator::MANIP_STATES_T Manipulator::Check(void)
{
	return this->CurrentState;
}

