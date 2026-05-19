#include "object.hpp"

Object::Object(const float *vertices, unsigned int vertex_count, std::string vertex_shader_path, std::string fragment_shader_path) : mesh(vertices, vertex_count),
     shader(vertex_shader_path, fragment_shader_path) {}

Object::Object(const float *vertices, unsigned int vertex_count, Shader& shader) : mesh(vertices, vertex_count),
     shader(shader) {}

void Object::draw()
{
    shader.use();
    mesh.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
