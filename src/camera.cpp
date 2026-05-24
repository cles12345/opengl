#include "camera.hpp"

Camera::Camera() 
{
    pos= glm::vec3(0.0f, 0.0f, 3.0f);  
    direction = glm::vec3(0, 0, -1);
    Up = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::get_view() const
{
    return glm::lookAt(pos, pos + direction, Up);
}

void Camera::move_forward(float speed)
{
    pos += speed * glm::vec3(0.0f, 0.0f, -1.0f);
}

void Camera::move_backward(float speed)
{
    pos -= speed * glm::vec3(0.0f, 0.0f, -1.0f);
}

void Camera::move_right(float speed)
{
    pos += glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f))) * speed;
}

void Camera::move_left(float speed)
{
    pos -= glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f))) * speed;
}

void Camera::move_up(float speed)
{
    pos += speed * glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::move_down(float speed)
{
    pos -= speed * glm::vec3(0.0f, 1.0f, 0.0f);
}