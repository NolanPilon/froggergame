#ifndef _CAPP_H_
#define _CAPP_H_

#define TICK_INTERVAL    10
#define NUM_SPRITES     30
#define MAX_SPEED       1

#include <string.h>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <SDL_mixer.h>

#include "mywindow.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "CPlayer.h"
#include "CCars.h"
#include "CScroll_Player.h"
#include "CLogs.h"
#include "CBox.h"
#include "CCollectable.h"
//==============================================================================

class CApp
{

private:
    int score = 0;
    int lives = 3;
    int spawnPosX = 196;
    int spawnPosY = 536;
    int gameTimer = 25;
    bool Running;

    Uint32 next_time;
    SDL_Window *window;
    SDL_Renderer *renderer;

    //Objects
    CPlayer frogger;
    CPlayer background;
    CScroll_Player river[2];
    CCars cars[NUM_SPRITES];
    CLogs logs[NUM_SPRITES];
    Collectable dvd[NUM_SPRITES];
    CBox box[3];

    //Fonts
    TTF_Font* font;
    TTF_Font* largeFont;
    SDL_Color color;
    SDL_Color redColor;
    SDL_Surface* messageSurface;
    SDL_Texture* messageTexture;
    SDL_Rect messageRect;
    char message[100];

    //HitBoxes
    SDL_Rect froggerBox;
    SDL_Rect riverBox[2];
    SDL_Rect deathZone[2];
    SDL_Rect winZone[3];
    SDL_Rect carBox[NUM_SPRITES];
    SDL_Rect logsBox[NUM_SPRITES];
    SDL_Rect dvdBox[3];
    
    //Audio
    Mix_Chunk* jump = NULL;
    Mix_Chunk* hit = NULL;
    Mix_Chunk* splash = NULL;
    Mix_Chunk* win = NULL;
    Mix_Chunk* dvdSound = NULL;
  
    SDL_Joystick* joy = NULL;

public:
    CApp();
    Uint32 time_left(void);
    int OnExecute();
    bool gameOver = false;

public:
    void displayGameStats(int x, int y,const char* formattedString, int number);
    void displayGameEnd(int x, int y, const char* formattedString, int number);
    void OnEvent(SDL_Event* Event);
    bool OnInit();
    bool check_collision(SDL_Rect a, SDL_Rect b);

    void OnLoop();

    void OnRender();
    void MoveSprites();
    void OnCleanup();
};

//==============================================================================

#endif
