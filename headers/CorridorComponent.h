#ifndef CORRIDOR_COMPONENT_HEADER
#define CORRIDOR_COMPONENT_HEADER

#include "MapComponent.h"
#include <vector>
#include "Tile.h"

class CorridorComponent : public MapComponent {
private:
    std::vector<Tile> internals;
    int dir;
public:
    CorridorComponent();
    void getWalkable(glm::vec3 pos);
    void Draw(Entity& entity, Shader& shader);
};

#endif