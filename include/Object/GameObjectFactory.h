#ifndef _GAME_OBJECT_FACTORY_H_
#define _GAME_OBJECT_FACTORY_H_

#include <iostream>
#include <string>
#include <map>

#include "GameObject.h"

class BaseCreator
{
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:
    bool RegisterType(std::string typeID, BaseCreator* pCreator);

    GameObject *Create(std::string typeID);

    static GameObjectFactory *Instance();

private:
    std::map<std::string, BaseCreator*> m_creators;
    static GameObjectFactory *s_pInstance;
};

#endif
