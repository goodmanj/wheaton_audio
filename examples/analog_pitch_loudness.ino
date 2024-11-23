/* 

This example uses the wheaton_audio library, any Arduino, and an analog microphone 
to detect pitch and loudness.  The output is printed to the serial monitor, and can be 
graphed using the Serial Plotter tool.

Materials:
  Arduino Uno
  Electret Microphone with amplifier: https://www.adafruit.com/product/1713 
  Wires and breadboard

Wiring:
  Arduino 5V 	→ mic Vdd
  Arduino GND 	→ mic GND
  Arduino A0 	→ mic Out
  mic Gain	→ mic Vdd

  Author: Jason Goodman goodman_jason@wheatoncollege.edu
  (C) 2024, MIT license https://opensource.org/license/mit
*/

#define SAMPLE_LENGTH 400   // Length of stored audio sample

#define MIC_PIN A0
#include "wheaton_audio.h"

WheatonAudio audio;

void setup() {
  Serial.begin(115200);
  audio.setup_analog(A0);    // Connect Wheaton Audio to analog pin A0
}

void loop() {
  int sample[SAMPLE_LENGTH];  // Storage for audio samples
  int sample_rate;
  float amplitude,frequency;

  // Record audio with a target sample rate of 10,000 samples/second
  sample_rate = audio.read_analog_sample(sample, SAMPLE_LENGTH,10000);
  amplitude = audio.find_amplitude(sample, SAMPLE_LENGTH);  // Calculate loudness
  frequency = audio.find_frequency(sample, SAMPLE_LENGTH, sample_rate);  // Calculate pitch
  Serial.print(amplitude*10); // Print results to serial port
  Serial.print(",");
  Serial.println(frequency);
  delay(10);
}