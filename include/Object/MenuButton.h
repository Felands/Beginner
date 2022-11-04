#ifndef MENU_BOTTON_H
#define MENU_BOTTON_H

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

enum class ButtonState
{
    MOUSE_OUT,
    MOUSE_OVER,
    CLICKED
};

class MenuButton : public SDLGameObject
{
public:
    void SetCallback(void(*callback_)())
    {
        callback = callback_;
    }

    ButtonState GetState()
    {
        return state;
    }

    virtual void Update();

    virtual void Draw();

    virtual int32_t GetCallbackId()
    {
        return objectAnimeInfos[(size_t)state].callBackId;
    }

    virtual int32_t GetAnimeSpeed()
    {
        return objectAnimeInfos[(size_t)state].animeSpeed;
    }

    virtual std::string GetTextureName()
    {
        return objectAnimeInfos[(size_t)state].textureName;
    }

private:
    void (*callback)();
    bool isReleased = true;
    ButtonState state;
};

class MenuButtonCreator : public BaseCreator
{
    GameObject* CreateGameObject() const
    {
        return new MenuButton();
    }
};

#endif
