#include "Player.h"

Player::Player(int width, int height, glm::vec3 position) {
    Player::width = width;
    Player::height = height;
    Position = position;
}

void Player::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane);

    playerMatrix = projection * view;
}

void Player::Matrix(Shader &shader, const char *uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(playerMatrix));
}

void Player::Inputs(GLFWwindow *window, Map* map)
{
    glm::vec3 forward = glm::normalize(glm::vec3(Orientation.x, 0.0f, Orientation.z));
    glm::vec3 right   = glm::normalize(glm::cross(forward, Up));

    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) && map->isPositionWalkable(Position + speed * forward))
    //if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
    {
        Position += speed * forward;
    }
    if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) && map->isPositionWalkable(Position + speed * right))
    //if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS))
    {
        Position += speed * right;
    }
    if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) && map->isPositionWalkable(Position - speed * forward))
    //if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS))
    {
        Position -= speed * forward;
    }
    if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) && map->isPositionWalkable(Position - speed * right))
    //if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS))
    {
        Position -= speed * right;
    }

    if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
    {
        speed = 0.4f;
    }
    else if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
    {
        speed = 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        if(!escaped) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            escaped = true;
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            escaped = false;
        }
        
    }

    if (!escaped)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

        if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) ||
              (glm::angle(newOrientation, -Up) <= glm::radians(5.0f))))
        {
            Orientation = newOrientation;
        }

        Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
        glfwSetCursorPos(window, width / 2, height / 2);
    }
}