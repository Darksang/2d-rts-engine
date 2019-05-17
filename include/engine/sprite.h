#ifndef SPRITE_H
#define SPRITE_H

#include "engine/texture.h"
#include "engine/transform2d.h"

class Sprite {
    public:
        Sprite(Texture SpriteTexture) : SpriteTexture(SpriteTexture) { }

        Transform2D Transform;
        Texture SpriteTexture;
};

#endif