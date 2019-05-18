#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "stb_image.h"

#include "engine/shader.h"
#include "engine/texture.h"
#include "engine/camera2d.h"
#include "engine/game_object.h"
#include "engine/transform2d.h"
#include "engine/sprite_renderer.h"

const float SCREEN_WIDTH = 1024.0f;
const float SCREEN_HEIGHT = 768.0f;

glm::vec2 MouseWheelDelta = glm::vec2(0.0f, 0.0f);

void ScrollCallback(GLFWwindow * Window, double OffsetX, double OffsetY) {
   //std::cout << "Offset X - " << OffsetX << " Offset Y - " << OffsetY << std::endl;
   MouseWheelDelta.y = OffsetY;
}

int main(int argc, char * argv[]) {
   glfwInit();

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   //glfwWindowHint(GLFW_DECORATED, GL_FALSE);
   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

   #ifdef __APPLE__
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   #endif

   GLFWwindow * Window = glfwCreateWindow(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT), "RTS Game", 0, 0);

   if (!Window) {
      std::cout << "Failed to create GLFW Window" << std::endl;
      glfwTerminate();
      return -1;
   }

   glfwMakeContextCurrent(Window);

   glfwSetScrollCallback(Window, ScrollCallback);

   // Load all OpenGL function pointers
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
       std::cout << "Failed to initialize GLAD" << std::endl;
       return -1;
   }

   glEnable(GL_CULL_FACE);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   // IMGUI
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO & io = ImGui::GetIO();
   (void)io;

   ImGui::StyleColorsDark();

   const char * glsl_version = "#version 150";
   ImGui_ImplGlfw_InitForOpenGL(Window, true);
   ImGui_ImplOpenGL3_Init(glsl_version);

   Shader SpriteShader("resources/shaders/vertex/sprite.glsl", "resources/shaders/fragment/sprite.glsl");

   // Camera
   Camera2D Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
   
   // Sprite Renderer
   SpriteRenderer Renderer(SpriteShader, &Camera);

   Texture PlayerTexture("resources/sprites/Laharl.png", true);

   Sprite Player(PlayerTexture);
   Player.Transform.Position.x = 20.0f;
   Player.Transform.Rotation = 45.0f;

   Sprite Player2(PlayerTexture);
   Player2.Transform.Position.x = 67.0f;
   Player2.Transform.Position.y = -100.0f;

   double DeltaTime = 0.0f;
   double LastFrameTime = glfwGetTime();
   int FrameCount = 0;

   while (!glfwWindowShouldClose(Window)) {
      double CurrentTime = glfwGetTime();
      DeltaTime = CurrentTime - LastFrameTime;
      LastFrameTime = CurrentTime;

      glfwPollEvents();

      if (MouseWheelDelta.y > 0.0f)
         Camera.ZoomIn(MouseWheelDelta.y * 0.1f);
      else if (MouseWheelDelta.y < 0.0f)
         Camera.ZoomOut(-MouseWheelDelta.y * 0.1f);

      // Game Update
      //Camera.Update();

      // IMGUI New Frame Prep
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      {
         ImGui::ShowDemoWindow();
      }

      // Main Menu
      {
         if (ImGui::BeginMainMenuBar()) {
            ImGui::EndMainMenuBar();
         }
      }

      // Camera Test
      {
         ImGui::Begin("Camera");
         if (ImGui::Button("Move Down"))
            Camera.Translate(glm::vec2(0.0f, 10.0f));
         if (ImGui::Button("Move Up"))
            Camera.Translate(glm::vec2(0.0f, -10.0f));
         if (ImGui::Button("Move Right"))
            Camera.Translate(glm::vec2(10.0f, 0.0f));
         if (ImGui::Button("Move Left"))
            Camera.Translate(glm::vec2(-10.0f, 0.0f));
         if (ImGui::Button("Test LookAt"))
            Camera.LookAt(glm::vec2(20.0f, 20.0f));
         ImGui::End();
      }

      {
         ImGui::Begin("Input");
         ImGui::BulletText("Mouse Wheel Delta: %f", MouseWheelDelta.y);
         ImGui::End();
      }

      // Other Info
      {
         ImGui::Begin("Information");
         ImGui::Text("Time Since Start: %.2f s", CurrentTime);
         ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
         ImGui::Text("Frame Count: %i", FrameCount);
         ImGui::End();
      }

      // Sprite
      {
         ImGui::Begin("Sprite");
         if (ImGui::CollapsingHeader("Transform")) {
            if (ImGui::TreeNode("Position")) {
               ImGui::Text("Position X: %f", Player.Transform.Position.x);
               ImGui::Text("Position Y: %f", Player.Transform.Position.y);

               ImGui::TreePop();
            }

            if (ImGui::TreeNode("Scale")) {
               ImGui::Text("Scale X: %f", Player.Transform.Scale.x);
               ImGui::Text("Scale Y: %f", Player.Transform.Scale.y);

               ImGui::TreePop();
            }

            ImGui::SliderFloat("Rotation", &Player.Transform.Rotation, 0.0f, 360.0f);
         }
         ImGui::End();
      }

      // Render Scene
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      Renderer.Draw(Player);
      Renderer.Draw(Player2);

      // Render ImGui
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(Window);

      // Reset Input for next frame
      MouseWheelDelta.y = 0.0f;

      FrameCount++;
   }

   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();
   glfwDestroyWindow(Window);
   glfwTerminate();

   return 0;
}