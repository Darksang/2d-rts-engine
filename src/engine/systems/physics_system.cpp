#include "engine/systems/physics_system.h"

#include "engine/components/physics_body.h"
#include "engine/components/transform.h"

PhysicsSystem::PhysicsSystem(b2World * PhysicsWorld) {
    this->PhysicsWorld = PhysicsWorld;
}

void PhysicsSystem::configure(ECS::World * world) {
    TimeStep = 1.0f / 60.0f;
    VelocityIterations = 6;
    PositionIterations = 2;
}

void PhysicsSystem::unconfigure(ECS::World * world) {
    
}

void PhysicsSystem::tick(ECS::World * world, float deltaTime) {
    PhysicsWorld->Step(TimeStep, VelocityIterations, PositionIterations);

    world->each<PhysicsBody>([&](ECS::Entity * E, ECS::ComponentHandle<PhysicsBody> B) -> void {
        Transform T = E->get<Transform>().get();
        B.get().Body->SetTransform(b2Vec2(T.Position.x, T.Position.y), glm::radians(T.Rotation));
    });
}