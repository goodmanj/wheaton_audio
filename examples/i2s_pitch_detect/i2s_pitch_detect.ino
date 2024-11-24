/*
   I2S microphone pitch detection
   
   This uses a Raspberry Pi Pico and an I2S MEMS microphone to detect pitch and loudness.  
   The output is printed to the serial monitor, and can be graphed using the Serial Plotter 
   tool.

   For an Adfruit I2S MEMS microphone (https://www.adafruit.com/product/3421),
   connect the pins as follows:
      DOUT -> GPIO0
      BCLK <- GPIO1
      LRCL <- GPIO2  # LRCLK = BCLK + 1
      GND <-> GND
      3V  <-> 3V3OUT

  Author: Jason Goodman goodman_jason@wheatoncollege.edu
  (C) 2024, MIT license https://opensource.org/license/mit

  Uses code from I2SInput by Earle F. Philhower, III
  (https://github.com/earlephilhower/arduino-pico/tree/master/libraries/I2S/examples/I2SInput)
*/

#define SAMPLE_LENGTH 400   // Length of stored audio sample
#define DATA_PIN 0
#define BCLK_PIN 1

#include "wheaton_audio.h"

WheatonAudio audio;

void setup() {
  Serial.begin(115200);
  audio.setup_i2s_input(DATA_PIN,BCLK_PIN); // Connect Wheaton Audio to i2S (RP2040 only)
}

void loop() {
  int sample[SAMPLE_LENGTH];  // Storage for audio samples
  int sample_rate;
  float amplitude,frequency;

  // Record audio 
  sample_rate = audio.read_i2s_sample(sample, SAMPLE_LENGTH);
  amplitude = audio.find_amplitude(sample, SAMPLE_LENGTH);  // Calculate loudness
  frequency = audio.find_frequency(sample, SAMPLE_LENGTH, sample_rate);  // Calculate pitch
  Serial.print(amplitude); // Print results to serial port
  Serial.print(",");
  Serial.println(frequency);
  delay(10);
}