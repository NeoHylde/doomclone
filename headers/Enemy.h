#ifndef ENEMY_CLASS_H
#define ENEMY_CLASS_H

#include "Model.h"
#include "AStar.h"
#include <vector>

class Enemy {
    public:
        Enemy(Model* model);

        void getPath(glm::vec3 dest);

        void updatePos(glm::vec3 nextPos);

        void Draw();
    private:
        std::vector<glm::vec3> currPath;
        glm::vec3 position;
        AStar AStar;
        Model model;
};

#endif