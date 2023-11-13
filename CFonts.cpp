#include "CApp.h"

void CApp::displayGameStats(int x, int y, const char* formattedString, int number) 
{
	SDL_DestroyTexture(messageTexture);
	SDL_FreeSurface(messageSurface);

	sprintf_s(message, formattedString, number);
	messageSurface = TTF_RenderText_Solid(font, message, color);
	messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(messageTexture, NULL, NULL, &texW, &texH);
	messageRect = { x, y, texW, texH };
	SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);
}


void CApp::displayGameEnd(int x, int y, const char* formattedString, int number)
{
	SDL_DestroyTexture(messageTexture);
	SDL_FreeSurface(messageSurface);

	sprintf_s(message, formattedString, number);
	messageSurface = TTF_RenderText_Solid(largeFont, message, redColor);
	messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(messageTexture, NULL, NULL, &texW, &texH);
	messageRect = { x, y, texW, texH };
	SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);
}