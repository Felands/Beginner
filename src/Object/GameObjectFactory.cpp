#include "GameObjectFactory.h"

#include "MenuButton.h"
#include "Player.h"
#include "Enemy.h"
#include "AnimatedGraphic.h"

GameObjectFactory *GameObjectFactory::instance = nullptr;

bool GameObjectFactory::RegisterType()
{
    bool isSuccess = true;
    isSuccess = isSuccess && RegisterType("MenuButton", new MenuButtonCreator());
    isSuccess = isSuccess && RegisterType("Player", new PlayerCreator());
    isSuccess = isSuccess && RegisterType("Enemy", new EnemyCreator());
    isSuccess = isSuccess && RegisterType("AnimatedGraphic", new AnimatedGraphicCreator());
    return isSuccess;
}

bool GameObjectFactory::RegisterType(std::string typeId, BaseCreator *creator)
{
    std::map<std::string, BaseCreator*>::iterator it = creators.find(typeId);
    if(it != creators.end()) {
        delete creator;
        return false;
    }
    creators[typeId] = creator;
    return true;
}

GameObject *GameObjectFactory::Create(std::string typeId)
{
    std::map<std::string, BaseCreator*>::iterator it = creators.find(typeId);
    if(it == creators.end()) {
        std::cout << "Could not find type: " << typeId << "\n";
        return nullptr;
    }
    BaseCreator *creator = (*it).second;
    return creator->CreateGameObject();
}
