#include "Tile.h"

Tile::Tile(Mesh* mesh, glm::vec3 pos) {
    Tile::mesh = mesh;
    position = pos;
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
}

void Tile::Draw(Camera& camera, Shader& shader) {
    shader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    mesh->Draw(shader, camera);
}
