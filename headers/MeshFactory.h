#ifndef MESHFACTORY_CLASS_H
#define MESHFACTORY_CLASS_H

#include "Mesh.h"

class MeshFactory {
public:
    static Mesh* createFloorMesh();
    static Mesh* createWallMesh();
    static Mesh* createLightMesh();
};

#endif