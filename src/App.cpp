#include "App.h"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void App::StyeColorsApp()
{
	static const ImVec4 bg_dark = ImVec4(0.15f, 0.16f, 0.21f, 1.00f);
	static const ImVec4 bg_mid = ImVec4(0.20f, 0.21f, 0.27f, 1.00f);
	static const ImVec4 accent_dark = ImVec4(0.292f, 0.360f, 0.594f, 1.000f);
	static const ImVec4 accent_light = ImVec4(0.409f, 0.510f, 0.835f, 1.000f);
	static const ImVec4 active = ImVec4(0.107f, 0.118f, 0.157f, 1.000f);
	static const ImVec4 attention = ImVec4(0.821f, 1.000f, 0.000f, 1.000f);

	auto& style = ImGui::GetStyle();
	style.WindowPadding = { 6, 6 };
	style.FramePadding = { 6, 3 };
	style.CellPadding = { 6, 3 };
	style.ItemSpacing = { 6, 6 };
	style.ItemInnerSpacing = { 6, 6 };
	style.ScrollbarSize = 16;
	style.GrabMinSize = 8;
	style.WindowBorderSize = style.ChildBorderSize = style.PopupBorderSize = style.TabBorderSize = 0;
	style.FrameBorderSize = 1;
	style.WindowRounding = style.ChildRounding = style.PopupRounding = style.ScrollbarRounding = style.GrabRounding = style.TabRounding = 4;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(0.89f, 0.89f, 0.92f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.38f, 0.45f, 0.64f, 1.00f);
	colors[ImGuiCol_WindowBg] = bg_mid;
	colors[ImGuiCol_ChildBg] = ImVec4(0.20f, 0.21f, 0.27f, 0.00f);
	colors[ImGuiCol_PopupBg] = bg_mid;
	colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.06f);
	colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.02f);
	colors[ImGuiCol_FrameBgHovered] = accent_light;
	colors[ImGuiCol_FrameBgActive] = active;
	colors[ImGuiCol_TitleBg] = accent_dark;
	colors[ImGuiCol_TitleBgActive] = accent_dark;
	colors[ImGuiCol_TitleBgCollapsed] = accent_dark;
	colors[ImGuiCol_MenuBarBg] = accent_dark;
	colors[ImGuiCol_ScrollbarBg] = bg_mid;
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.89f, 0.89f, 0.93f, 0.27f);
	colors[ImGuiCol_ScrollbarGrabHovered] = accent_light;
	colors[ImGuiCol_ScrollbarGrabActive] = active;
	colors[ImGuiCol_CheckMark] = accent_dark;
	colors[ImGuiCol_SliderGrab] = accent_dark;
	colors[ImGuiCol_SliderGrabActive] = accent_light;
	colors[ImGuiCol_Button] = accent_dark;
	colors[ImGuiCol_ButtonHovered] = accent_light;
	colors[ImGuiCol_ButtonActive] = active;
	colors[ImGuiCol_Header] = accent_dark;
	colors[ImGuiCol_HeaderHovered] = accent_light;
	colors[ImGuiCol_HeaderActive] = active;
	colors[ImGuiCol_Separator] = accent_dark;
	colors[ImGuiCol_SeparatorHovered] = accent_light;
	colors[ImGuiCol_SeparatorActive] = active;
	colors[ImGuiCol_ResizeGrip] = accent_dark;
	colors[ImGuiCol_ResizeGripHovered] = accent_light;
	colors[ImGuiCol_ResizeGripActive] = active;
	colors[ImGuiCol_Tab] = ImVec4(1.00f, 1.00f, 1.00f, 0.02f);
	colors[ImGuiCol_TabHovered] = accent_light;
	colors[ImGuiCol_TabActive] = accent_dark;
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = active;
	colors[ImGuiCol_PlotLines] = accent_light;
	colors[ImGuiCol_PlotLinesHovered] = active;
	colors[ImGuiCol_PlotHistogram] = accent_light;
	colors[ImGuiCol_PlotHistogramHovered] = active;
	colors[ImGuiCol_TableHeaderBg] = accent_dark;
	colors[ImGuiCol_TableBorderStrong] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(1.00f, 1.00f, 1.00f, 0.02f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0, 0, 0, 0);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.02f);
	colors[ImGuiCol_TextSelectedBg] = accent_light;
	colors[ImGuiCol_DragDropTarget] = attention;
	colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
#ifdef IMGUI_HAS_DOCK
	colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);
	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
