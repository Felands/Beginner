#ifndef _ANIMATED_GRAPHIC_H_
#define _ANIMATED_GRAPHIC_H_

#include <stdint.h>

#include "LoaderParams.h"
#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
    void Update();

private:
    int32_t m_animSpeed;
};

#endif
