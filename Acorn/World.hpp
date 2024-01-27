#pragma once

#include "Room.hpp"

class World {
private:
	// graph of rooms
	Room m_current_room;
	SDL_Surface* m_window_surface;
public:
	World(SDL_Surface* m_window_surface);
	void draw_current_room();

};