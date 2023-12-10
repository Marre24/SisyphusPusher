#pragma once

#include <SDL.h>
#include <memory>

#include "Animation.h";
#include "Sisyphus.h";


class Tartarus
{
public:

	Tartarus(Sisyphus* sisyphus) { 
		std::vector<SDL_Surface*> vect(0);
		vect.push_back(IMG_Load("SisyphusFrames/0.png"));
		vect.push_back(IMG_Load("SisyphusFrames/1.png"));
		vect.push_back(IMG_Load("SisyphusFrames/2.png"));
		vect.push_back(IMG_Load("SisyphusFrames/3.png"));
		vect.push_back(IMG_Load("SisyphusFrames/4.png"));
		vect.push_back(IMG_Load("SisyphusFrames/5.png"));
		vect.push_back(IMG_Load("SisyphusFrames/6.png"));
		vect.push_back(IMG_Load("SisyphusFrames/7.png"));
		vect.push_back(IMG_Load("SisyphusFrames/8.png"));
		vect.push_back(IMG_Load("SisyphusFrames/7.png"));
		vect.push_back(IMG_Load("SisyphusFrames/6.png"));
		vect.push_back(IMG_Load("SisyphusFrames/5.png"));
		vect.push_back(IMG_Load("SisyphusFrames/4.png"));
		vect.push_back(IMG_Load("SisyphusFrames/3.png"));
		vect.push_back(IMG_Load("SisyphusFrames/2.png"));
		vect.push_back(IMG_Load("SisyphusFrames/1.png"));
		this->sisyphusAnimation = std::make_unique<Animation>(vect, 150, window, sisyphus);
		tartarus = IMG_Load("Tartarus.png");
		
	}

	int Draw(SDL_Renderer* renderer) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tartarus);
		SDL_RenderCopy(renderer, texture, NULL, &window);
		SDL_DestroyTexture(texture);
		
		sisyphusAnimation.get()->Draw(renderer);
		return 0;
	}

private:
	std::unique_ptr<Animation> sisyphusAnimation;
	SDL_Surface* tartarus;
	const SDL_Rect window{0, 28, 1024, 1024};
};