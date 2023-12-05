#pragma once

#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <memory>
#include "LargeNumber.h"

class Button
{
protected:
	bool isHovering = false;
	SDL_Rect rect = { 0, 0, 0, 0};
	SDL_Surface* btn;
	SDL_Surface* btnHover;
	std::unique_ptr<LargeNumber> cost;
	std::unique_ptr<LargeNumber> baseCost;
	float coefficient;

public:
	
	Button(int x, int y, std::string buttonTexturePath, std::string hoverTexturePath, LargeNumber* baseCost, float coefficient) {
		if (baseCost != nullptr)
		{
			this->cost = std::make_unique<LargeNumber>(baseCost->Value(), baseCost->Exponent());
			this->baseCost = std::make_unique<LargeNumber>(*baseCost);
			this->coefficient = coefficient;
		}
		rect = { x, y, 224, 64};
		btn = IMG_Load(buttonTexturePath.c_str());
		btnHover = IMG_Load(hoverTexturePath.c_str());
	}

	int Update() {
		SDL_Point mouse = { 0,0 };
		SDL_GetMouseState(&mouse.x, &mouse.y);
		isHovering = SDL_PointInRect(&mouse, &rect);
		if (baseCost != nullptr)
			cost->Update();
		return 0;
	}

	int Draw(SDL_Renderer *renderer) {
		if (isHovering)
			SetTexture(btnHover, renderer);
		else 
			SetTexture(btn, renderer);
		
		
		return 0;
	}

	int SetTexture(SDL_Surface* surface, SDL_Renderer *renderer) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_DestroyTexture(texture);
		return 0;
	}

	~Button() {
		SDL_FreeSurface(btn);
		SDL_FreeSurface(btnHover);
	}
};