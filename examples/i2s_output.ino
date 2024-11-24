/*
   Play audio on an I2S amplifier

   This uses a Raspberry Pi Pico and an I2S amplifier to play a sinusoidal tone 
   when a button is pressed.

   For the Adfruit I2S amplifier microphone (https://www.adafruit.com/product/3006),
   connect the pins as follows:
    Amplifier - Pico
      DIN <- GPIO22   (Pin 29)
      BCLK <- GPIO20  (Pin 26)
      LRC <- GPIO21   (Pin 27)
      GND <-> GND     (Pin 38)
      Vin  <-> 3V3OUT (Pin 36)

  Button uses the Pico's internal pullup resistors:
    Button -> GPIO0   (Pin 1 )
    Button -> GND     (Pin 38)

  Author: Jason Goodman goodman_jason@wheatoncollege.edu
  (C) 2024, MIT license https://opensource.org/license/mit

  Uses code from SimpleTone by Earle F. Philhower, III
  (https://github.com/earlephilhower/arduino-pico/tree/master/libraries/I2S/examples/SimpleTone)
*/

#define SAMPLE_LENGTH 1600   // Length of stored audio sample
#define SAMPLE_RATE 16000
#define DATA_PIN 22
#define BCLK_PIN 20

#define BUTTON_PIN 0

#include "wheaton_audio.h"

WheatonAudio audio;

int sample[SAMPLE_LENGTH];  // Storage for audio samples
float amplitude = 2000;
float frequency = 800;

void setup() {
  int i;
  double sample_dt = 1./SAMPLE_RATE;

  audio.setup_i2s_output(DATA_PIN,BCLK_PIN); // Connect Wheaton Audio to i2S (RP2040 only)
  
  // Create a sinusoidal wave
  for (i = 0; i<SAMPLE_LENGTH; i++) {
    sample[i]  = int(amplitude*sin(2*PI*frequency*i*sample_dt));
  }
  pinMode(BUTTON_PIN,INPUT_PULLDOWN);
}

void loop() {
  if (digitalRead(BUTTON_PIN)) {
    audio.play_i2s(sample, SAMPLE_LENGTH);
  } else {
    delay(10);
  }
}

