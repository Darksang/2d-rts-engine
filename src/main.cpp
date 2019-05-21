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

#include "Box2D/Box2D.h"

#include "stb_image.h"

#include "engine/game_object.h"
#include "engine/engine.h"
#include "engine/shader.h"
#include "engine/sprite_renderer.h"
#include "engine/texture.h"
#include "engine/transform2d.h"

#include "engine/debug_draw.h"

const float SCREEN_WIDTH = 1024.0f;
const float SCREEN_HEIGHT = 768.0f;

glm::vec2 MouseWheelDelta = glm::vec2(0.0f, 0.0f);
glm::vec2 MousePosition = glm::vec2(0.0f, 0.0f);

void ScrollCallback(GLFWwindow * Window, double OffsetX, double OffsetY) {
   MouseWheelDelta.y = static_cast<float>(OffsetY);
}

void MousePositionCallback(GLFWwindow * Window, double PositionX, double PositionY) {
   MousePosition.x = static_cast<float>(PositionX);
   MousePosition.y = static_cast<float>(PositionY);
}

int main(int argc, char * argv[]) {
   glfwInit();

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

   glfwSetCursorPosCallback(Window, MousePositionCallback);
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

   // Box2D
   b2Vec2 Gravity(0.0f, 0.0f); // Zero gravity, why only want collision detection
   b2World World(Gravity);

   // Camera
   Camera2D Camera(SCREEN_WIDTH, SCREEN_HEIGHT, Engine::SCALE_FACTOR);

   // Debug Renderer
   DebugDraw DebugRenderer;
   DebugRenderer.Initialize(&Camera);

   // Sprite Renderer
   Shader SpriteShader("resources/shaders/vertex/sprite.glsl", "resources/shaders/fragment/sprite.glsl");
   SpriteRenderer Renderer(SpriteShader, &Camera);

   Texture PlayerTexture("resources/sprites/Laharl.png", true);

   Sprite Player(PlayerTexture);
   Player.Transform.Position.x = -4.0f;
   Player.Transform.Rotation = 45.0f;

   Sprite Player2(PlayerTexture);
   Player2.Transform.Position.x = 4.0f;
   Player2.Transform.Position.y = 0.0f;

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

      if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
         Camera.Translate(glm::vec2(-5.0f, 0.0f) * static_cast<float>(DeltaTime));
      
      if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
         Camera.Translate(glm::vec2(5.0f, 0.0f) * static_cast<float>(DeltaTime));

      if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
         Camera.Translate(glm::vec2(0.0f, -5.0f) * static_cast<float>(DeltaTime));

      if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
         Camera.Translate(glm::vec2(0.0f, 5.0f) * static_cast<float>(DeltaTime));

      // Test: Move sprite around world using mouse
      if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
         glm::vec2 NewPos = Camera.ScreenToWorld(MousePosition);
         Player.Transform.Position = NewPos;
      }

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
            if (ImGui::BeginMenu("General")) {
               if (ImGui::MenuItem("Exit"))
                  glfwSetWindowShouldClose(Window, true);
               ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
         }
      }

      // Camera Test
      {
         ImGui::Begin("Camera");
         if (ImGui::CollapsingHeader("Position")) {
            ImGui::BulletText("Position X: %.4f", Camera.Position.x);
            ImGui::BulletText("Position Y: %.4f", Camera.Position.y);
         }
         ImGui::BulletText("Zoom: %.2f", Camera.Zoom);
         ImGui::BulletText("Minimum Zoom: %.2f", Camera.MinimumZoom);
         ImGui::BulletText("Maximum Zoom: %.2f", Camera.MaximumZoom);
         ImGui::End();
      }

      // Other Info
      {
         ImGui::Begin("Information");
         ImGui::Text("Time Since Start: %.2f s", CurrentTime);
         ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
         ImGui::Text("Frame Count: %i", FrameCount);
         ImGui::Text("Mouse Screen Position: %.0fx %.0fy", MousePosition.x, MousePosition.y);
         glm::vec2 MouseWorldPos = Camera.ScreenToWorld(MousePosition);
         ImGui::Text("Mouse World Position: %.4fx %.4fy", MouseWorldPos.x, MouseWorldPos.y);
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

      DebugRenderer.DrawPoint(glm::vec2(-3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 3.0f);
      DebugRenderer.DrawSegment(glm::vec2(0.0f, 0.0f), glm::vec2(3.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

      DebugRenderer.Render();

      // Render ImGui
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(Window);

      // Reset Input for next frame
      MouseWheelDelta.y = 0.0f;

      FrameCount++;
   }

   DebugRenderer.Destroy();

   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();
   glfwDestroyWindow(Window);
   glfwTerminate();

   return 0;
}