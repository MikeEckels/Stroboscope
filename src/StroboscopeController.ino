//#define DEBUG
#include "Stroboscope.h" 

Stroboscope Strobe;

void setup() {
	Serial.begin(115200);

	Strobe.Initialize();
	Strobe.SetFrequency(10);
	Strobe.SetDutyCyclePercent(5);
	Strobe.Start();
}

void loop() {
	//Strobe.SetFrequency(Strobe.PotToFrequency(Strobe.GetFreqPotVal()));
	//Strobe.SetDutyCyclePercent(Strobe.PotToDutyCycle(Strobe.GetDutyPotVal()));

	Strobe.SetDutyCyclePercent(5);

	u8g2.firstPage();
	do {
		u8g2.setFont(u8g2_font_ncenB10_tr);
		u8g2.setCursor((u8g2.getDisplayWidth() / 2) - (20), (u8g2.getDisplayHeight() / 2));
		u8g2.print(Strobe.GetFrequency());
	} while (u8g2.nextPage());
}
