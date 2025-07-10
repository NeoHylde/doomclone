#include"Map.h"

Map::Map() {
}

void Map::addCorridor(glm::vec3 pos, Mesh* floorMesh, Mesh* wallMesh) {
    components.emplace_back(std::make_unique<Corridor>(pos, floorMesh, wallMesh));
}

void Map::generateGrid(int size,  Mesh* floorMesh) {
    for(float i = 0; i < size*2; i += 2) {
        for(float j = 0; j < size*2; j += 2) {
            tiles.emplace_back(Tile(floorMesh, glm::vec3(i+2, 0.0f, j+2)));
        }
    }
}

bool Map::isPositionWalkable(glm::vec3 pos) {
    for (auto& tile : tiles) {
        if (tile.contains(pos)) {
            return tile.getWalkable();
        }
    }
    return false;
}


void Map::Draw(Entity& entity, Shader& shader)
{
    for (const auto& component : components) {
        component->Draw(entity, shader);
    }

    for (Tile tile : tiles) {
        tile.Draw(entity, shader);
    }
}