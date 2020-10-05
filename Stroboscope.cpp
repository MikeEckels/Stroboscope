#include "Stroboscope.h"

//Stroboscope* StroboscopePointer;
//
//static void globalISR() {
//	StroboscopePointer->Flash();
//}

void Stroboscope::Initialize() {
	//StroboscopePointer = this;

	pinMode(this->ledPin, OUTPUT);
	pinMode(this->potPin, INPUT);
	pinMode(this->btnPin, INPUT_PULLUP);
	pinMode(this->externalTriggerPin, INPUT);
	TurnOffLed();

	Timer1.initialize();
	Timer1.pwm(this->ledPin, 512);
	//Timer1.attachInterrupt(globalISR);
	DEBUG_PRINT_NOTICE("Stroboscope Initialized");
}

void Stroboscope::Start() {
	Timer1.start();
}

void Stroboscope::Stop() {
	Timer1.stop();
	//Timer1.detachInterrupt();
	SetFrequency(0.0f);
	//TurnOffLed();
}

void Stroboscope::TurnOnLed() {
	Timer1.resume();
	digitalWrite(this->ledPin, LOW);
}

void Stroboscope::TurnOffLed() {
	Timer1.stop();
	digitalWrite(this->ledPin, HIGH);
}

void Stroboscope::SetDutyCyclePercent(unsigned char percent) {
	//this->pulseTime = (float(percent) * (this->flashPeriod * 1000000.0f)) / (100.0f);
	this->pulseTime = ((float(percent) * (1024.0f )) / (100.0f));
	Timer1.setPwmDuty(this->ledPin, this->pulseTime);
	DEBUG_PRINT_INFO("Pulse Width(uS): " + (String)(this->pulseTime));
}

void Stroboscope::SetFrequency(float freq) {
	this->flashFreq = freq;
	CalculatePeriod();

	Timer1.setPeriod(this->flashPeriod * 1000000.0f);
	DEBUG_PRINT_INFO("Frequency(Hz): " + (String)(this->flashFreq));
	DEBUG_PRINT_INFO("Period(S): " + (String)(this->flashPeriod));
	DEBUG_PRINT_INFO("Period(uS): " + (String)(this->flashPeriod * 1000000.0f));
}

void Stroboscope::SetRPM(float rpm) {
	rpm /= 60.0f;
	SetFrequency(rpm);
}

void Stroboscope::CalculatePeriod() {
	this->flashPeriod = ((1.0f) / (this->flashFreq));
}

unsigned int Stroboscope::GetPotVal() {
	return(analogRead(potPin));
}

unsigned int Stroboscope::MapPot(unsigned int value) {
	this->mappedPotValue = map(value, 0, 1023, 1, 100);
	return(mappedPotValue);
}

//void Stroboscope::Flash() {
//	TurnOnLed();
//	delayMicroseconds(this->pulseTime);
//	TurnOffLed();
//}