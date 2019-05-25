#ifndef CAMERA_H
#define CAMERA_H

#include "engine/ECS.h"
#include "engine/camera2d.h"

struct Camera {
    ECS_DECLARE_TYPE;

    Camera(Camera2D * C) : EngineCamera(C) { }

    Camera2D * EngineCamera;
};

ECS_DEFINE_TYPE(Camera);

#endif