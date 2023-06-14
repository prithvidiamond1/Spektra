#pragma once

#include "Iir.h"

#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace Iir;

class OctaveBandAnalyser {
private:
	int filterOrder;

	int sampleRate;
	int bandsPerOctave;

	float lowerLimitOfFreqRange;
	float upperLimitOfFreqRange;
	float refFrequency;

	std::vector<float> centerFreqsOfBands;

	Butterworth::BandPass<8> bandPassFilter;
public:
	OctaveBandAnalyser();	// default constructor

	void setParams(int filterOrder, int sampleRate, int bandsPerOctave, float lowerLimitOfFreqRange,
		float upperLimitOfFreqRange, float refFrequency = 1000.0f);

	void setup();

	std::vector<float> getCenterFreqsOfBands();

	void analyseFrames(std::vector<float>& inputFrames, std::vector<float>& outputVals);

};




