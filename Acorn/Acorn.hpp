#pragma once
#include <SDL.h>

class Acorn {
private:
	SDL_Rect m_player_position;
	SDL_Surface* m_avatar;
public:
	Acorn();
};//cum sa nu