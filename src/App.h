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
};