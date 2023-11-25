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
		stamRect->w = maxWidth * ProcentLeft();
		return 0;
	}

	int Draw(SDL_Renderer* renderer) {

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, greenColor);
		SDL_RenderCopy(renderer, texture, NULL, stamRect);
		SDL_DestroyTexture(texture);
		texture = SDL_CreateTextureFromSurface(renderer, border);
		SDL_RenderCopy(renderer, texture, NULL, borderRect);
		SDL_DestroyTexture(texture);
		return 0;
	}

	int AddRecoverySpeed(float f) {
		recoverySpeed += f;
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

	const int maxWidth = 256;
	const float maxStamina = 100;
	float currentStamina = 50;
	float recoverySpeed = 0.1f;

	float ProcentLeft() {
		return currentStamina / maxStamina;
	}
};