#pragma once

#include <SDL.h>
#include <iostream>

class Application
{
public:
	Application();
	~Application();

	void loop();
	void draw();
	void mousePress(SDL_MouseButtonEvent& b);
private:
	SDL_Window* m_window;
	SDL_Surface* m_window_surface;
	SDL_Event m_window_event;
	int m_resolution_width = 1280;
	int m_resolution_height = 720;
};