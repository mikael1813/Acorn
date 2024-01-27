#include "Room.hpp"
#include "FileLoader.hpp"

Room::Room() {
	m_background = load_surface("../Images/copac.bmp");
}

Room::Room(Acorn* player) {
	m_player = player;
	m_background = load_surface("../Images/copac.bmp");
}

void Room::draw(SDL_Surface* window_surface) {
	SDL_BlitScaled(this->m_background, NULL, window_surface, 0);
}