#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "engine/ECS.h"

#include "engine/sprite_renderer.h"

class RenderSystem : public ECS::EntitySystem {
    public:
        RenderSystem(SpriteRenderer * Renderer);
        ~RenderSystem() { 
            Renderer = 0;
        }

        void configure(ECS::World * world) override;
        void unconfigure(ECS::World * world) override;
        void tick(ECS::World * world, float deltaTime) override;
        
    private:
        SpriteRenderer * Renderer;
};

#endif