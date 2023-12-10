#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <list>
#include <memory>

#include "Sisyphus.h";

class Ground
{
public:

	Ground(Sisyphus* sisyphus) {
		ground1 = std::unique_ptr<SDL_Surface>(IMG_Load("Ground1.png"));
		ground2 = std::unique_ptr<SDL_Surface>(IMG_Load("Ground2.png"));
		this->sisyphus = sisyphus;
	}

	int Draw(SDL_Renderer* renderer) {
		if (sisyphus->isPushing)
		{
			rect1.x -= speed;
			rect1.y += speed / 2;
			rect2.x -= speed;
			rect2.y += speed / 2;
		}
		if (rect1.x <= -1024)
			rect1 = { 1024 - (int)speed,28,1024,1024 };
		if (rect2.x <= -1024)
			rect2 = { 1024,28,1024,1024 };

		SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, ground1.get());
		SDL_RenderCopy(renderer, texture1, NULL, &rect1);
		SDL_DestroyTexture(texture1);
		SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, ground2.get());
		SDL_RenderCopy(renderer, texture2, NULL, &rect2);
		SDL_DestroyTexture(texture2);
		return 0;
	}

private:
	std::unique_ptr<SDL_Surface> ground1;
	std::unique_ptr<SDL_Surface> ground2;
	SDL_Rect rect1{0,512 + 28,1024,1024};
	SDL_Rect rect2{1024,28,1024,1024};
	Sisyphus* sisyphus;
	float speed = 2;
};