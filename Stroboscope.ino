//#define DEBUG
#include <Wire.h>
#include <U8g2lib.h>
#include "Stroboscope.h" 

Stroboscope Strobe;
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

void setup() {
	Serial.begin(115200);
 
	u8x8.begin();
	u8x8.clear();
	u8x8.setFlipMode(1);
	u8x8.setCursor(0, 0);
	u8x8.setFont(u8x8_font_px437wyse700b_2x2_r);

	Strobe.Initialize();
	Strobe.SetFrequency(10);
	Strobe.SetDutyCyclePercent(5);
	Strobe.Start();
}

void loop() {
	//Strobe.SetFrequency(Strobe.PotToFrequency(Strobe.GetFreqPotVal()));
	//Strobe.SetDutyCyclePercent(Strobe.PotToDutyCycle(Strobe.GetDutyPotVal()));
 
	Strobe.SetDutyCyclePercent(5);
  
	u8x8.setCursor(3,3);
	u8x8.print(Strobe.GetFrequency());
}
