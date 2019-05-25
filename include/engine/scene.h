#ifndef SCENE_H
#define SCENE_H

#include "engine/ECS.h"
#include "Box2D/Box2D.h"

class Engine;

class Scene {
    public:
        Scene(Engine * E);
        ~Scene();

        void Start();
        void Update();

    private:
        // Hold pointer to Engine so we can access common components
        Engine * EnginePointer;

        // World that holds all entities in this scene
        ECS::World * EntityWorld;
        // Box2D world of this scene
        b2World * PhysicsWorld;

        // Scene related UI
        void GUI();
};

#endif