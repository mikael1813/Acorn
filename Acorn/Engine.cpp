#include "Engine.hpp"
#include "TextureManager.hpp"
#include "Vector2D.hpp"
#include "Transform.hpp"
#include "Input.hpp"
#include "Timer.hpp"
#include "MapParser.hpp"
#include "Camera.hpp"

#include "SDL.h"

Engine* Engine::s_Instance = nullptr;
//MapParser* MapParser::s_Instance = nullptr;

Engine::Engine() {

}

bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	SDL_WindowFlags winddow_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	m_Window = SDL_CreateWindow(
		"Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		winddow_flags);
	if (m_Window == nullptr) {
		SDL_Log("Failed to create Window: %s", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(
		m_Window,
		-1,
		SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) {
		SDL_Log("Failed to create Renderer: %s", SDL_GetError());
		return false;
	}

	if (!MapParser::GetInstance()->Load()) {
		SDL_Log("Failed to load map: %s", SDL_GetError());
	}

	m_LevelMap = MapParser::GetInstance()->GetMaps("map1");

	TextureManager::GetInstance()->Load("acorn", "../Images/ghinda_radu.png");
	TextureManager::GetInstance()->Load("tree", "../Images/copac.png");
	player = new Acorn(new Properties("acorn", 200, 200, 32, 32));


	Camera::GetInstance()->SetTarget(player->GetOrigin());

	m_IsRunning = true;
	return true;
}

bool Engine::Clean()
{
	TextureManager::GetInstance()->Clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();
	return false;
}

void Engine::Quit()
{
	m_IsRunning = false;
}

void Engine::Update()
{
	float dt = Timer::GetInstance()->GetDeltaTime();
	m_LevelMap->Update();
	player->Update(dt);
	Camera::GetInstance()->Update(dt);
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);

	TextureManager::GetInstance()->Draw("tree", 0, 0, 1280, 720);

	m_LevelMap->Render();
	player->Draw();
	
	SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
	Input::GetInstance()->Listen();

	/*SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		this->Quit();
		break;
	}*/
}
