#pragma once
#include "Glory.h";
#include "LargeNumber.h";

class Sisyphus
{
public:
	Glory* glory = new Glory();
	std::unique_ptr<LargeNumber> heightClimed = std::make_unique<LargeNumber>(0,0);
	std::unique_ptr<LargeNumber> strength = std::make_unique<LargeNumber>(1,0);

	Sisyphus() {
	}

	int Update() {
		glory->Update();
		heightClimed->Remove(new LargeNumber(1,0));

		return 0;
	}

	int Draw(SDL_Renderer* renderer) {
		glory->Draw(renderer);

		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont("FiraCode.TTF", 30), (heightClimed->ToString() + "m").c_str() , {255, 255, 255});
		if (surfaceMessage == nullptr)
			return -1;

		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		if (Message == nullptr) {
			SDL_FreeSurface(surfaceMessage);
			return -1;
		}
		SDL_Rect textRect = { 100, 100, surfaceMessage->w, surfaceMessage->h };
		SDL_RenderCopy(renderer, Message, NULL, &textRect);

		TTF_CloseFont(TTF_OpenFont("FiraCode.TTF", 30));

		return 0;
	}

	int Push() {
		heightClimed->Add(strength.get());
		glory->Earn(strength.get());
		return 0;
	}

	int Strengthen(LargeNumber* extra) {
		strength->Add(extra);
		return 0;
	}

private:

};