#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera
{
    public:
        glm::vec3 pos;  
        glm::vec3 direction;
        glm::vec3 Up; 
        Camera();
        glm::mat4 get_view() const;
        void move_forward(float speed);
        void move_backward(float speed);
        void move_right(float speed);
        void move_left(float speed);
        void move_up(float speed);
        void move_down(float speed);
};
