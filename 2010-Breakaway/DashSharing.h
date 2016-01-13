#ifndef _DASH_SHARING_H_
#define _DASH_SHARING_H_

#include "WPILib.h"


class DashSharing
{
	public:	
		double CameraErrorAngle_Dashout;
		double GyroAngle_DashOut;
		double SetPoint_DashOut;
		double BallUltraSonic_Distance_DashOut;
		double KLPot_Value_DashOut;
		double ALPot_Value_DashOut;
		double WheelStowDistanceGoal;
		double TargetDistance_DashOut;
		bool Driver_Button1;
		bool PressureSwitch_DashOut;
		bool Trigger_DashOut;
		
		//TODO: Fix Mispell "Eistance"
		double KickerExtendEistance_DashOut;
		double KickerPotDistance_DashOut;
		
		double AutoPotDistance_DashOut;
		
		double AutoTargetDistance_DashOut;
		double AutoExtendDistance_DashOut;
		
		int KickerCurrentState_DashOut;
		int AutonomousCurrentState_DashOut;
		
		int DribblerHasBall_DashOut;
		
		
		DashSharing(void)
		{
			CameraErrorAngle_Dashout = 0.0;
			GyroAngle_DashOut = 0.0;
			SetPoint_DashOut = 0.0;
			BallUltraSonic_Distance_DashOut = 0.0;
			KLPot_Value_DashOut = 0.0;
			ALPot_Value_DashOut = 0.0;
			WheelStowDistanceGoal = 0.0;
			AutoTargetDistance_DashOut = 0.0;
			TargetDistance_DashOut = 0.0;
			AutoPotDistance_DashOut = 0.0;
			AutoExtendDistance_DashOut = 0.0;
			PressureSwitch_DashOut = false;
			Trigger_DashOut = false;
			KickerExtendEistance_DashOut = 0.0;
			KickerPotDistance_DashOut = 0.0;
			KickerCurrentState_DashOut = 0;
			AutonomousCurrentState_DashOut = 0;
			
			DribblerHasBall_DashOut = 0;
		}
};

#endif

