#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <iostream>

#include "shader.h"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

void FramebufferSizeCallback(GLFWwindow * Window, int Width, int Height);
void KeyCallback(GLFWwindow * Window, int Key, int Scancode, int Action, int Mods);

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
   glfwSetKeyCallback(Window, KeyCallback);
   glfwSetFramebufferSizeCallback(Window, FramebufferSizeCallback);

   // Load all OpenGL function pointers
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
       std::cout << "Failed to initialize GLAD" << std::endl;
       return -1;
   }

   shader DefaultShader = BuildShader("../shaders/default.vs", "../shaders/default.fs");

   // set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------
   float Vertices[] = {
      0.5f,  0.5f, 0.0f,  // top right
      0.5f, -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f,  // bottom left
      -0.5f,  0.5f, 0.0f   // top left 
   };

   unsigned int Indices[] = {  // note that we start from 0!
      0, 1, 3,  // first Triangle
      1, 2, 3   // second Triangle
   };

   unsigned int VBO, VAO, EBO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glGenBuffers(1, &EBO);
   // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
   // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
   glBindVertexArray(0); 

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   // IMGUI
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO & io = ImGui::GetIO();
   (void)io;

   ImGui::StyleColorsDark();

   const char* glsl_version = "#version 150";
   ImGui_ImplGlfw_InitForOpenGL(Window, true);
   ImGui_ImplOpenGL3_Init(glsl_version);

   // Game loop
   while (!glfwWindowShouldClose(Window)) {
      // Process events
      glfwPollEvents();

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
      glClear(GL_COLOR_BUFFER_BIT);

      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      UseShader(DefaultShader);
      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      // Swap screen buffers (front and back buffers)
      glfwSwapBuffers(Window);
   }

   // Clear allocated resources
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
   glDeleteBuffers(1, &EBO);

   glfwTerminate();

   return 0;
}

void FramebufferSizeCallback(GLFWwindow * Window, int Width, int Height) {
    // Make sure the viewport matches the new window dimensions
    glViewport(0, 0, Width, Height);
}

void KeyCallback(GLFWwindow * Window, int Key, int Scancode, int Action, int Mods) {
   if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS) {
      printf("Escape key pressed\n");
   } else if (Key == GLFW_KEY_Q && Action == GLFW_PRESS) {
      printf("Q key pressed\n");
   } else if (Key == GLFW_KEY_W && Action == GLFW_PRESS) {
      printf("W key pressed\n");
   } else if (Key == GLFW_KEY_E && Action == GLFW_PRESS) {
      printf("E key pressed\n");
   } else if (Key == GLFW_KEY_A && Action == GLFW_PRESS) {
      printf("A key pressed\n");
   } else if (Key == GLFW_KEY_S && Action == GLFW_PRESS) {
      printf("S key pressed\n");
   } else if (Key == GLFW_KEY_D && Action == GLFW_PRESS) {
      printf("D key pressed\n");
   } else if (Key == GLFW_KEY_F && Action == GLFW_PRESS) {
      printf("F key pressed\n");
   } else if (Key == GLFW_KEY_SPACE && Action == GLFW_PRESS) {
      printf("Space key pressed\n");
   }
}