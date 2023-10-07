#pragma once

#include "fftw3.h"

#include <vector>
#include <cmath>
#include <algorithm>

struct FreqBandIndexRange {
	int startIndex;
	int endIndex; // inclusive
};

class FFTBandAnalyzer {
private:
	int fftSize;

	int sampleRate;
	int bandsPerOctave;

	float lowerLimitOfFreqRange;
	float upperLimitOfFreqRange;
	float refFrequency;

	float fftRes; // fft resolution

	std::vector<float> centerFreqsOfBands;
	std::vector<std::vector<int>> customBandsToBinsMap;

	fftwf_plan fftPlan;

public:

	FFTBandAnalyzer();
	~FFTBandAnalyzer();

	void setParams(int fftSize, int sampleRate, int bandsPerOctave, float lowerLimitOfFreqRange,
		float upperLimitOfFreqRange, float refFrequency = 1000.0f);

	std::vector<float> getCenterFreqsOfBands();

	void analyseFrames(std::vector<float>& inputFrames, std::vector<float>& outputVals);
};