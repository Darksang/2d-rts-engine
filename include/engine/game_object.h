#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

class GameObject {
    public:
        GameObject(const std::string & Name);

        std::string Name;
};

#endif