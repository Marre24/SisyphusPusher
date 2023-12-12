#pragma once

#include <SDL.h>
#include <memory>

#include "Animation.h";
#include "Sisyphus.h";


class Tartarus
{
public:

	Tartarus(Sisyphus* sisyphus, SDL_Texture* tartarusTexture, std::vector<SDL_Texture*> frames) : tartarusTexture(tartarusTexture), frames(frames){
		
		this->sisyphusAnimation = std::make_unique<Animation>(frames, 150, window, sisyphus);
	}

	~Tartarus() {
		
	}

	int Draw(SDL_Renderer* renderer) {
		SDL_RenderCopy(renderer, tartarusTexture, NULL, &window);
		sisyphusAnimation.get()->Draw(renderer);
		return 0;
	}

private:
	std::vector<SDL_Texture*> frames;
	SDL_Texture* tartarusTexture;
	std::unique_ptr<Animation> sisyphusAnimation;
	const SDL_Rect window{0, 28, 1024, 1024};
};