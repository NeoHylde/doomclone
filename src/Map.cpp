#include"Map.h"

Map::Map() {
}

void Map::generateGrid(int width, int depth, Mesh* floorMesh) {
    for(float x = 0; x < width*2; x += 2) {
        for(float y = 0; y < depth*2; y += 2) {
            glm::vec3 pos(x, 0.0f,y);
            tiles.emplace_back(floorMesh, pos);
        }
    }
}

void Map::Draw(Camera& camera, Shader& tileShader, Shader& wallShader)
{
    for (Tile& tile : tiles)
        tile.Draw(camera, tileShader);

    for (Wall& wall : walls)
        wall.Draw(camera, wallShader);
}