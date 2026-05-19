#pragma once
#include <glad.h>
#include <glfw3.h>
#include "utill.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

class Shader
{
    public:
        Shader(const std::string& vertex_path, const std::string& fragment_path);
        void use() const;
        ~Shader();

    private:
        unsigned int vertex_shader;
        unsigned int fragment_shader;
        unsigned int shader_program;

};