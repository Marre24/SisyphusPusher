#pragma once
#include "Button.h";
#include <SDL_ttf.h>

class ExitButton
{
public:
    bool exited = false;
	ExitButton(int x, int y, std::string buttonTexturePath, std::string hoverTexturePath, LargeNumber* cost, float coefficient) {
        rect = { x, y, 64, 64 };
        btn = IMG_Load(buttonTexturePath.c_str());
        btnHover = IMG_Load(hoverTexturePath.c_str());
	}

    int Draw(SDL_Renderer* renderer, TTF_Font* font){
        if (isHovering)
            SetTexture(btnHover, renderer);
        else
            SetTexture(btn, renderer);
        
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "Exit", { 255, 0, 0 });
        DrawTexture(renderer, new SDL_Rect{ rect.x + 10, rect.y + 10, surfaceMessage->w, surfaceMessage->h }, surfaceMessage);
        SDL_FreeSurface(surfaceMessage);
        return 0;
    }

    int DrawTexture(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Surface* surface) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, rect);
        SDL_DestroyTexture(texture);
        return 0;
    }

    int SetTexture(SDL_Surface* surface, SDL_Renderer* renderer) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_DestroyTexture(texture);
        return 0;
    }

    int Update() {
        SDL_Point mouse = { 0,0 };
        SDL_GetMouseState(&mouse.x, &mouse.y);
        isHovering = SDL_PointInRect(&mouse, &rect);
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
    bool isHovering = false;
    SDL_Rect rect = { 0, 0, 0, 0 };
    SDL_Surface* btn;
    SDL_Surface* btnHover;
};