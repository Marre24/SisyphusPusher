#pragma once
#include "Button.h";
#include <SDL_ttf.h>

class ExitButton : Button
{
public:
    bool exited = false;
	ExitButton(int x, int y, std::string buttonTexturePath, std::string hoverTexturePath, LargeNumber* cost, float coefficient) : Button(x, y, buttonTexturePath, hoverTexturePath, cost, coefficient) {
        rect.w = 64;
        rect.h = 64;
	}

    int Draw(SDL_Renderer* renderer){
        Button::Draw(renderer);
        
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont("FieldGuide.TTF", 30), "Exit", { 255, 0, 0 });
        DrawTexture(renderer, new SDL_Rect{ rect.x + 10, rect.y + 10, surfaceMessage->w, surfaceMessage->h }, surfaceMessage);
        SDL_FreeSurface(surfaceMessage);
        TTF_CloseFont(TTF_OpenFont("FieldGuide.TTF", 30));
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
        exited = true;
        SDL_Quit();
        return 0;
    }
private:

};