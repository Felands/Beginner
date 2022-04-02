#ifndef _LOADER_PARAS_H_
#define _LOADER_PARAS_H_

#include <stdint.h>
#include <string>

#include "Resource.h"

class LoaderParams
{
public:
    LoaderParams(int32_t x, int32_t y, std::string textureID, int32_t callbackID = 0, int32_t animSpeed = 0)
        : m_x(x), m_y(y), m_textureID(textureID), m_callbackID(callbackID), m_animSpeed(animSpeed)
    {}

    int32_t GetX() const
    {
        return m_x;
    }

    int32_t GetY() const
    {
        return m_y;
    }

    int32_t GetCallBackID() const
    {
        return m_callbackID;
    }

    int32_t GetAnimSpeed() const
    {
        return m_animSpeed;
    }

    std::string GetTextureID() const
    {
        return m_textureID;
    }

private:
    int32_t m_x;
    int32_t m_y;
    int32_t m_callbackID;
    int32_t m_animSpeed;
    std::string m_textureID;
};

#endif