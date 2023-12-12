#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <tuple>
#include <iostream>

#include "Button.h";
#include "Glory.h";
#include "Sisyphus.h";

class StaminaExpandButton : BuyButton
{
public:
	StaminaExpandButton(int x, int y, SDL_Texture* btn, SDL_Texture* btnHover, Sisyphus* sisyphus, float cost, float staminaReward, float coefficient) :
		BuyButton(x, y, btn, btnHover, cost, coefficient)
	{
		this->staminaReward = staminaReward;
		this->sisyphus = sisyphus;
	}

    int Load(int amountBought) {
        this->amountBought = amountBought;
        return 0;
    }

    int Draw(SDL_Renderer* renderer, TTF_Font* font, TTF_Font* smallFont)
    {
        BuyButton::Draw(renderer);

        SDL_Surface* surfaceMessage;
        SDL_Color textColor;

        if (sisyphus->glory->IsGreaterThan(currentCost))
            textColor = { 50, 205, 50 };
        else
            textColor = { 255, 0, 0 };

        surfaceMessage = TTF_RenderText_Solid(font, std::to_string(currentCost).c_str(), textColor);

        if (amountBought > maxBuy) {
            SDL_FreeSurface(surfaceMessage);
            surfaceMessage = TTF_RenderText_Solid(font, "MAX", { 105, 105, 105 });
        }

        DrawTexture(renderer, new SDL_Rect{ rect.x + 10, rect.y - 5, surfaceMessage->w, surfaceMessage->h }, surfaceMessage);
        SDL_FreeSurface(surfaceMessage);

        surfaceMessage = TTF_RenderText_Solid(smallFont, std::to_string(amountBought).c_str(), { 169, 169, 169 });
        DrawTexture(renderer, new SDL_Rect{ rect.x + 10, rect.y + 20, surfaceMessage->w, surfaceMessage->h }, surfaceMessage);
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
        sisyphus->SetMaxStamina(staminaReward * amountBought + 100);
        currentCost = baseCost * pow(coefficient, amountBought);
		BuyButton::Update();

		return 0;
	}

	int OnClick() {
		if (!isHovering)
			return 0;
		if (sisyphus->glory->Pay(currentCost) < 0)
			return -1;
		if (++amountBought >= maxBuy)
			return -1;
        currentCost = baseCost * pow(coefficient, amountBought);
		sisyphus->SetMaxStamina(staminaReward * amountBought + 100);
		return 0;
	}

    std::string ToString() {
        return "AmountBought:" + std::to_string(amountBought);
    }

private:
	int amountBought = 0;
	const int maxBuy = 8;
	Sisyphus* sisyphus;
	float staminaReward;
};