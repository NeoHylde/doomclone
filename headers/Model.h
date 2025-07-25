#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<json/json.h>
#include"Mesh.h"

using json = nlohmann::json;

class Model {
public:
    Model(const char* file, glm::vec3 pos);
    
    void Draw(Shader& shader, Entity& entity, glm::vec3 translation, glm::quat rotation, glm::vec3 scale);
private:
    const char* file;
    std::vector<unsigned char> data;
    json JSON;

    std::vector<Mesh> meshes;

    std::vector<std::string> loadedTexName;
    std::vector<Texture> loadedTex;

    void loadMesh(unsigned int indMesh);

    void traverseNode(unsigned int nextNode, glm::mat4 = glm::mat4(1.0f));
    std::vector<glm::vec3> translationsMeshes;
    std::vector<glm::quat> rotationsMeshes;
    std::vector<glm::vec3> scalesMeshes;
    std::vector<glm::mat4> matricesMeshes;

    std::vector<glm::vec4> materials;

    std::vector<unsigned char> getData();
    std::vector<float> getFloats(json accessor);
    std::vector<GLuint> getIndices(json accessor);
    std::vector<Texture> getTextures();
    std::vector<glm::vec4> getMaterials();

    std::vector<Vertex> assembleVertices(
        std::vector<glm::vec3> positions, 
        std::vector<glm::vec3> normals,
        std::vector<glm::vec2> texUVs
    );

    std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
    std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
    std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};

#endif