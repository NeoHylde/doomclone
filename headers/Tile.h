#ifndef TILE_CLASS_H
#define TILE_CLASS_H

#include"Mesh.h"
#include"Camera.h"
#include "shaderClass.h"
#include "Entity.h"

#include<glm/glm.hpp>
#include "MapComponent.h"


class Tile : public MapComponent{
private:
    glm::vec3 translations;
    glm::quat rotation;
    glm::vec3 scale;
    glm::vec3 position;
    Mesh* mesh;
    glm::mat4 modelMatrix;
    bool isWalkable = false;
    float size = 2.0f;
public:
    Tile(
        Mesh* mesh, 
        glm::vec3 position, 
        glm::vec3 translations,
        glm::quat rotation,
        glm::vec3 scale
    );
    
    bool contains(glm::vec3 pos) override;
    
    bool getWalkable() override;

    glm::vec3 getPosition();

    void Draw(Entity& entity, Shader& shader) override;
};

#endif