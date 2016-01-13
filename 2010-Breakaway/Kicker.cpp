#include "Kicker.h"


//A File Scope Function
static void AccessKickerStateMachine(Kicker *k)
{
	k->KickerStateMachine();
} //end of kickerstatemachine

Kicker::Kicker(Gamepad *DriverPass, Gamepad *OperatorPass, DashSharing *DashData, AutonomousKickerInterface *AutoInterface) 
	  : KickerTask("Kicker", (FUNCPTR) AccessKickerStateMachine)
{
	printf("KICKER CONSTRUCT\n");
	
	this->AutoInterface = AutoInterface;
	this->ExtendActionManual = true;
	
	RetractDistance = 1.0;
	ExtendDistance = 15.0 ;
	SitForShootDistance = 9.0;
	
	ExtenderA = new Solenoid(SOLENOID_MODULE1, EXTENDER_A_CHANNEL);
	RetractorA = new Solenoid(SOLENOID_MODULE1, RETRACTOR_A_CHANNEL);
	RetractorB = new Solenoid(SOLENOID_MODULE1, RETRACTOR_B_CHANNEL);
	LatchA = new Solenoid(SOLENOID_MODULE1, LATCH_A_CHANNEL);
	LatchB = new Solenoid(SOLENOID_MODULE1, LATCH_B_CHANNEL);
	VentA = new Solenoid(SOLENOID_MODULE1, VENT_A_CHANNEL);
	VentB = new Solenoid(SOLENOID_MODULE1, VENT_B_CHANNEL);

	LinearPot = new ChaosLinearPot(ANALOG_MODULE1, LINEAR_POT_CHANNEL);
	
	Driver = DriverPass;
	Operator = OperatorPass;
	this->DashData = DashData;
	
	SavedManualExtendDistance = 0.0;
	SaveExtendDistance = true;
	ReadExtendDistance = false;
	
	WheelStowDistanceGoal = WHEEL_STOW_DISTANCE_GOAL;
	
	DistanceOffset = 0.0;
	zone = ZONE__MID;
	lastZone = ZONE__MID;
	
	InitKicker();
	

} // end of constructure

Kicker::~Kicker()
{
	delete ExtenderA;
	delete ExtenderB;
	delete RetractorA;
	delete RetractorB;
	delete LatchA;
	delete LatchB;
	delete VentA;
	delete VentB;
	delete LinearPot;
		
} // end of destructure

void Kicker::SetValveStates(VALVE_CMD valve_cmd)
{
	switch(valve_cmd)
	{
		case VALVE_CMD__TENSIONER_EXTEND:  //on, off, off, off
			ExtenderA->Set(true);
			RetractorA->Set(false);
			VentA->Set(false);
			VentB->Set(true);
			LatchA->Set(false);
			break;
			
		case VALVE_CMD__TENSIONER_EXTEND_ON: //on, off, off, off
			ExtenderA->Set(true);
			RetractorA->Set(false);
			VentA->Set(false);
			VentB->Set(true);
			LatchA->Set(false);
			break;
			
		case VALVE_CMD__TENSIONER_EXTEND_PAUSE: // off, off, off, off
			ExtenderA->Set(false);
			RetractorA->Set(false);
			VentA->Set(false);
			VentB->Set(true);
			LatchA->Set(false);
			break;
			
		case VALVE_CMD__TENSIONER_CLEAR_ALL_VALVES: //off, off, off, off
			ClearValveStates();
			break;
		
		case VALVE_CMD__TENSIONER_RETRACT_TO_LOAD: //off, on, off, off
		    ExtenderA->Set(false);
			RetractorA->Set(true);
			VentA->Set(false);
			VentB->Set(true);
			LatchA->Set(false);
			break;
		
		case VALVE_CMD__LATCH_SHOOT: //off, off, off, on
			ExtenderA->Set(false);
			RetractorA->Set(false);
			VentA->Set(false);
			VentB->Set(true);
			LatchA->Set(true);
			break;
			
		case VALVE_CMD__RELEASE_LATCH_AND_HOLD_RETRACT:
			ExtenderA->Set(false);
			RetractorA->Set(true);
			VentA->Set(true);
			VentB->Set(false);
			LatchA->Set(true);
		    break;
		    
		case VALVE_CMD__RETRACT_PLUGGED: //off, on, on, off
			ExtenderA->Set(false);
			RetractorA->Set(true);
			VentA->Set(true);
			VentB->Set(false);
			LatchA->Set(false);
		    break;
		    
		case VALVE_CMD__RETRACT_HOLD_PLUGGED: //off, off, on, off
			ExtenderA->Set(false);
			RetractorA->Set(false);
			VentA->Set(true);
			VentB->Set(false);
			LatchA->Set(false);
		    break;
		
		default:
			break;
			
	} //End of switch
	if(!SINGLE_COIL_VALVE)
	{
		Wait(SET_VALVE_TRUE_DELAY);
		ClearValveStates();
		Wait(SET_VALVE_FALSE_DELAY);
	}
} //End of SetValveStates

