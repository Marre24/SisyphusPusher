#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <tuple>
#include <iostream>

#include "Button.h";
#include "Glory.h";
#include "Sisyphus.h";

class BuyAmountButton : Button
{
public:
	BuyAmountButton(int x, int y, std::string buttonTexturePath, std::string hoverTexturePath, Sisyphus* sisyphus) : Button(x, y, buttonTexturePath, hoverTexturePath, NULL, NULL)
	{
		this->sisyphus = sisyphus;
	}

	const int Draw(SDL_Renderer* renderer){
		Button::Draw(renderer);

		SDL_Surface* surfaceMessage;
		SDL_Color color = { 105,105,105 };
		surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 30), ("Buy: " + string).c_str(), color);

		DrawTexture(renderer, new SDL_Rect{ rect.x + 30, rect.y + 5, surfaceMessage->w, surfaceMessage->h }, surfaceMessage);
		SDL_FreeSurface(surfaceMessage);
		TTF_CloseFont(TTF_OpenFont(fontPath, 30));
		return 0;
	}

	int DrawTexture(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Surface* surface) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, texture, NULL, rect);
		SDL_DestroyTexture(texture);
		return 0;
	}

	int Update() {
		Button::Update();
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
	const char* fontPath = "FieldGuide.TTF";
};


