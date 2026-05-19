#pragma once
#include <glad.h>
#include <glfw3.h>

class Mesh
{
    public:
        Mesh(const float vertices[], unsigned int vertex_count);
        void bind();
        ~Mesh();
    private:
        unsigned int VAO, VBO, vertices_count;
};