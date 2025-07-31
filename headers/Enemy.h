#ifndef ENEMY_CLASS_H
#define ENEMY_CLASS_H

#include "Model.h"
#include "AStar.h"
#include <vector>
#include <iostream>

class Enemy {
    public:
        Enemy(Model* model, AStar* astar, glm::vec3 position);

        // Needed for A* calculations, need to pass rounded out grid space
        float snap(float value, float gridSize) {
            return std::round(value / gridSize) * gridSize;
        }

        void getPath(glm::vec3 dest);

        void updatePos(float deltaTime);

        void Draw(Shader& shader, Entity& entity);
    private:
        int pathIndex = 0;

        float moveSpeed = 1.0f;

        std::vector<glm::vec3> currPath;

        glm::vec3 position;

        AStar* astar;
        
        Model* model;
};

#endif