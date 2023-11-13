//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnCleanup() {

    //Free chunks
    Mix_FreeChunk(jump);
    Mix_FreeChunk(win);
    Mix_FreeChunk(hit);
    Mix_FreeChunk(dvdSound);
    Mix_FreeChunk(splash);

    //Free pointers
    splash = NULL;
    win = NULL;
    jump = NULL;
    hit = NULL;
    dvdSound = NULL;
    joy = NULL;
    messageSurface = NULL;
    messageTexture = NULL;
    font = NULL;
    largeFont = NULL;
    window = NULL;
    renderer = NULL;

    //Close subsystems
    Mix_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_CloseAudio();
    SDL_JoystickClose(0);
    SDL_Quit();
}
//==============================================================================
