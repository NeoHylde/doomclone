#include"Map.h"

Map::Map() {
}

void Map::addCorridor(glm::vec3 pos, Mesh* floorMesh, Mesh* wallMesh) {
    components.emplace_back(std::make_unique<Corridor>(pos, floorMesh, wallMesh));
}

void Map::Draw(Camera& camera, Shader& shader)
{
    for (const auto& component : components) {
        component->Draw(camera, shader);
    }
}