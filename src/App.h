#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "implot.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "ALB.h";

#include <string>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

class App {
private: 
	GLFWwindow* Window;

	ImVec4 ClearColor;

	AudioLoopBack ALB_Obj;


public:
	App(std::string title, int w, int h, int argc, char** argv);

	~App();

	void update();

	void run();

	ImVec2 GetWindowSize() const;
};