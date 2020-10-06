#pragma once
#include"Arduino.h"
#include "TimerOne.h"
#include "DebugUtils.h"

class Stroboscope {
private:
	const unsigned char freqPotPin = A0;
  const unsigned char dutyPotPin = A1;
	const unsigned char btnPin = 1;
	const unsigned char ledPin = 10;
	const unsigned char externalTriggerPin = 14;

	float potFreqValue;
  float potDutyCycleValue;

	float flashFreq;
	float flashPeriod;
	float pulseTime;

	void TurnOnLed();
	void TurnOffLed();
	void CalculatePeriod();
 
  float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
	
public:
	void Initialize();
	//void Flash();
	void Start();
	void Stop();

	void SetDutyCyclePercent(unsigned char percent);
	void SetFrequency(float freq);
	void SetRPM(float rpm);

	unsigned int GetFreqPotVal();
  unsigned int GetDutyPotVal();
 
	float PotToFrequency(unsigned int potValue);
  float PotToDutyCycle(unsigned int potValue);
};
