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
#include "texture.h"
#include "camera2d.h"

const float SCREEN_WIDTH = 800.0f;
const float SCREEN_HEIGHT = 600.0f;

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

   Texture PlayerTexture("resources/sprites/Laharl.png", true);

   // Camera
   Camera2D Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

   // Rendering prep
   SpriteShader.Use();
   SpriteShader.SetInt("Sprite", 0);
   SpriteShader.SetMat4("ProjectionMatrix", Camera.GetProjectionMatrix());

   while (!glfwWindowShouldClose(Window)) {
      /* Process Input
      if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS) {
         OrthographicCamera.SetPosition(OrthographicCamera.GetPosition() + glm::vec2(0.0f, 0.5f));
      }

      if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS) {
         OrthographicCamera.SetPosition(OrthographicCamera.GetPosition() + glm::vec2(0.0f, -0.5f));
      } */

      // Game Update
      //Camera.Update();

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
         if (ImGui::Button("Zoom In"))
            Camera.ZoomIn(0.05f);
         if (ImGui::Button("Zoom Out"))
            Camera.ZoomOut(0.05f);
         ImGui::End();
      }

      ImGui::Render();

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // Render Test Sprite
      SpriteShader.Use();
      glm::mat4 Model = glm::mat4(1.0f);;

      Model = glm::translate(Model, glm::vec3(0.0f - PlayerTexture.Width / 2.0f, 0.0f - PlayerTexture.Height / 2.0f, 0.0f));
      Model = glm::scale(Model, glm::vec3(152.0f, 162.0f, 1.0f));

      SpriteShader.SetMat4("ModelMatrix", Model);
      SpriteShader.SetMat4("ViewMatrix", Camera.GetViewMatrix());

      glActiveTexture(GL_TEXTURE0);
      PlayerTexture.Bind();

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