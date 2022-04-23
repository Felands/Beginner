#ifndef _ANIMATED_GRAPHIC_H_
#define _ANIMATED_GRAPHIC_H_

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{};

class AnimatedGraphicCreator : public BaseCreator
{
    GameObject* CreateGameObject() const
    {
        return new AnimatedGraphic();
    }
};

#endif
