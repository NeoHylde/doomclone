#include "Tile.h"

Tile::Tile(Mesh* mesh, glm::vec3 position, glm::vec3 translations, glm::quat rotation, glm::vec3 scale)
    : mesh(mesh), position(position), translations(-translations), rotation(rotation), scale(scale) {
    isWalkable = true;
    
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, translations);
    modelMatrix *= glm::mat4_cast(rotation);
    modelMatrix = glm::scale(modelMatrix, scale);
}


bool Tile::getWalkable() {
    return isWalkable;
}

glm::vec3 Tile::getPosition() {
    return position;
}

bool Tile::contains(glm::vec3 point) {
    return (point.x >= position.x - (size/2) &&
            point.x <= position.x + (size/2) &&
            point.z >= position.z - (size/2) &&
            point.z <= position.z + (size/2));
}

void Tile::Draw(Entity& entity, Shader& shader) {
    mesh->Draw(shader, entity, glm::mat4(1.0f), translations, rotation, scale);
}