void Kicker::ClearValveStates(void)
{
	ExtenderA->Set(false);
	RetractorA->Set(false);
	VentA->Set(false);
	LatchA->Set(false);
	
	if(!SINGLE_COIL_VALVE) ExtenderB->Set(false);
	if(!SINGLE_COIL_VALVE) RetractorB->Set(false);
	if(!SINGLE_COIL_VALVE) VentB->Set(false);
	if(!SINGLE_COIL_VALVE) LatchB->Set(false);
} //End of clearvalvestates

void Kicker::InitKicker(void)
{
	printf("KICKER INIT\n");
	m_EnableProcess = false;
} // end if InitKicker
		
void Kicker::Start(void)
{
	printf("KICKER START\n");
	if (!KickerTask.Start((INT32)this))
		{
		   printf("KICKER TASK NOT STARTED");
		   //wpi_fatal(DriverStationTaskError);
		}
	else
	{
		m_Enabled = true;
		m_EnableProcess = true;
		printf("KICKER TASK STARTED, END OF ELSE");
	}
} // end if Start

void Kicker::Stop(void)
{
	KickerTask.Stop();
	m_Enabled = false;
	
} // end of Stop

bool Kicker::Enabled(void)
{
	return m_Enabled;
	
} // end of Enabled

void Kicker::KickerStateMachine(void)
{
	float Distance = 100;

	bool ManualMode = false;
	bool ManualModeInDriversUse = false;
	bool ArrivedVia_KickerWheelStow_Button = false;
	
	Gamepad::DPadDirection ZoneControl_CurrentState = Gamepad::kCenter;
	Gamepad::DPadDirection ZoneControl_LastState = Gamepad::kCenter;
	
	bool CurrentIncrimentButton = false;
	bool PreviousIncrimentButton = false;
	bool CurrentDecrimentButton = false;
	bool PreviousDecrimentButton = false;
	
	
	
	do  // must stay in the loop otherwise the task needs to be restarted 
	{
		Distance = LinearPot->GetDistance();
		
		if(m_Enabled) // Lets Statemachine run
		{
			
			if(ExtendActionManual == true)
			{
				ZoneControl_CurrentState = Operator->GetDPad();
				
				switch(ZoneControl_CurrentState)
				{
					
					case Gamepad::kUp:
						if(ZoneControl_LastState != Gamepad::kUp)
						{
							zone = ZONE__FAR;
						}
						ZoneControl_LastState = Gamepad::kUp;
						break;
					
					case Gamepad::kRight:
						if(ZoneControl_LastState != Gamepad::kRight)
						{
							zone = ZONE__MID;
						}
						ZoneControl_LastState = Gamepad::kRight;
						break;
						
					case Gamepad::kDown:
						if(ZoneControl_LastState != Gamepad::kDown)
						{
							zone = ZONE__NEAR;
						}
						ZoneControl_LastState = Gamepad::kDown;
						break;	
						
					default:
						ZoneControl_LastState = Gamepad::kCenter;
						break;
				}//EndSwitch
				
				switch(zone)
				{
					case ZONE__FAR:
						if(lastZone != ZONE__FAR)
						{
							ExtendDistance = FAR_DISTANCE;
						}
						lastZone = ZONE__FAR;
						break;
						
					case ZONE__MID:
						if(lastZone != ZONE__MID)
						{
							ExtendDistance = MID_DISTANCE;
						}
						lastZone = ZONE__MID;
						break;
						
					case ZONE__NEAR:
						if(lastZone != ZONE__NEAR)
						{
							ExtendDistance = NEAR_DISTANCE;
						}
						lastZone = ZONE__NEAR;
						break;
						
					default:
						lastZone = ZONE__MID;
						break;
				}
				
				CurrentIncrimentButton = Operator->GetNumberedButton(OFFSET_UP);
				CurrentDecrimentButton = Operator->GetNumberedButton(OFFSET_DOWN);
				
				if(!CurrentIncrimentButton && !CurrentDecrimentButton)
				{
					PreviousIncrimentButton = false;
					PreviousDecrimentButton = false;
				}
				else if(CurrentIncrimentButton && !PreviousIncrimentButton)
				{
					ExtendDistance += DISTANCE_OFFSET_INCREMENT;
					PreviousIncrimentButton = true;
					PreviousDecrimentButton = false;
				}
				else if(CurrentDecrimentButton && !PreviousDecrimentButton)
				{
					ExtendDistance -= DISTANCE_OFFSET_DECRIMENT;
					PreviousDecrimentButton = true;
					PreviousIncrimentButton = false;
				}
				
				//Limiters
				if(ExtendDistance > EXTEND_DISTANCE_MAX) ExtendDistance = EXTEND_DISTANCE_MAX;
				if(ExtendDistance < EXTEND_DISTANCE_MIN) ExtendDistance = EXTEND_DISTANCE_MIN;
				
			}//End Set ExtendDistance
		
			
			//Begin Global State Machine Entrances
			
			if(Operator->GetNumberedButton(KICKER_STOW) || AutoInterface->AutoKickerStow == true)
			{
				NextState = KICK_STATE__RETRACT_TO_STOW;
				ArrivedVia_KickerWheelStow_Button = false;
			}
			
			//Manual Section
			ManualModeInDriversUse = false;
			
			if(Operator->GetNumberedButton(KICKER_MANUAL_RETRACT))
			{
				ManualMode = true;
				ManualModeInDriversUse = true;
				NextState = KICK_STATE__MANUAL_RETRACT;
			}
			
			if(Operator->GetNumberedButton(KICKER_MANUAL_EXTEND))
			{
				ManualMode = true;
				ManualModeInDriversUse = true;
				NextState = KICK_STATE__MANUAL_EXTEND;
			}
			
			if(Operator->GetNumberedButton(KICKER_MANUAL_LATCH))
			{
				ManualMode = true;
				ManualModeInDriversUse = true;
				NextState = KICK_STATE__MANUAL_LATCH;
			}
			
			if(ManualMode && !ManualModeInDriversUse)
			{
				ManualMode = true;
				NextState = KICK_STATE__MANUAL_WAIT;
			}
			
			//Stow behind Wheel
			if(Operator->GetNumberedButton(KICKER_WHEEL_STOW))
			{
				NextState = KICK_STATE__RETRACT_TO_STOW;
				ArrivedVia_KickerWheelStow_Button = true;
			}
			
			switch(NextState)
			{
				case KICK_STATE__RETRACT:
					
					AutoInterface->AutoKickerShoot = false;
					
					if(CurrentState != KICK_STATE__RETRACT)
					{
						SetValveStates(VALVE_CMD__TENSIONER_RETRACT_TO_LOAD);
					}
					
					CurrentState = KICK_STATE__RETRACT;
					printf("Kick State Retract PRIMARY RETRACT Distance\n");
					Distance = LinearPot->GetDistance();
					if(Distance < RetractDistance)
					{
						NextState = KICK_STATE__EXTEND_ON;
						ClearValveStates();
					} 
					break;
					
				case KICK_STATE__EXTEND_ON:
					if(CurrentState != KICK_STATE__EXTEND_ON)
					{
						SetValveStates(VALVE_CMD__TENSIONER_EXTEND_ON);
					}
					
					CurrentState = KICK_STATE__EXTEND_ON;
					printf("Kick State Extend ON, Distance: %f\n", ExtendDistance);
					Distance = LinearPot->GetDistance();
					if(Distance > (ExtendDistance - LOWER_HYSTERETIC_BAND))
					{
						NextState = KICK_STATE__SIT_FOR_SHOOT;
					}
					else if(Distance > (ExtendDistance - FULL_ON_DISTANCE))
					{
						NextState = KICK_STATE__EXTEND_PAUSE;
					}
					break;
					
				case KICK_STATE__EXTEND_PAUSE:
					if(CurrentState != KICK_STATE__EXTEND_PAUSE)
					{
						SetValveStates(VALVE_CMD__TENSIONER_EXTEND_PAUSE);
					}
					
					CurrentState = KICK_STATE__EXTEND_PAUSE;
					printf("Kick State Extend PAUSE, Distance: %f\n", ExtendDistance);
					Distance = LinearPot->GetDistance();
					if(Distance > ExtendDistance)
					{
						NextState = KICK_STATE__SIT_FOR_SHOOT;
					}
					else
					{
						NextState = KICK_STATE__EXTEND_ON;
					}
					break;
					
				case KICK_STATE__RETRACT_ON:
					if(CurrentState != KICK_STATE__RETRACT_ON)
					{
						SetValveStates(VALVE_CMD__TENSIONER_RETRACT_TO_LOAD);
					}
					
					CurrentState = KICK_STATE__RETRACT_ON;
					printf("Kick State Retract ON, Distance: %f\n", ExtendDistance);
					Distance = LinearPot->GetDistance();
					if(Distance < ExtendDistance)
					{
						NextState = KICK_STATE__SIT_FOR_SHOOT;
					}
					else
					{
						NextState = KICK_STATE__RETRACT_PAUSE;
					}
					break;
					
				case KICK_STATE__RETRACT_PAUSE:
					if(CurrentState != KICK_STATE__RETRACT_PAUSE)
					{
						SetValveStates(VALVE_CMD__TENSIONER_CLEAR_ALL_VALVES);
					}
					CurrentState = KICK_STATE__RETRACT_PAUSE;
					printf("Kick State Retract PAUSE, Distance: %f\n", ExtendDistance);
					Distance = LinearPot->GetDistance();
					if(Distance < ExtendDistance)
					{
						NextState = KICK_STATE__SIT_FOR_SHOOT;
					}
					else
					{
						NextState = KICK_STATE__RETRACT_ON;
					}
					break;
					
				case KICK_STATE__SIT_FOR_SHOOT:
					if(CurrentState != KICK_STATE__SIT_FOR_SHOOT)
					{
						SetValveStates(VALVE_CMD__TENSIONER_CLEAR_ALL_VALVES);
					}
					
					CurrentState = KICK_STATE__SIT_FOR_SHOOT;
					printf("Kick State Sit for shoot\n");
					
					Distance = LinearPot->GetDistance();
					
					if(Operator->GetNumberedButton(KICKER_SHOOT) || AutoInterface->AutoKickerShoot == true)
					{
						NextState = KICK_STATE__SHOOT;
					}
					else if(Distance > (ExtendDistance + UPPER_HYSTERETIC_BAND))
					{
						NextState = KICK_STATE__RETRACT_ON;
					}
					else if(Distance < (ExtendDistance - LOWER_HYSTERETIC_BAND))
					{
						NextState = KICK_STATE__EXTEND_ON;
					}
					else
					{
						NextState = KICK_STATE__SIT_FOR_SHOOT;
					}
					break;
					
				case KICK_STATE__SHOOT:
					if(CurrentState != KICK_STATE__SHOOT)
					{
						SetValveStates(VALVE_CMD__LATCH_SHOOT);
						Wait(SET_AFTER_KICK_DELAY);
						NextState = KICK_STATE__RETRACT;
					}
					
					CurrentState = KICK_STATE__SHOOT;
					printf("Kick State shoot\n");

					break;
				
				case KICK_STATE__RETRACT_TO_STOW:
					if(CurrentState != KICK_STATE__RETRACT_TO_STOW)
					{
						SetValveStates(VALVE_CMD__TENSIONER_RETRACT_TO_LOAD);
					}
					
					CurrentState = KICK_STATE__RETRACT_TO_STOW;
					
					printf("Retract To Stow State\n");
					
					Distance = LinearPot->GetDistance();
					if(Distance < RetractDistance)
					{
						NextState = KICK_STATE__RELEASE_LATCH_STOW;
					}
					break;
					
				case KICK_STATE__RELEASE_LATCH_STOW:
					if(CurrentState != KICK_STATE__RELEASE_LATCH_STOW)
					{
						SetValveStates(VALVE_CMD__LATCH_SHOOT);
					}
					
					CurrentState = KICK_STATE__RELEASE_LATCH_STOW;
					
					printf("Stow Release State\n");
					
					Distance = LinearPot->GetDistance();
					if(Distance > STOW_DISTANCE)
					{
						NextState = KICK_STATE__WAIT_STOW;
					}
					break;
					
				case KICK_STATE__WAIT_STOW:
					if(CurrentState != KICK_STATE__WAIT_STOW)
					{
						ClearValveStates();
					}
					
					CurrentState = KICK_STATE__WAIT_STOW;
					
					printf("STOW WAIT State\n");
					
					
					if(Operator->GetNumberedButton(KICKER_LOAD))
					{
						NextState = KICK_STATE__RETRACT;
					}
					else if(ArrivedVia_KickerWheelStow_Button)
					{
						NextState = KICK_STATE__WHEEL_STOW_MOVE;
					}
					break;
					
				//Manual Mode	
				case KICK_STATE__MANUAL_RETRACT:
					if(CurrentState != KICK_STATE__MANUAL_RETRACT)
					{
						SetValveStates(VALVE_CMD__TENSIONER_RETRACT_TO_LOAD);
					}
					CurrentState = KICK_STATE__MANUAL_RETRACT;
					
					printf("MANUAL state RETRACT\n");
					
					
					break;
					
				case KICK_STATE__MANUAL_EXTEND:
					if(CurrentState != KICK_STATE__MANUAL_EXTEND)
					{
						SetValveStates(VALVE_CMD__TENSIONER_EXTEND);
					}
					CurrentState = KICK_STATE__MANUAL_EXTEND;
					
					printf("MANUAL state EXTEND\n");
					
					
					break;
					
				case KICK_STATE__MANUAL_LATCH:
					if(CurrentState != KICK_STATE__MANUAL_LATCH)
					{
						SetValveStates(VALVE_CMD__LATCH_SHOOT);
					}
					CurrentState = KICK_STATE__MANUAL_LATCH;
					
					printf("MANUAL state LATCH\n");
					
					break;
					
				case KICK_STATE__MANUAL_WAIT:
					if(CurrentState != KICK_STATE__MANUAL_WAIT)
					{
						ClearValveStates();
					}
					CurrentState = KICK_STATE__MANUAL_WAIT;
					
					printf("MANUAL state WAIT\n");
					
					if(Operator->GetNumberedButton(KICKER_LOAD))
					{
						ManualMode = false;
						ManualModeInDriversUse = false;
						NextState = KICK_STATE__RETRACT;
					}
					
					break;
					
				case KICK_STATE__WHEEL_STOW_MOVE:
					if(CurrentState != KICK_STATE__WHEEL_STOW_MOVE)
					{
						SetValveStates(VALVE_CMD__RETRACT_PLUGGED);
					}
					CurrentState = KICK_STATE__WHEEL_STOW_MOVE;
					
					Distance = LinearPot->GetDistance();
					if(Distance < WheelStowDistanceGoal)
					{
						NextState = KICK_STATE__WHEEL_STOW_WAIT;
					}
					
					break;
					
				case KICK_STATE__WHEEL_STOW_WAIT:
					if(CurrentState != KICK_STATE__WHEEL_STOW_WAIT)
					{
						SetValveStates(VALVE_CMD__RETRACT_HOLD_PLUGGED);
					}
					CurrentState = KICK_STATE__WHEEL_STOW_WAIT;
					
					if(Operator->GetNumberedButton(KICKER_LOAD))
					{
						NextState = KICK_STATE__RETRACT;
					}
					
					break;
					
			
				default:
					NextState = KICK_STATE__RETRACT;
					ClearValveStates();
					break;
					
			}//end of state switch
		}//end of the if for processing the statemachine
		Wait(0.1);
		DashData->KickerPotDistance_DashOut = LinearPot->GetDistance();
		DashData->KickerCurrentState_DashOut = (int) CurrentState;
	} while(m_EnableProcess);

} //end of kickerstatemachine

