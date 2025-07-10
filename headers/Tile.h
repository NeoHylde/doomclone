#ifndef TILE_CLASS_H
#define TILE_CLASS_H

#include"Mesh.h"
#include"Camera.h"
#include "shaderClass.h"
#include "Entity.h"

#include<glm/glm.hpp>


class Tile{
private:
    glm::vec3 position;
    Mesh* mesh;
    glm::mat4 modelMatrix;
    bool isWalkable = false;
    float size = 2.0f;
public:
    
    bool contains(glm::vec3 pos);

    Tile(Mesh* mesh, glm::vec3 position);

    bool getWalkable();

    glm::vec3 getPosition();

    void Draw(Entity& entity, Shader& shader);
};

#endif