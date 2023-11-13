//==============================================================================
#include "CApp.h"
//==============================================================================

void CApp::MoveSprites()
{
    background.display(renderer);
    river[0].display(renderer);
    river[1].display(renderer);
    river[0].move();
    river[1].move();
    for (int i = 0; i < NUM_SPRITES; ++i)
    {
        
        cars[i].move();
        cars[i].display(renderer);
        logs[i].display(renderer);
        logs[i].move();
    }
    frogger.display(renderer);

    for (int i = 0; i < 3; i++) 
    {
        box[i].display(renderer);
        dvd[i].display(renderer);
    }
   
}

//==============================================================================
bool CApp::check_collision(SDL_Rect a, SDL_Rect b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // Calculate sides of rect A 
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    // Calculate sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA <= topB)
    {
        return false;
    }
    if (topA >= bottomB)
    {
        return false;
    }
    if (rightA <= leftB)
    {
        return false;
    }
    if (leftA >= rightB)
    {
        return false;
    }

    return true;
}
//==============================================================================

void CApp::OnLoop()
{
    SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
    SDL_RenderClear(renderer);
    MoveSprites();

    //Hitbox positioning
    riverBox[0].x = 0;
    riverBox[0].y = 312;
    riverBox[0].w = 416;
    riverBox[0].h = 96;

    riverBox[1].x = 0;
    riverBox[1].y = 56;
    riverBox[1].w = 416;
    riverBox[1].h = 32;

    froggerBox.x = frogger.position.x;
    froggerBox.y = frogger.position.y;

    //Collisions

    for (int i = 0; i < NUM_SPRITES; i++)
    {
        logsBox[i].x = logs[i].position.x;
        logsBox[i].y = logs[i].position.y;
        carBox[i].x = cars[i].position.x;
        carBox[i].y = cars[i].position.y;

        if (check_collision(froggerBox, carBox[i])) 
        {
            frogger.position.x = spawnPosX;
            frogger.position.y = spawnPosY;
            lives--;
            Mix_PlayChannel(-1, hit, 0);
        }

        if (check_collision(froggerBox, logsBox[i]))
        {
            frogger.velocity.x = logs[i].velocity.x;
            frogger.onLog = true;
            frogger.move();
        }
    }


if (check_collision(froggerBox, deathZone[0]) || (check_collision(froggerBox, deathZone[1])))
{
    frogger.position.x = spawnPosX;
    frogger.position.y = spawnPosY;

    //This fixes a bug where score is diminished by 2 if colliding with first death zone 
    frogger.onLog = true;
    //----------------------------------------------------------------------------------

    lives--;
    Mix_PlayChannel(-1, hit, 0);
}

    for (int i = 0; i < 3; i++) 
    {
        //Check river collision
        if (check_collision(froggerBox, riverBox[i]) && frogger.onLog == false)
        {
            frogger.position.x = spawnPosX;
            frogger.position.y = spawnPosY;
            lives--;
            Mix_PlayChannel(-1, splash, 0);
        }

        //Check DVD collision
        dvdBox[i].x = dvd[i].position.x;
        dvdBox[i].y = dvd[i].position.y;

        if (check_collision(froggerBox, dvdBox[i]))
        {
            score += 100;
            dvd[i].position.x = 600;
            Mix_PlayChannel(-1, dvdSound, 0);
        }

        //Check win zone
        if (check_collision(froggerBox, winZone[i]) && !box[i].exists)
        {
            frogger.position.x = spawnPosX;
            frogger.position.y = spawnPosY;
            score += 100;
            Mix_PlayChannel(-1, win, 0);

            //Spawn box at frogger end position
            box[i].spawnBox(winZone[i].x + 32, winZone[i].y);
            strncpy_s(box[i].imagename, "sprites\\box.bmp", 255);
            box[i].loadPlayer(renderer);
            box[i].exists = true;

            //Respawn discs
            dvd[0].placeCollectable(rand() % 352 + 0, rand() % 536 + 0);
            dvd[1].placeCollectable(rand() % 352 + 0, rand() % 536 + 0);
            dvd[2].placeCollectable(rand() % 352 + 0, rand() % 536 + 0);

            gameTimer = 25;
        }
        else if (check_collision(froggerBox, winZone[i]) && box[i].exists) 
        {
            frogger.position.x = spawnPosX;
            frogger.position.y = spawnPosY;
            lives--;
            Mix_PlayChannel(-1, hit, 0);
        }

        //Reset boxes when all 3 are placed
        if (box[0].exists && box[1].exists && box[2].exists) 
        {
            for (int i = 0; i < 3; i++) 
            {
                box[i].position.x = 600;
                box[i].exists = false;
            }
        }
    }
   
    //Display Stats
    displayGameStats(16, 576, "score: %i", score);
    displayGameStats(336, 576, "lives: %i", lives);
    displayGameStats(182, 576, "time: %i", gameTimer);

    //Check for frogger screen bounds
    if (frogger.position.x > 400 || frogger.position.x < 0 || frogger.position.y > window_h - frogger.position.h - 32|| frogger.position.y < 0 - frogger.position.h)
    {
        frogger.position.x = spawnPosX;
        frogger.position.y = spawnPosY;
        lives--;
        Mix_PlayChannel(-1, hit, 0);
    }

    //End game 
    if (lives == 0) 
    {
        displayGameEnd(window_w / 2 - 128, window_h / 2 - 96, "Game Over!", 0);
        displayGameEnd(window_w / 2 - 128, window_h / 2 - 64, "Score:%i", score);
        gameOver = true;
    }

    //Timer
    int tickTimer = SDL_GetTicks();

    if (tickTimer % 1000 <= 10 && !gameOver) 
    {
        tickTimer = 0;
        gameTimer--;
    }

    //Out of time
    if (gameTimer == 0) 
    {
        lives = 0;
        frogger.position.x = spawnPosX;
        frogger.position.y = spawnPosY;
    }
    
    frogger.onLog = false;
}