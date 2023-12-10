#pragma once

#include <list>
#include <SDL.h>
#include <SDL_image.h>
#include <list>
#include <memory.h>
#include <vector>

#include "Sisyphus.h";

class Animation
{
public:
	Animation(std::vector<SDL_Surface*> frames, const float timeBetweenFrames, SDL_Rect window, Sisyphus* sisyphus) {
		this->frames = frames;
		this->sisyphus = sisyphus;
		interval = timeBetweenFrames;
		rect = window;
	}

	int Draw(SDL_Renderer* renderer) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, frames.at(frameCounter));
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_DestroyTexture(texture);
		if (lastUpdateTime + interval > SDL_GetTicks() || !sisyphus->isPushing)
			return 0;
		lastUpdateTime = SDL_GetTicks();
		if (++frameCounter >= frames.size())
			frameCounter = 0;
		return 0;
	}

private:
	std::vector<SDL_Surface*> frames;
	Uint32 lastUpdateTime = 0;
	Uint32 interval;
	int frameCounter = 0;
	SDL_Rect rect;
	Sisyphus* sisyphus;
};