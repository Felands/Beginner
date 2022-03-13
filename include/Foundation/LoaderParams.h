#ifndef _LOADER_PARAS_H_
#define _LOADER_PARAS_H_

#include <stdint.h>
#include <string>

class LoaderParams
{
public:
    LoaderParams(int32_t x, int32_t y, int32_t width, int32_t height, std::string textureID)
        : m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID)
    {}

    int32_t GetX() const
    {
        return m_x;
    }

    int32_t GetY() const
    {
        return m_y;
    }

    int32_t GetWidth() const
    {
        return m_width;
    }

    int32_t GetHeight() const
    {
        return m_height;
    }

    std::string GetTextureID() const
    {
        return m_textureID;
    }

private:
    int32_t m_x;
    int32_t m_y;
    int32_t m_width;
    int32_t m_height;
    std::string m_textureID;
};

#endif