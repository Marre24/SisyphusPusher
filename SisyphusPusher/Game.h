#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include <list>
#include <memory.h>

#include "Glory.h";
#include "Tartarus.h";
#include "StrButton.h";
#include "EventHandler.h";
#include "Sisyphus.h";
#include "StaminaRefillButton.h";
#include "StaminaExpandButton.h";
#include "BuyAmountButton.h"
#include "Ground.h";


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
	const std::string borderTexturePath = "StaminaBar.png";
	const std::string greenTexturePath = "Stamina.png";
	Uint32 flags = 0;
	SDL_DisplayMode display;

	SDL_Color White = { 255, 255, 255 };

	std::vector<SDL_Surface*> surfaceses;
	std::vector<SDL_Texture*> frames;
	SDL_Surface* tartarusSurface;
	SDL_Texture* tartarusTexture;

	SDL_Surface* buttonWindow;
	SDL_Surface* btnUp;
	SDL_Surface* btnDown;
	SDL_Surface* smallBtnDown;
	SDL_Surface* smallBtnUp;
	SDL_Surface* exitButtonSurface;
	SDL_Surface* border;
	SDL_Surface* greenColor;
	SDL_Surface* groundSurface1;
	SDL_Surface* groundSurface2;

	SDL_Texture* buttonWindowTexture;
	SDL_Texture* btnUpTexture;
	SDL_Texture* btnDownTexture;
	SDL_Texture* smallBtnDownTexture;
	SDL_Texture* smallBtnUpTexture;
	SDL_Texture* exitButtonTexture;
	SDL_Texture* borderTexure;
	SDL_Texture* greenColorTexture;
	SDL_Texture* groundTexture1;
	SDL_Texture* groundTexture2;


	TTF_Font* font;
	TTF_Font* smallFont;
	const float cps = 8;
	const char* fontPath = "FieldGuide.TTF";

