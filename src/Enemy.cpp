#include "Enemy.h"

Enemy::Enemy(Model* model, AStar* astar, glm::vec3 pos) : model(model), astar(astar), position(pos) {}

void Enemy::getPath(glm::vec3 dest) {
    pathIndex = 0;

    glm::vec2 startPos(snap(position.x, 2.0f), snap(position.z, 2.0f));
    glm::vec2 goalPos(snap(dest.x, 2.0f), snap(dest.z, 2.0f));

    Node* start = astar->graph->getNodeAt(startPos);
    Node* goal = astar->graph->getNodeAt(goalPos);

    currPath = astar->getPath(start, goal);
}


void Enemy::updatePos(float deltaTime) {
    std::cout << position.x << ", " << position.z << std::endl;
    if (pathIndex >= currPath.size()) return;

    glm::vec3 target = currPath[pathIndex];
    glm::vec3 direction = glm::normalize(target - position);
    float distanceToTarget = glm::length(target - position);

    float step = moveSpeed * deltaTime;

    if (distanceToTarget <= step) {
        position = target;
        pathIndex++;
    } else {
        position += direction * step;
    }
}

void Enemy::Draw(Shader& shader, Entity& entity) {
    glm::quat rotation = glm::angleAxis(glm::radians(180.0f), glm::vec3(1, 0, 0));  // Rotate 180° around X
    glm::vec3 scale = glm::vec3(2.0f);
    glm::vec3 flippedPos = glm::vec3(-position.x, position.y, -position.z);

    model->Draw(shader, entity, flippedPos, rotation, scale);
}
