#include "block.hpp"

Block::Block(const char* texture_path) : pos(0), texture(texture_path, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR) {}

void Block::draw(Shader& shader, Mesh& mesh, glm::vec3 pos)
{
    shader.use();
    mesh.bind();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
    shader.set_uniform(model, "model");
    glDrawElements(GL_TRIANGLES, mesh.indices_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}