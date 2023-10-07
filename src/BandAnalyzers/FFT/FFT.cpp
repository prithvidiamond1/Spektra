#include "FFT.h"

FFTBandAnalyzer::FFTBandAnalyzer()
{
}

FFTBandAnalyzer::~FFTBandAnalyzer()
{
}

void FFTBandAnalyzer::setParams(int fftSize, int sampleRate, int bandsPerOctave, float lowerLimitOfFreqRange, float upperLimitOfFreqRange, float refFrequency)
{
	this->fftSize = fftSize;
	this->sampleRate = sampleRate;
	this->bandsPerOctave = bandsPerOctave;
	this->lowerLimitOfFreqRange = lowerLimitOfFreqRange;
	this->upperLimitOfFreqRange = upperLimitOfFreqRange;
	this->refFrequency = refFrequency;

	this->fftRes = this->sampleRate / (float)this->fftSize;

	int lowerN = (int)std::roundf(this->bandsPerOctave * std::log2f(this->lowerLimitOfFreqRange / this->refFrequency));
	int upperN = (int)std::roundf(this->bandsPerOctave * std::log2f(this->upperLimitOfFreqRange / this->refFrequency));

	for (int n = lowerN; n <= upperN; n++) {
		float centerFreq = this->refFrequency * std::powf(2, ((float)n / bandsPerOctave));
		this->centerFreqsOfBands.push_back(centerFreq);
	}

	int startIndexOffset = 1; // to ignore 0 since it is 0hz bin (DC)
	float bandConst = std::sqrtf(std::powf(2, (1.0f / this->bandsPerOctave)));

	//float centerFreq : this->centerFreqsOfBands

	for (int i = 0; i < this->centerFreqsOfBands.size() - 1; i++) {
		float centerFreq = this->centerFreqsOfBands[i];
		float nextCenterFreq = this->centerFreqsOfBands[i + 1];

		float lowerFreq = centerFreq / bandConst;
		//float higherFreq = centerFreq * bandConst;
		float higherFreq = nextCenterFreq / bandConst;

		//int lowerIndex = startIndexOffset + (int)(lowerFreq / this->fftRes);
		//int higherIndex = startIndexOffset + (int)(higherFreq / this->fftRes);

		int lowerIndex = (int)(lowerFreq / this->fftRes);
		int higherIndex = (int)(higherFreq / this->fftRes);

		/*if (higherIndex >= (this->fftSize / 2) + 1) {
			higherIndex = (this->fftSize / 2) + 1;
		}*/

		std::vector<int> bandIndexRange{ lowerIndex, higherIndex };

		this->customBandsToBinsMap.push_back(bandIndexRange);
	}

	float lowerFreq = this->centerFreqsOfBands[this->centerFreqsOfBands.size() - 1] / bandConst;

	//int lowerIndex = startIndexOffset + (int)(lowerFreq / this->fftRes);
	int lowerIndex = (int)(lowerFreq / this->fftRes);
	int higherIndex = (this->fftSize / 2);

	std::vector<int> bandIndexRange{ lowerIndex, higherIndex };

	this->customBandsToBinsMap.push_back(bandIndexRange);
}

std::vector<float> FFTBandAnalyzer::getCenterFreqsOfBands()
{
	return this->centerFreqsOfBands;
}

void FFTBandAnalyzer::analyseFrames(std::vector<float>& inputFrames, std::vector<float>& outputVals)
{
	// perform fft

	/*std::transform(inputFrames.begin(), inputFrames.end(), inputFrames.begin(),
		[](float x) {
			return std::isnan(x) ? 0.0f : x;
		});*/

	fftwf_complex* fftOut = new fftwf_complex[(this->fftSize / 2) + 1];

	this->fftPlan = fftwf_plan_dft_r2c_1d(this->fftSize, const_cast<float*>(inputFrames.data()), fftOut, FFTW_ESTIMATE);
	fftwf_execute(this->fftPlan);
	fftwf_destroy_plan(this->fftPlan);

	for (std::vector<int> bandIndexRange : this->customBandsToBinsMap) {
		int bandPower = 0; // sum of bin energies

		for (int i = bandIndexRange[0]; i <= bandIndexRange[1]; i++) {
			float binValReal = fftOut[i][0];
			float binValComplex = fftOut[i][1];

			float binPower = std::powf(binValReal, 2) + std::powf(binValComplex, 2);

			bandPower += binPower;
		}

		float bandAmplitude = std::sqrtf(bandPower); // rms amplitude

		const float floorVal = 1e0;
		float dBFS = -((20 * std::log10f(bandAmplitude + floorVal)) - 20 * std::log10f(floorVal));

		outputVals.push_back(dBFS);
	}

	delete[] fftOut;
}


