#include "World.hpp"


World::World() {
	m_player = Acorn();
	m_current_room = Room(&m_player);
}

void World::draw_current_room(SDL_Surface* window_surface) {
	m_current_room.draw(window_surface);
}