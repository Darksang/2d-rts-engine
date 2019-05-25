#ifndef INPUT_H
#define INPUT_H

#include "engine/ECS.h"
#include "engine/input_state.h"

struct Input {
    ECS_DECLARE_TYPE;

    Input(InputState * I) : EngineInput(I) { }

    InputState * EngineInput;
};

ECS_DEFINE_TYPE(Input);

#endif