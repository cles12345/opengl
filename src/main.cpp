#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include "shader.hpp"
#include "mesh.hpp"
#include "object.hpp"
#include "texture.hpp"
#include "camera.hpp"

void check_events(Camera& cam, GLFWwindow* window, float delta_time);

int main(int argc, char const *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    GLFWwindow* window = glfwCreateWindow(800, 600, "game", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create a window\n";
        glfwTerminate();
        assert(false);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize glad\n";
        assert(false);
    }    
    glViewport(0, 0, 800, 600);

    float vertices[] = {
        // Front face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,

        // Back face
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,

        // Left face
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,

        // Right face
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f,

        // Top face
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  1.0f, 1.0f,

        // Bottom face
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f
    };

    unsigned int indicies[] = {
        0,  1,  2,  0,  2,  3,   // Front
        4,  5,  6,  4,  6,  7,   // Back
        8,  9,  10, 8,  10, 11,  // Left
        12, 13, 14, 12, 14, 15,  // Right
        16, 17, 18, 16, 18, 19,  // Top
        20, 21, 22, 20, 22, 23   // Bottom
    };
    Object triangle(
        vertices,
        indicies,
        sizeof(vertices),
        sizeof(indicies),
        8,
        32,
        "shaders/shader.vert",
        "shaders/shader.frag"
    );

    triangle.mesh.set_layout(0, 3, FLOAT);
    triangle.mesh.set_layout(1, 3, FLOAT);
    triangle.mesh.set_layout(2, 2, FLOAT);

    Texture texture("sprite/texture.jpeg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    
    glm::vec3 pos = glm::vec3( 0.0f,  0.0f,  0.0f);

    Camera cam;

    glEnable(GL_DEPTH_TEST);
    float delta_time = 0.0f;
    float last_frame = glfwGetTime();
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        check_events(cam, window, delta_time);
        view = cam.get_view();
        model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        triangle.shader.set_uniform(model, "model");
        triangle.shader.set_uniform(view, "view");
        triangle.shader.set_uniform(projection, "projection");

        triangle.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}

void check_events(Camera& cam, GLFWwindow* window, float delta_time)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cam.move_forward(3.0f * delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cam.move_backward(3.0f * delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cam.move_right(3.0f * delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cam.move_left(3.0f * delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        cam.move_up(3.0f * delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        cam.move_down(3.0f * delta_time);
    }
}