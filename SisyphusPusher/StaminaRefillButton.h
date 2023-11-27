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
		if (amountBought > maxBuy)
			surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 30), "MAX", { 105,105,105 });

		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		DrawTexture(renderer, new SDL_Rect{ rect.x + 10, rect.y-5, surfaceMessage->w, surfaceMessage->h }, surfaceMessage);
		surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 20), std::to_string(amountBought).c_str(), { 169,169,169 });
		DrawTexture(renderer, new SDL_Rect{ rect.x + 10, rect.y + 20, surfaceMessage->w, surfaceMessage->h }, surfaceMessage);
		SDL_DestroyTexture(message);
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
		if (++amountBought >= maxBuy || sisyphus->glory->Pay(cost) < 0)
			return -1;
		cost->Times(coefficient);
		sisyphus->IncreaseRecoverySpeed(staminaReward);
		return 0;
	}

private:
	int amountBought = 0;
	const int maxBuy = 15;
	Sisyphus* sisyphus;
	float staminaReward;
	const char* fontPath = "FieldGuide.TTF";
};

