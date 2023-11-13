//==============================================================================
#include "CApp.h"
//==============================================================================

bool CApp::OnInit()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) < 0)
    {
        return false;
    }

    //Open joystick
    if (SDL_NumJoysticks() > 0)
    {
        joy = SDL_JoystickOpen(0);
    }

    //TTF init
    TTF_Init();
    font = TTF_OpenFont("PixelFont.TTF", 12);
    largeFont = TTF_OpenFont("PixelFont.TTF", 32);
    color = { 255, 255, 255 };
    redColor = { 255, 0, 0 };

    //Initialise Mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    //Create window
    window = SDL_CreateWindow("Frogger Game - Nolan",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!window)
        return false;
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
        return false;

    //Print number of joysticks for debugging
    printf("Number of joysticks connected: %i\n", SDL_NumJoysticks());

    srand(time(NULL));

    //Create bg
    strncpy_s(background.imagename, "sprites\\background.bmp", 255);
    background.loadPlayer(renderer);

    //Create Frogger
    strncpy_s(frogger.imagename, "sprites\\frogger_up.bmp", 255);
    froggerBox.w = 32;
    froggerBox.h = 32;
    frogger.spawnFrogger();
    frogger.loadPlayer(renderer);
    
    //Load audio
    jump = Mix_LoadWAV("sounds\\jump.wav");
    hit = Mix_LoadWAV("sounds\\hit.wav");
    splash = Mix_LoadWAV("sounds\\splash.wav");
    win = Mix_LoadWAV("sounds\\win.wav");
    dvdSound = Mix_LoadWAV("sounds\\dvd.wav");
   
    //Cars lane 1
    cars[0].spawnCar(0, 504, -1);
    cars[1].spawnCar(128, 504, -1);
    cars[2].spawnCar(256, 504, -1);
    
    //Cars lane 2
    cars[3].spawnCar(128, 472, 1);
    cars[4].spawnCar(256, 472, 1);
    cars[5].spawnCar(384, 472, 1);

    //Cars lane 3
    cars[6].spawnCar(64, 440, -1);
    cars[7].spawnCar(192, 440, -1);
    cars[8].spawnCar(320, 440, -1);

    //Cars lane 4
    cars[9].spawnCar(0, 248, -3);
    cars[10].spawnCar(272, 248, -3);

    //Cars lane 5
    cars[11].spawnCar(0, 216, 1);
    cars[12].spawnCar(128, 216, 1);

    //Cars lane 6
    cars[13].spawnCar(0, 184, -2);
    cars[14].spawnCar(128, 184, -2);
    cars[15].spawnCar(256, 184, -2);

    //Render Cars and hitbox
    for (int i = 0; i < 16; i++)
    {
        if (cars[i].velocity.x < 0)
        {
            strncpy_s(cars[i].imagename, "sprites\\car_left.bmp", 255);
        }
        else
        {
            strncpy_s(cars[i].imagename, "sprites\\car_right.bmp", 255);
        }

        cars[i].loadPlayer(renderer);
        carBox[i].w = 32;
        carBox[i].h = 32;
    }

    //Create logs 
    logs[0].spawnLogs(256, 376, 2);
    logs[1].spawnLogs(0, 376, 2);
    logs[2].spawnLogs(256, 344, 1);
    logs[3].spawnLogs(0, 344, 1);
    logs[4].spawnLogs(0, 312, 3);
    logs[5].spawnLogs(256, 312, 3);
    logs[6].spawnLogs(0, 56, 1);
 
    logs[2].isLong = true;
    logs[3].isLong = true;
    logs[6].isLong = true;

    //Render and add hitbox
    for (int i = 0; i < 7; i++) 
    {
        if (logs[i].isLong)  
        {
            strncpy_s(logs[i].imagename, "sprites\\double_barrel.bmp", 255);
            logsBox[i].w = 124;
            logsBox[i].h = 32;
        }
        else 
        {
            strncpy_s(logs[i].imagename, "sprites\\barrel.bmp", 255);
            logsBox[i].w = 60;
            logsBox[i].h = 32;
        }
        logs[i].loadPlayer(renderer);
    }
    
    //Create Rivers
    strncpy_s(river[0].imagename, "sprites\\river.bmp", 255);
    river[0].loadPlayer(renderer);
    river[0].set_scroll_loc(0, 0, window_w, 96);
    river[0].destscr.y = 312;
    river[0].destscr.h = 96;
    river[0].destscr.w = 416;

    strncpy_s(river[1].imagename, "sprites\\river.bmp", 255);
    river[1].loadPlayer(renderer);
    river[1].set_scroll_loc(0, 0, window_w, 32);
    river[1].destscr.y = 52;
    river[1].destscr.h = 38;
    river[1].destscr.w = 416;

    //Create win zones
    for (int i = 0; i < 3; i++) 
    {
        winZone[i].w = 96;
        winZone[i].h = 52;
    }

    winZone[0].x = 0;
    winZone[0].y = 0;

    winZone[1].x = 160;
    winZone[1].y = 0;

    winZone[2].x = 320;
    winZone[2].y = 0;

    //Death zones
    deathZone[0].w = 64;
    deathZone[0].h = 52;
    deathZone[0].x = 96;
    deathZone[0].y = 0;

    deathZone[1].w = 64;
    deathZone[1].h = 52;
    deathZone[1].x = 256;
    deathZone[1].y = 0;

    //Create onitial collectables
    for (int i = 0; i < 3; i++)
    {
        dvdBox[i].w = 32;
        dvdBox[i].h = 32;
        dvd[i].placeCollectable(rand() % 352 + 0, rand() % 536 + 0);
        strncpy_s(dvd[i].imagename, "sprites\\dvd.bmp", 255);
        dvd[i].loadPlayer(renderer);
    }


    return true;
}
//==============================================================================
