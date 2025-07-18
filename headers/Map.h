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
#include"MapComponent.h"

class Map {
public:
    std::vector<std::unique_ptr<MapComponent>> components;
    
    Map();

    void generateGrid(int size,  Mesh* floorMesh);

    std::vector<std::unique_ptr<MapComponent>>& getComponents();

    bool isPositionWalkable(glm::vec3 pos);

    void Draw(Entity& entity, Shader& shader);
};

#endif