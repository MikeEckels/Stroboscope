#define DEBUG
#include "Stroboscope.h" 

Stroboscope Strobe;

void setup() {
	Serial.begin(115200);

	Strobe.Initialize();
	Strobe.SetFrequency(1000000);
	Strobe.SetDutyCyclePercent(15);
	Strobe.Start();
}

void loop() {
	//Strobe.SetFrequency(Strobe.PotToFrequency(Strobe.GetFreqPotVal()));
	//Strobe.SetDutyCyclePercent(Strobe.PotToDutyCycle(Strobe.GetDutyPotVal()));
	Strobe.SetDutyCyclePercent(25);
}
