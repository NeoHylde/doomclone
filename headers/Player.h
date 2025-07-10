#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#define GLM_ENABLE_EXPERIMENTAL

#include "Entity.h"
#include "Map.h"

#include <glm/glm.hpp>

class Player : public Entity {
private:
    
public:
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 playerMatrix = glm::mat4(1.0f);

    bool escaped = false;

    int width;
    int height;

    float speed = 0.1f;
    float sensitivity = 100.0f;

    Player(int width, int height, glm::vec3 position);
    void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
    void Matrix(Shader &shader, const char *uniform) override;
    void Inputs(GLFWwindow *window, Map* map);
};

#endif