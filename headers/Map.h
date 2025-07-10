#ifndef MAP_CLASS_H
#define MAP_CLASS_H

#include<vector>
#include<glm/glm.hpp>
#include<memory>
#include<iostream>

#include"Tile.h"
#include"Wall.h"
#include"Mesh.h"
#include"shaderClass.h"
#include"Camera.h"
#include"Corridor.h"
#include"MapComponent.h"

class Map {
public:
    std::vector<std::unique_ptr<MapComponent>> components;
    std::vector<Tile> tiles;
    
    Map();

    void addCorridor(glm::vec3 pos, Mesh* floorMesh, Mesh* wallMesh);

    void generateGrid(int size,  Mesh* floorMesh);

    bool isPositionWalkable(glm::vec3 pos);

    void Draw(Entity& entity, Shader& shader);
};

#endif