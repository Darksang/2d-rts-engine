#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "engine/window.h"
#include "engine/resources_manager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Frame time variables
float DeltaTime = 0.0f;
float LastFrameTime = 0.0f;

int main(int argc, char * argv[]) {
   Window GameWindow(1024, 768, "RTSGame");

   // Load all OpenGL function pointers
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
       std::cout << "Failed to initialize GLAD" << std::endl;
       return -1;
   }

   // IMGUI
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO & io = ImGui::GetIO();
   (void)io;

   ImGui::StyleColorsDark();

   const char* glsl_version = "#version 150";
   ImGui_ImplGlfw_InitForOpenGL(GameWindow.GetWindowPointer(), true);
   ImGui_ImplOpenGL3_Init(glsl_version);

   // Game loop
   while (!GameWindow.ShouldClose()) {
      // Update delta time
      float CurrentFrameTime = glfwGetTime();
      DeltaTime = CurrentFrameTime - LastFrameTime;
      LastFrameTime = CurrentFrameTime;

      // Exit
      if (glfwGetKey(GameWindow.GetWindowPointer(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
         GameWindow.Close();

      // IMGUI
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      {
         ImGui::Begin("Hello, World");

         ImGui::Text("This is a test");

         ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

         ImGui::End();
      }

      ImGui::Render();

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // Render ImGui
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      // Swap screen buffers (front and back buffers)
      GameWindow.SwapBuffers();

      // NOTE: Fix for initial black screen. GLFW bug on OSX Mojave.
      #ifdef __APPLE__
      static bool FixOSX = false;

      if (!FixOSX) {
         GameWindow.OSXFix();
         FixOSX = true;
      }
      #endif
   }

   // Clear allocated resources
   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();

   return 0;
}