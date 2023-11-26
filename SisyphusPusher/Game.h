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
#include "StaminaRefillButton.h";
#include "StaminaExpandButton.h";


class Game
{
private:

	SDL_Window* window;
	SDL_Renderer* renderer;

	int windowHeight;
	int windowWidth;
	
	const std::string title = "SisyphusPusher";
	const std::string btnUpPath = "ButtonUp.png";
	const std::string btnDownPath = "ButtonDown.png";
	Uint32 flags = 0;
	SDL_DisplayMode display;

	TTF_Font* sans = NULL;
	SDL_Color White = { 255, 255, 255 };

	SDL_Surface* tartarus;
	SDL_Surface* buttonWindow;
	SDL_Rect* buttonWindowRect = new SDL_Rect{ 1024, 28, 896, 1024 };
	SDL_Rect* tartarusWindow = new SDL_Rect{ 0, 28, 1024, 1024 };

public:
	std::unique_ptr<Sisyphus> player = std::make_unique<Sisyphus>();
	std::list<StrButton*> strButtons = std::list<StrButton*>();
	std::list<StaminaRefillButton*> stamButtons = std::list<StaminaRefillButton*>();
	std::list<StaminaExpandButton*> stamExpandButtons = std::list<StaminaExpandButton*>();
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
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		windowWidth = SDL_GetWindowSurface(window)->w; 
		windowHeight = SDL_GetWindowSurface(window)->h;

		if (window == NULL || renderer == NULL) {
			throw std::exception("Game could not initialize");
			return 1;
		}

		tartarus = IMG_Load("Tartarus.png");
		buttonWindow = IMG_Load("ButtonWindow.png");

		for (int i = 0; i < 5; i++)
		{
			strButtons.push_back((new StrButton(64 + 1024, 264 + 160 * i, 224, 96, 
				btnUpPath, btnDownPath, 
				player.get(), 
				new LargeNumber(1, 0), new LargeNumber(1, 0))));
			stamButtons.push_back(new StaminaRefillButton(64 + 1024 + 272, 264 + 160 * i, 224, 96,
				btnUpPath, btnDownPath, 
				player.get(), 
				new LargeNumber(1, 0), 0.1f));
			stamExpandButtons.push_back(new StaminaExpandButton(64 + 1024 + 544, 264 + 160 * i, 224, 96, 
				btnUpPath, btnDownPath, 
				player.get(), 
				new LargeNumber(1, 0), 1));
		}

		return 0;
	}


	int Update() {
		player->Update();
		for(StrButton* button : strButtons)
			button->Update();
		for (StaminaRefillButton* button : stamButtons)
			button->Update();
		for (StaminaExpandButton* button : stamExpandButtons)
			button->Update();
		return 0;
	}


	int Draw() {
		SDL_RenderClear(renderer);

		Draw(SDL_CreateTextureFromSurface(renderer, buttonWindow), buttonWindowRect);
		Draw(SDL_CreateTextureFromSurface(renderer, tartarus), tartarusWindow);

		player->Draw(renderer);
		for (StrButton* button : strButtons)
			button->Draw(renderer);
		for (StaminaRefillButton* button : stamButtons)
			button->Draw(renderer);
		for (StaminaExpandButton* button : stamExpandButtons)
			button->Draw(renderer);

		SDL_RenderPresent(renderer);
		return 0;
	}

	int Draw(SDL_Texture* texture, SDL_Rect* rect) {
		SDL_RenderCopy(renderer, texture, NULL, rect);
		SDL_DestroyTexture(texture);
		return 0;
	}

	int Exit() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}
};

