#pragma once

#include "Acorn.hpp"
#include <SDL.h>

class Room {
private:
	Acorn player;
	SDL_Surface* m_background;
	int max_width = 1280, max_height = 720;
public:
	Room();
	void draw(SDL_Surface* window_surface);
};