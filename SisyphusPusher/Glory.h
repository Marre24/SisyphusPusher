#pragma once

#include <map>
#include <string>
#include <tuple>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>


class Glory
{
public:
	Glory() {

	}

	int Load(float glry) {
		glory = glry;
		return 0;
	}

	std::string ToString() {
		return std::to_string(glory) + " Glory";
	}


	int Draw(SDL_Renderer* renderer, TTF_Font* font) {
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, ToString().c_str(), { 255, 255, 255 });
		if (surfaceMessage == nullptr) 
			return -1;

		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		if (Message == nullptr) {
			SDL_FreeSurface(surfaceMessage);
			return -1;
		}
		SDL_Rect textRect = { 1400, 80, surfaceMessage->w, surfaceMessage->h };
		SDL_RenderCopy(renderer, Message, NULL, &textRect);
		return 0;
	}

	int Pay(float cost) {
		if (cost > glory)
			return -1;
		glory -= cost;
		return 0;
	}

	int Earn(float price) {
		glory += price;
		return 0;
	}

	bool IsGreaterThan(float num) {
		return glory > num;
	}

	float GetGlory() {
		return glory;
	}

private:
	float glory = 0;
	const int expInterval = 3;
};