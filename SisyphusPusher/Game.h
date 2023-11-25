#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include <list>
#include <memory.h>

#include "Glory.h";
#include "StrButton.h";
#include "EventHandler.h";
#include "Sisyphus.h";
#include "LargeNumber.h";
#include "StaminaButton.h";


class Game
{
private:

	SDL_Window* window;
	SDL_Renderer* renderer;

	static const int windowHeight = 1080;
	static const int windowWidth = 1920;
	const char* fontPath = "FiraCode.TTF";
	
	const std::string title = "SisyphusPusher";
	const std::string btnPath = "StrButton.png";
	const std::string hoveringBtnPath = "HoveringStrButton.png";
	Uint32 flags = 0;
	SDL_DisplayMode display;

	TTF_Font* sans = NULL;
	SDL_Color White = { 255, 255, 255 };

public:
	std::unique_ptr<Sisyphus> player = std::make_unique<Sisyphus>();
	std::list<StrButton*> strButtons = std::list<StrButton*>();
	std::list<StaminaButton*> stamButtons = std::list<StaminaButton*>();
	bool isPlaying = true;

	int Init() {
		if (SDL_Init(SDL_INIT_VIDEO) == -1 || TTF_Init() == -1)
			return 0;

		if (SDL_GetCurrentDisplayMode(0, &display) != 0) {
			throw std::exception("Could not get current display");
			return 1;
		}

		int x = display.w / 2 - windowWidth / 2, y = display.h / 2 - windowHeight / 2;

		window = SDL_CreateWindow(title.c_str(), x, y, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (window == NULL || renderer == NULL) {
			throw std::exception("Game could not initialize");
			return 1;
		}

		sans = TTF_OpenFont(fontPath, 30);

		stamButtons.push_back(new StaminaButton(100, 400, 3 * 96, 3 * 16, btnPath, hoveringBtnPath, player.get(), new LargeNumber(1, 0), 0.1f));
		strButtons.push_back((new StrButton(100, 200, 3 * 96, 3 * 16, btnPath, hoveringBtnPath, player.get(), new LargeNumber(1, 0), new LargeNumber(1, 0))));

		return 0;
	}


	int Update() {
		player->Update();
		for(StrButton* button : strButtons)
			button->Update();
		for (StaminaButton* button : stamButtons)
			button->Update();
		return 0;
	}


	int Draw() {
		SDL_RenderClear(renderer);

		player->Draw(renderer);
		for (StrButton* button : strButtons)
			button->Draw(renderer);
		for (StaminaButton* button : stamButtons)
			button->Draw(renderer);

		SDL_RenderPresent(renderer);
		return 0;
	}

	int Exit() {
		TTF_CloseFont(sans);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}
};

