#include "CollisionHandler.hpp"
#include "Engine.hpp"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler() {
	m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetInstance()->GetMap()->GetMapLayers().back();
	m_CollisionTileMap = m_CollisionLayer->GetTileMap();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
	bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);

	return x_overlaps && y_overlaps;
}

CollisionType CollisionHandler::MapCollision(SDL_Rect a)
{
	int tileSize = a.w;
	//int tileSize = m_CollisionLayer->GetTileSize();
	int RowCount = m_CollisionLayer->GetRowCount();
	int ColCount = m_CollisionLayer->GetColCount();

	int left_side = a.x / tileSize;
	int right_side = (a.x + a.w) / tileSize;

	float center_x = (static_cast<float>(left_side) + right_side) / 2;
	
	int top_side = a.y / tileSize;
	int bottom_side = (a.y + a.h) / tileSize;

	float center_y = (static_cast<float>(top_side) + bottom_side) / 2;

	if (left_side < 0) left_side = 0;
	if (right_side > ColCount) right_side = ColCount;

	if (top_side < 0) top_side = 0;
	if (bottom_side > RowCount) bottom_side = RowCount;

	// TO DO find which side of the tile the collision is happening
	// important

	int x_side = 0, y_side = 0;

	for (int i = left_side; i <= right_side; i++) {
		for (int j = top_side; j <= bottom_side; j++) {
			if (m_CollisionTileMap[j][i] > 0) {
				//return true;
				if (i < center_x) {
					x_side -= 1;
				}
				else {
					x_side += 1;
				}
				if (j < center_y) {
					y_side -= 1;
				}
				else {
					y_side += 1;
				}
			}
		}
	}

	if (x_side == 0 && y_side == 0) {
		return CollisionType::NONE;
	}

	if (abs(x_side) > abs(y_side)) {
		if (x_side > 0) {
			return CollisionType::RIGHT;
		}
		else {
			return CollisionType::LEFT;
		}
	}
	else {
		if (y_side > 0) {
			return CollisionType::DOWN;
		}
		else {
			return CollisionType::UP;
		}
	}
}
