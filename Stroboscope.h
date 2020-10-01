#pragma once
#include"Arduino.h"
#include "TimerOne.h"
#include "DebugUtils.h"

class Stroboscope {
private:
	const unsigned char potPin = A6;
	const unsigned char btnPin = 1;
	const unsigned char ledPin = LED_BUILTIN;
	const unsigned char externalTriggerPin = 14;

	unsigned int mappedPotValue;

	float flashFreq;
	float flashPeriod;
	float pulseTime;

	void TurnOnLed();
	void TurnOffLed();
	void CalculatePeriod();
	

public:
	void Initialize();
	void Flash();
	void Start();
	void Stop();

	void SetDutyCyclePercent(unsigned char percent);
	void SetFrequency(float freq);
	void SetRPM(float rpm);

	unsigned int GetPotVal();
	unsigned int MapPot(unsigned int value);
};
