#pragma once

#include "Room.hpp"

class World {
private:
	// graph of rooms
	Room m_current_room;
	Acorn m_player;
public:
	World();
	void draw_current_room(SDL_Surface* m_window_surface);
	void move_player(int x, int y);

};