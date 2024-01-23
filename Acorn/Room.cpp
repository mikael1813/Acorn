#include "Room.hpp"

Room::Room() {

}

void Room::draw(SDL_Surface* window_surface) {
	SDL_BlitScaled(this->m_background, NULL, window_surface, 0);
}