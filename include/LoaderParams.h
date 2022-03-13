#ifndef _LOADER_PARAMS_H_
#define _LOADER_PARAMS_H_

#include <stdint.h>
#include <string>

class LoaderParams
{
public:
    LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames/*, int callbackID = 0, int animSpeed = 0*/) :
    m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID), m_numFrames(numFrames)
    /*, m_callbackID(callbackID), m_animSpeed(animSpeed)*/
    {}

    int32_t GetX() const
    {
        return m_x;
    }

    int32_t GetY() const
    {
        return m_y;
    }

    uint32_t GetWidth() const
    {
        return m_width;
    }

    uint32_t GetHeight() const
    {
        return m_height;
    }

    std::string GetTextureID() const
    {
        return m_textureID;
    }

    uint32_t GetNumFrames() const
    {
        return m_numFrames;
    }

private:
    int32_t m_x;
    int32_t m_y;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_numFrames;
    std::string m_textureID;
};

#endif