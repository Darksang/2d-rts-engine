#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <iostream>

#include "window.h"
#include "shader.h"
#include "camera.h"

#include "stb_image.h"

void ProcessKeys(GLFWwindow * Window);
void CameraMouseMovement(double PositionX, double PositionY);

// Frame time variables
float DeltaTime = 0.0f;
float LastFrameTime = 0.0f;

// Camera
Camera MainCamera(glm::vec3(0.0f, 0.0f, 3.0f), 60, 0.3f, 1000.0f);
bool FirstMouse = true;
float LastMousePositionX;
float LastMousePositionY;

int main(int argc, char * argv[]) {
   Window GameWindow(800, 600, "RTSGame"); 

   LastMousePositionX = (float)GameWindow.Width / 2.0f;
   LastMousePositionY = (float)GameWindow.Height / 2.0f;

   // Load all OpenGL function pointers
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
       std::cout << "Failed to initialize GLAD" << std::endl;
       return -1;
   }

   glEnable(GL_DEPTH_TEST);

   Shader DefaultShader("resources/shaders/default.vs", "resources/shaders/default.fs");

   // set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------
   float Vertices[] = {
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
   };

   glm::vec3 CubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),
      glm::vec3(-1.3f, 1.0f, -1.5f)
   };

   unsigned int VBO, VAO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

   // Position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   // Texture attribute
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);

   // Load and create a texture
   unsigned int Texture;
   glGenTextures(1, &Texture);
   glBindTexture(GL_TEXTURE_2D, Texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   // NOTE: This image it's in Resources folder, but it must be copied where the exe is for the time being
   int Width, Height, Channels;
   unsigned char * Data = stbi_load("resources/textures/container.jpg", &Width, &Height, &Channels, 0);

   if (Data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
      glGenerateMipmap(GL_TEXTURE_2D);
   } else {
      std::cout << "Failed to load image" << std::endl;
   }

   stbi_image_free(Data);

   // IMGUI
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO & io = ImGui::GetIO();
   (void)io;

   ImGui::StyleColorsDark();

   const char* glsl_version = "#version 150";
   ImGui_ImplGlfw_InitForOpenGL(GameWindow.MainWindow, true);
   ImGui_ImplOpenGL3_Init(glsl_version);

   DefaultShader.Activate();
   DefaultShader.SetInt("Texture1", 0);

   double MouseX = 0;
   double MouseY = 0;

   // Game loop
   while (!GameWindow.ShouldClose()) {
      // Update delta time
      float CurrentFrameTime = glfwGetTime();
      DeltaTime = CurrentFrameTime - LastFrameTime;
      LastFrameTime = CurrentFrameTime;

      // Process input TODO: Rewrite Input handling
      ProcessKeys(GameWindow.MainWindow);
      /* if (glfwGetKey(GameWindow.MainWindow, GLFW_KEY_Q) == GLFW_PRESS)
         std::cout << "Window Width: " << GameWindow.Width << " Window Height: " << GameWindow.Height << std::endl; */

      GameWindow.GetCursorPosition(&MouseX, &MouseY);
      CameraMouseMovement(MouseX, MouseY);

      // IMGUI
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      {
         static float f = 0.0f;
         static int counter = 0;

         ImGui::Begin("Hello, World");

         ImGui::Text("This is a test");

         ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

         ImGui::End();
      }

      ImGui::Render();

      // Render
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glBindTexture(GL_TEXTURE_2D, Texture);

      DefaultShader.Activate();

      glm::mat4 Projection = glm::perspective(glm::radians((float)MainCamera.FieldOfView), (float)GameWindow.Width / (float)GameWindow.Height, MainCamera.NearClippingPlane, MainCamera.FarClippingPlane);
      DefaultShader.SetMat4("Projection", Projection);

      glm::mat4 View = MainCamera.GetViewMatrix();
      DefaultShader.SetMat4("View", View);

      glBindVertexArray(VAO);
      for (unsigned int i = 0; i < 10; i++) {
         glm::mat4 Model = glm::mat4(1.0f);
         Model = glm::translate(Model, CubePositions[i]);
         float angle = 20.0f * i;
         Model = glm::rotate(Model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
         DefaultShader.SetMat4("Model", Model);

         glDrawArrays(GL_TRIANGLES, 0, 36);
      }

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
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);

   return 0;
}

void CameraMouseMovement(double PositionX, double PositionY) {
   if (FirstMouse) {
      LastMousePositionX = PositionX;
      LastMousePositionY = PositionY;
      FirstMouse = false;
   }

   float OffsetX = PositionX - LastMousePositionX;
   float OffsetY = LastMousePositionY - PositionY; // Reversed since y-coordinates go from bottom to top

   LastMousePositionX = PositionX;
   LastMousePositionY = PositionY;

   MainCamera.ProcessMouseMovement(OffsetX, OffsetY);
}

void ProcessKeys(GLFWwindow * Window) {
   if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
      MainCamera.ProcessKeyboard(FORWARD, DeltaTime);
   if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
      MainCamera.ProcessKeyboard(BACKWARDS, DeltaTime);
   if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
      MainCamera.ProcessKeyboard(LEFT, DeltaTime);
   if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
      MainCamera.ProcessKeyboard(RIGHT, DeltaTime);
}