#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>

#include <GLFW/glfw3.h>

#include "engine/ECS.h"
ECS_TYPE_IMPLEMENTATION;

#include "engine/camera2d.h"
#include "engine/debug_draw.h"
#include "engine/input_state.h"
#include "engine/scene.h"
#include "engine/sprite_renderer.h"

class Engine {
    public:
        Engine();
        ~Engine();

        static float PIXELS_PER_METER;
        static float SCALE_FACTOR;

        int ScreenWidth;
        int ScreenHeight;

        int LastScreenWidth;
        int LastScreenHeight;
        int LastWindowPosX;
        int LastWindowPosY;

        bool IsFullscreen;

        float DeltaTime;
        double CurrentTime;
        int FrameCount;
        
        // Engine components shared by all scenes
        InputState * EngineInput;
        Camera2D * EngineCamera;

        DebugDraw * EngineDebugRenderer;
        SpriteRenderer * EngineSpriteRenderer;

        void Start();

        void SetFullscreen(bool Fullscreen);

    private:
        GLFWwindow * EngineWindow;
        GLFWmonitor * EngineMonitor;

        float LastFrameTime;

        Scene ActiveScene;

        bool InitializeVideo();
        void InitializeGui();

        void Update();
        void UpdateGUI();
        void Render();
};

#endif