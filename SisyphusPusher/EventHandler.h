#pragma once

#include <SDL.h>
#include <list>

#include "StrButton.h";
#include "StaminaButton.h";
#include "Sisyphus.h";

class EventHandler
{
private:
	std::list<StrButton*> strButtonList;
	std::list<StaminaButton*> stamButtonList;
	std::map<SDL_Keycode, bool> lastFrameKeys;
	bool first = true;
	Sisyphus* player;

public:

	EventHandler(std::list<StrButton*> &strButtonList, std::list<StaminaButton*>& stamButtonList, Sisyphus* player) : strButtonList(strButtonList), stamButtonList(stamButtonList)
	{ 
		this->player = player;
	}

	int MousePress(SDL_MouseButtonEvent b) {
		if (b.button == SDL_BUTTON_LEFT) {
			if (!strButtonList.empty())
				for(StrButton* var : strButtonList)
					var->OnClick();
			if (!stamButtonList.empty())
				for (StaminaButton* var : stamButtonList)
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

