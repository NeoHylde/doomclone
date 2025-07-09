#ifndef MAP_CLASS_H
#define MAP_CLASS_H

#include<vector>
#include<glm/glm.hpp>

#include"Tile.h"
#include"Wall.h"
#include"Mesh.h"
#include"shaderClass.h"
#include"Camera.h"

class Map {
public:
    std::vector<Tile> tiles;
    std::vector<Wall> walls;
    
    Map();

    void generateGrid(int width, int depth, Mesh* floorMesh);

    void Draw(Camera& camera, Shader& tileShader, Shader& wallShader);
};

#endif