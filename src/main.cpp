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

#include "engine/shader.h"
#include "engine/sprite_renderer.h"
#include "engine/texture.h"
#include "engine/input_state.h"
#include "engine/debug_draw.h"
#include "engine/engine.h"

// #### ESC TEST
#include "engine/ECS.h"
ECS_TYPE_IMPLEMENTATION;

// Components
#include "engine/components/camera.h"
#include "engine/components/input.h"
#include "engine/components/physics_body.h"
#include "engine/components/sprite.h"
#include "engine/components/transform.h"

// Systems
#include "engine/systems/camera_system.h"
#include "engine/systems/debug_system.h"
#include "engine/systems/physics_system.h"
#include "engine/systems/render_system.h"
// ####

/*const float SCREEN_WIDTH = 1024.0f;
const float SCREEN_HEIGHT = 768.0f;

void ScrollCallback(GLFWwindow * Window, double OffsetX, double OffsetY) {
   InputState * Input = static_cast<InputState *>(glfwGetWindowUserPointer(Window));
   Input->MouseWheelDelta = static_cast<float>(OffsetY);
}

void MousePositionCallback(GLFWwindow * Window, double PositionX, double PositionY) {
   InputState * Input = static_cast<InputState *>(glfwGetWindowUserPointer(Window));
   Input->MousePosition = glm::vec2(static_cast<float>(PositionX), static_cast<float>(PositionY));
}*/

int main(int argc, char * argv[]) {
   Engine * MainEngine = new Engine();

   MainEngine->Start();

   delete MainEngine;

   return 0;
   
   /* #### ESC TEST
   ECS::World * EntityWorld = ECS::World::createWorld();

   EntityWorld->registerSystem(new CameraSystem());
   EntityWorld->registerSystem(new DebugSystem(&PhysicsWorld, &DebugRenderer));
   EntityWorld->registerSystem(new PhysicsSystem(&PhysicsWorld));
   EntityWorld->registerSystem(new RenderSystem(&Renderer));

   // Test entity
   ECS::Entity * Entity = EntityWorld->create();
   Entity->assign<Transform>();
   Texture PlayerTexture("resources/sprites/Laharl.png", true);
   Entity->assign<Sprite>(PlayerTexture);

   b2BodyDef BodyDef;
   BodyDef.type = b2_dynamicBody;
   BodyDef.position.Set(Entity->get<Transform>()->Position.x, Entity->get<Transform>()->Position.x);
   b2Body * Body = PhysicsWorld.CreateBody(&BodyDef);

   b2PolygonShape Box;
   Box.SetAsBox(Entity->get<Sprite>()->SpriteTexture.Width * Engine::SCALE_FACTOR * 0.5f, Entity->get<Sprite>()->SpriteTexture.Height * Engine::SCALE_FACTOR * 0.5f);
   b2FixtureDef FixtureDef;
   FixtureDef.shape = &Box;
   FixtureDef.density = 1.0f;
   FixtureDef.friction = 0.3f;

   Body->CreateFixture(&FixtureDef);
   Body->SetUserData(Entity);

   Entity->assign<PhysicsBody>(Body); */

   /* IMGUI New Frame Prep
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
         ImGui::BulletText("Position X: %.4f", EngineCamera.Position.x);
         ImGui::BulletText("Position Y: %.4f", EngineCamera.Position.y);
      }
      ImGui::BulletText("Zoom: %.2f", EngineCamera.Zoom);
      ImGui::BulletText("Minimum Zoom: %.2f", EngineCamera.MinimumZoom);
      ImGui::BulletText("Maximum Zoom: %.2f", EngineCamera.MaximumZoom);
      ImGui::End();
   }

   // Other Info
   {
      ImGui::Begin("Information");
      ImGui::Text("Time Since Start: %.2f s", CurrentTime);
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::Text("Frame Count: %i", FrameCount);
      glm::vec2 MouseP = InputTest->MousePosition;
      ImGui::Text("Mouse Screen Position: %.0fx %.0fy", MouseP.x, MouseP.y);
      glm::vec2 MouseWorldPos = EngineCamera.ScreenToWorld(MouseP);
      ImGui::Text("Mouse World Position: %.4fx %.4fy", MouseWorldPos.x, MouseWorldPos.y);
      ImGui::Text("Input Poll Time: %f ms", (InputPollEnd - InputPollStart) * 1000.0f);
      ImGui::End();
   }

   // Sprite
   {
      ImGui::Begin("Sprite");
      if (ImGui::CollapsingHeader("Transform")) {
         if (ImGui::TreeNode("Position")) {
            ImGui::Text("Position X: %f", Entity->get<Transform>()->Position.x);
            ImGui::Text("Position X: %f", Entity->get<Transform>()->Position.y);

            ImGui::TreePop();
         }

         if (ImGui::TreeNode("Scale")) {
            ImGui::Text("Position X: %f", Entity->get<Transform>()->Scale.x);
            ImGui::Text("Position X: %f", Entity->get<Transform>()->Scale.y);

            ImGui::TreePop();
         }

         ImGui::SliderFloat("Rotation", &Entity->get<Transform>()->Rotation, 0.0f, 360.0f);
      }
      ImGui::End();
   } */
}