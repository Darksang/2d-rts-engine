#include "engine/engine.h"

// External libraries include
#include <glad/glad.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Internal files include
#include "engine/input_state.h"

// GLFW Callbacks #################################################################

void ScrollCallback(GLFWwindow * Window, double OffsetX, double OffsetY) {
    InputState * Input = static_cast<InputState *>(glfwGetWindowUserPointer(Window));
    Input->MouseWheelDelta = static_cast<float>(OffsetY);
}

void MousePositionCallback(GLFWwindow * Window, double PositionX, double PositionY) {
    InputState * Input = static_cast<InputState *>(glfwGetWindowUserPointer(Window));
    Input->MousePosition = glm::vec2(static_cast<float>(PositionX), static_cast<float>(PositionY));
}

// ################################################################################

// 100 pixels equals 1 meter
float Engine::PIXELS_PER_METER = 100.0f;
float Engine::SCALE_FACTOR = 1.0f / PIXELS_PER_METER;

Engine::Engine() : EngineWindow(0), EngineInput(0), EngineCamera(0), EngineDebugRenderer(0), EngineSpriteRenderer(0), ActiveScene(this) {
    // Default resolution 1024x768
    ScreenWidth = 1024;
    ScreenHeight = 768;

    DeltaTime = 0.0f;
    CurrentTime = 0.0f;
    FrameCount = 0;
}

Engine::~Engine() {
    delete EngineInput;
    delete EngineCamera;

    EngineDebugRenderer->Destroy();
    delete EngineDebugRenderer;

    delete EngineSpriteRenderer;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(EngineWindow);
    glfwTerminate();
}

void Engine::Start() {
    if (!InitializeVideo()) {
        std::cout << "Failed to initialize video system. Closing engine." << std::endl;
        return;
    }

    InitializeGui();

    // Initialize input
    EngineInput = new InputState(EngineWindow);
    // Set EngineInput as User Pointer so we can update it with callbacks
    glfwSetWindowUserPointer(EngineWindow, EngineInput);

    // Initialize camera
    EngineCamera = new Camera2D(ScreenWidth, ScreenHeight, SCALE_FACTOR);

    // Initialize renderers
    EngineDebugRenderer = new DebugDraw();
    EngineDebugRenderer->Initialize(EngineCamera);

    Shader SpriteShader("resources/shaders/vertex/sprite.glsl", "resources/shaders/fragment/sprite.glsl");
    EngineSpriteRenderer = new SpriteRenderer(SpriteShader, EngineCamera);

    ActiveScene.Start();

    LastFrameTime = glfwGetTime();

    // Main game loop
    while (!glfwWindowShouldClose(EngineWindow)) {
        // Calculate delta time
        CurrentTime = glfwGetTime();
        DeltaTime = CurrentTime - LastFrameTime;
        LastFrameTime = CurrentTime;

        UpdateGUI();
        Update();
        Render();

        FrameCount++;
    }
}

void Engine::Update() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Process Input
    EngineInput->Update();
    glfwPollEvents();

    ActiveScene.Update();
}

void Engine::Render() {
    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(EngineWindow);
}

bool Engine::InitializeVideo() {
    // Initialize GLFW
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Create window
    EngineWindow = glfwCreateWindow(ScreenWidth, ScreenHeight, "Shiv Engine", 0, 0);

    if (!EngineWindow) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(EngineWindow);

    // Register window callbacks
    glfwSetCursorPosCallback(EngineWindow, MousePositionCallback);
    glfwSetScrollCallback(EngineWindow, ScrollCallback);

    // Load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void Engine::InitializeGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO & io = ImGui::GetIO();
    (void)io;

    //io.Fonts->AddFontFromFileTTF("Monoid Retina Nerd Font Complete.ttf", 15.0f);

    ImGui::StyleColorsDark();

    const char * glsl_version = "#version 150";
    ImGui_ImplGlfw_InitForOpenGL(EngineWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void Engine::UpdateGUI() {
    // IMGUI New Frame Prep
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui Demo Window
    {
        ImGui::ShowDemoWindow();
    }

    // Main Engine Menu
    {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("General")) {
                if (ImGui::MenuItem("Exit"))
                    glfwSetWindowShouldClose(EngineWindow, true);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    // Misc Info
    {
        ImGui::Begin("Info");
        ImGui::Text("Time Since Start: %.2f s", CurrentTime);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Frame Count: %i", FrameCount);
        ImGui::Text("Window Resolution: %ix%i", ScreenWidth, ScreenHeight);
        glm::vec2 MouseP = EngineInput->MousePosition;
        ImGui::Text("Mouse Screen Position: %.0fx %.0fy", MouseP.x, MouseP.y);
        //glm::vec2 MouseWorldPos = EngineCamera.ScreenToWorld(MouseP);
        //ImGui::Text("Mouse World Position: %.4fx %.4fy", MouseWorldPos.x, MouseWorldPos.y);
        ImGui::End();
    }
}