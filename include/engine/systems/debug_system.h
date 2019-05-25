#ifndef DEBUG_SYSTEM_H
#define DEBUG_SYSTEM_H

#include "engine/ECS.h"
#include "engine/debug_draw.h"

#include "Box2D/Box2D.h"

class DebugSystem : public ECS::EntitySystem {
    public:
        DebugSystem(b2World * PhysicsWorld, DebugDraw * DebugRenderer);
        ~DebugSystem() { 
            PhysicsWorld = 0;
            DebugRenderer = 0;
        }

        void configure(ECS::World * world) override;
        void unconfigure(ECS::World * world) override;
        void tick(ECS::World * world, float deltaTime) override;
        
    private:
        b2World * PhysicsWorld;
        DebugDraw * DebugRenderer;
};

#endif