#include "Octave.h"

OctaveBandAnalyser::OctaveBandAnalyser() {}

void OctaveBandAnalyser::setParams(int filterOrder, int sampleRate, int bandsPerOctave, float lowerLimitOfFreqRange,
	float upperLimitOfFreqRange, float refFrequency)
{
	this->filterOrder = filterOrder;
	this->sampleRate = sampleRate;
	this->bandsPerOctave = bandsPerOctave;
	this->lowerLimitOfFreqRange = lowerLimitOfFreqRange;
	this->upperLimitOfFreqRange = upperLimitOfFreqRange;
	this->refFrequency = refFrequency;
}

void OctaveBandAnalyser::setup()
{
	int lowerN = (int)std::roundf(this->bandsPerOctave * std::log2f(this->lowerLimitOfFreqRange / this->refFrequency));
	int upperN = (int)std::roundf(this->bandsPerOctave * std::log2f(this->upperLimitOfFreqRange / this->refFrequency));

	for (int n = lowerN; n <= upperN; n++) {
		float centerFreq = this->refFrequency * std::powf(2, (n / bandsPerOctave));
		this->centerFreqsOfBands.push_back(centerFreq);
	}
}

std::vector<float> OctaveBandAnalyser::getCenterFreqsOfBands()
{
	return this->centerFreqsOfBands;
}

void OctaveBandAnalyser::analyseFrames(std::vector<float>& inputFrames, std::vector<float>& outputVals)
{
	std::vector<float> filteredRMS;
	for (int i = 0; i < this->centerFreqsOfBands.size(); i++) {
		float centerFreqOfBand = this->centerFreqsOfBands[i];
		float bandConst = std::sqrtf(std::powf(2, (1.0f / this->bandsPerOctave)));
		float lowerCutoffFreqOfBand = centerFreqOfBand / bandConst;
		float upperCutoffFreqOfBand = centerFreqOfBand * bandConst;

		this->bandPassFilter.setup(this->filterOrder, this->sampleRate, centerFreqOfBand, upperCutoffFreqOfBand - lowerCutoffFreqOfBand);
		
		double filteredMS = 0;
		for (int i = 0; i < inputFrames.size(); i++) {
			float filteredFrame = this->bandPassFilter.filter(inputFrames[i]);
			filteredMS += std::pow(filteredFrame, 2);
		}

		double rms = std::sqrt(filteredMS);

		filteredRMS.push_back(rms);
	}

	outputVals = std::vector<float>(filteredRMS.data(), filteredRMS.data() + filteredRMS.size());
}