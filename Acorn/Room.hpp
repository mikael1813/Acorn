#pragma once

#include "Acorn.hpp"
#include <SDL.h>

class Room {
private:
	Acorn* m_player;
	SDL_Surface* m_background;
	int m_max_width = 1280, m_max_height = 720;
public:
	Room();
	Room(Acorn* m_player);
	void draw(SDL_Surface* window_surface);
};