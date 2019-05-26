#include "engine/engine.h"
#include "engine/scene.h"
#include "engine/texture.h"

#include "imgui/imgui.h"

Scene::Scene(Engine * E) : EnginePointer(E) {
    PhysicsWorld = new b2World(b2Vec2(0.0f, 0.0f));
}

Scene::~Scene() {
    EnginePointer = 0;

    delete PhysicsWorld;
}

void Scene::Start() {
    Texture PlayerTexture("resources/sprites/Laharl.png", true);

    Entity = Sprite(PlayerTexture);
}

void Scene::Update() {
    GUI();

    if (EnginePointer->EngineInput->IsKeyDown(Key::KEY_A))
        EnginePointer->EngineCamera->Translate(glm::vec2(-5.0f, 0.0f) * EnginePointer->DeltaTime);

    if (EnginePointer->EngineInput->IsKeyDown(Key::KEY_D))
        EnginePointer->EngineCamera->Translate(glm::vec2(5.0f, 0.0f) * EnginePointer->DeltaTime);

    if (EnginePointer->EngineInput->IsKeyDown(Key::KEY_W))
        EnginePointer->EngineCamera->Translate(glm::vec2(0.0f, -5.0f) * EnginePointer->DeltaTime);

    if (EnginePointer->EngineInput->IsKeyDown(Key::KEY_S))
        EnginePointer->EngineCamera->Translate(glm::vec2(0.0f, 5.0f) * EnginePointer->DeltaTime);

    EnginePointer->EngineSpriteRenderer->Draw(Entity);
}

void Scene::GUI() {
    ImGui::Begin("Scene");
    ImGui::End();
}