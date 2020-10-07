#include "Stroboscope.h"

Stroboscope* UpPointer;
Stroboscope* DwnPointer;

static void upBtnGlobalISR() {
	UpPointer->IncreaseFreq();
}

static void dwnBtnGlobalISR() {
	DwnPointer->DecreaseFreq();
}

void Stroboscope::Initialize() {
	UpPointer = this;
	DwnPointer = this;
	DEBUG_PRINT_NOTICE("Initializing Stroboscope");

	pinMode(this->ledPin, OUTPUT);
	pinMode(this->freqPotPin, INPUT);
	pinMode(this->dutyPotPin, INPUT);
	pinMode(this->freqUpBtnPin, INPUT_PULLUP);
	pinMode(this->freqDwnBtnPin, INPUT_PULLUP);
	pinMode(this->externalTriggerPin, INPUT);
	TurnOffLed();

	Timer1.initialize();
	Timer1.pwm(this->ledPin, 512);

	attachInterrupt(digitalPinToInterrupt(this->freqUpBtnPin), upBtnGlobalISR, FALLING);
	attachInterrupt(digitalPinToInterrupt(this->freqDwnBtnPin), dwnBtnGlobalISR, FALLING);
}

void Stroboscope::Start() {
	Timer1.start();
	DEBUG_PRINT_NOTICE("Timer Started");
}

void Stroboscope::Stop() {
	Timer1.stop();
	SetFrequency(0.0f);
	DEBUG_PRINT_ERR("Timer Stopped");

	detachInterrupt(digitalPinToInterrupt(this->freqUpBtnPin));
	detachInterrupt(digitalPinToInterrupt(this->freqDwnBtnPin));
	//TurnOffLed();
}

void Stroboscope::TurnOnLed() {
	digitalWrite(this->ledPin, LOW);
	DEBUG_PRINT_INFO("LED On");
}

void Stroboscope::TurnOffLed() {
	Timer1.stop();
	digitalWrite(this->ledPin, HIGH);
	DEBUG_PRINT_INFO("LED Off");
}

void Stroboscope::SetDutyCyclePercent(unsigned char percent) {
	//this->pulseTime = (float(percent) * (this->flashPeriod * 1000000.0f)) / (100.0f);
	this->pulseTime = ((float(percent) * (1024.0f )) / (100.0f));
	Timer1.setPwmDuty(this->ledPin, this->pulseTime);
}

void Stroboscope::SetFrequency(float freq) {
	this->flashFreq = freq;
	CalculatePeriod();

	Timer1.setPeriod(this->flashPeriod * 1000000.0f);
	DEBUG_PRINT_INFO("Period(S): " + (String)(this->flashPeriod));
	DEBUG_PRINT_INFO("Period(uS): " + (String)(this->flashPeriod * 1000000.0f));
	DEBUG_PRINT_INFO("Frequency(Hz): " + (String)(this->flashFreq));
	DEBUG_PRINT_INFO("Pulse Width(uS): " + (String)(this->pulseTime));
}

void Stroboscope::SetRPM(float rpm) {
	rpm /= 60.0f;
	SetFrequency(rpm);
}

void Stroboscope::CalculatePeriod() {
	this->flashPeriod = ((1.0f) / (this->flashFreq));
}

unsigned int Stroboscope::GetFreqPotVal() {
	return(analogRead(freqPotPin));
}

unsigned int Stroboscope::GetDutyPotVal() {
	return(analogRead(dutyPotPin));
}

float Stroboscope::PotToFrequency(unsigned int potValue) {
	this->potFreqValue = mapFloat((float)potValue, 0.0f, 1023.0f, this->minFrequency, this->maxFrequency);
	return(this->potFreqValue);
}

float Stroboscope::PotToDutyCycle(unsigned int potValue) {
	this->potDutyCycleValue = mapFloat((float)potValue, 0.0f, 1023.0f, this->minDutyCyclePercent, this->maxDutyCyclePercent);
	return(this->potDutyCycleValue);
}

float Stroboscope::mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Stroboscope::IncreaseFreq() {
	if ((this->flashFreq + 10000) <= this->maxFrequency) {
		this->flashFreq += 10000;
	}
	else {
		this->flashFreq = this->maxFrequency;
	}
	
	SetFrequency(this->flashFreq);
  DEBUG_PRINT_NOTICE("Increased Frequency");
}

void Stroboscope::DecreaseFreq() {
	if ((this->flashFreq - 10000) >= this->minFrequency) {
		this->flashFreq -= 10000;
	}
	else {
		this->flashFreq = this->minFrequency;
	}

	SetFrequency(this->flashFreq);
  DEBUG_PRINT_NOTICE("Decreased Frequency");
}
