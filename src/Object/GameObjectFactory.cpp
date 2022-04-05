#include "GameObjectFactory.h"

GameObjectFactory *GameObjectFactory::s_pInstance = nullptr;

bool GameObjectFactory::RegisterType(std::string typeID, BaseCreator* pCreator)
{
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
    if(it != m_creators.end()) {
        delete pCreator;
        return false;
    }
    m_creators[typeID] = pCreator;
    return true;
}

GameObject *GameObjectFactory::Create(std::string typeID)
{
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
    if(it == m_creators.end()) {
        std::cout << "could not find type: " << typeID << "\n";
        return nullptr;
    }
    BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject();
}

GameObjectFactory *GameObjectFactory::Instance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new GameObjectFactory();
    }
    return s_pInstance;
}
