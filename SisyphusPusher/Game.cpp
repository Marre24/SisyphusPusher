#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>

#include "Glory.h";




class Game
{
private:
    Glory* glory = new Glory();

    SDL_Window* window = NULL;
    SDL_Renderer* render = NULL;

    const int windowHeight = 800, windowWidth = 700;
    const char* title = { "SisyphusPusher" };
    Uint32 flags = 0;
    SDL_DisplayMode display;

    TTF_Font* sans = NULL;
    SDL_Color White = { 255, 255, 255 };

public:

    bool isPlaying = true;

    int Init() {
        if (SDL_Init(SDL_INIT_VIDEO) == -1 || TTF_Init() == -1)
            return 0;

        if (SDL_GetCurrentDisplayMode(0, &display) != 0) {
            throw std::exception("Could not get current display");
            return 1;
        }

        int x = display.w / 2 - windowWidth / 2, y = display.h / 2 - windowHeight / 2;

        window = SDL_CreateWindow(title, x, y, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
        render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (window == NULL || render == NULL) {
            throw std::exception("Game could not initialize");
            return 1;
        }

        sans = TTF_OpenFont("Sans.TTF", 24);
        
        return 0;
    }


    int Update() {
        glory->AddGlory(1000, 0);
        glory->Update();
        return 0;
    }


    int Draw() {
        SDL_RenderClear(render);

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(sans, glory->ToString().c_str(), White);
        SDL_Texture* Message = SDL_CreateTextureFromSurface(render, surfaceMessage);

        SDL_Rect textRect = { 0, 0, 200, 50};

        SDL_RenderCopy(render, Message, NULL, &textRect);
        
        SDL_RenderPresent(render);
        return 0;
    }
};



int main(int argc, char* args[]) {
    Game* game = new Game;
    if (game->Init())
        return 1;
    
    SDL_Event eventHandler;

    while (game->isPlaying)
    {
        while (SDL_PollEvent(&eventHandler) != 0)          //Have events in que
        {
            if (eventHandler.type == SDL_QUIT)
                game->isPlaying = false;
        }
        game->Update();
        game->Draw();
    }
    return 0;
}