/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef CHAOSJAGUAR_H
#define CHAOSJAGUAR_H


#include "Jaguar.h"
/**
 * Luminary Micro Jaguar Speed Control
 */
class chaosJaguar : public Jaguar
{
public:
	explicit chaosJaguar(UINT32 channel);
	void Set(float value);

};
#endif

