#pragma once
#include<Arduino.h>

class Stroboscope {
private:
	const unsigned char potPin = A6;
	const unsigned char btnPin = 1;
	const unsigned char ledPin = 0;
	const unsigned char externalTriggerPin = 14;

	unsigned int mappedPotValue;

	float flashFreq;

	void TurnOnLed();
	void TurnOffLed();

	unsigned int GetPotVal();
	unsigned int MapPot(unsigned int value);

public:
	void Begin();
	void Start();
	void Stop();

	void SetFrequency(float freq);
	void SetRPM(float rpm);
};
