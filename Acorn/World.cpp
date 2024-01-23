#include "World.hpp"


World::World(SDL_Surface* m_window_surface) {
	this->m_window_surface = m_window_surface;
}

void World::draw_current_room() {
	current_room = Room();
	current_room.draw(m_window_surface);
}