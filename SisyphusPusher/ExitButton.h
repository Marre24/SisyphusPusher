#pragma once
#include "Button.h";
#include <SDL_ttf.h>

class ExitButton
{
public:
    bool exited = false;
	ExitButton(int x, int y, int w, int h, SDL_Texture* btn, SDL_Texture* btnHover, SDL_Texture* surfaceMessage) :
        surfaceMessage(surfaceMessage), btn(btn), btnHover(btnHover)
    {
        rect = { x, y, 64, 64 };
        textRect = { x + 10, y + 10, w, h };
	}


    int Draw(SDL_Renderer* renderer, TTF_Font* font){
        if (isHovering)
            SDL_RenderCopy(renderer, btnHover, NULL, &rect);
        else
            SDL_RenderCopy(renderer, btn, NULL, &rect);

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
    SDL_Rect rect;
    SDL_Rect textRect;
    SDL_Texture* btn;
    SDL_Texture* btnHover;
    SDL_Texture* surfaceMessage;
};