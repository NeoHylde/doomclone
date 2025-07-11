#ifndef ROOM_CLASS_H
#define ROOM_CLASS_H

#include"Tile.h"
#include"Wall.h"
#include"shaderClass.h"
#include"Mesh.h"
#include"Camera.h"
#include"MapComponent.h"

#include <glm/glm.hpp>
#include <vector>

class Room : public MapComponent {
public:
    std::vector <Tile> tiles;
    std::vector <Wall> walls;

    Room(glm::vec3 position, Mesh* tileMesh, Mesh* wallMesh);
    void Draw(Camera& camera, Shader& shader) override;
};

#endif