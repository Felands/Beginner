#ifndef _LOADER_PARAS_H_
#define _LOADER_PARAS_H_

#include <stdint.h>
#include <string>

#include "Resource.h"

class LoaderParams
{
public:
    LoaderParams(int32_t x, int32_t y, std::string textureID)
        : m_x(x), m_y(y), m_textureID(textureID)
    {}

    int32_t GetX() const
    {
        return m_x;
    }

    int32_t GetY() const
    {
        return m_y;
    }

    std::string GetTextureID() const
    {
        return m_textureID;
    }

private:
    int32_t m_x;
    int32_t m_y;
    std::string m_textureID;
};

#endif