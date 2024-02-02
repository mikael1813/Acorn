#pragma once

#include "Layer.hpp"
#include <string>
#include <vector>

struct TileSet {
	int FirstID, LastID;
	int RowCount, ColCount;
	int TileCount, TileSize;
	std::string Name, Source;
};

using TileSetList = std::vector<TileSet>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer : public Layer{
public:
	TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TileSetList tileSets);
	virtual void Render();
	virtual void Update();
	inline TileMap GetTileMap() { return m_TileMap; }

	inline int GetTileSize() const { return m_TileSize; }
	inline int GetRowCount() const { return m_RowCount; }
	inline int GetColCount() const { return m_ColCount; }

private:
	int m_TileSize;
	int m_RowCount, m_ColCount;

	TileMap m_TileMap;
	TileSetList m_TileSets;
};