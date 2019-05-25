#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "engine/ECS.h"

class CameraSystem : public ECS::EntitySystem {
    public:
        CameraSystem() { }
        ~CameraSystem() { }

        void configure(ECS::World * world) override;
        void unconfigure(ECS::World * world) override;
        void tick(ECS::World * world, float deltaTime) override;
};

#endif