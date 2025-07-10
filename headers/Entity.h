#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Entity {
public: 
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 playerMatrix = glm::mat4(1.0f);

    virtual ~Entity() = default;
    virtual void Matrix(Shader& shader, const char *uniform) = 0;
    //virtual void setSpawn(glm::vec3 pos) = 0;
};

#endif

