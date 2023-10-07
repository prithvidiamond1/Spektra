#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "implot.h"
#include "imgui_internal.h"
#include "../OpenGL/Imgui/imgui_impl_glfw.h"
#include "../OpenGL/Imgui/imgui_impl_opengl3.h"

#include "../AudioLoopBack/ALB.h"
#include "../BandAnalyzers/Octave/Octave.h"
#include "../BandAnalyzers/FFT/FFT.h"

#include <string>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

class App {
private: 
	GLFWwindow* Window;

	ImVec4 ClearColor;

	AudioLoopBack ALB_Obj;

	OctaveBandAnalyser OBA_Obj;	// set filter order here

	FFTBandAnalyzer FFT_Obj;

	std::vector<float> bandCenterFreqs;

public:
	App(std::string title, int w, int h, int argc, char** argv);

	~App();

	void update();

	void run();

	ImVec2 GetWindowSize() const;
};