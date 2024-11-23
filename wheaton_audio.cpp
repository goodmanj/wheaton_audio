/* Audio processing class for robotics projects.  Capabilities:
  - Read audio samples from an I2S input (Needs an I2S-capable microcontroller such as RP2040)
  - Read audio samples from an analog input (any Arduino microcontroller)
  - Generate a sinusoidal audio sample at a given frequency
  - Play an audio sample to an I2S output
  - Detect loudness of an audio sample
  - Detect fundamental frequency of an audio sample
  - Detect loudness of a given frequency in an audio sample
To use, put this file in the folder containing
your project's .ino file, and add a line at the top of the .ino file: 
    #include "wheaton_audio.cpp"
    audio = WheatonAudio();

Author: Jason Goodman goodman_jason@wheatoncollege.edu
(C) 2024, MIT license https://opensource.org/license/mit
*/

#include "wheaton_audio.h"

void WheatonAudio::setup_analog(int pin) {
  analog_pin = pin;
  pinMode(pin,INPUT);
}

int WheatonAudio::read_analog_sample(int *sample, int n_samples, int target_sample_rate) {
  int32_t tic,start_micros,end_micros;
  int32_t target_delay_micros;
  int i;
  
  target_delay_micros = 1000000/target_sample_rate;

  tic = micros();
  for (i=0; i< n_samples; i++) {
    start_micros = micros();
    sample[i] = analogRead(analog_pin);
    end_micros = micros();
    if (end_micros < (target_delay_micros + start_micros)) {
      delayMicroseconds(target_delay_micros + start_micros - end_micros );
    }
  }
  return (1000000*n_samples)/(micros() - tic);  // sample rate = (# samples/ us) * (1000000 us/s)
}

float WheatonAudio::find_average(int *sample, int n_samples) {
  int32_t avg = 0;
  for (int i = 0; i<n_samples; i++) {
    avg += int32_t(sample[i]);
  }
  return avg/n_samples;
}

float WheatonAudio::find_amplitude(int *sample, int n_samples) {
  float amp, avg;
  avg = find_average(sample,n_samples);
  for (int i = 0; i<n_samples; i++) {    
    amp += (sample[i]-avg)*(sample[i]-avg);
  }
  return sqrt(amp/n_samples);
}

float WheatonAudio::find_frequency(int *sample, int n_samples, int samplerate) {
  int i;
  int this_sample,prev_sample;
  float avg;
  int zero_crossings=0;
  float freq;
  avg = find_average(sample, n_samples);

  this_sample = sample[0]-avg;
  for (i=0; i< n_samples; i++) {
    prev_sample = this_sample;
    this_sample = sample[i]-avg;
    if (((this_sample>0) && (prev_sample<0)) || ((this_sample<0) && (prev_sample>0))) {
      zero_crossings +=1;
    }    
  }
  freq = float(samplerate)*zero_crossings/2 / n_samples;
  return freq;
}

//int WheatonAudio::int find_amp_of_frequency(int *sample, int n_samples, int samplerate,int frequency){
  // Discrete Fourier transform 
//}
