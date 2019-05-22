#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include "engine/ecs/ECS.h"

#include "Box2D/Box2D.h"

struct PhysicsBody {
    ECS_DECLARE_TYPE;

    PhysicsBody(b2Body * Body) : Body(Body) { }

    b2Body * Body;
};

ECS_DEFINE_TYPE(PhysicsBody);

#endif