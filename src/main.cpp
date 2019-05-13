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

#include "shader.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char * argv[]) {
   glfwInit();

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

   #ifdef __APPLE__
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   #endif

   GLFWwindow * Window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RTS Game", 0, 0);

   if (!Window) {
      std::cout << "Failed to create GLFW Window" << std::endl;
      glfwTerminate();
      return -1;
   }

   glfwMakeContextCurrent(Window);

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

   // Configure Sprite Rendering Data
   GLuint VAO, VBO;
   GLfloat Vertices[] = {
      // Pos      // Tex
      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f, 
   
      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f
   };

   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

   glBindVertexArray(VAO);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid *)0);

   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);

   // Texture load
   GLuint Texture;
   glGenTextures(1, &Texture);
   glBindTexture(GL_TEXTURE_2D, Texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   int Width, Height, Channels;
   //stbi_set_flip_vertically_on_load(true);
   
   unsigned char * Data = stbi_load("resources/sprites/Laharl.png", &Width, &Height, &Channels, 0);

   if (Data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
      glGenerateMipmap(GL_TEXTURE_2D);
   }

   stbi_image_free(Data);

   glBindTexture(GL_TEXTURE_2D, 0);

   // Rendering prep
   glm::mat4 Projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

   SpriteShader.Use();
   SpriteShader.SetInt("Sprite", 0);
   SpriteShader.SetMat4("ProjectionMatrix", Projection);

   while (!glfwWindowShouldClose(Window)) {
      // IMGUI New Frame Prep
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

      // Render Test Sprite
      SpriteShader.Use();
      glm::mat4 Model = glm::mat4(1.0f);;

      Model = glm::translate(Model, glm::vec3(200.0f, 200.0f, 0.0f));
      Model = glm::scale(Model, glm::vec3(152.0f, 162.0f, 1.0f));

      SpriteShader.SetMat4("ModelMatrix", Model);

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, Texture);

      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      // Render ImGui
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(Window);
      glfwPollEvents();
   }

   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();
   glfwDestroyWindow(Window);
   glfwTerminate();

   return 0;
}