#include <Arduino.h>

#include <SevSeg.h>
#include <HX711.h>

HX711 hx711;
SevSeg sevseg;
float units;
int load = 1;

uint16_t duration = 0;
uint32_t interval = 0;

float distance = 0;

void setup()
{
  uint8_t numDigits = 4;
  uint8_t digitPins[] = {2, 3, 4, 5};
  uint8_t segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  uint8_t displayType = COMMON_CATHODE; // (Common Anode or Common Cathode)

  bool resistorsOnSegments = false;
  bool updateWithDelays = false;
  bool leadingZeros = false;
  bool disableDecPoint = false;

  hx711.begin(A0, A1);
   hx711.set_scale(165.0);
  hx711.tare();

  sevseg.begin(displayType, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
  pinMode(load, OUTPUT);
  digitalWrite(load, LOW);
}

void loop()
{
  if ((millis() - interval) >= 200) {
    interval = millis();

    units = hx711.get_units();

    sevseg.setNumber(units,4);
  }
  sevseg.refreshDisplay();
  if(units > 30)
  {
    digitalWrite(load, HIGH);
  }
  else{
    digitalWrite(load, LOW);
  }

}
