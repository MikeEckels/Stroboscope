#include "Stroboscope.h"

#define DEBUG

Stroboscope Strobe;

void setup() {
	Serial.begin(115200);

	Strobe.Initialize();
	Strobe.SetFrequency(1000000);
	Strobe.SetDutyCyclePercent(15);
	Strobe.Start();
}

void loop() {
	//Strobe.SetFrequency(Strobe.MapPot(Strobe.GetPotVal()));
	//DEBUG_PRINTLN(Strobe.MapPot(Strobe.GetPotVal()));
}
