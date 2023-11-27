#pragma once

#include <SDL.h>
#include <list>

#include "StrButton.h";
#include "StaminaRefillButton.h";
#include "StaminaExpandButton.h";
#include "Sisyphus.h";
#include "BuyAmountButton.h"

class EventHandler
{
private:
	std::list<StrButton*> strButtonList;
	StaminaRefillButton* stamButton;
	StaminaExpandButton* stamExpandButton;
	BuyAmountButton* buyAmountButton;
	std::map<SDL_Keycode, bool> lastFrameKeys;
	bool first = true;
	Sisyphus* player;
	const SDL_Rect* window;

public:

	EventHandler(std::list<StrButton*> &strButtonList, StaminaRefillButton* stamButton, StaminaExpandButton* stamExpandButton, BuyAmountButton* buyAmountButton, Sisyphus* player, const SDL_Rect* window) : strButtonList(strButtonList)
	{ 
		this->buyAmountButton = buyAmountButton;
		this->stamButton = stamButton;
		this->stamExpandButton = stamExpandButton;
		this->player = player;
		this->window = window;
	}

	int MousePress(SDL_MouseButtonEvent b) {
		if (b.button == SDL_BUTTON_LEFT) {
			if (!strButtonList.empty())
				for(StrButton* var : strButtonList)
					var->OnClick();
			stamButton->OnClick();
			stamExpandButton->OnClick();
			buyAmountButton->OnClick();
			SDL_Point mouse = { 0,0 };
			SDL_GetMouseState(&mouse.x, &mouse.y);
			if (SDL_PointInRect(&mouse, window))
				player->Push();
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

