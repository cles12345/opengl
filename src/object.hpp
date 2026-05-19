#pragma once
#include <glad.h>
#include <glfw3.h>
#include "mesh.hpp"
#include "shader.hpp"
#include <string>

class Object
{
    public:
        Object(const float *vertices, unsigned int vertex_count, std::string vertex_shader_path, std::string fragment_shader_path);
        Object(const float *vertices, unsigned int vertex_count, Shader& shader);
        void draw();

    private:
        Mesh mesh;
        Shader shader;
        float vertices[];
};