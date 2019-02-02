#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

int main(int argc, char * argv[]) {
   printf("Simple Program Running\n");

   glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);

   std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;

   return 0;
}