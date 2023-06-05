#include "App.h"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
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

    glfwSetWindowTitle(Window, title.c_str());

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    
    ClearColor = ImVec4(0.15f, 0.16f, 0.21f, 1.00f);
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
    // allocate arrays for left and right channel FFT data
    float* leftChFFTData = new float[(ALB_Obj.ALB_frameCountPerCallback) / 2];
    float* rightChFFTData = new float[(ALB_Obj.ALB_frameCountPerCallback) / 2];

    ALB_Obj.ALB_FFTdata(leftChFFTData, rightChFFTData);

    //// Generate frequency values for use as x-axis
    //int* frequencies = new int[(ALB_Obj.ALB_frameCountPerCallback) / 2];
    //for (int i = 0; i < (ALB_Obj.ALB_frameCountPerCallback) / 2; i++) {
    //    frequencies[i] = i + 1;
    //}

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
        ImPlot::SetupAxes("Frequency (Hz)", "Amplitude");
        // Set Axes Limits here - IGNORE for now

        ImPlot::PlotLine("LeftAmplitudeCurve", leftChFFTData, (ALB_Obj.ALB_frameCountPerCallback/2), 1, 1);

        ImPlot::EndPlot();
    }

    ImGui::EndChild();

    // Right Channel graph
    ImGui::BeginChild("RightChannelSpectrumSection", ImVec2(-1, -1));
    ImGui::Text("Right Channel Spectrum");
    ImGui::Separator();

    // plot Left Channel data
    if (ImPlot::BeginPlot("RightChannelSpectrumPlot", ImVec2(-1, -1))) {
        ImPlot::SetupAxes("Frequency (Hz)", "Amplitude");
        // Set Axes Limits here - IGNORE for now

        ImPlot::PlotLine("RightAmplitudeCurve", rightChFFTData, (ALB_Obj.ALB_frameCountPerCallback / 2), 1, 1);

        ImPlot::EndPlot();
    }

    ImGui::EndChild();
    ImGui::End();
    
    delete[] leftChFFTData;
    delete[] rightChFFTData;
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
