#include "arduinoFFT.h"
#include <FastLED.h>
#define SAMPLES 128             //Must be a power of 2
#define SAMPLING_FREQUENCY 10000 //Hz, must be less than 10000 due to ADC
CRGB leds[60];
arduinoFFT FFT = arduinoFFT();
 
unsigned int sampling_period_us;
unsigned long microseconds;
 
double vReal[SAMPLES];
double vImag[SAMPLES];

double brightness;
int sound;
int scale;
void setup() {
    Serial.begin(115200);
     FastLED.addLeds<WS2812, 10,GRB>(leds, 60);
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));

}
 
void loop() {

    for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();    //Overflows after around 70 minutes!
     
        vReal[i] = analogRead(0);
        vImag[i] = 0;
     
        while(micros() < (microseconds + sampling_period_us)){
        
    }
    }
 
    /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    
    
    for(int i=0; i<60; i++)
    {
      //Serial.println(vReal[i]);
      scale = map(vReal[i+2], 0, 450, 0, 5);
      if(scale<=2){
        leds[i]=CRGB(0,255,0);
      }else if(scale<=4){
        leds[i]=CRGB(255,255,0);
      }else{
        leds[i]=CRGB(255,0,0);
      }
      brightness=(vReal[i+2]*256)/20000;
      brightness=256-brightness;
      leds[i].fadeLightBy(brightness);
    }
    
    FastLED.show();
}


