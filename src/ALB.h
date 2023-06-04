#pragma once

#include "miniaudio.h"
#include "fftw3.h"
#include "matplot/matplot.h"

#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>

class AudioLoopBack {
private:
	void* ALB_rawData;
	ma_device ALB_device;

	static void ALB_displayVector(const std::vector<float>& inputVector);

	static void FFT_complexArrToAbsoluteArr(fftwf_complex* in, int size, float* out, bool ignoreDC);

public:
	const int ALB_callbackPeriodMs = 1000;
	const int ALB_captureSampleRate = 48000;
	const int ALB_captureChannelCount = 2;
	const ma_format ALB_captureFormat = ma_format_f32;
	const ma_uint32 ALB_frameCountPerCallback = ALB_captureSampleRate / (1000 / ALB_callbackPeriodMs);

	static void ALB_dataCallback(ma_device* ALB_device, void* ALB_output, const void* ALB_input, ma_uint32 frameCount);

	void ALB_start();
	void ALB_FFTdata(float* leftChFFTData, float* rightChFFTData);
	void ALB_finish();
};