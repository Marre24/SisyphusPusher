#pragma once

#include <SDL.h>
#include <string>
#include <SDL_image.h>

class Button
{
protected:
	bool isHovering = false;
	SDL_Rect rect = { 0, 0, 0, 0};
	SDL_Surface* btn;
	SDL_Surface* btnHover;

public:
	
	Button(int x, int y, int width, int height, std::string buttonTexturePath, std::string hoverTexturePath) {
		rect = { x, y, width, height};
		btn = IMG_Load(buttonTexturePath.c_str());
		btnHover = IMG_Load(hoverTexturePath.c_str());
	}

	int Update() {
		SDL_Point mouse = { 0,0 };
		SDL_GetMouseState(&mouse.x, &mouse.y);
		isHovering = SDL_PointInRect(&mouse, &rect);

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