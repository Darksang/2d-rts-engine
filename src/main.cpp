#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

void FramebufferSizeCallback(GLFWwindow * Window, int Width, int Height);
void KeyCallback(GLFWwindow *Window, int Key, int Scancode, int Action, int Mods);

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
   GLFWwindow * Window = glfwCreateWindow(800, 600, "RTS Game", 0, 0);
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

   // Game loop
   while (!glfwWindowShouldClose(Window)) {
      // Process events
      glfwPollEvents();

      // Render
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // Swap screen buffers (front and back buffers)
      glfwSwapBuffers(Window);
   }

   // Clear allocated resources
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