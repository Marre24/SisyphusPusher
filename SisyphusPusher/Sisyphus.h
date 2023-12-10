#pragma once
#include <memory>
#include "Glory.h";
#include "LargeNumber.h";
#include "Stamina.h";
#include <list>

class Sisyphus
{
public:
	std::unique_ptr<Stamina> stamina = std::make_unique<Stamina>();
	std::unique_ptr<LargeNumber> heightClimed = std::make_unique<LargeNumber>(0,0);
	std::unique_ptr<LargeNumber> strength = std::make_unique<LargeNumber>(0.3f,0);
	std::map<int, std::unique_ptr<LargeNumber>> dividedStrength = { };
	int buyCounter = 1;
	bool isPushing = false;
	Glory* glory;

	Sisyphus(Glory* glory) {
		this->glory = glory;
	}

	int Load(LargeNumber* height, std::list<LargeNumber*> nums) {
		heightClimed = std::unique_ptr<LargeNumber>(height);
		int i = 0;
		for (LargeNumber* num : nums)
			dividedStrength.insert({ i++, std::unique_ptr<LargeNumber>(num) });
		strength = std::make_unique<LargeNumber>(StrengthSum());
		return 0;
	}

	int Update() {
		heightClimed->Remove(new LargeNumber(1,0));
		heightClimed->Update();
		strength->Update();
		stamina->Update(SDL_GetTicks() - lastPushTime);
		if (SDL_GetTicks() - lastPushTime < 500)
			isPushing = true;
		else
			isPushing = false;
		return 0;
	}

	int Draw(SDL_Renderer* renderer) {
		stamina->Draw(renderer);

		ShowMessage(renderer, heightClimed->ToString(true) + "meter (" + strength->ToString(true) + "meter/click)", 450, 100);
		return 0;
	}

	int ShowMessage(SDL_Renderer* renderer, std::string string, int x, int y) {
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont(fontPath, 30), string.c_str(), { 255, 255, 255 });
		if (surfaceMessage == nullptr)
			return -1;

		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		if (Message == nullptr) {
			SDL_FreeSurface(surfaceMessage);
			return -1;
		}
		SDL_Rect textRect = { x - surfaceMessage->w / 2, y, surfaceMessage->w, surfaceMessage->h };
		SDL_RenderCopy(renderer, Message, NULL, &textRect);

		TTF_CloseFont(TTF_OpenFont(fontPath, 30));
	}

	int Push() {
		if (stamina->Remove(1) < 0)				//placeholder for real stamina cost
			return -1;
		lastPushTime = SDL_GetTicks();
		heightClimed->Add(strength.get());
		glory->Earn(strength.get());
		return 0;
	}

	int GoalReached(int id, float multiplyer) {
		if (!dividedStrength.contains(id))
			return -1;
		dividedStrength[id]->Times(multiplyer);
		strength = std::make_unique<LargeNumber>(StrengthSum());
		return 0;
	}

	int Strengthen(LargeNumber* extra, int id) {
		if (!dividedStrength.contains(id))
			dividedStrength.insert({ id, std::make_unique<LargeNumber>(0,0) });
		dividedStrength[id]->Add(extra);
		strength = std::make_unique<LargeNumber>(StrengthSum());
		return 0;
	}

	LargeNumber StrengthSum() {
		LargeNumber sum = LargeNumber(0, 0);
		for (const auto& kv : dividedStrength)
			sum.Add(kv.second.get());
		sum.Add(new LargeNumber(0.3, 0));
		return sum;
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
		std::string str = "";
		str += "Height:(" + std::to_string(heightClimed->Value()) + "," + std::to_string(heightClimed->Exponent()) + ")\n";
		str += "Strength:";
		for (const auto& kv : dividedStrength)
			str += "ID:" + std::to_string(kv.first) + "(" + std::to_string(kv.second->Value()) + "," + std::to_string(kv.second->Exponent()) + ")";
		return str;
	}

private:
	float lastPushTime = 0;	//In ms
	const char* fontPath = "FieldGuide.TTF";
};