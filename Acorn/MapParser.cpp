#include "MapParser.hpp"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load()
{
    return Parse("map1", "../Assets/maps/map2.tmx");	
}

bool MapParser::Parse(std::string id, std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);

    if (xml.Error()) {
		SDL_Log("Failed to load map: %s", source.c_str());
		return false;
	}

    TiXmlElement* root = xml.RootElement();
    int rowCount, colCount, tileSize = 0;
    root->Attribute("width", &colCount);
    root->Attribute("height", &rowCount);
    root->Attribute("titleWidth", &tileSize);

    // Parse TileSets
    TileSetList tileSets;
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
			tileSets.push_back(ParseTileSet(e));
        }
    }

    // Parse TileLayers
    GameMap* map = new GameMap();
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer")) {
			TileLayer* layer = ParseTileLayer(e, tileSets, tileSize, rowCount, colCount);
			map->m_MapLayers.push_back(layer);
		}
    }

    m_MapDict[id] = map;
    return true;
}

TileSet MapParser::ParseTileSet(TiXmlElement* xmlTileSet)
{
    TileSet tileSet;
    tileSet.Name = xmlTileSet->Attribute("name");
    xmlTileSet->Attribute("firstgid", &tileSet.FirstID);

    xmlTileSet->Attribute("tilecount", &tileSet.TileCount);
    tileSet.LastID = (tileSet.FirstID + tileSet.TileCount) - 1;

    xmlTileSet->Attribute("columns", &tileSet.ColCount);
    tileSet.RowCount = tileSet.TileCount / tileSet.ColCount;
    xmlTileSet->Attribute("tilewidth", &tileSet.TileSize);

    TiXmlElement* Image = xmlTileSet->FirstChildElement();
    tileSet.Source = Image->Attribute("source");
    return tileSet;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TileSetList tileSets, int tileSize, int rowCount, int colCount)
{
    
    TiXmlElement* data = nullptr;
    for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("data")) {
            data = e;
            break;
		}
    }

    if (data == nullptr) {
        SDL_Log("Couldn't find 'data' for layer");
        return nullptr;
    }

    // Parse layer tile map
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tileMap(rowCount, std::vector<int>(colCount));
    
    for (int row = 0; row < rowCount; row++) {
        for (int col = 0; col < colCount; col++) {
            getline(iss, id, ',');
			tileMap[row][col] = std::stoi(id);

            if (!iss.good()) {
                break;
            }
		}
	}

    return (new TileLayer(tileSize, rowCount, colCount, tileMap, tileSets));
}

void MapParser::Clean()
{
    std::map<std::string, GameMap*>::iterator it;
    for (it = m_MapDict.begin(); it != m_MapDict.end(); it++) {
		//delete it->second;
        it->second = nullptr;
	}

    m_MapDict.clear();
	SDL_Log("map parser cleaned");
}