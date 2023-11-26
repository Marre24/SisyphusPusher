#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <tuple>
#include <iostream>

#include "Button.h";
#include "Glory.h";
#include "Sisyphus.h";

class StrButton : Button
{
public:
	StrButton(int x, int y, int width, int height, std::string buttonTexturePath, std::string hoverTexturePath, Sisyphus* sisyphus, LargeNumber* cost, LargeNumber* reward) : Button(x, y, width,height, buttonTexturePath, hoverTexturePath)
	{
		this->reward = reward;
		this->sisyphus = sisyphus;
		this->cost = cost;
	}

	int Draw(SDL_Renderer* renderer){
		Button::Draw(renderer);
		
		SDL_Surface* surfaceMessage;
		if (sisyphus->glory->IsGreaterThan(cost))
			surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 30), cost->ToString().c_str(), { 0, 255, 0 });
		else
			surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 30), cost->ToString().c_str(), { 255, 0, 0 });

		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		SDL_Rect textRect = { rect.x + 50, rect.y, surfaceMessage->w, surfaceMessage->h };
		SDL_RenderCopy(renderer, message, NULL, &textRect);

		SDL_DestroyTexture(message);
		SDL_FreeSurface(surfaceMessage);

		TTF_CloseFont(TTF_OpenFont(fontPath, 30));
		return 0;
	}

	int Update() {
		Button::Update();


		return 0;
	}

	int OnClick() {
		if (!isHovering)
			return 0;
		if (sisyphus->glory->Pay(cost) < 0)
			return -1;

		sisyphus->Strengthen(reward);
		return 0;
	}

private:
	Sisyphus* sisyphus;
	LargeNumber* cost;
	LargeNumber* reward;
	const char* fontPath = "FieldGuide.TTF";
};