public:
	const SDL_Rect buttonWindowRect = { 1024, 28, 896, 1024 };
	const SDL_Rect tartarusWindow{ 0, 28, 1024, 1024 };

	std::unique_ptr<Ground> ground;
	std::unique_ptr<Sisyphus> player;
	std::unique_ptr<Tartarus> tartarus;
	std::unique_ptr<Glory> glory = std::make_unique<Glory>();

	std::unique_ptr<ExitButton> exitButton;
	std::unique_ptr<StaminaRefillButton> stamButton;
	std::unique_ptr<BuyAmountButton> buyAmountButton;
	std::unique_ptr<StaminaExpandButton> stamExpandButton;
	std::vector<StrButton> strButtons = std::vector<StrButton>();

	bool isPlaying = true;

	int Init() {
		if (SDL_Init(SDL_INIT_VIDEO) == -1 || TTF_Init() == -1)
			return 0;

		InitDisplay();

		font = TTF_OpenFont(fontPath, 30);
		smallFont = TTF_OpenFont(fontPath, 20);
		if (!font || !smallFont) 
			throw std::exception("Failed to load font");

		//Init Surfaces and Textures
		buttonWindow = IMG_Load("ButtonWindow.png");
		btnDown = IMG_Load(btnDownPath.c_str());
		btnUp = IMG_Load(btnUpPath.c_str());
		smallBtnDown = IMG_Load("ExitButtonUp.png");
		smallBtnUp = IMG_Load("ExitButtonDown.png");
		exitButtonSurface = TTF_RenderText_Solid(font, "Exit", { 255, 255, 255 });
		border = IMG_Load(borderTexturePath.c_str());
		greenColor = IMG_Load(greenTexturePath.c_str());
		tartarusSurface = IMG_Load("Tartarus.png");
		surfaceses.push_back(IMG_Load("SisyphusFrames/0.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/1.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/2.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/3.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/4.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/5.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/6.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/7.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/8.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/7.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/6.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/5.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/4.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/3.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/2.png"));
		surfaceses.push_back(IMG_Load("SisyphusFrames/1.png"));
		groundSurface1 = IMG_Load("Ground1.png");
		groundSurface2 = IMG_Load("Ground2.png");


		buttonWindowTexture = SDL_CreateTextureFromSurface(renderer, buttonWindow);
		btnDownTexture = SDL_CreateTextureFromSurface(renderer, btnDown);
		btnUpTexture = SDL_CreateTextureFromSurface(renderer, btnUp);
		smallBtnDownTexture = SDL_CreateTextureFromSurface(renderer, btnDown);
		smallBtnUpTexture = SDL_CreateTextureFromSurface(renderer, btnUp);
		exitButtonTexture = SDL_CreateTextureFromSurface(renderer, exitButtonSurface);
		borderTexure = SDL_CreateTextureFromSurface(renderer, border);
		greenColorTexture = SDL_CreateTextureFromSurface(renderer, greenColor);
		tartarusTexture = SDL_CreateTextureFromSurface(renderer, tartarusSurface);
		for (SDL_Surface* surface : surfaceses)
			frames.push_back(SDL_CreateTextureFromSurface(renderer, surface));
		groundTexture1 = SDL_CreateTextureFromSurface(renderer, groundSurface1);
		groundTexture2 = SDL_CreateTextureFromSurface(renderer, groundSurface2);

		//Frees surface after making them into textures
		for (SDL_Surface* surface : surfaceses)
			SDL_FreeSurface(surface);
		SDL_FreeSurface(tartarusSurface);
		SDL_FreeSurface(buttonWindow);
		SDL_FreeSurface(btnDown);
		SDL_FreeSurface(btnUp);
		SDL_FreeSurface(smallBtnDown);
		SDL_FreeSurface(smallBtnUp);
		SDL_FreeSurface(exitButtonSurface);
		SDL_FreeSurface(border);
		SDL_FreeSurface(greenColor);
		SDL_FreeSurface(groundSurface1);
		SDL_FreeSurface(groundSurface2);

		//init player, ground and tartarus
		player = std::make_unique<Sisyphus>(glory.get());
		tartarus = std::make_unique<Tartarus>(player.get(), tartarusTexture, frames);
		ground = std::make_unique<Ground>(player.get(), groundTexture1, groundTexture2);

		int id = -1;
		//Row 1
		strButtons.push_back(StrButton(1344, 192 + 40,
			btnUpTexture, btnDownTexture, borderTexure, greenColorTexture,
			player.get(),
			4, 1.6 / cps, 1.07f, ++id));
		strButtons.push_back(StrButton(1344, 320 + 40,
			btnUpTexture, btnDownTexture, borderTexure, greenColorTexture,
			player.get(),
			 60,  20 / cps, 1.15f, ++id));
		strButtons.push_back(StrButton(1344, 448 + 40,
			btnUpTexture, btnDownTexture, borderTexure, greenColorTexture,
			player.get(),
			 720,  90 / cps, 1.14f, ++id));
		strButtons.push_back(StrButton(1344, 576 + 40,
			btnUpTexture, btnDownTexture, borderTexure, greenColorTexture,
			player.get(),
			 8640,  360 / cps, 1.13f, ++id));
		strButtons.push_back(StrButton(1344, 704 + 40,
			btnUpTexture, btnDownTexture, borderTexure, greenColorTexture,
			player.get(),
			 103000,  2160.0 / cps, 1.12f, ++id));
		//Row 2
		strButtons.push_back(StrButton(1632, 192 + 40,
			btnUpTexture, btnDownTexture, borderTexure, greenColorTexture,
			player.get(),
			 1244000,  6480.0 / cps, 1.11f, ++id));
		strButtons.push_back(StrButton(1632, 320 + 40,
			btnUpTexture, btnDownTexture, borderTexure, greenColorTexture,
			player.get(),
			 14929920, 19440 / cps, 1.10f, ++id));
		strButtons.push_back(StrButton(1632, 448 + 40,
			btnUpTexture, btnDownTexture, borderTexure, greenColorTexture,
			player.get(),
			 179159040, 58320 / cps, 1.09f, ++id));
		strButtons.push_back(StrButton(1632, 576 + 40,
			btnUpTexture, btnDownTexture, borderTexure, greenColorTexture,
			player.get(),
			 2149908480,  174960 / cps, 1.08f, ++id));
		strButtons.push_back(StrButton(1632, 704 + 40,
			btnUpTexture, btnDownTexture, borderTexure, greenColorTexture,
			player.get(),
			 25798901760, 804816 / cps, 1.07f, ++id));
		
		//Stamina buttons
		stamButton = std::make_unique<StaminaRefillButton>(1632, 896 + 40,
			btnUpTexture, btnDownTexture,
			player.get(), 
			5, 0.5f, 5.0f);
		stamExpandButton = std::make_unique<StaminaExpandButton>(1344, 896 + 40,
			btnUpTexture, btnDownTexture,
			player.get(), 
			1, 10, 10.0f);
		
		//BuyButton
		buyAmountButton = std::make_unique<BuyAmountButton>(1024 + 32, 256 + 40, btnUpTexture, btnDownTexture, player.get());

		//ExitButton
		exitButton = std::make_unique<ExitButton>(windowWidth - 85, 50, exitButtonSurface->w, exitButtonSurface->h, smallBtnUpTexture, smallBtnDownTexture, exitButtonTexture);
		
		return 0;
	}
	
	int InitDisplay() {
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
	}


	int Update() {
		exitButton->Update();
		player->Update();
		for (int i = 0; i < strButtons.size(); i++)
			strButtons.at(i).Update();
		stamButton->Update();
		stamExpandButton->Update();
		buyAmountButton->Update();
		return 0;
	}


	int Draw() {
		SDL_RenderClear(renderer);

		tartarus->Draw(renderer);
		player->Draw(renderer, font);
		ground->Draw(renderer);
		SDL_RenderCopy(renderer, buttonWindowTexture, NULL, &buttonWindowRect);
		glory->Draw(renderer, font);
		exitButton->Draw(renderer, font);
		for (int i = 0; i < strButtons.size(); i++)
			strButtons.at(i).Draw(renderer,font, smallFont);
		stamButton->Draw(renderer, font, smallFont);
		stamExpandButton->Draw(renderer, font, smallFont);
		buyAmountButton->Draw(renderer, font);

		SDL_RenderPresent(renderer);
		return 0;
	}

	int Exit() {
		SDL_DestroyTexture(buttonWindowTexture);
		SDL_DestroyTexture(btnUpTexture);
		SDL_DestroyTexture(btnDownTexture);
		SDL_DestroyTexture(smallBtnDownTexture);
		SDL_DestroyTexture(smallBtnUpTexture);
		SDL_DestroyTexture(exitButtonTexture);
		for (SDL_Texture* frame : frames)
			SDL_DestroyTexture(frame);
		SDL_DestroyTexture(tartarusTexture);
		for (SDL_Surface* surface : surfaceses)
			SDL_FreeSurface(surface);
		SDL_FreeSurface(tartarusSurface);

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		TTF_CloseFont(font);
		TTF_CloseFont(smallFont);
		return 0;
	}
};

