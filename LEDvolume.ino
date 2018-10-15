
#include <FastLED.h>

#define NUM_LEDS_PER_STRIP 60
CRGB leds[NUM_LEDS_PER_STRIP];

//variables for storing raw sound and scaled value
int sound;
int scale;
int i;
const int mainPin = 7;
const int soundPin = 0;


 
 

void setup()
{
  Serial.begin(9600);
  FastLED.addLeds<WS2812, 7, GRB>(leds, NUM_LEDS_PER_STRIP);
 //start the serial port a@ 9600bps


}

void loop()
{
 //read and store the audio from Envelope pin
 sound = analogRead(soundPin);
 //map sound which in a quiet room a clap is 300
 //from 0 to 3 to be used with switch case
 scale = map(sound, 0, 900, 0, 3);

 //print values over the serial port for debugging
 Serial.print(sound);
 Serial.print("   ");
 Serial.println(scale);

//for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
switch (scale) {


case 0:
//FastLED.clear();
for (i = 0; i <  NUM_LEDS_PER_STRIP; i++) {
    leds[i] = CRGB(0, 0, 255);
    FastLED.show();
}

break;

case 1:
//FastLED.clear();
for (i = 0; i <  NUM_LEDS_PER_STRIP; i++) {
    leds[i] = CRGB(0, 100, 0);
    FastLED.show();
}

break;

case 2:
//FastLED.clear();
for (i = 0; i <  NUM_LEDS_PER_STRIP; i++) {
    leds[i] = CRGB(255, 0, 0);
    FastLED.show();
}

break;
case 3:
//FastLED.clear();
for (i = 0; i <  NUM_LEDS_PER_STRIP; i++) {
    leds[i] = CRGB(255, 255, 255);
    FastLED.show();
}

break;

default:
for (i = 0; i <  NUM_LEDS_PER_STRIP; i++) {
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();  
  }

break;

}
}
