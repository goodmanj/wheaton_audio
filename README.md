# Wheaton Audio Library

Audio processing class for robotics projects.  Capabilities:
  - Read audio samples from an I2S input (Needs an I2S-capable microcontroller such as RP2040)
  - Read audio samples from an analog input (any Arduino microcontroller)
  - Generate a sinusoidal audio sample at a given frequency
  - Play an audio sample to an I2S output
  - Detect loudness of an audio sample
  - Detect fundamental frequency of an audio sample
  - Detect loudness of a given frequency in an audio sample (Future)
To use, put this file in the folder containing
your project's .ino file, and add a line at the top of the .ino file: 
    
```
  #include "wheaton_audio.cpp"
  audio = WheatonAudio();
```

Author: Jason Goodman goodman_jason@wheatoncollege.edu
(C) 2024, MIT license https://opensource.org/license/mit