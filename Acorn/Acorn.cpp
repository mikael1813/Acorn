#include "Acorn.hpp"
#include "FileLoader.hpp"

Acorn::Acorn() {
	m_player_position.x = 1280 / 2;
	m_player_position.y = 520;
	m_player_position.w = 300;
	m_player_position.h = 400;
	m_avatar = load_surface("../Images/ghinda.bmp");
}

void Acorn::draw(SDL_Surface* window_surface) {
	SDL_BlitScaled(this->m_avatar, NULL, window_surface, &this->m_player_position);
}

void Acorn::move(int x, int y) {
	m_player_position.x = m_player_position.x + x * m_player_speed;
	m_player_position.y = m_player_position.y + y * m_player_speed;
}