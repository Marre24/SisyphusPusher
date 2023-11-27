#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <tuple>
#include <iostream>

#include "Button.h";
#include "Glory.h";
#include "Sisyphus.h";

class StaminaRefillButton : Button
{
public:
	StaminaRefillButton(int x, int y, std::string buttonTexturePath, std::string hoverTexturePath, Sisyphus* sisyphus, LargeNumber* cost, float staminaReward, float coefficient) : 
		Button(x, y, buttonTexturePath, hoverTexturePath, cost, coefficient)
	{
		this->cost = cost;
		this->staminaReward = staminaReward;
		this->sisyphus = sisyphus;
	}

	int Draw(SDL_Renderer* renderer) {
		Button::Draw(renderer);
		SDL_Surface* surfaceMessage;
		if (sisyphus->glory->IsGreaterThan(cost))
			surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 30), cost->ToString().c_str(), { 50,205,50 });
		else
			surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 30), cost->ToString().c_str(), { 255, 0, 0 });

		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		SDL_Rect textRect = { rect.x + 10, rect.y, surfaceMessage->w, surfaceMessage->h };
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
		cost->Times(coefficient);
		sisyphus->IncreaseRecoverySpeed(staminaReward);
		return 0;
	}

private:
	Sisyphus* sisyphus;
	float staminaReward;
	const char* fontPath = "FieldGuide.TTF";
};

