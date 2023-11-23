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


class Game
{
private:
	Glory* glory;


	SDL_Window* window;
	SDL_Renderer* render;

	const int windowHeight = 800, windowWidth = 700;
	const std::string title = "SisyphusPusher";
	Uint32 flags = 0;
	SDL_DisplayMode display;

	TTF_Font* sans = NULL;
	SDL_Color White = { 255, 255, 255 };

public:
	StrButton* button;

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

		sans = TTF_OpenFont("FiraCode.TTF", 30);

		glory = new Glory();
		button = new StrButton(100, 200, 3 * 96, 3 * 16,  "StrButton.png", "HoveringStrButton.png", glory, std::tuple<float, int>(1.0f, 3), std::tuple<float, int>(1.5f, 0));

		return 0;
	}


	int Update() {
		glory->Update();
		button->Update();
		return 0;
	}


	int Draw() {
		SDL_RenderClear(render);

		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(sans, glory->ToString().c_str(), White);
		SDL_Texture* Message = SDL_CreateTextureFromSurface(render, surfaceMessage);
		SDL_Rect textRect = { 0, 0, surfaceMessage->w, surfaceMessage->h };
		SDL_RenderCopy(render, Message, NULL, &textRect);

		button->Draw(render);

		SDL_RenderPresent(render);
		return 0;
	}
};

