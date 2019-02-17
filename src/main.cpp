#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <iostream>

#include "shader.h"
#include "camera.h"

#include "stb_image.h"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

void FramebufferSizeCallback(GLFWwindow * Window, int Width, int Height);
void KeyCallback(GLFWwindow * Window, int Key, int Scancode, int Action, int Mods);
void MouseCallback(GLFWwindow * Window, double PositionX, double PositionY);
void ProcessInput(GLFWwindow * Window);

// Frame time variables
float DeltaTime = 0.0f;
float LastFrameTime = 0.0f;

// Camera
camera MainCamera;
bool FirstMouse = true;
float LastMousePositionX = (float)SCREEN_WIDTH / 2.0f;
float LastMousePositionY = (float)SCREEN_HEIGHT / 2.0f;

int main(int argc, char * argv[]) {
   // Initialize GLFW
   glfwInit();

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

   #ifdef __APPLE__
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   #endif

   // Create a window
   GLFWwindow * Window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RTS Game", 0, 0);
   if (!Window) {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
   }

   // Asign OpenGL context to our window
   glfwMakeContextCurrent(Window);

   // Register callbacks
   glfwSetFramebufferSizeCallback(Window, FramebufferSizeCallback);
   glfwSetCursorPosCallback(Window, MouseCallback);

   glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   // Load all OpenGL function pointers
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
       std::cout << "Failed to initialize GLAD" << std::endl;
       return -1;
   }

   glEnable(GL_DEPTH_TEST);

   // Initialize camera
   MainCamera = CreatePerspectiveCamera(glm::vec3(0.0f, 0.0f, 3.0f), 60, 0.3, 1000);

   // TODO: Path has to go backwards two times in Windows, once in OSX, fix it
   shader DefaultShader = BuildShader("resources/shaders/default.vs", "resources/shaders/default.fs");

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
   ImGui_ImplGlfw_InitForOpenGL(Window, true);
   ImGui_ImplOpenGL3_Init(glsl_version);

   UseShader(DefaultShader);
   SetInt(DefaultShader, "Texture1", 0);

   // Game loop
   while (!glfwWindowShouldClose(Window)) {
      // Update delta time
      float CurrentFrameTime = glfwGetTime();
      DeltaTime = CurrentFrameTime - LastFrameTime;
      LastFrameTime = CurrentFrameTime;

      // Process input
      ProcessInput(Window);

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

      UseShader(DefaultShader);

      glm::mat4 Projection = glm::perspective(glm::radians((float)MainCamera.FieldOfView), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, MainCamera.NearClippingPlane, MainCamera.FarClippingPlane);
      SetMat4(DefaultShader, "Projection", Projection);

      glm::mat4 View = GetViewMatrix(MainCamera);
      SetMat4(DefaultShader, "View", View);

      glBindVertexArray(VAO);
      for (unsigned int i = 0; i < 10; i++) {
         glm::mat4 Model = glm::mat4(1.0f);
         Model = glm::translate(Model, CubePositions[i]);
         float angle = 20.0f * i;
         Model = glm::rotate(Model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
         SetMat4(DefaultShader, "Model", Model);

         glDrawArrays(GL_TRIANGLES, 0, 36);
      }

      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      // Swap screen buffers (front and back buffers)
      glfwSwapBuffers(Window);
      glfwPollEvents();

      // NOTE: Fix for initial black screen. GLFW bug on OSX Mojave.
      #ifdef _APPLE_
      static bool FixOSX = false;

      if (!FixOSX) {
         int x, y;
         glfwGetWindowPos(Window, &x, &y);
         glfwSetWindowPos(Window, ++x, y);
         FixOSX = true;
      }
      #endif
   }

   // Clear allocated resources
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);

   glfwTerminate();

   return 0;
}

void FramebufferSizeCallback(GLFWwindow * Window, int Width, int Height) {
    // Make sure the viewport matches the new window dimensions
    glViewport(0, 0, Width, Height);
}

void MouseCallback(GLFWwindow * Window, double PositionX, double PositionY) {
   if (FirstMouse) {
      LastMousePositionX = PositionX;
      LastMousePositionY = PositionY;
      FirstMouse = false;
   }

   float OffsetX = PositionX - LastMousePositionX;
   float OffsetY = LastMousePositionY - PositionY; // Reversed since y-coordinates go from bottom to top

   LastMousePositionX = PositionX;
   LastMousePositionY = PositionY;

   CameraProcessMouseMovement(&MainCamera, OffsetX, OffsetY);
}

void ProcessInput(GLFWwindow * Window) {
   if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(Window, true);

   if (glfwGetKey(Window, GLFW_KEY_H) == GLFW_PRESS) {
      std::cout << "Position -> X: " << MainCamera.Position.x << " Y: " << MainCamera.Position.y << " Z: " << MainCamera.Position.z << std::endl;
   }

   if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
      CameraProcessKeyboard(&MainCamera, FORWARD, DeltaTime);
   if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
      CameraProcessKeyboard(&MainCamera, BACKWARDS, DeltaTime);
   if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
      CameraProcessKeyboard(&MainCamera, LEFT, DeltaTime);
   if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
      CameraProcessKeyboard(&MainCamera, RIGHT, DeltaTime);
}