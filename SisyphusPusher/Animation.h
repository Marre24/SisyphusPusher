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
	Animation(std::vector<SDL_Texture*> frames, const float timeBetweenFrames, SDL_Rect window, Sisyphus* sisyphus) :
		sisyphus(sisyphus), frames(frames), interval(timeBetweenFrames), rect(window) { }

	int Draw(SDL_Renderer* renderer) {
		SDL_RenderCopy(renderer, frames.at(frameCounter), NULL, &rect);
		if (lastUpdateTime + interval > SDL_GetTicks() || !sisyphus->isPushing)
			return 0;
		lastUpdateTime = SDL_GetTicks();
		if (++frameCounter >= frames.size())
			frameCounter = 0;
		return 0;
	}

private:
	std::vector<SDL_Texture*> frames;
	Uint32 lastUpdateTime = 0;
	Uint32 interval;
	int frameCounter = 0;
	SDL_Rect rect;
	Sisyphus* sisyphus;
};