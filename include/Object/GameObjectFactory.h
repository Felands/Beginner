#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include <iostream>
#include <string>
#include <map>

#include "GameObject.h"

class BaseCreator
{
public:
    virtual GameObject *CreateGameObject() const = 0;
    virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:
    static GameObjectFactory *Instance()
    {
        if(instance == nullptr) {
            instance = new GameObjectFactory();
        }
        return instance;
    }

    bool RegisterType();

    GameObject *Create(std::string typeId);

private:
    bool RegisterType(std::string typeId, BaseCreator *creator);

    static GameObjectFactory *instance;
    std::map<std::string, BaseCreator*> creators;
};

#endif
