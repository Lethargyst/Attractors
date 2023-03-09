#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/vec2.hpp>
#include "../Objects/Geometry2D.hpp"


class Window
{
public:
    Window(int width, int height, const char* label);
    ~Window() {}

    glm::vec2 getResolution() const { return glm::vec2(width, height); }
    Rectangle2d& getBounds() const;

    GLFWwindow *glWindow_;
private:
    Window(const Window& other) = delete;
    Window& operator=(const Window& other) = delete;

    static void frameBufferSizeCallback(GLFWwindow* window, int window_width, int window_height);

    static Rectangle2d bounds;    
    static int width, height;
};

#endif