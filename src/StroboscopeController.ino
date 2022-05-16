/*############################################################
Teensy 4.0	- MIN Freq   = 17.9 Hz
			- MAX Freq   = 1.0  Mhz
			- MIN Period = 1    %
			- MAX Period = 100  %
			- PINS		 = 7 and 8

Arduino Uno - MIN Freq   = 0.1  Hz
			- MAX Freq   = 333  kHz
			- MIN Period = 1	%
			- MAX Period = 100	%
			- PINS		 = 9 and 10
############################################################*/

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
		u8g2.setCursor((u8g2.getDisplayWidth() / 2) - (60), (u8g2.getDisplayHeight() / 2));
		u8g2.print("Freq: " + (String)Strobe.GetFrequency() + "Hz");
		u8g2.setCursor((u8g2.getDisplayWidth() / 2) - (60), (u8g2.getDisplayHeight() / 2) + 20);
		u8g2.print("RPM: " + (String)Strobe.GetRPM());
	} while (u8g2.nextPage());
}
