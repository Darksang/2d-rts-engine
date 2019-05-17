#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "game/steering.h"

class Behaviour {
    public:
        float Priority;

        virtual Steering GetSteering();
};

#endif