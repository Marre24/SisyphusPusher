#pragma once

#include <map>
#include <string>
#include <tuple>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>

#include "LargeNumber.h";

class Glory
{
public:
	Glory() {

	}

	int Load(LargeNumber* glry) {
		glory = std::unique_ptr<LargeNumber>(glry);
		return 0;
	}

	std::string ToString() {
		return glory->ToString() + " Glory";
	}


	int Update() {
		glory->Update();
		return 0;
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

	int Pay(LargeNumber* cost) {
		return glory->Remove(cost);
	}

	int Earn(LargeNumber* price) {
		return glory->Add(price);
	}

	bool IsGreaterThan(LargeNumber* num) {
		return glory->LargerThan(num);
	}

	LargeNumber* GetGlory() {
		return glory.get();
	}

private:
	std::unique_ptr<LargeNumber> glory = std::make_unique<LargeNumber>(0, 0);
	const int expInterval = 3;
};