#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>


class Game
{
private:
    SDL_Window* window;
    SDL_Renderer* render;

    const int windowHeight = 800, windowWidth = 700;
    const char* title = { "SisyphusPusher" };
    Uint32 flags = 0;
    SDL_DisplayMode display;

    TTF_Font* sans;
    SDL_Color White = { 255, 255, 255 };

public:

    bool isPlaying = true;

    int Init() {
        SDL_Init(SDL_INIT_VIDEO);
        if (SDL_GetCurrentDisplayMode(0, &display) != 0) {
            throw std::exception("Could not get current display");
            return 1;
        }

        int x = display.w / 2 - windowWidth / 2, y = display.h / 2 - windowHeight / 2;

        window = SDL_CreateWindow(title, x, y, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
        render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (window == NULL || render == NULL)
            return 1;

        sans = TTF_OpenFont("C:/Windows/Fonts/Arial.TTF", 24);
        
        return 0;
    }

    int Update() {


        return 0;
    }

    int Draw() {
        //Clear screen
        //SDL_RenderClear(render);

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(sans, "Hello this is sans", White);
        SDL_Texture* Message = SDL_CreateTextureFromSurface(render, surfaceMessage);

        SDL_Rect Message_rect = { display.w / 2 - windowWidth / 2, display.h / 2 - windowHeight / 2,200,100};

        SDL_RenderCopy(render, Message, NULL, &Message_rect);
        //SDL_RenderPresent(render);

        return 0;
    }
};



int main(int argc, char* args[]) {
    Game* game = new Game;
    if (game->Init()) {
        throw std::exception("Game could not initialize");
        return 1;
    }
    
    SDL_Event eventHandler;

    while (game->isPlaying)
    {
        while (SDL_PollEvent(&eventHandler) != 0)          //Have events in que
        {
            if (eventHandler.type == SDL_QUIT)
                game->isPlaying = false;

            game->Update();
            game->Draw();
        }
    }
    return 0;
}



