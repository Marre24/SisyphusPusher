#pragma once
#include "Glory.h";

class Sisyphus
{
public:
	Glory* glory = new Glory();

	Sisyphus() {

	}

	int Update() {
		glory->Update();

		return 0;
	}

	int Draw(SDL_Renderer* renderer) {
		glory->Draw(renderer);

		return 0;
	}

private:

};