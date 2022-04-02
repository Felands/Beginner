#ifndef _GAME_OBJECT_FACTORY_H_
#define _GAME_OBJECT_FACTORY_H_

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
    bool registerType(std::string typeID, BaseCreator* pCreator)
    {
        std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
        // if the type is already registered, do nothing
        if(it != m_creators.end()) {
            delete pCreator;
            return false;
        }
        m_creators[typeID] = pCreator;
        return true;
    }

    GameObject* create(std::string typeID)
    {
        std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
        if(it == m_creators.end()) {
            std::cout << "could not find type: " << typeID << "\n";
            return NULL;
        }
        BaseCreator* pCreator = (*it).second;
        return pCreator->createGameObject();
    }

    static GameObjectFactory* Instance()
    {
        if(s_pInstance == nullptr)
        {
            s_pInstance = new GameObjectFactory();
        }
        return s_pInstance;
    }

private:
    std::map<std::string, BaseCreator*> m_creators;
    static GameObjectFactory *s_pInstance;
};

#endif
