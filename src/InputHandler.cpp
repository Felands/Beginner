#include "InputHandler.h"

void InputHandler::initialiseJoysticks()
{
 if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
 {
 SDL_InitSubSystem(SDL_INIT_JOYSTICK);
 }
 if(SDL_NumJoysticks() > 0)
 {
 for(int i = 0; i < SDL_NumJoysticks(); i++)
 {
 SDL_Joystick* joy = SDL_JoystickOpen(i);
if(SDL_JoystickOpened(i) == 1)
 {
 m_joysticks.push_back(joy);
 }
 else
 {
 std::cout << SDL_GetError();
 }
 }
 SDL_JoystickEventState(SDL_ENABLE);
 m_bJoysticksInitialised = true;
 std::cout << "Initialised "<< m_joysticks.size() << " 
 joystick(s)";
 }
 else
 {
 m_bJoysticksInitialised = false;
 }
}

InputHandler::InputHandler()
{
    for(int i = 0; i < 3; i++)
    {
        m_mouseButtonStates.push_back(false);
    }
}



void InputHandler::clean()
{
 if(m_bJoysticksInitialised)
 {
 for(unsigned int i = 0; i < SDL_NumJoysticks(); i++)
 {
 SDL_JoystickClose(m_joysticks[i]);
 }
 }
}

void InputHandler::update()
{
 SDL_Event event;
 while(SDL_PollEvent(&event))
 {
 if(event.type == SDL_MOUSEBUTTONDOWN)
{
 if(event.button.button == SDL_BUTTON_LEFT)
 {
 m_mouseButtonStates[LEFT] = true;
 }
 if(event.button.button == SDL_BUTTON_MIDDLE)
 {
 m_mouseButtonStates[MIDDLE] = true;
 }
 if(event.button.button == SDL_BUTTON_RIGHT)
 {
 m_mouseButtonStates[RIGHT] = true;
 }
}
if(event.type == SDL_MOUSEBUTTONUP)
{
 if(event.button.button == SDL_BUTTON_LEFT)
 {
 m_mouseButtonStates[LEFT] = false;
 }
 if(event.button.button == SDL_BUTTON_MIDDLE)
 {
 m_mouseButtonStates[MIDDLE] = false;
 }
 if(event.button.button == SDL_BUTTON_RIGHT)
 {
 m_mouseButtonStates[RIGHT] = false;
 }
}
if(event.type == SDL_MOUSEMOTION)
{
 m_mousePosition->setX(event.motion.x);
 m_mousePosition->setY(event.motion.y);
}
 }
 m_keystates = SDL_GetKeyboardState(0);

}

bool getMouseButtonState(int buttonNumber)
{
 return m_mouseButtonStates[buttonNumber];
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
 if(m_keystates != 0)
 {
 if(m_keystates[key] == 1)
 {
 return true;
 }
 else
 {
 return false;
 }
 }
 return false;
}

void InputHandler::update()
{
 SDL_Event event;
 while(SDL_PollEvent(&event))
 {
 switch (event.type)
 {
 case SDL_QUIT:
 TheGame::Instance()->quit();
 break;
 case SDL_JOYAXISMOTION:
 onJoystickAxisMove(event);
 break;
 case SDL_JOYBUTTONDOWN:
 onJoystickButtonDown(event);
 break;
 case SDL_JOYBUTTONUP:
 onJoystickButtonUp(event);
 break;
 case SDL_MOUSEMOTION:
 onMouseMove(event);
 break;
 case SDL_MOUSEBUTTONDOWN:
 onMouseButtonDown(event);
 break;
 case SDL_MOUSEBUTTONUP:
 onMouseButtonUp(event);
 break;
 case SDL_KEYDOWN:
 onKeyDown();
 break;
 case SDL_KEYUP:
 onKeyUp();
 break;
 default:
 break;
 }
 }
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
 if(event.button.button == SDL_BUTTON_LEFT)
 {
 m_mouseButtonStates[LEFT] = true;
 }
 if(event.button.button == SDL_BUTTON_MIDDLE)
 {
 m_mouseButtonStates[MIDDLE] = true;
 }
 if(event.button.button == SDL_BUTTON_RIGHT)
 {
 m_mouseButtonStates[RIGHT] = true;
 }
}