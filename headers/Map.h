#ifndef MAP_CLASS_H
#define MAP_CLASS_H

#include<vector>
#include<glm/glm.hpp>
#include<memory>

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
    
    Map();

    void addCorridor(glm::vec3 pos, Mesh* floorMesh, Mesh* wallMesh);

    void Draw(Camera& camera, Shader& shader);
};

#endif