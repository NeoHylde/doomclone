#include "Corridor.h"

Corridor::Corridor(glm::vec3 position, Mesh* tileMesh, Mesh* wallMesh) : tile(tileMesh, position){
    walls.emplace_back(Wall(wallMesh, position + glm::vec3(0.0f, 0.0f, -1.0f)));
    walls.emplace_back(Wall(wallMesh, position+ glm::vec3(0.0f, 0.0f, 1.0f)));

}

void Corridor::Draw(Entity& entity, Shader& shader) {
    tile.Draw(entity, shader);
    walls[0].Draw(entity, shader);
    walls[1].Draw(entity, shader);
}