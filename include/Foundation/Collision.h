#ifndef COLLISION_H
#define COLLISION_H

#include <stdint.h>

#include "SDL_rect.h"

const static int g_buffer = 4;
static bool RectRect(SDL_Rect* A, SDL_Rect* B)
{
    int aHBuf = A->h / g_buffer;
    int aWBuf = A->w / g_buffer;
    int bHBuf = B->h / g_buffer;
    int bWBuf = B->w / g_buffer;
    // if the bottom of A is less than the top of B - no collision
    if((A->y + A->h) - aHBuf <= B->y + bHBuf) { return false; }
    // if the top of A is more than the bottom of B = no collision
    if(A->y + aHBuf >= (B->y + B->h) - bHBuf) { return false; }
    // if the right of A is less than the left of B - no collision
    if((A->x + A->w) - aWBuf <= B->x + bWBuf) { return false; }
    // if the left of A is more than the right of B - no collision
    if(A->x + aWBuf >= (B->x + B->w) - bWBuf) { return false; }
    // otherwise there has been a collision
    return true;
}

#endif