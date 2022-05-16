#include "Stroboscope.h"

U8G2_SH1106_128X64_NONAME_2_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE);

void Stroboscope::Initialize() {
	InternalStroboscope::_pThis = this;

	DEBUG_PRINT_NOTICE("Initializing Stroboscope");

	u8g2.begin();
	u8g2.setFlipMode(1);

	pinMode(this->ledPin, OUTPUT);
	pinMode(this->freqPotPin, INPUT);
	pinMode(this->dutyPotPin, INPUT);
	pinMode(this->upBtnPin, INPUT_PULLUP);
	pinMode(this->dwnBtnPin, INPUT_PULLUP);
	pinMode(this->externalEnablePin, INPUT);
	TurnOffLed();

	attachInterrupt(digitalPinToInterrupt(this->upBtnPin), upBtnISR, FALLING);
	attachInterrupt(digitalPinToInterrupt(this->dwnBtnPin), dwnBtnISR, FALLING);
	attachInterrupt(digitalPinToInterrupt(this->leftBtnPin), leftBtnISR, FALLING);
	attachInterrupt(digitalPinToInterrupt(this->rightBtnPin), rightBtnISR, FALLING);
}

void Stroboscope::Start() {
	Timer.begin(PulseISR, this->flashPeriod * 1000000.0f);
	DEBUG_PRINT_NOTICE("Timer Started");
}

void Stroboscope::Stop() {
	Timer.end();
	SetFrequency(0.0f);
	DEBUG_PRINT_ERR("Timer Stopped");

	detachInterrupt(digitalPinToInterrupt(this->upBtnPin));
	detachInterrupt(digitalPinToInterrupt(this->dwnBtnPin));
}

void Stroboscope::Pulse() {
	Stroboscope::TurnOnLed();
	if ((float(this->pulseTime) * 1000000.0f) > 1.0f) {
		delayMicroseconds(this->pulseTime * 1000000.0f);
	}
	else {
		delayNanoseconds(this->pulseTime * 1000000000.0f);
	}
	Stroboscope::TurnOffLed();
}

void Stroboscope::TurnOnLed() {
	digitalWrite(this->ledPin, LOW);
	//DEBUG_PRINT_INFO("LED On");
}

void Stroboscope::TurnOffLed() {
	digitalWrite(this->ledPin, HIGH);
	//DEBUG_PRINT_INFO("LED Off");
}

void Stroboscope::SetDutyCyclePercent(unsigned char percent) {
	//this->pulseTime = ((float(percent) * (1024.0f)) / (100.0f));
	this->pulseTime = ((float(percent) / (100.0f)) * (float(this->flashPeriod)));
	DEBUG_PRINT_INFO("Pulse Width(uS): " + (String)(this->pulseTime * 1000000.0f));
}

void Stroboscope::SetFrequency(float freq) {
	this->flashFreq = freq;
	CalculatePeriod();

	Timer.update(this->flashPeriod * 1000000.0f);
	DEBUG_PRINT_INFO("Period(S): " + (String)(this->flashPeriod));
	DEBUG_PRINT_INFO("Period(uS): " + (String)(this->flashPeriod * 1000000.0f));
	DEBUG_PRINT_INFO("Frequency(Hz): " + (String)(this->flashFreq));
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

float Stroboscope::GetFrequency() {
	return(this->flashFreq);
}

float Stroboscope::GetRPM() {
	return(Stroboscope::GetFrequency() * 60.0f);
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

void Stroboscope::UpBtnClick() {
	if ((this->flashFreq + 0.5f) <= this->maxFrequency) {
		this->flashFreq += 0.5f;
	}
	else {
		this->flashFreq = this->maxFrequency;
	}
	//SetFrequency(this->flashFreq);
	DEBUG_PRINT_NOTICE("Increased Frequency");
}

void Stroboscope::DwnBtnClick() {
	if ((this->flashFreq - 0.5f) >= this->minFrequency) {
		this->flashFreq -= 0.5f;
	}
	else {
		this->flashFreq = this->minFrequency;
	}
	//SetFrequency(this->flashFreq);
	DEBUG_PRINT_NOTICE("Decreased Frequency");
}

void Stroboscope::LeftBtnClick() {

	DEBUG_PRINT_NOTICE("Left button clicked");
}

void Stroboscope::RightBtnClick() {
	SetFrequency(this->flashFreq);
	DEBUG_PRINT_NOTICE("Right button clicked");
}
