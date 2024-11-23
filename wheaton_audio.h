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

#ifdef ARDUINO_ARCH_RP2040
#include <I2S.h>
#endif

#include <Arduino.h>

class WheatonAudio {
  public:
    void setup_analog(int pin);
    int read_analog_sample(int *sample,int n_samples, int target_sample_rate);
    float find_amplitude(int *sample, int n_samples);
    float find_average(int *sample, int n_samples);
    float find_frequency(int *sample, int n_samples, int samplerate);
    int find_amp_of_frequency(int *sample, int n_samples, int samplerate,int frequency);

#ifdef ARDUINO_ARCH_RP2040
    void setup_i2s_input(int dataPin, int bclkPin);
    void setup_i2s_output(int dataPin, int bclkPin);
    int read_i2s_sample(int *sample, int n_samples);
    void play_i2s(int *sample, int n_samples);
#endif
  private:
    int analog_pin = -1;
#ifdef ARDUINO_ARCH_RP2040
    I2S i2s_input;
    int i2s_input_samplerate = 16000;
    I2S i2s_output;
    int i2s_output_samplerate = 16000;
#endif
};