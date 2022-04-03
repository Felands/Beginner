#ifndef _ANIMATED_GRAPHIC_H_
#define _ANIMATED_GRAPHIC_H_

#include <stdint.h>

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
public:
    void Update();
};

class AnimatedGraphicCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new AnimatedGraphic();
    }
};

#endif
