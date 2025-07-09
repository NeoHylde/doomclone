#include "Corridor.h"

Corridor::Corridor(glm::vec3 position, Mesh* tileMesh, Mesh* wallMesh) : tile(tileMesh, position){
    walls.emplace_back(Wall(wallMesh, position + glm::vec3(0.0f, 0.0f, -1.0f)));
    walls.emplace_back(Wall(wallMesh, position+ glm::vec3(0.0f, 0.0f, 1.0f)));

}

void Corridor::Draw(Camera& camera, Shader& shader) {
    tile.Draw(camera, shader);
    walls[0].Draw(camera, shader);
    walls[1].Draw(camera, shader);
}