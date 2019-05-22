#include "engine/systems/debug_system.h"

DebugSystem::DebugSystem(b2World * PhysicsWorld, DebugDraw * DebugRenderer) {
    this->PhysicsWorld = PhysicsWorld;
    this->DebugRenderer = DebugRenderer;
}

void DebugSystem::configure(ECS::World * world)  {
    uint32 flags = 0x0001;
    DebugRenderer->AppendFlags(flags);
    PhysicsWorld->SetDebugDraw(DebugRenderer);
}

void DebugSystem::unconfigure(ECS::World * world) {

}

void DebugSystem::tick(ECS::World * world, float deltaTime) {
    PhysicsWorld->DrawDebugData();
    DebugRenderer->Render();
}