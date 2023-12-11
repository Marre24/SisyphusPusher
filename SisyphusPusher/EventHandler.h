#pragma once
#pragma once

#include <SDL.h>
#include <list>

#include "StrButton.h";
#include "StaminaRefillButton.h";
#include "StaminaExpandButton.h";
#include "Sisyphus.h";
#include "BuyAmountButton.h";
#include "ExitButton.h";

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
	ExitButton* exitButton;

public:

	EventHandler(std::list<StrButton*>& strButtonList, StaminaRefillButton* stamButton, StaminaExpandButton* stamExpandButton, BuyAmountButton* buyAmountButton, Sisyphus* player, const SDL_Rect* window, ExitButton* exitButton) : 
		strButtonList(strButtonList), stamButton(stamButton), stamExpandButton(stamExpandButton), buyAmountButton(buyAmountButton), player(player), window(window), exitButton(exitButton)
	{ 

	}

	int MousePress(SDL_MouseButtonEvent b) {
		if (b.button == SDL_BUTTON_LEFT) {
			exitButton->OnClick();
			for (StrButton* var : strButtonList) {
				var->OnClick();
			}
			stamButton->OnClick();
			stamExpandButton->OnClick();
			buyAmountButton->OnClick();
			HandleWindowInteraction();
		}
		return 0;
	}

	void HandleWindowInteraction() {
		SDL_Point mouse = { 0, 0 };
		SDL_GetMouseState(&mouse.x, &mouse.y);
		if (SDL_PointInRect(&mouse, window)) {
			player->Push();
		}
	}

	int Update(std::map<SDL_Keycode, bool> keyMap) {
		if (first)
		{
			lastFrameKeys = keyMap;
			first = false;
			return 0;
		}

		if (keyMap[SDLK_SPACE] && !lastFrameKeys[SDLK_SPACE])
			player->Push();
		lastFrameKeys = keyMap;
		return 0;
	}

};

