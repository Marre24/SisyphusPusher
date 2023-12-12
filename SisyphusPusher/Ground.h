#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <list>
#include <memory>

#include "Sisyphus.h";

class Ground
{
public:

	Ground(Sisyphus* sisyphus, SDL_Texture* ground1, SDL_Texture* ground2) :
		ground1(ground1), ground2(ground2), sisyphus(sisyphus)
	{
	}

	int Draw(SDL_Renderer* renderer) {
		if (sisyphus->isPushing)
		{
			rect1.x -= speed;
			rect1.y += speed / 2;
			rect2.x -= speed;
			rect2.y += speed / 2;
		}
		if (rect1.x <= -1014)
			rect1 = { 1014,28,1024,1024 };
		if (rect2.x <= -1014)
			rect2 = { 1014,28,1024,1024 };

		SDL_RenderCopy(renderer, ground1, NULL, &rect1);
		SDL_RenderCopy(renderer, ground2, NULL, &rect2);
		return 0;
	}

private:
	SDL_Texture* ground1;
	SDL_Texture* ground2;
	SDL_Rect rect1{0,512 + 28,1024,1024};
	SDL_Rect rect2{1024,28,1024,1024};
	Sisyphus* sisyphus;
	float speed = 2;
};