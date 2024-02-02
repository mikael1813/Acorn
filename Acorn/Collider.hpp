#pragma once

#include "SDL.h"

class Collider {
public:

	inline SDL_Rect GetBox() const { return m_Box; }
	inline void SetBuffer(int x, int y, int w, int h) { m_Buffer = { x, y, w, h }; }

	void SetBox(int x,int y,int w,int h) {
		m_Box = { 
			x - m_Buffer.x, 
			y - m_Buffer.y,
			w - m_Buffer.w,
			h - m_Buffer.h 
		};
	}

private:
	SDL_Rect m_Box;
	SDL_Rect m_Buffer;
};