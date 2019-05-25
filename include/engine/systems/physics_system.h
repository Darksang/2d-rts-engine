#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "engine/ECS.h"

#include "Box2D/Box2D.h"

class PhysicsSystem : public ECS::EntitySystem {
    public:
        PhysicsSystem(b2World * PhysicsWorld);
        ~PhysicsSystem() { 
            PhysicsWorld = 0;
        }

        void configure(ECS::World * world) override;
        void unconfigure(ECS::World * world) override;
        void tick(ECS::World * world, float deltaTime) override;
        
    private:
        b2World * PhysicsWorld;

        float32 TimeStep;
        int32 VelocityIterations;
        int32 PositionIterations;
};

#endif