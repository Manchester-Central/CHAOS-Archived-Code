
#include "DashboardDataFormat.h"
#include "Logger.h"
#include "chaos09.h"



//Logger logger;

DashboardDataFormat::DashboardDataFormat(void)
	: m_ds (DriverStation::GetInstance())
{
	
}

DashboardDataFormat::~DashboardDataFormat()
{
	
}

/**
 * Pack data using the correct types and in the correct order to match the
 * default "Dashboard Datatype" in the LabVIEW Dashboard project.
 */
void DashboardDataFormat::PackAndSend(void)
{
	Dashboard &dashboardPacker = m_ds->GetDashboardPacker();
	UINT32 module;
	UINT32 channel;
	//timer.Start();
	// Pack the analog modules
	//for (module = 0; module < kAnalogModules; module++)
	//{
		dashboardPacker.AddCluster();
		//for (channel = 0; channel < kAnalogChannels; channel++)
		//{
			//dashboardPacker.AddFloat(m_AnalogChannels[module][channel]);
			dashboardPacker.AddFloat(logger.chassisEncodersV[0]);
			dashboardPacker.AddFloat(logger.chassisEncodersV[1]);
			dashboardPacker.AddFloat(logger.vChaSide[0]);
			dashboardPacker.AddFloat(logger.vChaSide[1]);
			dashboardPacker.AddFloat(logger.mailLoopTm1);
			dashboardPacker.AddFloat(logger.mailLoopTm2);
			dashboardPacker.AddFloat(logger.mailLoopTm3);
			dashboardPacker.AddFloat(logger.mailLoopTm4);
			dashboardPacker.FinalizeCluster();
			dashboardPacker.AddFloat(0);
			dashboardPacker.AddFloat(0);
			dashboardPacker.AddFloat(0);
			dashboardPacker.AddFloat(0);
			dashboardPacker.AddFloat(0);
			dashboardPacker.AddFloat(0);
			dashboardPacker.AddFloat(0);
			dashboardPacker.AddFloat(0);
			dashboardPacker.FinalizeCluster();
			//logger.mailLoopTm2 = timer.Get();
		//}
		//dashboardPacker.FinalizeCluster();
	//}
	// Pack the digital modules
	for (module = 0; module < kDigitalModules; module++)
	{
		dashboardPacker.AddCluster();
		dashboardPacker.AddU8(m_RelayFwd[module]);
		dashboardPacker.AddU8(m_RelayRev[module]);
		dashboardPacker.AddU16(m_DIOChannels[module]);
		dashboardPacker.AddU16(m_DIOChannelsOutputEnable[module]);
		dashboardPacker.AddCluster();
		for(channel = 0; channel < kPwmChannels; channel++)
		{
			dashboardPacker.AddU8(m_PWMChannels[module][channel]);
		}
		dashboardPacker.FinalizeCluster();
		dashboardPacker.FinalizeCluster();
	}
	// Pack the solenoid module
	dashboardPacker.AddU8(m_SolenoidChannels);
	//logger.mailLoopTm3 = timer.Get();
	// Flush the data to the driver station.
	dashboardPacker.Finalize();
	//timer.Stop();
}
