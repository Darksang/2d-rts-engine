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

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

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

   // IMGUI
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO & io = ImGui::GetIO();
   (void)io;

   ImGui::StyleColorsDark();

   const char * glsl_version = "#version 150";
   ImGui_ImplGlfw_InitForOpenGL(Window, true);
   ImGui_ImplOpenGL3_Init(glsl_version);

   // Read shaders from file
   std::string VertexCode;
   std::string FragmentCode;

   std::ifstream VertexFile("resources/shaders/vertex/sprite.glsl");
   std::ifstream FragmentFile("resources/shaders/fragment/sprite.glsl");

   std::stringstream Buffer;

   // Read Vertex File
   Buffer << VertexFile.rdbuf();
   VertexCode = Buffer.str();

   // Read Fragment File
   Buffer.str(std::string());
   Buffer << FragmentFile.rdbuf();
   FragmentCode = Buffer.str();

   VertexFile.close();
   FragmentFile.close();

   // Compile shaders
   const char * VertexSource = VertexCode.c_str();
   const char * FragmentSource = FragmentCode.c_str();

   GLuint VertexShader, FragmentShader;

   VertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(VertexShader, 1, &VertexSource, 0);
   glCompileShader(VertexShader);

   int Success;
   char InfoLog[1024];

   glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);
   if (!Success) {
      glGetShaderInfoLog(VertexShader, 1024, 0, InfoLog);
      std::cout << "-Vertex Shader Compilation Failed-\n" << InfoLog << std::endl;
   }

   FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(FragmentShader, 1, &FragmentSource, 0);
   glCompileShader(FragmentShader);

   glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Success);
   if (!Success) {
      glGetShaderInfoLog(FragmentShader, 1024, 0, InfoLog);
      std::cout << "-Fragment Shader Compilation Failed-\n" << InfoLog << std::endl;
   }

   GLuint SpriteShader = glCreateProgram();
   glAttachShader(SpriteShader, VertexShader);
   glAttachShader(SpriteShader, FragmentShader);
   glLinkProgram(SpriteShader);

   glGetProgramiv(SpriteShader, GL_LINK_STATUS, &Success);
   if (!Success) {
      glGetProgramInfoLog(SpriteShader, 1024, 0, InfoLog);
      std::cout << "-Sprite Program Shader Compilation Failed-\n" << InfoLog << std::endl;
   }

   glDeleteShader(VertexShader);
   glDeleteShader(FragmentShader);

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
   stbi_set_flip_vertically_on_load(true);
   
   unsigned char * Data = stbi_load("resources/sprites/Laharl.png", &Width, &Height, &Channels, 0);

   if (Data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
      glGenerateMipmap(GL_TEXTURE_2D);
   }

   stbi_image_free(Data);

   glBindTexture(GL_TEXTURE_2D, 0);

   // Rendering prep
   glm::mat4 Projection = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);

   glUseProgram(SpriteShader);
   glUniform1i(glGetUniformLocation(SpriteShader, "Sprite"), 0);
   glUniformMatrix4fv(glGetUniformLocation(SpriteShader, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(Projection));

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
      glUseProgram(SpriteShader);
      glm::mat4 Model;

      Model = glm::translate(Model, glm::vec3(200.0f, 200.0f, 0.0f));
      Model = glm::scale(Model, glm::vec3(300.0f, 400.0f, 1.0f)); // Last scale

      glUniformMatrix4fv(glGetUniformLocation(SpriteShader, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(Model));

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