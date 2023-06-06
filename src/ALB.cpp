
#include "ALB.h"

void AudioLoopBack::ALB_displayVector(const std::vector<float>& inputVector)
{
	for (float value : inputVector) {
		std::cout << value << " ";
	}
	std::cout << std::endl;
}

void AudioLoopBack::FFT_complexArrToAbsoluteArr(fftwf_complex* in, int size, float* out, bool ignoreDC)
{
	int offset = ignoreDC ? 1 : 0;
	for (int i = offset; i < size; i++) {
		out[i-offset] = std::sqrt(std::pow(in[i][0], 2) + std::pow(in[i][1], 2));
	}
}

void AudioLoopBack::ALB_dataCallback(ma_device* device, void* output, const void* input, ma_uint32 frameCount)
{
	device->pUserData = const_cast<void*>(input);

	(void)output;
}

void AudioLoopBack::ALB_start()
{
	ma_device_config ALB_deviceConfig = ma_device_config_init(ma_device_type_loopback);
	ALB_deviceConfig.capture.pDeviceID = NULL; /*change this to capture from a different device*/
	ALB_deviceConfig.capture.format = ALB_captureFormat;
	ALB_deviceConfig.capture.channels = ALB_captureChannelCount;
	ALB_deviceConfig.sampleRate = ALB_captureSampleRate;
	ALB_deviceConfig.dataCallback = ALB_dataCallback;
	ALB_deviceConfig.pUserData = ALB_rawData;
	ALB_deviceConfig.periodSizeInMilliseconds = ALB_callbackPeriodMs;

	/* Loopback mode is currently only supported on WASAPI. */
	ma_backend backends[] = {
		ma_backend_wasapi
	};

	ma_result ALB_result = ma_device_init_ex(backends, sizeof(backends) / sizeof(backends[0]), NULL, &ALB_deviceConfig, &ALB_device);
	if (ALB_result != MA_SUCCESS) {
		// Error
		std::cout << "Error: MA_DEVICE_INIT failed!" << std::endl;
		return;
	}

	ALB_result = ma_device_start(&ALB_device);
	if (ALB_result != MA_SUCCESS) {
		ma_device_uninit(&ALB_device);
		// Error
		std::cout << "Error: MA_DEVICE_START failed!" << std::endl;
		return;
	}
}

void AudioLoopBack::ALB_FFTdata(float* leftChFFTData, float* rightChFFTData)
{
	// EVENTS HERE MUST OCCUR AS PART OF A LOOP

	// Previous main loop was from here to the bottom of this method
	void* ALB_deinterleavedLeftData = new float[ALB_frameCountPerCallback];
	void* ALB_deinterleavedRightData = new float[ALB_frameCountPerCallback];

	void** ALB_deinterleavedData = new void* [ALB_captureChannelCount];
	ALB_deinterleavedData[0] = ALB_deinterleavedLeftData;
	ALB_deinterleavedData[1] = ALB_deinterleavedRightData;

	ma_deinterleave_pcm_frames(ALB_captureFormat, ALB_captureChannelCount, ALB_frameCountPerCallback, ALB_device.pUserData, ALB_deinterleavedData);

	float* ALB_castedLeftData = static_cast<float*>(ALB_deinterleavedLeftData);
	float* ALB_castedRightData = static_cast<float*>(ALB_deinterleavedRightData);

	/*std::vector<float> ALB_leftChannelData = std::vector<float>(ALB_castedLeftData, ALB_castedLeftData + ALB_frameCountPerCallback);
	std::vector<float> ALB_rightChannelData = std::vector<float>(ALB_castedRightData, ALB_castedRightData + ALB_frameCountPerCallback);*/

	/*std::cout << "Left channel sample count: " << ALB_leftChannelData.size() << std::endl;
	ALB_displayVector(ALB_leftChannelData);
	std::cout << std::endl;

	std::cout << "Right channel sample count: " << ALB_rightChannelData.size() << std::endl;
	ALB_displayVector(ALB_rightChannelData);
	std::cout << std::endl;*/

	// Take FFT of both Left and Right channel data
	fftwf_complex* leftChannelFFTOut = new fftwf_complex[(ALB_frameCountPerCallback / 2) + 1];
	fftwf_complex* rightChannelFFTOut = new fftwf_complex[(ALB_frameCountPerCallback / 2) + 1];

	// fft execution for Left channel data
	fftwf_plan fftwLeftChannelPlan = fftwf_plan_dft_r2c_1d(ALB_frameCountPerCallback, ALB_castedLeftData, leftChannelFFTOut, FFTW_PRESERVE_INPUT);
	fftwf_execute(fftwLeftChannelPlan);
	fftwf_destroy_plan(fftwLeftChannelPlan);

	// fft execution for Right channel data
	fftwf_plan fftwRightChannelPlan = fftwf_plan_dft_r2c_1d(ALB_frameCountPerCallback, ALB_castedRightData, rightChannelFFTOut, FFTW_PRESERVE_INPUT);
	fftwf_execute(fftwRightChannelPlan);
	fftwf_destroy_plan(fftwRightChannelPlan);

	// Absolute value of ffts for both channels
	float* leftChannelFFTAbs = new float[ALB_frameCountPerCallback / 2];
	float* rightChannelFFTAbs = new float[ALB_frameCountPerCallback / 2];

	FFT_complexArrToAbsoluteArr(leftChannelFFTOut, (ALB_frameCountPerCallback / 2) + 1, leftChannelFFTAbs, true);
	FFT_complexArrToAbsoluteArr(rightChannelFFTOut, (ALB_frameCountPerCallback / 2) + 1, rightChannelFFTAbs, true);

	// copy to output arrays
	for (int i = 0; i < (ALB_frameCountPerCallback / 2); i++) {
		leftChFFTData[i] = leftChannelFFTAbs[i];
		rightChFFTData[i] = rightChannelFFTAbs[i];
	}

	delete[] leftChannelFFTAbs;
	delete[] rightChannelFFTAbs;

	delete[] leftChannelFFTOut;
	delete[] rightChannelFFTOut;

	delete[] ALB_deinterleavedData;
	delete[] ALB_deinterleavedLeftData;
	delete[] ALB_deinterleavedRightData;
}

void AudioLoopBack::ALB_finish()
{
	ma_device_uninit(&ALB_device);
}
