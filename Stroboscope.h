#pragma once
#include"Arduino.h"
#include "TimerOne.h"
#include "DebugUtils.h"

class Stroboscope {
private:
	const unsigned char ledPin = 7;
	const unsigned char freqPotPin = A0;
	const unsigned char dutyPotPin = A1;
	const unsigned char upBtnPin = 3;
	const unsigned char dwnBtnPin = 4;
	const unsigned char leftBtnPin = 1;
	const unsigned char rightBtnPin = 2;
	const unsigned char externalEnablePin = 0;

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
	static void upBtnGlobalISR();
	static void dwnBtnGlobalISR();
	static void leftBtnGlobalISR();
	static void rightBtnGlobalISR();

	void Initialize();
	void Start();
	void Stop();

	//ISR's not for user use
	void UpBtnClick();
	void DwnBtnClick();
	void LeftBtnClick();
	void RightBtnClick();

	void SetDutyCyclePercent(unsigned char percent);
	void SetFrequency(float freq);
	void SetRPM(float rpm);

	unsigned int GetFreqPotVal();
	unsigned int GetDutyPotVal();
	float GetFrequency();
 
	float PotToFrequency(unsigned int potValue);
	float PotToDutyCycle(unsigned int potValue);
};
