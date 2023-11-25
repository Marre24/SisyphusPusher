#pragma once

#include <SDL.h>
#include <list>

#include "StrButton.h";
#include "StaminaRefillButton.h";
#include "StaminaExpandButton.h";
#include "Sisyphus.h";

class EventHandler
{
private:
	std::list<StrButton*> strButtonList;
	std::list<StaminaRefillButton*> stamButtonList;
	std::list<StaminaExpandButton*> stamExpandButtonList;
	std::map<SDL_Keycode, bool> lastFrameKeys;
	bool first = true;
	Sisyphus* player;

public:

	EventHandler(std::list<StrButton*> &strButtonList, std::list<StaminaRefillButton*>& stamButtonList, std::list<StaminaExpandButton*>& stamExpandButtonList, Sisyphus* player) : strButtonList(strButtonList), stamButtonList(stamButtonList), stamExpandButtonList(stamExpandButtonList)
	{ 
		this->player = player;
	}

	int MousePress(SDL_MouseButtonEvent b) {
		if (b.button == SDL_BUTTON_LEFT) {
			if (!strButtonList.empty())
				for(StrButton* var : strButtonList)
					var->OnClick();
			if (!stamButtonList.empty())
				for (StaminaRefillButton* var : stamButtonList)
					var->OnClick();
			if (!stamExpandButtonList.empty())
				for (StaminaExpandButton* var : stamExpandButtonList)
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

