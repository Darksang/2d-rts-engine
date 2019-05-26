#ifndef SPRITE_H
#define SPRITE_H

#include "engine/texture.h"
#include "engine/transform.h"

class Sprite {
    public:
        Sprite() { }
        Sprite(Texture SpriteTexture) : SpriteTexture(SpriteTexture) { }

        Transform Transform;
        Texture SpriteTexture;
};

#endif