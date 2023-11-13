//==============================================================================
#include "CPlayer.h"
#include "CApp.h"
//==============================================================================

int CPlayer::loadPlayer(SDL_Renderer *renderer)
{
    SDL_Surface *temp;

    temp = SDL_LoadBMP(imagename);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s", imagename, SDL_GetError());
        return (-1);
    }

    position.w = temp->w;
    position.h = temp->h;

    if (temp->format->palette)
    {
        SDL_SetColorKey(temp, SDL_TRUE, *(Uint8 *) temp->pixels);
    }
    else
    {
        switch (temp->format->BitsPerPixel)
        {
        case 15:
            SDL_SetColorKey(temp, SDL_TRUE,
                            (*(Uint16 *) temp->pixels) & 0x00007FFF);
            break;
        case 16:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint16 *) temp->pixels);
            break;
        case 24:
            SDL_SetColorKey(temp, SDL_TRUE,
                            (*(Uint32 *) temp->pixels) & 0x00FFFFFF);
            break;
        case 32:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint32 *) temp->pixels);
            break;
        }
    }

    texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!texture)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return (-1);
    }

    SDL_FreeSurface(temp);

    return (0);
}

//==============================================================================

void CPlayer::display(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &position);
}

//==============================================================================

void CPlayer::move()
{
    SDL_Rect *p;
    SDL_Rect *v;

    p = &position;
    v = &velocity;

    p->x += v->x;
    p->y += v->y;

    //Objects wrap around screen
    if ((p->x - p->w >= (window_w - p->w)))
    {
        p->x = -p->w;
    }
    else if (p->x <= -p->w) 
    {
        p->x = window_w;
    }
}

//==============================================================================

void CPlayer::spawnFrogger() 
{
    position.x = 196; // Center
    position.y = 536; // 64 pixels above bottom
    velocity.x = 0;
    velocity.y = 0;
}