void Kicker::SetExtendDistance(double ExtendDistancePass)
{
	if(ExtendDistancePass > EXTEND_DISTANCE_MAX)
	{
		ExtendDistancePass = EXTEND_DISTANCE_MAX;
	}
	else if(ExtendDistancePass < EXTEND_DISTANCE_MIN)
	{
		ExtendDistancePass = EXTEND_DISTANCE_MIN;
	}
	
	ExtendDistance = ExtendDistancePass;
}

Kicker::KICK_STATE Kicker::GetKickerStateMachineState(void)
{
	return CurrentState;
}

void Kicker::DoSetExtendDistanceManual(bool ExtendActionManual)
{
	if(!ExtendActionManual)
	{
		ReadExtendDistance = true;
		
		if(SaveExtendDistance)
		{
			this->SavedManualExtendDistance = this->ExtendDistance;
			SaveExtendDistance = false;
		}
		
		this->ExtendActionManual = false;
		
	} //End If
	else
	{
		SaveExtendDistance = true;
		
		if(ReadExtendDistance)
		{
			this->SetExtendDistance(this->SavedManualExtendDistance);
			ReadExtendDistance = false;
		}
		
		this->ExtendActionManual = true;
		
	} //END Else
}

void Kicker::SetWheelStowDistance(double WheelStowDistancePass)
{
	static double WheelDistanceHold;
	
	if(WheelDistanceHold != WheelStowDistancePass)
	{
		WheelStowDistanceGoal = WHEEL_STOW_DISTANCE_GOAL + WheelStowDistancePass;
		WheelDistanceHold = WheelStowDistancePass;
		DashData->WheelStowDistanceGoal = this->WheelStowDistanceGoal;
	}
}

bool Kicker::IsDistanceExtended(void)
{
	if((LinearPot->GetDistance() > ExtendDistance - 1) && (LinearPot->GetDistance() < ExtendDistance + 1))
	{
		return true;
	}
	
	return false;
}
