#pragma once
#include "Glory.h";
#include "LargeNumber.h";
#include "Stamina.h";

class Sisyphus
{
public:
	std::unique_ptr<Glory> glory = std::make_unique<Glory>();
	std::unique_ptr<Stamina> stamina = std::make_unique<Stamina>();
	std::unique_ptr<LargeNumber> heightClimed = std::make_unique<LargeNumber>(0,0);
	std::unique_ptr<LargeNumber> strength = std::make_unique<LargeNumber>(1,0);

	Sisyphus() {
	}

	int Update() {
		heightClimed->Remove(new LargeNumber(1,0));
		glory->Update();
		heightClimed->Update();
		stamina->Update(SDL_GetTicks() - lastPushTime);
		return 0;
	}

	int Draw(SDL_Renderer* renderer) {
		glory->Draw(renderer);
		stamina->Draw(renderer);

		ShowMessage(renderer, strength->ToString() + "pwr", 100, 50);
		ShowMessage(renderer, heightClimed->ToString(true) + "meter", 900, 0);

		return 0;
	}

	int ShowMessage(SDL_Renderer* renderer, std::string string, int x, int y) {
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont("FiraCode.TTF", 30), string.c_str(), { 255, 255, 255 });
		if (surfaceMessage == nullptr)
			return -1;

		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		if (Message == nullptr) {
			SDL_FreeSurface(surfaceMessage);
			return -1;
		}
		SDL_Rect textRect = { x, y, surfaceMessage->w, surfaceMessage->h };
		SDL_RenderCopy(renderer, Message, NULL, &textRect);

		TTF_CloseFont(TTF_OpenFont("FiraCode.TTF", 30));
	}

	int Push() {
		if (stamina->Remove(1) < 0)				//placeholder for real stamina cost
			return -1;
		lastPushTime = SDL_GetTicks();
		heightClimed->Add(strength.get());
		glory->Earn(strength.get());
		return 0;
	}

	int Strengthen(LargeNumber* extra) {
		strength->Add(extra);
		return 0;
	}

	int IncreaseRecoverySpeed(float f) {
		stamina->AddRecoverySpeed(f);
		return 0;
	}

	int IncreaseStamina(float f) {
		stamina->AddStamina(f);
		return 0;
	}

private:
	float lastPushTime = 0;	//In ms
};