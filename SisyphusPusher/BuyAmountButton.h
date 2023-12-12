#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <tuple>
#include <iostream>

#include "Button.h";
#include "Glory.h";
#include "Sisyphus.h";

class BuyAmountButton
{
public:
	BuyAmountButton(int x, int y, SDL_Texture* btn, SDL_Texture* btnHover, Sisyphus* sisyphus) :
		btn(btn), btnHover(btnHover), sisyphus(sisyphus)
	{
		rect = { x, y, 128, 64};
	}

	const int Draw(SDL_Renderer* renderer, TTF_Font* font){
		if (isHovering)
			SDL_RenderCopy(renderer, btnHover, NULL, &rect);
		else
			SDL_RenderCopy(renderer, btn, NULL, &rect);

		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, ("Buy:" + string).c_str(), { 105,105,105 });
		SDL_Rect rect1 = SDL_Rect{ rect.x + 5, rect.y + 10, surfaceMessage->w, surfaceMessage->h };
		DrawTexture(renderer, &rect1, surfaceMessage);
		SDL_FreeSurface(surfaceMessage);
		return 0;
	}

	int DrawTexture(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Surface* surface) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, texture, NULL, rect);
		SDL_DestroyTexture(texture);
		return 0;
	}

	int Update() {
		SDL_Point mouse = { 0,0 };
		SDL_GetMouseState(&mouse.x, &mouse.y);
		isHovering = SDL_PointInRect(&mouse, &rect);
		return 0;
	}

	int OnClick() {
		if (!isHovering)
			return 0;
		switch (++counter)
		{
		case 1:
			string = "1";
			break;
		case 2:
			string = "10";
			break;
		case 3:
			counter = 1;
			string = "1";
			break;
		}
		sisyphus->buyCounter = counter;
		return 0;
	}

private:
	Sisyphus* sisyphus;
	int counter = 1;
	std::string string = "1";
	bool isHovering = false;
	SDL_Rect rect;
	SDL_Texture* btn;
	SDL_Texture* btnHover;
};


