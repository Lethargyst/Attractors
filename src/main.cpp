#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include "Renderer/Window.hpp"
#include "Scene/Scene.hpp"

void showFPS(Window& window, double deltaTime)
{
    double fps = 1 / deltaTime;
    std::stringstream ss;
    ss << "Swarm " << "[" << fps << " FPS]";
    glfwSetWindowTitle(window.glWindow_, ss.str().c_str());
}

int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    Window window(800, 600, "Particles");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    Scene& scene = Scene::initialize(&window, 1000000);
        
    const float fps = 60.0f;
    const float max_peroid = 1 / fps;
    float lastTime = 0.0f;
    while (!glfwWindowShouldClose(window.glWindow_))
    {
        double time = glfwGetTime();
        double deltaTime = time - lastTime;

        if (deltaTime >= max_peroid) {
            lastTime = time;
            // scene.update();
            scene.render();
            showFPS(window, deltaTime);
        }
    }

    glfwTerminate();

    return 0;
}

