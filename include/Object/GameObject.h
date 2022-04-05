#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "LoaderParams.h"

class GameObject
{
public:
    virtual void Draw() = 0;
    virtual void Update() = 0;
    virtual void Clean() = 0;
    virtual void Load(const LoaderParams* pParams) = 0;

protected:
    GameObject() {}
    virtual ~GameObject() {}
}; 

#endif
