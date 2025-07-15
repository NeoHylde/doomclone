#ifndef MAP_COMPONENT_CLASS_H
#define MAP_COMPONENT_CLASS_H

#include "Entity.h"
#include "Camera.h"
#include "shaderClass.h"

class MapComponent {
public:
    virtual bool contains(glm::vec3 pos) = 0;
    virtual bool getWalkable() = 0;
    virtual void Draw(Entity& entity, Shader& shader) = 0;
    virtual ~MapComponent() = default;
};

#endif