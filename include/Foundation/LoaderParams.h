#ifndef _LOADER_PARAS_H_
#define _LOADER_PARAS_H_

#include <string>

class LoaderParams
{
public:
    LoaderParams(int32_t x, int32_t y, uint32_t width, uint32_t height, std::string textureID, uint32_t numFrames,
        int32_t callbackID = 0, int32_t animSpeed = 0):
        m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID), m_numFrames(numFrames),
        m_callbackID(callbackID), m_animSpeed(animSpeed)
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

    uint32_t GetNumFrames() const
    {
        return m_numFrames;
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
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_numFrames;
    int32_t m_callbackID;
    int32_t m_animSpeed;
    std::string m_textureID;
};

#endif