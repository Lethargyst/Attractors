#include "Camera.hpp"


Camera::Camera(vec3 pos, vec3 front, vec3 up, float speed)
{
    _pos = pos; _front = front; _up = up; _speed = speed;
    
    _right = glm::normalize(glm::cross(up, front));
    _right = glm::normalize(glm::cross(front, up));
    
    _down = _up;
    _down.y *= -1;
}


void Camera::initialize(vec3 pos, vec3 front, vec3 up, float speed)
{
    _pos = pos; _front = front; _up = up; _speed = speed;
    
    _right = glm::normalize(glm::cross(up, front));
    _left = glm::normalize(glm::cross(front, up));
    
    _down = _up;
    _down.y *= -1;

    /* std::cout << "front: " << _front.x << " " << _front.y << " " << _front.z << "\n";
    std::cout << "right: " << _right.x << " " << _right.y << " " << _right.z << "\n";
    std::cout << "left: " << _left.x << " " << _left.y << " " << _left.z << "\n";
    std::cout << "up: " << _up.x << " " << _up.y << " " << _up.z << "\n";
    std::cout << "down: " << _down.x << " " << _down.y << " " << _down.z << "\n"; */
}

void Camera::processInput(const Window* window)
{
    if (glfwGetKey(window->glWindow_, GLFW_KEY_W) == GLFW_PRESS)
        _pos += glm::normalize(_up) * _speed;
    if (glfwGetKey(window->glWindow_, GLFW_KEY_S) == GLFW_PRESS)
        _pos += glm::normalize(_down) * _speed;
    if (glfwGetKey(window->glWindow_, GLFW_KEY_A) == GLFW_PRESS)
        _pos -= glm::normalize(glm::cross(_front, _up)) * _speed;
    if (glfwGetKey(window->glWindow_, GLFW_KEY_D) == GLFW_PRESS)
        _pos += glm::normalize(glm::cross(_front, _up)) * _speed;
    /* std::cout << _pos.x << " " << _pos.y << " " << _pos.z << "\n"; */
}
