//==============================================================================
#ifndef CPLAYER_H
#define CPLAYER_H

#include <string.h>
#include <cstdio>

#include "mywindow.h"
#include "SDL.h"
//==============================================================================

class CPlayer
{
    public:
            char imagename[255];
            SDL_Rect position;
            SDL_Rect velocity;
            bool loaded;
            bool onLog = false;

            CPlayer(const char image[]="",int x=0, int y=0, int vx=0, int vy=0)
            {
                strncpy_s(imagename,image,255);
                position.x = x;
                position.y = y;
                velocity.x = vx;
                velocity.y = vy;
                loaded = false;
            }

            int loadPlayer(SDL_Renderer* prenderer);
            void display(SDL_Renderer *prenderer);
            void spawnFrogger();
            void move();
    
    protected:
            SDL_Texture *texture;

};

//==============================================================================

#endif
