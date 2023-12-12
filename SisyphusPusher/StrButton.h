#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <tuple>
#include <iostream>

#include "Button.h";
#include "Glory.h";
#include "Sisyphus.h";

class StrButton : BuyButton
{
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
	SDL_Rect borderRect;
	SDL_Rect greenRect;
	SDL_Texture* borderTexure;
	SDL_Texture* greenColorTexture;
	float reward;
	float tenCost = 0;
	int id;

public:
	StrButton(int x, int y, SDL_Texture* btn, SDL_Texture* btnHover, SDL_Texture* borderTexure, SDL_Texture* greenColorTexture, Sisyphus* sisyphus, float cost, float reward, float coefficient, int id) :
		BuyButton(x, y, btn, btnHover, cost, coefficient), reward(reward), borderTexure(borderTexure), greenColorTexture(greenColorTexture)
	{
		this->id = id;
		this->sisyphus = sisyphus;
		
		borderRect = SDL_Rect{ x , y + 80, 256, 16 };
		greenRect = SDL_Rect{ x, y + 80, 16, 16 };
	}

	int Draw(SDL_Renderer* renderer, TTF_Font* font, TTF_Font* smallFont) {
		BuyButton::Draw(renderer);

		SDL_Surface* surfaceMessage;
		SDL_Color color;

		switch (sisyphus->buyCounter) {
		case 1:
			if (sisyphus->glory->IsGreaterThan(currentCost))
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
		default:
			color = { 255, 255, 255 };
			break;
		}

		if (nextGoal > maxGoal) {
			color = { 105,105,105 };
			surfaceMessage = TTF_RenderText_Solid(font, "MAX", color);
		}
		else {
			std::string string = "";
			switch (sisyphus->buyCounter) {
			case 1:
				string = std::to_string(currentCost);
				break;
			case 2:
				string = std::to_string(tenCost);
				break;
			}
			surfaceMessage = TTF_RenderText_Solid(font, string.c_str(), color);
		}

		SDL_Rect msgRect = SDL_Rect{ rect.x + 10, rect.y - 5, surfaceMessage->w, surfaceMessage->h };
		DrawTexture(renderer, &msgRect, surfaceMessage);
		surfaceMessage = TTF_RenderText_Solid(smallFont, std::to_string(amountBought).c_str(), { 169,169,169 });
		msgRect = SDL_Rect{ rect.x + 10, rect.y + 20, surfaceMessage->w, surfaceMessage->h };
		DrawTexture(renderer, &msgRect, surfaceMessage);
		SDL_RenderCopy(renderer, greenColorTexture, NULL, &greenRect);
		SDL_RenderCopy(renderer, borderTexure, NULL, &borderRect);
		surfaceMessage = TTF_RenderText_Solid(smallFont, ("x" + std::to_string((int)goals[nextGoal])).c_str(), {0,255,0});
		msgRect = SDL_Rect{ borderRect.x - 20, borderRect.y - 5, surfaceMessage->w, surfaceMessage->h };
		DrawTexture(renderer, &msgRect, surfaceMessage);
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
		currentCost = baseCost * pow(coefficient, amountBought);
		BuyButton::Update();
		tenCost = baseCost * (pow(coefficient,amountBought) * (pow(coefficient, 10) - 1)) / (coefficient - 1);
		if (amountBought >= nextGoal)
			nextGoal *= 2;

		if (nextGoal > maxGoal)
			greenRect.w = borderRect.w;
		else
			greenRect.w = borderRect.w * amountBought / nextGoal;
		
		sisyphus->UpdateStrength(id, TotalStrength());
		return 0;
	}

	int OnClick() {
		if (!isHovering || nextGoal > maxGoal)
			return 0;
		float chosenCost = currentCost;
		int amount = 1;
		switch (sisyphus->buyCounter)
		{
			case 2:
				amount = std::min(10, maxGoal - amountBought);
				chosenCost = baseCost * (pow(coefficient, amountBought) * (pow(coefficient, amount) - 1)) / (coefficient - 1);
				break;
		}
		if (sisyphus->glory->Pay(chosenCost) < 0)
			return -1;
		amountBought += amount;
		currentCost = baseCost * pow(coefficient, amountBought);
		return 0;
	}

	std::string ToString() {
		return "AmountBought:" + std::to_string(amountBought);
	}

	int Load(int amountBought) {
		this->amountBought = amountBought;
		return 0;
	}

	float TotalStrength() {
		if (amountBought == 0)
			return 0;
		float multiplyer = 1;
		for (auto kv : goals)
			if (kv.first <= amountBought)
				multiplyer *= kv.second;

		return reward * multiplyer * amountBought;
	}


};

