//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnRender()
{
    SDL_RenderPresent(renderer);
    SDL_Delay(time_left());
    next_time += TICK_INTERVAL;
}

//==============================================================================