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
	StrButton(int x, int y, std::string buttonTexturePath, std::string hoverTexturePath, Sisyphus* sisyphus, LargeNumber* cost, LargeNumber* reward, float coefficient, int id) : 
		Button(x, y, buttonTexturePath, hoverTexturePath, cost, coefficient)
	{
		this->id = id;
		this->reward = reward;
		this->sisyphus = sisyphus;
		border = IMG_Load(borderTexturePath.c_str());
		greenColor = IMG_Load(greenTexturePath.c_str());
		borderRect = new SDL_Rect{ x , y + 80, 256, 16 };
		greenRect = new SDL_Rect{ x, y + 80, 16, 16 };
	}

	int Draw(SDL_Renderer* renderer){
		Button::Draw(renderer);
		
		SDL_Surface* surfaceMessage;
		SDL_Color color;
		if (sisyphus->glory->IsGreaterThan(cost))
			color = { 50, 205,50 };
		else
			color = { 255, 0, 0 };
		if (nextGoal > 400) {
			color = { 105,105,105 };
			surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 30), "MAX", color);
		}
		else
			surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 30), cost->ToString().c_str(), color);


		DrawTexture(renderer, new SDL_Rect{ rect.x + 10, rect.y- 5, surfaceMessage->w, surfaceMessage->h }, surfaceMessage);
		surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 20), std::to_string(amountBought).c_str(), {211,211,211});
		DrawTexture(renderer, new SDL_Rect{ rect.x + 10, rect.y + 20, surfaceMessage->w, surfaceMessage->h }, surfaceMessage);
		DrawTexture(renderer, greenRect, greenColor);
		DrawTexture(renderer, borderRect, border);

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
		if (nextGoal > 400)
			greenRect->w = borderRect->w;
		else
			greenRect->w = borderRect->w * amountBought / nextGoal;
		return 0;
	}

	int OnClick() {
		if (!isHovering || nextGoal > 400)
			return 0;
		if (sisyphus->glory->Pay(cost) < 0)
			return -1;

		if (++amountBought == nextGoal)
		{
			sisyphus->GoalReached(id, goals[amountBought]);
			nextGoal *= 2;
		}
		cost->Times(coefficient);
		sisyphus->Strengthen(reward, id);
		return 0;
	}

private:
	int amountBought = 350;
	float nextGoal = 400;
	int counter = 0;
	std::map<int, float> goals = {
		{25, 2.0f},
		{50, 3.0f},
		{100, 2.0f},
		{200, 2.0f},
		{400, 4.0f},
	};
	Sisyphus* sisyphus;
	LargeNumber* reward;
	const char* fontPath = "FieldGuide.TTF";
	SDL_Surface* border;
	SDL_Surface* greenColor;
	const std::string borderTexturePath = "StaminaBar.png";
	const std::string greenTexturePath = "Stamina.png";
	SDL_Rect* borderRect;
	SDL_Rect* greenRect;
	int id;
};

