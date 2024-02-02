#pragma once

#include <SDL.h>

#include <vector>
#include "TileLayer.hpp"
#include "GameMap.hpp"


class CollisionHandler {
public:
	static CollisionHandler* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler();
	}

	bool CheckCollision(SDL_Rect a, SDL_Rect b);
	bool MapCollision(SDL_Rect a);

private:
	CollisionHandler();
	static CollisionHandler* s_Instance;

	TileMap m_CollisionTileMap;
	TileLayer* m_CollisionLayer;


};