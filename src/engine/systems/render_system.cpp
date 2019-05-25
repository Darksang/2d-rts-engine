#include "engine/systems/render_system.h"

#include "engine/components/sprite.h"
#include "engine/components/transform.h"

RenderSystem::RenderSystem(SpriteRenderer * Renderer) {
    this->Renderer = Renderer;
}

void RenderSystem::configure(ECS::World * world) {

}

void RenderSystem::unconfigure(ECS::World * world) {

}

void RenderSystem::tick(ECS::World * world, float deltaTime) {
    // This systems draws all Entities with Sprite and Transform components
    world->each<Sprite, Transform>([&](ECS::Entity * E, ECS::ComponentHandle<Sprite> S, ECS::ComponentHandle<Transform> T) -> void {
        Renderer->Draw(T.get(), S.get());
    });
}