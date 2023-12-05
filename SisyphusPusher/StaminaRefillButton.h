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
        this->cost = std::make_unique<LargeNumber>(*cost);
        this->staminaReward = staminaReward;
        this->sisyphus = sisyphus;
        this->font = TTF_OpenFont(fontPath, 30);
        if (!font) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        }
    }

    ~StaminaRefillButton()
    {
        TTF_CloseFont(font);
    }

    int Draw(SDL_Renderer* renderer)
    {
        Button::Draw(renderer);

        SDL_Surface* surfaceMessage;
        SDL_Color textColor;

        if (sisyphus->glory->IsGreaterThan(cost.get()))
            textColor = { 50, 205, 50 };
        else
            textColor = { 255, 0, 0 };

        surfaceMessage = TTF_RenderText_Solid(font, cost->ToString().c_str(), textColor);

        if (amountBought > maxBuy) {
            SDL_FreeSurface(surfaceMessage);
            surfaceMessage = TTF_RenderText_Solid(font, "MAX", { 105, 105, 105 });
        }

        DrawTexture(renderer, new SDL_Rect{ rect.x + 10, rect.y - 5, surfaceMessage->w, surfaceMessage->h }, surfaceMessage);
        SDL_FreeSurface(surfaceMessage);

        surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 20), std::to_string(amountBought).c_str(), { 169, 169, 169 });
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

    int Update()
    {
        Button::Update();
        return 0;
    }

    int OnClick()
    {
        if (!isHovering)
            return 0;
        if (sisyphus->glory->Pay(cost.get()) < 0)
            return -1;
        if (++amountBought >= maxBuy)
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
    TTF_Font* font;
    const char* fontPath = "FieldGuide.TTF";
};

