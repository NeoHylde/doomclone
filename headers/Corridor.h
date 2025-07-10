#ifndef CORRIDOR_CLASS_H
#define CORRIDOR_CLASS_H

#include"Tile.h"
#include"Wall.h"
#include"shaderClass.h"
#include"Mesh.h"
#include"Camera.h"
#include"MapComponent.h"
#include "Entity.h"

#include<vector>
#include<glm/glm.hpp>

class Corridor : public MapComponent {
public:
    //std::vector<Tile> tiles;
    Tile tile;
    std::vector<Wall> walls;
    glm::vec3 position;

    Corridor(glm::vec3 position, Mesh* tileMesh, Mesh* wallMesh);
    void Draw(Entity& entity, Shader& shader) override;
};


#endif