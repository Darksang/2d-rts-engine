#include "engine/engine.h"
#include "engine/scene.h"
#include "engine/texture.h"

#include "imgui/imgui.h"

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

Scene::Scene(Engine * E) : EnginePointer(E) {
    EntityWorld = ECS::World::createWorld();
    PhysicsWorld = new b2World(b2Vec2(0.0f, 0.0f));
}

Scene::~Scene() {
    EnginePointer = 0;

    EntityWorld->cleanup();
    EntityWorld->destroyWorld();

    delete PhysicsWorld;
}

void Scene::Start() {
    // Initialize systems
    EntityWorld->registerSystem(new CameraSystem());
    EntityWorld->registerSystem(new PhysicsSystem(PhysicsWorld));
    EntityWorld->registerSystem(new RenderSystem(EnginePointer->EngineSpriteRenderer));

    // Camera Entity
    ECS::Entity * CameraEntity = EntityWorld->create();
    CameraEntity->assign<Camera>(EnginePointer->EngineCamera);

    // Input Entity
    ECS::Entity * InputEntity = EntityWorld->create();
    InputEntity->assign<Input>(EnginePointer->EngineInput);

    // Test entities
    ECS::Entity * TestEntity = EntityWorld->create();
    TestEntity->assign<Transform>();
    Texture PlayerTexture("resources/sprites/Laharl.png", true);
    TestEntity->assign<Sprite>(PlayerTexture);
}

void Scene::Update() {
    EntityWorld->tick(EnginePointer->DeltaTime);
    GUI();
}

void Scene::GUI() {

}