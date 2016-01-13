#include "DashboardDataSender.h"
#include "Timer.h"

/**
 * Send data to the dashboard.
 * This class sends two types of data to the dashboard program:
 * 1. Data representing all the ports on the robot
 * 2. Camera tracking data so the dashboard can annotate the video stream with
 *    target information.
 */
DashboardDataSender::DashboardDataSender(DashSharing *DashDataPass)
{
	// these timers make sure that the data is not sent to the dashboard more
	// than 10 times per second for efficiency.
	IOTimer = new Timer();
	visionTimer = new Timer();
	IOTimer->Start();
	visionTimer->Start();
	
	DashData = DashDataPass;
	UpdateTimeIO = 0.1;
}

/**
 * Send the vision tracking data.
 * Sends the vision information to the dashboard so that the images will be annotated
 * and the graphs will operate.
 */
void DashboardDataSender::sendVisionData() 
{
	if (visionTimer->Get() < 0.1)
		return;
	visionTimer->Reset();
	Dashboard &dash = DriverStation::GetInstance()->GetLowPriorityDashboardPacker();
	dash.AddCluster();
	{
		
	}
	dash.FinalizeCluster(); // wire
	dash.Finalize();
}

/**
 * Send IO port data to the dashboard.
 * Send data representing the output of all the IO ports on the cRIO to the dashboard.
 * This is probably not the best data to send for your robot. Better would be higher
 * level information like arm angle or collector status. But this is a sample and you're
 * free to modify it. Be sure to make the corresponding changes in the LabVIEW example
 * dashboard program running on your driver station.
 */
void DashboardDataSender::sendIOPortData() 
{
	if (IOTimer->Get() < UpdateTimeIO)
		return;
	IOTimer->Reset();
	Dashboard &dash = DriverStation::GetInstance()->GetHighPriorityDashboardPacker();
	dash.AddCluster();
	{
		dash.AddCluster();
		{ //analog modules 
			dash.AddCluster();
			{
				for (int i = 1; i <= 8; i++) {
					dash.AddFloat((float) AnalogModule::GetInstance(1)->GetAverageVoltage(i));
//					dash.AddFloat((float) i * 5.0 / 8.0);
				}
			}
			dash.FinalizeCluster();
			dash.AddCluster();
			{
				for (int i = 1; i <= 8; i++) {
					dash.AddFloat((float) AnalogModule::GetInstance(2)->GetAverageVoltage(i));
				}
			}
			dash.FinalizeCluster();
		}
		dash.FinalizeCluster();

		dash.AddCluster();
		{ //digital modules
			dash.AddCluster();
			{
				dash.AddCluster();
				{
					int module = 1;
					dash.AddU8(DigitalModule::GetInstance(module)->GetRelayForward());
					dash.AddU8(DigitalModule::GetInstance(module)->GetRelayReverse());
					dash.AddU16((short)DigitalModule::GetInstance(module)->GetDIO());
					//dash.AddU16((short) 0xAAAA);
					dash.AddU16((short)DigitalModule::GetInstance(module)->GetDIODirection());
					//dash.AddU16((short) 0x7777);
					dash.AddCluster();
					{
						for (int i = 1; i <= 10; i++) {
							dash.AddU8((unsigned char) DigitalModule::GetInstance(module)->GetPWM(i));
//							dash.AddU8((unsigned char) (i-1) * 255 / 9);
						}
					}
					dash.FinalizeCluster();
				}
				dash.FinalizeCluster();
			}
			dash.FinalizeCluster();

			dash.AddCluster();
			{
				dash.AddCluster();
				{
					int module = 2;
					dash.AddU8(DigitalModule::GetInstance(module)->GetRelayForward());
					dash.AddU8(DigitalModule::GetInstance(module)->GetRelayForward());
					dash.AddU16((short)DigitalModule::GetInstance(module)->GetDIO());
					dash.AddU16(DigitalModule::GetInstance(module)->GetDIODirection());
					dash.AddCluster();
					{
						for (int i = 1; i <= 10; i++) {
							dash.AddU8((unsigned char) DigitalModule::GetInstance(module)->GetPWM(i));
//							dash.AddU8((unsigned char) i * 255 / 10);
						}
					}
					dash.FinalizeCluster();
				}
				dash.FinalizeCluster();
			}
			dash.FinalizeCluster();
		}
		dash.FinalizeCluster();

		
		// Can't read solenoids without an instance of the object
		dash.AddU8((char) 0);
		
		//*****************************************************
		//CHAOS Custom Clusters
		
		//Line Tracker Booleans
		dash.AddCluster();
		{
			dash.AddBoolean(DashData->UpperLineTracker_D);
			dash.AddBoolean(DashData->LowerLineTracker_D);
		}
		dash.FinalizeCluster();
		
		//Line Tracking State
//		dash.AddCluster();
//		{
//			dash.AddI16(DashData->LineFollowingStates_D);
//		}
//		dash.FinalizeCluster();
		

		
		//Ultrasonic
		dash.AddCluster();
		{
			dash.AddDouble(DashData->LeftInches_D);
			dash.AddDouble(DashData->RightInches_D);
			dash.AddDouble(DashData->AvgInches_D);
//			dash.AddDouble(DashData->UltraAngle_D);
		}
		dash.FinalizeCluster();
		
		//Elbow
//		dash.AddCluster();
//		{
//			dash.AddFloat(DashData->ElbowProportionalConstant_D);
//			dash.AddFloat(DashData->ElbowIntegralConstant_D);
//			dash.AddFloat(DashData->ElbowDerivativeConstant_D);
//			dash.AddFloat(DashData->ElbowPidGet_D);
//			dash.AddFloat(DashData->ElbowPidSetpoint_D);
//			dash.AddFloat(DashData->ElbowPreviousAngle_D);
//		}
//		dash.FinalizeCluster();
		
		//Escape mini clusters
//		dash.AddCluster();
//		{
//			dash.AddBoolean(DashData->EscapeBTN_D);
//		}
//		dash.FinalizeCluster();
//		dash.AddCluster();
//		{
//			dash.AddDouble(DashData->EscapeTime_D);
//		}
//		dash.FinalizeCluster();
		
		dash.AddCluster();
		{
			dash.AddI16(DashData->CurrentAutoState_D);
			dash.AddI16(DashData->ManipStates_D);
			dash.AddI16(DashData->ElbowStates_D);
			dash.AddI16(DashData->ShoulderStates_D);
		}
		dash.FinalizeCluster();
		
		dash.AddCluster();
		{
			dash.AddFloat(DashData->ElbowPot_D);
			dash.AddFloat(DashData->ShoulderAngle_D);
		}
		dash.FinalizeCluster();
		
//		//Line Following Gyro
		dash.AddCluster();
		{
			dash.AddFloat(DashData->LineFollowingGyroAngle_D);
		}
		dash.FinalizeCluster();
		
	}
	dash.FinalizeCluster();
	dash.Finalize();
}
