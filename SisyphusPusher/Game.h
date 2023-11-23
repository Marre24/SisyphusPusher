#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include <list>

#include "Glory.h";
#include "StrButton.h";
#include "EventHandler.h";
#include "Sisyphus.h";


class Game
{
private:
	std::unique_ptr<Sisyphus> player;

	SDL_Window* window;
	SDL_Renderer* render;

	static const int windowHeight = 1080;
	static const int windowWidth = 1920;
	const char* fontPath = "FiraCode.TTF";
	
	const std::string title = "SisyphusPusher";
	Uint32 flags = 0;
	SDL_DisplayMode display;

	TTF_Font* sans = NULL;
	SDL_Color White = { 255, 255, 255 };

public:
	std::list<StrButton*> buttons = std::list<StrButton*>();
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
		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (window == NULL || render == NULL) {
			throw std::exception("Game could not initialize");
			return 1;
		}

		sans = TTF_OpenFont(fontPath, 30);

		player = std::make_unique<Sisyphus>();
		buttons.push_back((new StrButton(100, 200, 3 * 96, 3 * 16, "StrButton.png", "HoveringStrButton.png", player.get(), std::tuple<float, int>(1.0f, 3), std::tuple<float, int>(1.5f, 0))));

		return 0;
	}


	int Update() {
		player->Update();
		for(StrButton* button : buttons)
			button->Update();
		return 0;
	}


	int Draw() {
		SDL_RenderClear(render);

		player->Draw(render);
		for (StrButton* button : buttons)
			button->Draw(render);

		SDL_RenderPresent(render);
		return 0;
	}

	int Exit() {
		TTF_CloseFont(sans);
		SDL_DestroyRenderer(render);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}
};

