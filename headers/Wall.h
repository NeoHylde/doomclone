#ifndef WALL_CLASS_H
#define WALL_CLASS_H

#include<glm/glm.hpp>
#include"Camera.h"
#include"Mesh.h"
#include "Entity.h"

class Wall {
public:
    glm::vec3 position;
    Mesh* mesh;
    glm::mat4 modelMatrix;

    Wall(Mesh* mesh, glm::vec3 position);
    void Draw(Entity& entity, Shader& shader);
};

#endif