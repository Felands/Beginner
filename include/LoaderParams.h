#ifndef _LOADER_PARAS_H_
#define _LOADER_PARAS_H_

#include <string>

class LoaderParams
{
public:
    LoaderParams(int x, int y, int width, int height, std::string textureID)
        : m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID)
    {}

    int GetX() const
    { return m_x; }

    int GetY() const
    { return m_y; }

    int GetWidth() const
    { return m_width; }

    int GetHeight() const
    { return m_height; }

    std::string GetTextureID() const
    { return m_textureID; }

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    std::string m_textureID;
};

#endif