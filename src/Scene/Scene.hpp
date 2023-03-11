#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer/ShaderProgram.hpp"
#include "Renderer/Window.hpp"
#include "Utils/Random.hpp"

class Scene
{
public:
    static Scene& initialize(Window* window, GLuint particlesAmount, GLuint attractorsAmount);
    
    // void update();
    void render();
    
private:    
    Scene() = delete;
    Scene(Window* window, GLuint particlesAmount, GLuint attractorsAmount) 
        : _window(window), _particlesAmount(particlesAmount), _attractorsAmount(attractorsAmount) {}  
    ~Scene() {};

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    
//----------------------------------------------------------------------------
    void initBuffers();
    void prepareShaderPrograms();
 
    void initAttractors();
//----------------------------------------------------------------------------
    std::vector<GLfloat> _attractorsPos;
    std::vector<GLfloat> _attractorsGravity;

    glm::mat4 _projection, _model, _view;
    

    GLSLProgram _renderProgram, _computeProgram;
    Window* _window;

    GLuint _attractorsPosBuf;
    GLuint _attractorsVBO, _attractorsVAO;
    GLuint _particlesVAO;
   
    GLuint _particlesAmount, _attractorsAmount;
};

#endif

