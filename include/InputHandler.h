#include <vector>

#include "SDL.h"
enum mouse_buttons
{
 LEFT = 0,
 MIDDLE = 1,
 RIGHT = 2
};

class InputHandler
{
public:
 static InputHandler* Instance()
 {
 if(s_pInstance == 0)
 {
 s_pInstance = new InputHandler();
 }
 return s_pInstance;
 }
 void update();
 void clean();
 Vector2D* getMousePosition()
{
 return m_mousePosition;
}

private:
    // private functions to handle different event types
// handle keyboard events
void onKeyDown();
void onKeyUp();
// handle mouse events
void onMouseMove(SDL_Event& event);
void onMouseButtonDown(SDL_Event& event);
void onMouseButtonUp(SDL_Event& event);
// handle joysticks events
void onJoystickAxisMove(SDL_Event& event);
void onJoystickButtonDown(SDL_Event& event);
void onJoystickButtonUp(SDL_Event& event);

private:
 InputHandler();
 ~InputHandler() {}
 static InputHandler* s_pInstance;
 std::vector<bool> m_mouseButtonStates;
 Vector2D* m_mousePosition;
 Uint8* m_keystate;
};