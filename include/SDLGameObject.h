#ifndef _SDL_GAME_OBJECT_H_
#define _SDL_GAME_OBJECT_H_

#include <stdint.h>
#include <string>
#include <memory>

#include "SDLGameObject.h"
#include "GameObject.h"
#include "LoaderParams.h"

class SDLGameObject : public GameObject
{
public:
    SDLGameObject();

    virtual void Load(std::unique_ptr<LoaderParams> pParams);

    virtual void Draw();

    virtual void Update();

    virtual void Clean();

    virtual void Collision();
};

#endif