#include <stdint.h>
#include "SDL.h"

class ScrollingBackground
{
public:
    /*void Load(std::unique_ptr<LoaderParams> const &pParams);

    void Draw();

    void Update();*/

private:
    uint32_t count;
    uint32_t maxcount;
    int32_t scrollSpeed;
    SDL_Rect srcRect1;
    SDL_Rect destRect1;
    SDL_Rect srcRect2;
    SDL_Rect destRect2;
};