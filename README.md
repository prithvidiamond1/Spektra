# Spektra

Real-time audio visualizer made using [miniaudio](https://github.com/mackron/miniaudio), [Imgui](https://github.com/ocornut/imgui), [IIR1](https://github.com/berndporr/iir1), [Implot](https://github.com/epezent/implot) and [FFTW](https://github.com/FFTW/fftw3) libraries. 

Currently supports 2 forms of audio analysis:
 * Fractional Octave Analysis - achieved using bandpass filters
 * Fourier Analysis - achieved using 1-dimensional Fast-Fourier Transform

Audio sources for visualization are currently limited to only WASAPI loopback (Windows) audio.

**THIS PROJECT CURRENTLY ONLY WORKS FOR WINDOWS (Tested for Windows 10 or newer)**

### LICENSE

Due to the use of FFTW, this code is currently licensed under the terms of the GPL-2.0 license.


