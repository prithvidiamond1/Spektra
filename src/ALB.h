#pragma once

#include "miniaudio.h"

#include <iostream>
#include <vector>
#include <cstdio>

class AudioLoopBack {
private:
	const int ALB_callbackPeriodMs = 1;
	const int ALB_captureSampleRate = 48000;
	const int ALB_captureChannelCount = 2;
	const ma_format ALB_captureFormat = ma_format_f32;
	const ma_uint32 ALB_latestFrameCount = ALB_captureSampleRate/(1000/ALB_callbackPeriodMs);

	void* ALB_rawData;
	ma_device ALB_device;

	static void ALB_displayVector(const std::vector<float>& inputVector);

public:
	static void ALB_dataCallback(ma_device* ALB_device, void* ALB_output, const void* ALB_input, ma_uint32 frameCount);

	void ALB_contextAndDeviceInit();
	void ALB_run();
};