#pragma once
#include"Arduino.h"
#include "TimerOne.h"
#include "DebugUtils.h"

class Stroboscope {
private:
	const unsigned char ledPin = 10;
	const unsigned char freqPotPin = A0;
	const unsigned char dutyPotPin = A1;
	const unsigned char freqUpBtnPin = 2;
	const unsigned char freqDwnBtnPin = 3;
	const unsigned char externalTriggerPin = 14;

	float maxFrequency = 1000000.0f;
	float minFrequency = 1.0f;
	float maxDutyCyclePercent = 100.0f;
	float minDutyCyclePercent = 0.0f;

	float potFreqValue;
	float potDutyCycleValue;

	volatile float flashFreq;
	volatile float flashPeriod;
	float pulseTime;

	void TurnOnLed();
	void TurnOffLed();
	void CalculatePeriod();
 
	float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
	
public:
	void Initialize();
	void Start();
	void Stop();

	//ISR's not for user use
	void IncreaseFreq();
	void DecreaseFreq();

	void SetDutyCyclePercent(unsigned char percent);
	void SetFrequency(float freq);
	void SetRPM(float rpm);

	unsigned int GetFreqPotVal();
	unsigned int GetDutyPotVal();
 
	float PotToFrequency(unsigned int potValue);
	float PotToDutyCycle(unsigned int potValue);
};
