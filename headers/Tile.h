#ifndef TILE_CLASS_H
#define TILE_CLASS_H

#include"Mesh.h"
#include"Camera.h"
#include "shaderClass.h"

#include<glm/glm.hpp>


class Tile {
public:
    glm::vec3 position;
    Mesh* mesh;
    glm::mat4 modelMatrix;

    Tile(Mesh* mesh, glm::vec3 position);
    void Draw(Camera& camera, Shader& shader);
};

#endif