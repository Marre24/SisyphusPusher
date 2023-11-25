#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <SDL_rect.h>

class Stamina
{
public:
	Stamina() {
		border = IMG_Load(borderTexturePath.c_str());
		greenColor = IMG_Load(greenTexturePath.c_str());
	}

	int Update(float timeSincePush) {
		if (timeSincePush > 2000 && currentStamina < maxStamina)
			currentStamina += recoverySpeed;
		else if (timeSincePush > 2000 && currentStamina != maxStamina)
			currentStamina = maxStamina;
		borderRect->w = startWidth * maxStamina / 100;
		stamRect->w = (startWidth * maxStamina / 100) * ProcentLeft();
		return 0;
	}

	int Draw(SDL_Renderer* renderer) {

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, greenColor);
		SDL_RenderCopy(renderer, texture, NULL, stamRect);
		SDL_DestroyTexture(texture);
		texture = SDL_CreateTextureFromSurface(renderer, border);
		SDL_RenderCopy(renderer, texture, NULL, borderRect);
		SDL_DestroyTexture(texture);
		std::tuple<std::string, std::string> msg = LargeNumber::Round(recoverySpeed, 2);
		ShowMessage(renderer, "Stamina recovery speed: " + std::get<0>(msg) + "." + std::get<1>(msg), 100, 150);
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

	int AddRecoverySpeed(float f) {
		recoverySpeed += f;
		return 0;
	}

	int AddStamina(float f) {
		maxStamina += f;
		return 0;
	}

	int Remove(float stam) {
		if (stam > currentStamina)
			return -1;
		currentStamina -= stam;
		return 0;
	}

private:
	SDL_Surface* border;
	SDL_Surface* greenColor;
	const std::string borderTexturePath = "StaminaBar.png";
	const std::string greenTexturePath = "Stamina.png";
	SDL_Rect* borderRect = new SDL_Rect{ 500, 500, 256, 16 };
	SDL_Rect* stamRect = new SDL_Rect{ 500, 500, 16, 16 };

	const int startWidth = 256;
	float maxStamina = 100;
	float currentStamina = 50;
	float recoverySpeed = 0.1f;

	float ProcentLeft() {
		return currentStamina / maxStamina;
	}
};