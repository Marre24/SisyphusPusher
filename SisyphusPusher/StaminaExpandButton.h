#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <tuple>
#include <iostream>

#include "Button.h";
#include "Glory.h";
#include "Sisyphus.h";

class StaminaExpandButton : Button
{
public:
	StaminaExpandButton(int x, int y, int width, int height, std::string buttonTexturePath, std::string hoverTexturePath, Sisyphus* sisyphus, LargeNumber* cost, float staminaReward) : Button(x, y, width, height, buttonTexturePath, hoverTexturePath)
	{
		this->staminaReward = staminaReward;
		this->sisyphus = sisyphus;
		this->cost = cost;
	}

	int Draw(SDL_Renderer* renderer) {
		Button::Draw(renderer);
		std::tuple<std::string, std::string> msg = LargeNumber::Round(staminaReward, 2);
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(
			TTF_OpenFont("FiraCode.TTF", 30),
			("Cost: " + cost->ToString() + " Reward: +" + std::get<0>(msg) + "." + std::get<1>(msg) + " bar size").c_str(),
			{ 255, 255, 255 });

		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		SDL_Rect textRect = { rect.x, rect.y, surfaceMessage->w, surfaceMessage->h };
		SDL_RenderCopy(renderer, Message, NULL, &textRect);

		SDL_DestroyTexture(Message);
		SDL_FreeSurface(surfaceMessage);

		TTF_CloseFont(TTF_OpenFont("FiraCode.TTF", 30));
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

		sisyphus->IncreaseStamina(staminaReward);
		return 0;
	}

private:
	Sisyphus* sisyphus;
	LargeNumber* cost;
	float staminaReward;
	const std::map<int, std::string> strEquivalent = {
		{0, ""},
		{3, " Thousand"},
		{6, " Million"},
		{9, " Billion"},
		{12, " Trillion"},
		{15, " Quadrillion"},
		{18, " Quintillion"},
	};
};

