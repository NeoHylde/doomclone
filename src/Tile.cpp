#include "Tile.h"

Tile::Tile(Mesh* mesh, glm::vec3 pos) {
    Tile::mesh = mesh;
    position = pos;
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    isWalkable = true;
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
    shader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    mesh->Draw(shader, entity);
}
