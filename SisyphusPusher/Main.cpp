
#include <list>

#include "Glory.h";
#include "StrButton.h";
#include "EventHandler.h";
#include "Game.h";

const int FPS = 60;
const int frameDelay = 1000 / FPS;

int main(int argc, char* args[]) {
    std::unique_ptr<Game> game = std::make_unique<Game>();
    if (game->Init())
        return 1;
    
    std::unique_ptr<EventHandler> eventHandler = std::make_unique<EventHandler>(game->strButtons, game->stamButton, game->stamExpandButton, game->buyAmountButton, game->player.get(), game->tartarusWindow);
    std::map<SDL_Keycode, bool> keyMap;
    SDL_Event e;
    Uint32 frameStart;
    int frameTime;

    while (game->isPlaying)
    {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0)          //Have events in que
        {
            switch (e.type) {
            case SDL_QUIT:
                game->isPlaying = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                eventHandler->MousePress(e.button);
                break;
            case SDL_KEYDOWN:
                keyMap[e.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                keyMap[e.key.keysym.sym] = false;
                break;
            }
            eventHandler->Update(keyMap);
        }
        game->Update();
        game->Draw();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
    game->Exit();
    return 0;
}