#include "TileLayer.hpp"
#include "TextureManager.hpp"

TileLayer::TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TileSetList tileSets) :
	m_TileSize(tileSize), m_RowCount(rowCount),m_ColCount(colCount),m_TileMap(tileMap), m_TileSets(tileSets)
{

	for (unsigned int i = 0; i < m_TileSets.size(); i++) {
		TextureManager::GetInstance()->Load(m_TileSets[i].Name, "../Assets/maps/" + m_TileSets[i].Source);
	}
}

void TileLayer::Render()
{
	for (unsigned int row = 0; row < m_RowCount; row++)
		for (unsigned int col = 0; col < m_ColCount; col++) {
			int tileID = m_TileMap[row][col];

			if (tileID == 0) continue;

			// else, render the tile
			int index = 0;
			if (m_TileSets.size() > 1) {
				for (unsigned int i = 1; i < m_TileSets.size(); i++) {
					if (tileID > m_TileSets[i].FirstID && tileID < m_TileSets[i].LastID) {
						tileID = tileID + m_TileSets[i].TileCount - m_TileSets[i].LastID;
						index = i;
						break;
					}
				}
			}

			TileSet ts = m_TileSets[index];
			int tileRow = tileID / ts.ColCount;
			int tileCol = tileID - tileRow * ts.ColCount - 1;

			// if this tile is on the last column
			if (tileID % ts.ColCount == 0) {
				tileRow--;
				tileCol = ts.ColCount - 1;
			}

			TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, tileCol, tileRow, col, row);
			//TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, row * ts.TileSize, col * ts.TileSize, tileRow, tileCol);


		}

}

void TileLayer::Update()
{

}
