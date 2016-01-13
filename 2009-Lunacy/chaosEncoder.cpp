/*----------------------------------------------------------------------------*
* Copyright (c) CHAOS 2009
*----------------------------------------------------------------------------*/

#include "chaosEncoder.h"


void chaosEncoder::SetPrevious_lpf(double previous)
{
	lpf.SetPrevious(previous);
}

/**construct the chaosEncoder object
 * @param int PortA
 * @param int PortB
 * @param float DistancePerPulse
 */

chaosEncoder::chaosEncoder(int PortA, int PortB, float DistancePerPulse):
	encoder(PortA, PortB, false, Encoder::k2X), lpf(0)
{
	period = 0;
	encoder.SetDistancePerPulse (DistancePerPulse);
	encoder.Start ();
}

/**
 * Reset the chaosEncoder. 
 */
void chaosEncoder::Reset_lpf()
{
	lpf.Reset();
}

/**
 * Delete (free)  the chaosEncoder.
 */
chaosEncoder::~chaosEncoder()
{
}

/**
 * finding the value of the encoder and whether it is stopped
 * @return the encoder value that has been passed through the low pass filter
 */

float chaosEncoder::GetValue()
{
	double v_encoder;
				
	if ( encoder.GetStopped() )
	{
		v_encoder = 0;
				
	}
	else
	{
		v_encoder = encoder.GetRate();
				
	}

	
	return lpf.GetValue(v_encoder);
	
}

/**
* Sets the LowPassFilter Coefficient.
* 
*@param int Hertz Frequency of collecting data
*@param double Period
 */
void chaosEncoder::SetCoefficient_lpf(double Hertz, double Period)
{
	period = Period;
	lpf.SetCoefficient(Hertz, Period);
}

/**
 * Start the QuadEncoder.
 * Starts counting pulses on the QuadEncoder device.
 */
void chaosEncoder::Start()
{
	encoder.Start();
}

/**
 * Gets the current count.
 * Returns the current count on the QuadEncoder. Quadrature encoders return 4x the
 * expected number of counts since the hardware counts all 4 edges for higher
 * resolution.
 *
 * @return Current count from the QuadEncoder.
 */
INT32 chaosEncoder::Get()
{
	return encoder.Get();
}

/**
 * Gets the raw value from the encoder.
 * The raw value is the actual count unscaled by the 1x, 2x, or 4x scale
 * factor.
 * @return Current raw count from the encoder
 */
INT32 chaosEncoder::GetRaw()
{
	return encoder.GetRaw();
}

/**
 * Reset the QuadEncoder to zero.
 * Resets the current count to zero on the encoder.
 */
void chaosEncoder::Reset()
{
	encoder.Reset();
}

/**
 * Stops counting pulses on the QuadEncoder device. The value is not changed.
 */
void chaosEncoder::Stop()
{
	encoder.Stop();
}

/**
 * Returns the period of the most recent pulse.
 * Returns the period of the most recent Quad Encoder pulse in seconds.
 * @return Period in seconds of the most recent pulse.
 */
double chaosEncoder::GetPeriod()
{
	return encoder.GetPeriod();
}

/**
 * Sets the maximum period for stopped detection.
 * Sets the value that represents the maximum period of the QuadEncoder before it will assume
 * that the attached device is stopped. This timeout allows users to determine if the wheels or
 * other shaft has stopped rotating.
 * @param maxPeriod The maximum time between rising and falling edges before the FPGA will
 * consider the device stopped. This is expressed in seconds.
 */
void chaosEncoder::SetMaxPeriod(double maxPeriod)
{
	encoder.SetMaxPeriod(maxPeriod);
}

/**
 * Determine if the encoder is stopped.
 * Using the MaxPeriod value, a boolean is returned that is true if the encoder is considered
 * stopped and false if it is still moving. A stopped encoder is one where the most recent pulse
 * width exceeds the MaxPeriod.
 * @return True if the encoder is considered stopped.
 */
bool chaosEncoder::GetStopped()
{
	return encoder.GetStopped();
}

/**
 * The last direction the encoder value changed.
 * @return The last direction the encoder value changed.
 */
bool chaosEncoder::GetDirection()
{
	return encoder.GetDirection();
}

/**
 * Get the distance the robot has driven since the last reset
 * @return The distance driven since the last reset based on the distance per tick
 * variable being set by SetDistancePerTick(). It is just a simple multiplication, but
 * makes the bookkeeping a little easier since the encoder remembers the scale factor.
 */
float chaosEncoder::GetDistance()
{
	return encoder.GetDistance();
}


/**
 * Get the current rate of the encoder.
 * Units are distance per second as scaled by the value from SetDistancePerPulse().
 * 
 * @return The current rate of the encoder.
 */
double chaosEncoder::GetRate()
{
	return encoder.GetRate();
}


/**
 * Set the minimum rate of the device before the hardware reports it stopped.
 * 
 * @param minRate The minimum rate.  The units are in distance per second as scaled by the value from SetDistancePerPulse().
 */
void chaosEncoder::SetMinRate(double minRate)
{
	encoder.SetMaxPeriod(minRate);
}

/**
 * Set the distance per tick for this encoder.
 * This sets the multiplier used to determine the distance driven based on the count value
 * from the encoder. Reseting the encoder also resets the distance since it's just a simple
 * multiply.
 */
void chaosEncoder::SetDistancePerPulse(double distancePerPulse)
{
	encoder.SetDistancePerPulse(distancePerPulse);
}

/**
 * Set the direction sensing for this encoder.
 * This sets the direction sensing on the encoder so that it couldl count in the correct
 * software direction regardless of the mounting.
 * @param reverseDirection true if the encoder direction should be reversed
 */
void chaosEncoder::SetReverseDirection(bool reverseDirection)
{
	encoder.SetReverseDirection(reverseDirection);
}
