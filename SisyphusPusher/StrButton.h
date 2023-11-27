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
		switch (sisyphus->buyCounter)
		{
		case 1:
			if (sisyphus->glory->IsGreaterThan(cost))
				color = { 50, 205,50 };
			else
				color = { 255, 0, 0 };
			break;
		case 2:
			if (sisyphus->glory->IsGreaterThan(tenCost))
				color = { 50, 205,50 };
			else
				color = { 255, 0, 0 };
			break;
		}
		
		if (nextGoal > maxGoal) {
			color = { 105,105,105 };
			surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 30), "MAX", color);
		}
		else {
			std::string string = "";
			
			switch (sisyphus->buyCounter)
			{
			case 1:
				string = cost->ToString();
				break;
			case 2:
				string = tenCost->ToString();
				break;
			}
			surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 30), string.c_str(), color);
		}


		DrawTexture(renderer, new SDL_Rect{ rect.x + 10, rect.y- 5, surfaceMessage->w, surfaceMessage->h }, surfaceMessage);
		surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 20), std::to_string(amountBought).c_str(), { 169,169,169 });
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
		tenCost = baseCost->Times((pow(coefficient,amountBought) * (pow(coefficient, 10) - 1)) / (coefficient - 1), false);
		tenCost->Update();
		if (amountBought >= nextGoal)
		{
			sisyphus->GoalReached(id, goals[nextGoal]);
			nextGoal *= 2;
		}

		if (nextGoal > maxGoal)
			greenRect->w = borderRect->w;
		else
			greenRect->w = borderRect->w * amountBought / nextGoal;
		
		return 0;
	}

	int OnClick() {
		if (!isHovering || nextGoal > maxGoal)
			return 0;
		LargeNumber* chosenCost = cost;
		int amount = 1;
		switch (sisyphus->buyCounter)
		{
		case 2:
			amount = std::min(10, maxGoal - amountBought);
			chosenCost = baseCost->Times((pow(coefficient, amountBought) * (pow(coefficient, amount) - 1)) / (coefficient - 1), false);
			break;
		}
		chosenCost->Update();
		if (sisyphus->glory->Pay(chosenCost) < 0)
			return -1;
		amountBought += amount;
		cost->Times(pow(coefficient, amount));
		sisyphus->Strengthen(reward->Times(amount, false), id);
		return 0;
	}

private:
	int amountBought = 0;
	float nextGoal = 25;
	std::map<int, float> goals = {
		{25, 2.0f},
		{50, 3.0f},
		{100, 2.0f},
		{200, 4.0f},
	};
	const int maxGoal = 200;
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
	LargeNumber* tenCost;
};

