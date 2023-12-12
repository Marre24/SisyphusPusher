#pragma once
#include <memory>
#include "Glory.h";
#include "Stamina.h";
#include <list>

class Sisyphus
{
public:
	std::unique_ptr<Stamina> stamina = std::make_unique<Stamina>();
	float heightClimed = 0;
	float strength = startStrength;
	std::map<int, float> dividedStrength = { };
	int buyCounter = 1;
	bool isPushing = false;
	Glory* glory;

	Sisyphus(Glory* glory) {
		this->glory = glory;
	}

	int Load(float height, std::list<float> dividedStrengthNumbers) {
		heightClimed = height;
		int i = 0;
		for (float num : dividedStrengthNumbers)
			dividedStrength.insert({ i++, num });
		strength = StrengthSum();
		return 0;
	}

	int Update() {
		strength = StrengthSum();
		if (heightClimed - 1 < 0)
			heightClimed = 0;
		else
			heightClimed -= 1;
		stamina->Update(SDL_GetTicks() - lastPushTime);
		if (SDL_GetTicks() - lastPushTime < 500)
			isPushing = true;
		else
			isPushing = false;
		return 0;
	}

	int Draw(SDL_Renderer* renderer, TTF_Font* font) {
		stamina->Draw(renderer);

		ShowMessage(renderer, std::to_string(heightClimed) + "meter (" + std::to_string(strength) + "meter/click)", 450, 100, font);
		return 0;
	}

	int ShowMessage(SDL_Renderer* renderer, std::string string, int x, int y, TTF_Font* font) {
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, string.c_str(), { 255, 255, 255 });
		if (surfaceMessage == nullptr)
			return -1;

		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		if (Message == nullptr) {
			SDL_FreeSurface(surfaceMessage);
			return -1;
		}
		SDL_Rect textRect = { x - surfaceMessage->w / 2, y, surfaceMessage->w, surfaceMessage->h };
		SDL_RenderCopy(renderer, Message, NULL, &textRect);
	}

	int Push() {
		if (stamina->Remove(1) < 0)				//placeholder for real stamina cost
			return -1;
		lastPushTime = SDL_GetTicks();
		heightClimed += strength;
		glory->Earn(strength);
		return 0;
	}

	float StrengthSum() {
		float sum = startStrength;
		for (auto kv : dividedStrength)
			sum += kv.second;
		return sum;
	}

	int UpdateStrength(int id, float lNum) {
		dividedStrength[id] = lNum;
		return 0;
	}

	int SetRecoverySpeed(float f) {
		stamina->SetRecoverySpeed(f);
		return 0;
	}

	int SetMaxStamina(float f) {
		stamina->SetStamina(f);
		return 0;
	}

	std::string ToString() {
		return "Height:(" + std::to_string(heightClimed) + ")";
	}

private:
	float lastPushTime = 0;	//In ms
	const float startStrength = 0.3f;
};