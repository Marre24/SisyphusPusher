#pragma once

#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <memory>

class BuyButton
{
protected:
	bool isHovering = false;
	SDL_Rect rect = { 0, 0, 0, 0};
	SDL_Texture* btn;
	SDL_Texture* btnHover;
	float currentCost;
	float baseCost;
	float coefficient;

public:
	
	BuyButton(int x, int y, SDL_Texture* btn, SDL_Texture* btnHover, float baseCost, float coefficient) :
		currentCost(baseCost), baseCost(baseCost), coefficient(coefficient), btn(btn), btnHover(btnHover) {
		rect = { x, y, 224, 64};
	}

	int Update() {
		SDL_Point mouse = { 0,0 };
		SDL_GetMouseState(&mouse.x, &mouse.y);
		isHovering = SDL_PointInRect(&mouse, &rect);
		return 0;
	}

	int Draw(SDL_Renderer *renderer) {
		if (isHovering)
			SDL_RenderCopy(renderer, btnHover, NULL, &rect);
		else 
			SDL_RenderCopy(renderer, btn, NULL, &rect);
		return 0;
	}
};