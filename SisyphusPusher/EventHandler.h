#pragma once

#include <SDL.h>
#include <list>

#include "StrButton.h";

class EventHandler
{
private:
	std::list<StrButton*> &buttonList;

public:

	EventHandler(std::list<StrButton*> &buttonList) : buttonList(buttonList) { }

	int MousePress(SDL_MouseButtonEvent b) {
		if (b.button == SDL_BUTTON_LEFT) {
			for(StrButton* var : buttonList)
				var->OnClick();
		}
		return 0;
	}



};

