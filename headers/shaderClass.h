#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <unordered_map>

std::string get_file_contents(const char *filename);

class Shader
{
public:
    GLuint ID;

    Shader(const char *vertexFile, const char *fragmentFile);

    void Activate();
    void Delete();

    // Caches glGetUniformLocation results, since drawing calls this per-uniform
    // every frame and the lookup involves a name hash + driver round trip.
    GLint GetUniformLocation(const std::string& name);
private:
    void compileErrors(unsigned int shader, const char *type);

    std::unordered_map<std::string, GLint> uniformLocationCache;
};

#endif