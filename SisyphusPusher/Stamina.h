#pragma once
#include <SDL.h>
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
		if (timeSincePush > millisecondsToRefill && currentStamina < maxStamina)
			currentStamina += recoverySpeed;
		else if (timeSincePush > millisecondsToRefill && currentStamina != maxStamina)
			currentStamina = maxStamina;
		borderRect.w = startWidth * maxStamina / 100;
		stamRect.w = (startWidth * maxStamina / 100) * ProcentLeft();
		return 0;
	}

	int Draw(SDL_Renderer* renderer) {

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, greenColor);
		SDL_RenderCopy(renderer, texture, NULL, &stamRect);
		SDL_DestroyTexture(texture);
		texture = SDL_CreateTextureFromSurface(renderer, border);
		SDL_RenderCopy(renderer, texture, NULL, &borderRect);
		SDL_DestroyTexture(texture);
		return 0;
	}

	int SetRecoverySpeed(float f) {
		recoverySpeed = f;
		return 0;
	}

	int SetStamina(float f) {
		maxStamina = f;
		return 0;
	}

	int Remove(float stam) {
		if (stam > currentStamina)
			return -1;
		currentStamina -= stam;
		return 0;
	}

private:
	static const int millisecondsToRefill = 200;
	SDL_Surface* border;
	SDL_Surface* greenColor;
	const std::string borderTexturePath = "StaminaBar.png";
	const std::string greenTexturePath = "Stamina.png";
	SDL_Rect borderRect = { 322, 150, 256, 16 };
	SDL_Rect stamRect = { 322, 150, 16, 16 };

	const int startWidth = 256;
	float maxStamina = 100;
	float currentStamina = 100;
	float recoverySpeed = 0.1f;

	float ProcentLeft() {
		return currentStamina / maxStamina;
	}
};