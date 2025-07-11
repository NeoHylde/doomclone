#include"Map.h"

Map::Map() {
}

void Map::generateGrid(int size, Mesh* floorMesh) {
    for (float i = 0; i < size * 2; i += 2) {
        for (float j = 0; j < size * 2; j += 2) {
            glm::vec3 position = glm::vec3(i + 2, 0.0f, j + 2);
            glm::vec3 translation = position;
            glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
            glm::vec3 scale = glm::vec3(1.0f);

            tiles.emplace_back(Tile(floorMesh, position, translation, rotation, scale));
        }
    }
}


// Checks if tiles in grid are walkable
bool Map::isPositionWalkable(glm::vec3 pos) {
    for (auto& tile : tiles) {
        if (tile.contains(pos)) {
            return tile.getWalkable();
        }
    }
    return false;
}

// Renders all map components for current frame
void Map::Draw(Entity& entity, Shader& shader)
{
    for (const auto& component : components) {
        component->Draw(entity, shader);
    }

    for (Tile tile : tiles) {
        tile.Draw(entity, shader);
    }
}