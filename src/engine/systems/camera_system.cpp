#include "engine/systems/camera_system.h"

#include "engine/components/camera.h"
#include "engine/components/input.h"

void CameraSystem::configure(ECS::World * world) {

}

void CameraSystem::unconfigure(ECS::World * world) {

}

void CameraSystem::tick(ECS::World * world, float deltaTime) {
    ECS::ComponentHandle<Input> Inp;

    world->each<Input>([&](ECS::Entity * E, ECS::ComponentHandle<Input> I) -> void {
        Inp = I;
    });

    world->each<Camera>([&](ECS::Entity * E, ECS::ComponentHandle<Camera> C) -> void {
        // Zoom in and out using scroll wheel
        if (Inp->EngineInput->MouseWheelDelta > 0.0f)
            C->EngineCamera->ZoomIn(Inp->EngineInput->MouseWheelDelta * 0.1f);
        else if (Inp->EngineInput->MouseWheelDelta < 0.0f)
            C->EngineCamera->ZoomOut(-Inp->EngineInput->MouseWheelDelta * 0.1f);

        // Move camera using WASD keys
        if (Inp->EngineInput->IsKeyDown(Key::KEY_W)) {
            C->EngineCamera->Translate(glm::vec2(0.0f, -5.0f) * deltaTime);
        }

        if (Inp->EngineInput->IsKeyDown(Key::KEY_S)) {
            C->EngineCamera->Translate(glm::vec2(0.0f, 5.0f) * deltaTime);
        }

        if (Inp->EngineInput->IsKeyDown(Key::KEY_A)) {
            C->EngineCamera->Translate(glm::vec2(-5.0f, 0.0f) * deltaTime);
        }

        if (Inp->EngineInput->IsKeyDown(Key::KEY_D)) {
            C->EngineCamera->Translate(glm::vec2(5.0f, 0.0f) * deltaTime);
        }
    });
}