#pragma once
#include <Wire.h>
#include "Menu.h"
#include"Arduino.h"
#include <U8g2lib.h>
#include "TimerOne.h"
#include "DebugUtils.h"

class Stroboscope;
//extern U8X8_SH1106_128X64_NONAME_HW_I2C u8x8;
extern U8G2_SH1106_128X64_NONAME_2_HW_I2C u8g2;

namespace InternalStroboscope {
	static Stroboscope* _pThis;
}

class Stroboscope {
private:
	Stroboscope(const Stroboscope&) = delete;
	Stroboscope& operator=(const Stroboscope&) = delete;

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

	void UpBtnClick();
	void DwnBtnClick();
	void LeftBtnClick();
	void RightBtnClick();

	static void upBtnISR() {
		InternalStroboscope::_pThis->UpBtnClick();
	}

	static void dwnBtnISR() {
		InternalStroboscope::_pThis->DwnBtnClick();
	}

	static void leftBtnISR() {
		InternalStroboscope::_pThis->LeftBtnClick();
	}

	static void rightBtnISR() {
		InternalStroboscope::_pThis->RightBtnClick();
	}

public:
	Stroboscope() = default;
	~Stroboscope() = default;

	void Initialize();
	void Start();
	void Stop();

	void SetDutyCyclePercent(unsigned char percent);
	void SetFrequency(float freq);
	void SetRPM(float rpm);

	unsigned int GetFreqPotVal();
	unsigned int GetDutyPotVal();
	float GetFrequency();
	float GetRPM();

	float PotToFrequency(unsigned int potValue);
	float PotToDutyCycle(unsigned int potValue);
};
