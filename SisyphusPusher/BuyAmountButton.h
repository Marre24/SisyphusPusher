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
	BuyAmountButton(int x, int y, std::string buttonTexturePath, std::string hoverTexturePath, Sisyphus* sisyphus)
	{
		this->sisyphus = sisyphus;
		rect = { x, y, 128, 64};
		btn = IMG_Load(buttonTexturePath.c_str());
		btnHover = IMG_Load(hoverTexturePath.c_str());
	}

	const int Draw(SDL_Renderer* renderer, TTF_Font* font){
		if (isHovering)
			SetTexture(btnHover, renderer);
		else
			SetTexture(btn, renderer);

		SDL_Surface* surfaceMessage;
		SDL_Color color = { 105,105,105 };
		surfaceMessage = TTF_RenderText_Solid(font, ("Buy:" + string).c_str(), color);

		DrawTexture(renderer, new SDL_Rect{ rect.x + 5, rect.y + 10, surfaceMessage->w, surfaceMessage->h }, surfaceMessage);
		SDL_FreeSurface(surfaceMessage);
		return 0;
	}

	int DrawTexture(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Surface* surface) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, texture, NULL, rect);
		SDL_DestroyTexture(texture);
		return 0;
	}

	int SetTexture(SDL_Surface* surface, SDL_Renderer* renderer) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, texture, NULL, &rect);
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

	~BuyAmountButton()
	{
		delete sisyphus;
	}
private:
	int counter = 1;
	Sisyphus* sisyphus;
	std::string string = "1";
	bool isHovering = false;
	SDL_Rect rect = { 0, 0, 0, 0 };
	SDL_Surface* btn;
	SDL_Surface* btnHover;
};


