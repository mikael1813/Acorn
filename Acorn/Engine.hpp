#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Acorn.hpp"
#include "GameMap.hpp"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

class Engine {
public:

	static Engine* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
	}

	bool Init();
	bool Clean();
	void Quit();


	void Update();
	void Render();
	void Events();

	inline GameMap* GetMap() const { return m_LevelMap; }
	inline bool isRunning() { return m_IsRunning; }
	inline SDL_Renderer* GetRenderer() { return m_Renderer; }


private:
	Engine();
	bool m_IsRunning;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	static Engine* s_Instance;

	Acorn* player;
	GameMap* m_LevelMap;
};