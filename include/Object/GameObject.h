#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <string>

class GameObject
{
public:
    virtual void Load(int32_t x, int32_t y, int32_t callBackId, int32_t animeSpeed, std::vector<std::string> textureNames) = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Clean() = 0;
}; 

#endif
