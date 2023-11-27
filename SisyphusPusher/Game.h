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
#include "BuyAmountButton.h"


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

public:
	const SDL_Rect* buttonWindowRect = new SDL_Rect{ 1024, 28, 896, 1024 };
	const SDL_Rect* tartarusWindow = new SDL_Rect{ 0, 28, 1024, 1024 };
	std::unique_ptr<Sisyphus> player = std::make_unique<Sisyphus>();
	std::list<StrButton*> strButtons = std::list<StrButton*>();
	StaminaRefillButton* stamButton;
	StaminaExpandButton* stamExpandButton;
	BuyAmountButton* buyAmountButton;

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
		int id = 0;
		//Row 1
		strButtons.push_back(new StrButton(1344, 192 + 40,
			btnUpPath, btnDownPath,
			player.get(),
			new LargeNumber(4, 0), new LargeNumber(1.6 / cps, 0), 1.07f, ++id));
		strButtons.push_back(new StrButton(1344, 320 + 40,
			btnUpPath, btnDownPath,
			player.get(),
			new LargeNumber(60, 0), new LargeNumber(20 / cps, 0), 1.15f, ++id));
		strButtons.push_back(new StrButton(1344, 448 + 40,
			btnUpPath, btnDownPath,
			player.get(),
			new LargeNumber(720, 0), new LargeNumber(90 / cps, 0), 1.14f, ++id));
		strButtons.push_back(new StrButton(1344, 576 + 40,
			btnUpPath, btnDownPath,
			player.get(),
			new LargeNumber(8640, 0), new LargeNumber(360 / cps, 0), 1.13f, ++id));
		strButtons.push_back(new StrButton(1344, 704 + 40,
			btnUpPath, btnDownPath,
			player.get(),
			new LargeNumber(103, 3), new LargeNumber(2160.0 / cps, 0), 1.12f, ++id));
		//Row 2
		strButtons.push_back(new StrButton(1632, 192 + 40,
			btnUpPath, btnDownPath,
			player.get(),
			new LargeNumber(1244, 3), new LargeNumber(6480.0 / cps, 0), 1.11f, ++id));
		strButtons.push_back(new StrButton(1632, 320 + 40,
			btnUpPath, btnDownPath,
			player.get(),
			new LargeNumber(14.929920f, 6), new LargeNumber(19440 / cps, 0), 1.10f, ++id));
		strButtons.push_back(new StrButton(1632, 448 + 40,
			btnUpPath, btnDownPath,
			player.get(),
			new LargeNumber(179.159040f, 6), new LargeNumber(58320 / cps, 0), 1.09f, ++id));
		strButtons.push_back(new StrButton(1632, 576 + 40,
			btnUpPath, btnDownPath,
			player.get(),
			new LargeNumber(2.149908480f, 9), new LargeNumber(174960 / cps, 0), 1.08f, ++id));
		strButtons.push_back(new StrButton(1632, 704 + 40,
			btnUpPath, btnDownPath,
			player.get(),
			new LargeNumber(25.798901760f, 9), new LargeNumber(804816 / cps, 0), 1.07f, ++id));
		//Stamina buttons
		stamButton = new StaminaRefillButton(1632, 896 + 40,
			btnUpPath, btnDownPath, 
			player.get(), 
			new LargeNumber(10, 0), 0.2f, 2.0f);
		stamExpandButton = new StaminaExpandButton(1344, 896 + 40,
			btnUpPath, btnDownPath, 
			player.get(), 
			new LargeNumber(1, 0), 10, 10.0f);
		//BuyButton
		buyAmountButton = new BuyAmountButton(1024 + 32, 256 + 40, btnUpPath, btnDownPath, player.get());

		return 0;
	}
	const float cps = 8;

	int Update() {
		player->Update();
		for(StrButton* button : strButtons)
			button->Update();
		stamButton->Update();
		stamExpandButton->Update();
		buyAmountButton->Update();
		return 0;
	}


	int Draw() {
		SDL_RenderClear(renderer);

		Draw(SDL_CreateTextureFromSurface(renderer, buttonWindow), buttonWindowRect);
		Draw(SDL_CreateTextureFromSurface(renderer, tartarus), tartarusWindow);

		player->Draw(renderer);
		for (StrButton* button : strButtons)
			button->Draw(renderer);
		stamButton->Draw(renderer);
		stamExpandButton->Draw(renderer);
		buyAmountButton->Draw(renderer);

		SDL_RenderPresent(renderer);
		return 0;
	}

	int Draw(SDL_Texture* texture, const SDL_Rect* rect) {
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

