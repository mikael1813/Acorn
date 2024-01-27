#include "Room.hpp"

Room::Room() {

}

Room::Room(Acorn* player) {
	m_player = player;
}

void Room::draw(SDL_Surface* window_surface) {
	SDL_BlitScaled(this->m_background, NULL, window_surface, 0);
}