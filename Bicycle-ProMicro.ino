//by Jeremy S. Cook
//Code optimized to use on bicycle handlebars w/ Arduino Pro Micro
//Also includes a selector switch

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PINRGB 2
#define NUMPIXELSRGB 1
Adafruit_NeoPixel pixelsRGB = Adafruit_NeoPixel(NUMPIXELSRGB, PINRGB, NEO_RGB + NEO_KHZ800);

const int RXPin = 8, TXPin = 9;
const uint32_t GPSBaud = 9600;
int speedM;
bool buttonState;
int lightOption = 0;
int totalOptions = 1; //this number, plus 0 is the total # of options


//TinyGPS++ object
TinyGPSPlus gps;

//Serial setup
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  pixelsRGB.begin(); // This initializes the NeoPixel library as pixelsRGB object.
  
  Serial.begin(115200);
  ss.begin(GPSBaud);

  Serial.println("speed on/off lighting");
  pinMode(3, INPUT_PULLUP);
}

void loop()
{
  buttonState = digitalRead(3);
  if (buttonState == LOW){ 
    Serial.println("button pressed");
    lightOption++;
    if (lightOption == totalOptions +1) lightOption = 0;
    delay(500); 
  }
  if (lightOption == 0)speedLight();
  if (lightOption == 1)blinkLight();
}

void speedLight()
{
  while (ss.available()) gps.encode(ss.read());
  speedM = gps.speed.mph();
  Serial.print("Speed in miles/hr: "); Serial.println(speedM);
  Serial.print("latitude, longitude: "); Serial.print(gps.location.lat()); Serial.print(" "); Serial.println(gps.location.lng());
  if (speedM > 13){
    Serial.println("speed above 15 MPH");
    pixelsRGB.setPixelColor(0, pixelsRGB.Color(200,0,0)); // Green/Red/Blue
    pixelsRGB.show(); // This sends the updated pixel color to the hardware.
    delay(100);
  }
  
  else if (speedM > 9){
    Serial.println("speed above 10 MPH");
    pixelsRGB.setPixelColor(0, pixelsRGB.Color(0,0,200)); // Green/Red/Blue
    pixelsRGB.show(); // This sends the updated pixel color to the hardware.
    delay(100);
  }
  
  else if (speedM > 2){
    Serial.println("Non-zero speed");
    pixelsRGB.setPixelColor(0, pixelsRGB.Color(100,125,0)); // Green/Red/Blue
    pixelsRGB.show(); // This sends the updated pixel color to the hardware.
    delay(100);
  }
  else { 
    Serial.println("Speed is zero");
    pixelsRGB.setPixelColor(0, pixelsRGB.Color(0,200,0)); // Green/Red/Blue
    pixelsRGB.show(); // This sends the updated pixel color to the hardware.
    delay(100);
  }
}

void blinkLight()
{
  Serial.println("blinking routine");
  pixelsRGB.setPixelColor(0, pixelsRGB.Color(200,200,200)); // lights up in white
  pixelsRGB.show(); // This sends the updated pixel color to the hardware.
  delay(1000);
  pixelsRGB.setPixelColor(0, pixelsRGB.Color(0,0,0)); // lights up in white
  pixelsRGB.show(); // This sends the updated pixel color to the hardware.
  delay(500);
}
