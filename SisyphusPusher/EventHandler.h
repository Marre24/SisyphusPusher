#pragma once

#include <SDL.h>
#include <list>

#include "StrButton.h";
#include "Sisyphus.h";

class EventHandler
{
private:
	std::list<StrButton*> &buttonList;
	std::map<SDL_Keycode, bool> lastFrameKeys;
	bool first = true;
	Sisyphus* player;

public:

	EventHandler(std::list<StrButton*> &buttonList, Sisyphus* player) : buttonList(buttonList) 
	{ 
		this->player = player;
	}

	int MousePress(SDL_MouseButtonEvent b) {
		if (b.button == SDL_BUTTON_LEFT) {
			if (!buttonList.empty())
				for(StrButton* var : buttonList)
					var->OnClick();
		}
		return 0;
	}

	int Update(std::map<SDL_Keycode, bool> keyMap) {
		if (first)
		{
			lastFrameKeys = keyMap;
			first = false;
			return 0;
		}

		for (int i = 0; i < keyMap.size(); i++) {
			if (keyMap[SDLK_SPACE] && !lastFrameKeys[SDLK_SPACE])
				player->Push();
		}
		lastFrameKeys = keyMap;
		return 0;
	}

};

