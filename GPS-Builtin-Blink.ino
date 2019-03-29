//Routine blinks onboard LED if speed in not zero
//By Jeremy S. Cook 3/29/2019

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

const int RXPin = 4, TXPin = 3;
const uint32_t GPSBaud = 9600;
int speedK;

//TinyGPS++ object
TinyGPSPlus gps;

//Serial setup
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);

  Serial.println("speed on/off lighting");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  
  speedK = gps.speed.kmph();
  Serial.print("Speed in km/hr: "); Serial.println(speedK);
  if (speedK > 0){
    Serial.println("Non-zero speed");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  //expand this to use RGB LED, perhaps printed case, put on bike eventually?
  while (ss.available()) gps.encode(ss.read());
}