#endif

	ImPlot::StyleColorsAuto();

	ImVec4* pcolors = ImPlot::GetStyle().Colors;
	pcolors[ImPlotCol_PlotBg] = ImVec4(0, 0, 0, 0);
	pcolors[ImPlotCol_PlotBorder] = ImVec4(0, 0, 0, 0);
	pcolors[ImPlotCol_Selection] = attention;
	pcolors[ImPlotCol_Crosshairs] = colors[ImGuiCol_Text];

	ImPlot::GetStyle().DigitalBitHeight = 20;

	auto& pstyle = ImPlot::GetStyle();
	pstyle.PlotPadding = pstyle.LegendPadding = { 12, 12 };
	pstyle.LabelPadding = pstyle.LegendInnerPadding = { 6, 6 };
	pstyle.LegendSpacing = { 10, 2 };
	pstyle.AnnotationPadding = { 4,2 };

	const ImU32 Dracula[] = { 4288967266, 4285315327, 4286315088, 4283782655, 4294546365, 4287429361, 4291197439, 4294830475, 4294113528, 4284106564 };
	ImPlot::GetStyle().Colormap = ImPlot::AddColormap("Dracula", Dracula, 10);
}

App::App(std::string title, int w, int h, int argc, char** argv)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        abort();
    }

    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);           // Required on Mac

    // Create window with graphics context
    Window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
    if (Window == NULL)
    {
        fprintf(stderr, "Failed to initialize GLFW window!\n");
        abort();
    }
    glfwMakeContextCurrent(Window);
    //glfwSwapInterval(1);    // Enables vsync but maybe not needed

    glfwSetWindowTitle(Window, title.c_str());

    // Glad requires you to pass a function pointer that returns the context address
        // Note: reinterpret_cast is equivalent to a c-style cast, dont use lightly, always prefer static_cast
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        unsigned int error_code = glad_glGetError();
        std::cout << "Error initializing Glad: " << error_code << std::endl; 
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Different color themes
    /*ClearColor = ImVec4(0.15f, 0.16f, 0.21f, 1.00f);
    StyeColorsApp();*/

    ImGui::StyleColorsDark();
    ImPlot::StyleColorsDark();

    OBA_Obj.setParams(2, ALB_Obj.ALB_captureSampleRate, 3, 20, 20000);

    this->bandCenterFreqs = OBA_Obj.getCenterFreqsOfBands();
    ALB_Obj.ALB_displayVector(this->bandCenterFreqs);
}

App::~App()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(Window);
    glfwTerminate();
}

void App::update()
{
    std::vector<float> leftChData, rightChData;

    ALB_Obj.ALB_getAudioData(leftChData, rightChData);

    // Process the Audio Data
    std::vector<float> leftChOut, rightChOut;

    OBA_Obj.analyseFrames(leftChData, leftChOut);
    OBA_Obj.analyseFrames(rightChData, rightChOut);

    // Draw graph
    // Set up ImGUI
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(GetWindowSize(), ImGuiCond_Always);
    ImGui::Begin("AudioLoopBackSpectrums", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    // Left Channel graph
    ImGui::BeginChild("LeftChannelSpectrumSection", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, -1));
    ImGui::Text("Left Channel Spectrum");
    ImGui::Separator();

    // plot Left Channel data
    if (ImPlot::BeginPlot("LeftChannelSpectrumPlot", ImVec2(-1,-1))) {
        ImPlot::SetupAxesLimits(16, ALB_Obj.ALB_captureSampleRate / 2, 0.001, 100);
        ImPlot::SetupAxes("Frequency (Hz)", "Amplitude (dB)");        
        ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_SymLog);
        ImPlot::SetupAxisScale(ImAxis_Y1, ImPlotScale_Log10);
        // Set Axes Limits here - IGNORE for now

        ImPlot::PlotBars("LeftAmplitudeCurve", this->bandCenterFreqs.data(), leftChOut.data(), leftChOut.size(), 1);

        ImPlot::EndPlot();
    }

    ImGui::EndChild();


    ImGui::SameLine();

    // Right Channel graph
    ImGui::BeginChild("RightChannelSpectrumSection", ImVec2(0, -1));
    ImGui::Text("Right Channel Spectrum");
    ImGui::Separator();

    // plot Right Channel data
    if (ImPlot::BeginPlot("RightChannelSpectrumPlot", ImVec2(-1, -1))) {
        ImPlot::SetupAxesLimits(16, ALB_Obj.ALB_captureSampleRate / 2, 0.001, 100);
        ImPlot::SetupAxes("Frequency (Hz)", "Amplitude (dB)");
        ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_SymLog);
        ImPlot::SetupAxisScale(ImAxis_Y1, ImPlotScale_Log10);
        // Set Axes Limits here - IGNORE for now

        ImPlot::PlotBars("RightAmplitudeCurve", this->bandCenterFreqs.data(), rightChOut.data(), rightChOut.size(), 1);

        ImPlot::EndPlot();
    }

    ImGui::EndChild();
    ImGui::End();
}

void App::run()
{
    // ALB start
    ALB_Obj.ALB_start();

    // main loop
    while (!glfwWindowShouldClose(Window))
    {
        glfwPollEvents();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        update();
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(Window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(ClearColor.x, ClearColor.y, ClearColor.z, ClearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(Window);
    }

    // ALB finish
    ALB_Obj.ALB_finish();
}

ImVec2 App::GetWindowSize() const
{
    int w, h;
    glfwGetWindowSize(Window, &w, &h);
    return ImVec2(w, h);
}
