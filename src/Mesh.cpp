#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures) {
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

    VAO;
    VAO.Bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)(3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void *)(6 * sizeof(float)));
    VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void *)(9 * sizeof(float)));

    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void Mesh::Draw(
    Shader& shader, 
    Entity& entity,
    glm::mat4 matrix,
    glm::vec3 translations,
    glm::quat rotation,
    glm::vec3 scale
){
    shader.Activate();
    VAO.Bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for(unsigned int i = 0; i < textures.size(); i++) {
        std::string num;
        std::string type = textures[i].type;
        if(type == "diffuse") {
            num = std::to_string(numDiffuse++);
        }
        else if(type == "specular") {
            num = std::to_string(numSpecular++);
        }
        textures[i].texUnit(shader, (type + num).c_str(), i);
        textures[i].Bind();
    }
    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), entity.Position.x, entity.Position.y, entity.Position.z);
    entity.Matrix(shader, "camMatrix");

    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    trans = glm::translate(trans, translations);
    rot = glm::mat4_cast(rotation);
    sca = glm::scale(sca, scale);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1 , GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1 , GL_FALSE, glm::value_ptr(rot));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1 , GL_FALSE, glm::value_ptr(sca));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1 , GL_FALSE, glm::value_ptr(matrix));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
