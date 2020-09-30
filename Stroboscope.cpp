#include "Stroboscope.h"

void Stroboscope::Begin() {
	pinMode(this->ledPin, OUTPUT);

	pinMode(this->potPin, INPUT);
	pinMode(this->btnPin, INPUT_PULLUP);
	pinMode(this->externalTriggerPin, INPUT);
}

void Stroboscope::Start() {

}

void Stroboscope::Stop() {
	SetFrequency(0.0f);
	TurnOffLed();
}

void Stroboscope::TurnOnLed() {
	digitalWrite(this->ledPin, HIGH);
}

void Stroboscope::TurnOffLed() {
	digitalWrite(this->ledPin, LOW);
}

void Stroboscope::SetFrequency(float freq) {
	this->flashFreq = freq;
}

void Stroboscope::SetRPM(float rpm) {
	rpm /= 60.0f;
	SetFrequency(rpm);
}

unsigned int Stroboscope::GetPotVal() {
	return(analogRead(potPin));
}

unsigned int Stroboscope::MapPot(unsigned int value) {
	this->mappedPotValue = map(value, 0, 1023, 0, 255);
	return(mappedPotValue);
}