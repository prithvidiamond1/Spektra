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

    // App Color scheme/theme
    ImGui::StyleColorsDark();
    ImPlot::StyleColorsDark();

    OBA_Obj.setParams(2, ALB_Obj.ALB_captureSampleRate, 3, 16, 20000);

    FFT_Obj.setParams(8192, ALB_Obj.ALB_captureSampleRate, 3, 16, 20000);

    this->bandCenterFreqs = OBA_Obj.getCenterFreqsOfBands();
    ALB_Obj.ALB_displayVector(this->bandCenterFreqs);

    std::cout << "Band Count: " << this->bandCenterFreqs.size() << std::endl;
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

    // Draw graph
    // Set up ImGUI
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(GetWindowSize(), ImGuiCond_Always);
    ImGui::Begin("AudioLoopBackSpectrums", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    ImGui::BeginChild("Spectra Plots");
    if (ImGui::BeginTabBar("Plots")) {
        if (ImGui::BeginTabItem("Fractional Octave")) {
            OBA_Obj.analyseFrames(leftChData, leftChOut);
            OBA_Obj.analyseFrames(rightChData, rightChOut);


            // Left Channel graph
            ImGui::BeginChild("LeftChannelSpectrumSection", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, -1));
            ImGui::Text("Left Channel Spectrum");
            ImGui::Separator();

            // plot Left Channel data
            if (ImPlot::BeginPlot("Left Channel Spectrum Plot", ImVec2(-1, -1))) {
                ImPlot::SetupAxesLimits(12, ALB_Obj.ALB_captureSampleRate / 2, -100, 0);
                ImPlot::SetupAxes("Frequency (Hz)", "Amplitude (dB)", 0, ImPlotAxisFlags_Invert);
                ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_SymLog);
                //ImPlot::SetupAxisScale(ImAxis_Y1, ImPlotScale_Log10);

                ImPlot::PlotBars("Left Amplitude Curve", this->bandCenterFreqs.data(), leftChOut.data(), leftChOut.size(), 1);

                ImPlot::EndPlot();
            }
            ImGui::EndChild();

            ImGui::SameLine();

            // Right Channel graph
            ImGui::BeginChild("RightChannelSpectrumSection", ImVec2(0, -1));
            ImGui::Text("Right Channel Spectrum");
            ImGui::Separator();

            // plot Right Channel data
            if (ImPlot::BeginPlot("Right Channel Spectrum Plot", ImVec2(-1, -1))) {
                ImPlot::SetupAxesLimits(12, ALB_Obj.ALB_captureSampleRate / 2, -100, 0);
                ImPlot::SetupAxes("Frequency (Hz)", "Amplitude (dB)", 0, ImPlotAxisFlags_Invert);
                ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_SymLog);
                //ImPlot::SetupAxisScale(ImAxis_Y1, ImPlotScale_Log10);

                ImPlot::PlotBars("Right Amplitude Curve", this->bandCenterFreqs.data(), rightChOut.data(), rightChOut.size(), 1);

                ImPlot::EndPlot();
            }
            ImGui::EndChild();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Fourier")) {


            FFT_Obj.analyseFrames(leftChData, leftChOut);
            FFT_Obj.analyseFrames(rightChData, rightChOut);

            // Left Channel graph
            ImGui::BeginChild("LeftFFTChannelSpectrumSection", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, -1));
            ImGui::Text("Left Channel Spectrum");
            ImGui::Separator();

            // plot Left Channel data
            if (ImPlot::BeginPlot("Left Channel Spectrum Plot", ImVec2(-1, -1))) {
                ImPlot::SetupAxesLimits(12, ALB_Obj.ALB_captureSampleRate / 2, -80, 0);
                ImPlot::SetupAxes("Frequency (Hz)", "Amplitude (dB)", 0, ImPlotAxisFlags_Invert);
                ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_SymLog);
                //ImPlot::SetupAxisScale(ImAxis_Y1, ImPlotScale_Log10);

                ImPlot::PlotBars("Left Amplitude Curve", this->bandCenterFreqs.data(), leftChOut.data(), leftChOut.size(), 1);

                ImPlot::EndPlot();
            }
            ImGui::EndChild();

            ImGui::SameLine();

            // Right Channel graph
            ImGui::BeginChild("RightFFTChannelSpectrumSection", ImVec2(0, -1));
            ImGui::Text("Right Channel Spectrum");
            ImGui::Separator();

            // plot Right Channel data
            if (ImPlot::BeginPlot("Right Channel Spectrum Plot", ImVec2(-1, -1))) {
                ImPlot::SetupAxesLimits(12, ALB_Obj.ALB_captureSampleRate / 2, -80, 0);
                ImPlot::SetupAxes("Frequency (Hz)", "Amplitude (dB)", 0, ImPlotAxisFlags_Invert);
                ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_SymLog);
                //ImPlot::SetupAxisScale(ImAxis_Y1, ImPlotScale_Log10);

                ImPlot::PlotBars("Right Amplitude Curve", this->bandCenterFreqs.data(), rightChOut.data(), rightChOut.size(), 1);

                ImPlot::EndPlot();
            }
            ImGui::EndChild();
            ImGui::EndTabItem();
        }
    }
    ImGui::EndTabBar();
    ImGui::EndChild();

//------------------------------------------------

    //// Left Channel graph
    //ImGui::BeginChild("LeftChannelSpectrumSection", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, -1));
    //ImGui::Text("Left Channel Spectrum");
    //ImGui::Separator();

    //// plot Left Channel data
    //if (ImPlot::BeginPlot("LeftChannelSpectrumPlot", ImVec2(-1,-1))) {
    //    ImPlot::SetupAxesLimits(12, ALB_Obj.ALB_captureSampleRate / 2, -100, 0);
    //    ImPlot::SetupAxes("Frequency (Hz)", "Amplitude (dB)", 0, ImPlotAxisFlags_Invert);
    //    ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_SymLog);
    //    //ImPlot::SetupAxisScale(ImAxis_Y1, ImPlotScale_Log10);

    //    ImPlot::PlotBars("LeftAmplitudeCurve", this->bandCenterFreqs.data(), leftFFTChOut.data(), leftFFTChOut.size(), 1);

    //    ImPlot::EndPlot();
    //}

    //ImGui::EndChild();


    //ImGui::SameLine();

    //// Right Channel graph
    //ImGui::BeginChild("RightChannelSpectrumSection", ImVec2(0, -1));
    //ImGui::Text("Right Channel Spectrum");
    //ImGui::Separator();

    //// plot Right Channel data
    //if (ImPlot::BeginPlot("RightChannelSpectrumPlot", ImVec2(-1, -1))) {
    //    ImPlot::SetupAxesLimits(12, ALB_Obj.ALB_captureSampleRate / 2, -100, 0);
    //    ImPlot::SetupAxes("Frequency (Hz)", "Amplitude (dB)", 0, ImPlotAxisFlags_Invert);
    //    ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_SymLog);
    //    //ImPlot::SetupAxisScale(ImAxis_Y1, ImPlotScale_Log10);

    //    ImPlot::PlotBars("RightAmplitudeCurve", this->bandCenterFreqs.data(), rightFFTChOut.data(), rightFFTChOut.size(), 1);

    //    ImPlot::EndPlot();
    //}

    //ImGui::EndChild();


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
