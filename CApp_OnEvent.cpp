//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT||Event->type == SDL_KEYDOWN) {
        Running = false;
    }

    switch (Event->type) 
    {
    case SDL_JOYBUTTONDOWN:
        if (Event->jbutton.button == 11 && !gameOver)
        {
            score += 10;
            strncpy_s(frogger.imagename, "sprites\\frogger_up.bmp", 255);
            frogger.loadPlayer(renderer);
            frogger.position.y -= 32;
            Mix_PlayChannel(-1, jump, 0);
        }
        else if (Event->jbutton.button == 12 && !gameOver) 
        {
            score -= 10;
            strncpy_s(frogger.imagename, "sprites\\frogger_down.bmp", 255);
            frogger.loadPlayer(renderer);
            frogger.position.y += 32;
            Mix_PlayChannel(-1, jump, 0);
        }
        else if (Event->jbutton.button == 13 && !gameOver)
        {
            strncpy_s(frogger.imagename, "sprites\\frogger_left.bmp", 255);
            frogger.loadPlayer(renderer);
            frogger.position.x -= 32;
            Mix_PlayChannel(-1, jump, 0);
        }
        else if (Event->jbutton.button == 14 && !gameOver)
        {
            strncpy_s(frogger.imagename, "sprites\\frogger_right.bmp", 255);
            frogger.loadPlayer(renderer);
            frogger.position.x += 32;
            Mix_PlayChannel(-1, jump, 0);
        }
        else if (Event->jbutton.button == 0 && gameOver == true)
        {
            //Reset Boxes, score, time, dvd, and lives when game over
            score = 0;
            lives = 3;
            gameTimer = 20;
            gameOver = false;
            for (int i = 0; i < 3; i++) 
            {
                box[i].position.x = 600;
                box[i].exists = false;
            }

            dvd[0].placeCollectable(rand() % 352 + 0, rand() % 536 + 0);
            dvd[1].placeCollectable(rand() % 352 + 0, rand() % 536 + 0);
            dvd[2].placeCollectable(rand() % 352 + 0, rand() % 536 + 0);

            strncpy_s(frogger.imagename, "sprites\\frogger_up.bmp", 255);
            frogger.loadPlayer(renderer);
        }
        break;
    }
    
}

//==============================================================================
