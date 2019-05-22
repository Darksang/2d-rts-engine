#ifndef SPRITE_H
#define SPRITE_H

#include "engine/ecs/ECS.h"

#include "engine/texture.h"

struct Sprite {
    ECS_DECLARE_TYPE;

    Sprite(Texture & Texture) : SpriteTexture(Texture) { }

    Texture SpriteTexture;
};

ECS_DEFINE_TYPE(Sprite);

#endif