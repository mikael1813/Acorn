#pragma once

#include <SDL.h>
#include "string"

class Acorn {
private:
	SDL_Rect m_player_position;
	SDL_Surface* m_avatar;
public:
	Acorn();
	void draw(SDL_Surface* window_surface);
};