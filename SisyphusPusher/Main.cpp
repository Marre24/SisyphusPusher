
#include <list>

#include "Glory.h";
#include "StrButton.h";
#include "EventHandler.h";
#include "Game.h";


int main(int argc, char* args[]) {
    std::unique_ptr<Game> game = std::make_unique<Game>();
    if (game->Init())
        return 1;
    
    std::unique_ptr<EventHandler> eventHandler = std::make_unique<EventHandler>(game->buttons, game->player.get());
    std::map<SDL_Keycode, bool> keyMap;
    SDL_Event e;

    while (game->isPlaying)
    {
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
    }
    game->Exit();
    return 0;
}