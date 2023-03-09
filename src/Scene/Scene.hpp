#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/ShaderProgram.hpp"
#include "Renderer/Window.hpp"
#include "Utils/Random.hpp"

class Scene
{
public:
    static Scene& initialize(Window* window, GLuint partsAmount);
    
    // void update();
    void render();
    
private:    
    Scene() = delete;
    Scene(Window* window, GLuint particlesAmount) : _window(window), _particlesAmount(particlesAmount) {}  
    ~Scene() {};

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    
    void initBuffers(GLuint partsAmount);
    void prepareShaderPrograms();
    
    glm::mat4 _projection, _model, _view;
    
    glm::vec4 _attr1 = {5, 0, 0, 1}, _attr2 = {-5, 0, 0, 1};

    GLSLProgram _renderProgram, _computeProgram;
    Window* _window;

    GLfloat _angle = 0.0f, _speed = 35.0f;
    GLuint _attrVBO, _attrVAO;
    GLuint _particlesVAO;
   
    GLuint _particlesAmount;
};

#endif

