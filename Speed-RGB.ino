//Speed changes RGB light color
//By Jeremy S. Cook 3/29/2019

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PINRGB 5
#define NUMPIXELSRGB 1
Adafruit_NeoPixel pixelsRGB = Adafruit_NeoPixel(NUMPIXELSRGB, PINRGB, NEO_RGB + NEO_KHZ800);

const int RXPin = 4, TXPin = 3;
const uint32_t GPSBaud = 9600;
int speedK;



//TinyGPS++ object
TinyGPSPlus gps;

//Serial setup
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  pixelsRGB.begin(); // This initializes the NeoPixel library as pixelsRGB object.
  
  Serial.begin(9600);
  ss.begin(GPSBaud);

  Serial.println("speed on/off lighting");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  
  speedK = gps.speed.kmph();
  Serial.print("Speed in km/hr: "); Serial.println(speedK);

  if (speedK > 5){
    Serial.println("speed above 5 Km/h");
    pixelsRGB.setPixelColor(0, pixelsRGB.Color(200,0,0)); // Green/Red/Blue
    pixelsRGB.show(); // This sends the updated pixel color to the hardware.
    delay(10);
  }
  
  else if (speedK > 0){
    Serial.println("Non-zero speed");
    pixelsRGB.setPixelColor(0, pixelsRGB.Color(100,125,0)); // Green/Red/Blue
    pixelsRGB.show(); // This sends the updated pixel color to the hardware.
    delay(10);
  }
  else { 
    Serial.println("Speed is zero");
    pixelsRGB.setPixelColor(0, pixelsRGB.Color(0,200,0)); // Green/Red/Blue
    pixelsRGB.show(); // This sends the updated pixel color to the hardware.
    delay(10);
  }
  delay(50);
  //expand this to use RGB LED, perhaps printed case, put on bike eventually?
  while (ss.available()) gps.encode(ss.read());
}
