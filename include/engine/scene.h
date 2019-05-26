#ifndef SCENE_H
#define SCENE_H

#include "Box2D/Box2D.h"

#include "engine/sprite.h"

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

        // Box2D world of this scene
        b2World * PhysicsWorld;

        // NOTE: Placeholder for testing
        Sprite Entity;

        // Scene related UI
        void GUI();
};

#endif