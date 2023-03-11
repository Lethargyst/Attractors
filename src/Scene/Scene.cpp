
#include "Scene.hpp"

Scene& Scene::initialize(Window* window, GLuint _particlesAmount, GLuint _attractorsAmount) 
{
    static Scene sceneObj(window, _particlesAmount, _attractorsAmount);
    sceneObj.initAttractors();
    sceneObj.prepareShaderPrograms();
    sceneObj.initBuffers();
    

    glClearColor(0.9f, 0.9f, 0.98f, 1.0f);

    glm::vec2 res = window->getResolution();
    sceneObj._projection = glm::perspective(glm::radians(70.0f), (float)res.x / res.y, 1.0f, 100.0f);
    
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return sceneObj;
}

void Scene::prepareShaderPrograms()
{
    try
    {
        _renderProgram.compileShader("../src/Shaders/particles.vert");
        _renderProgram.compileShader("../src/Shaders/particles.frag");
        _renderProgram.link();
    
        _computeProgram.compileShader("../src/Shaders/particles.comp");
        _computeProgram.link();
    }
    catch(GLSLProgramException &err) 
    {
        std::cerr << err.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    
    #if DEBUG
        _shader->printActiveUniforms();
        _shader->printActiveUniforms();
    #endif
}

void Scene::initBuffers()
{
    std::vector<GLfloat> positions(_particlesAmount * 4);
    std::vector<GLfloat> velocities(_particlesAmount * 4, 0.0f);

    for (std::size_t i = 0; i < positions.size(); ++i)
        positions[i] = (Random::getNormalizedFloat() * 2 - 1.0f);

    GLuint bufs[4];
    glGenBuffers(4, bufs);   
    GLuint particlesPosBuf = bufs[0];
    GLuint particlesVelBuf = bufs[1];
    GLuint attractorsPosBuf = bufs[2];
    GLuint attractorsGravBuf = bufs[3];

    _attractorsPosBuf = attractorsPosBuf;
    
    // prepare compute shader buffers
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particlesPosBuf);
    glBufferData(GL_SHADER_STORAGE_BUFFER, _particlesAmount * 4 * sizeof(GLfloat), &positions[0], GL_DYNAMIC_COPY);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, particlesVelBuf);
    glBufferData(GL_SHADER_STORAGE_BUFFER, _particlesAmount * 4 * sizeof(GLfloat), &velocities[0], GL_DYNAMIC_DRAW);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, attractorsPosBuf);
    glBufferData(GL_SHADER_STORAGE_BUFFER, _attractorsAmount * 4 * sizeof(GLfloat), &_attractorsPos[0], GL_DYNAMIC_DRAW);
    
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, attractorsGravBuf);
    glBufferData(GL_SHADER_STORAGE_BUFFER, _attractorsAmount * sizeof(GLfloat), &_attractorsGravity[0], GL_DYNAMIC_DRAW);
    
    //prepare particles VAO
    glGenVertexArrays(1, &_particlesVAO);
    glBindVertexArray(_particlesVAO);

    glBindBuffer(GL_ARRAY_BUFFER, particlesPosBuf);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    
    //prepare attractors VAO
    glGenVertexArrays(1, &_attractorsVAO);
    glBindVertexArray(_attractorsVAO);

    glBindBuffer(GL_ARRAY_BUFFER, attractorsPosBuf);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    _computeProgram.use();
    _computeProgram.setUniform("AttractorsAmount", _attractorsAmount);
}

void Scene::initAttractors()
{
    _attractorsPos.resize(_attractorsAmount * 4);
    for (std::size_t i = 0; i < _attractorsAmount * 4; i += 4) {
        _attractorsPos[i] = (Random::getNormalizedFloat() * 2.0f - 1) * 10;
        _attractorsPos[i + 1] = (Random::getNormalizedFloat() * 2.0f - 1) * 10;
        _attractorsPos[i + 2] = 0.0f;
        _attractorsPos[i + 3] = 1.0f;
    }

    _attractorsGravity.resize(_attractorsAmount);
    for (std::size_t i = 0; i < _attractorsAmount; ++i) 
        _attractorsGravity[i] = 1000;
}

void Scene::render()
{
    
    // Execute the compute shader
    _computeProgram.use();
    glDispatchCompute(_particlesAmount / 1000, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    // Draw the scene
    _renderProgram.use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _view = glm::lookAt(glm::vec3(2,0,20), glm::vec3(0,0,0), glm::vec3(0,1,0));
    _model = glm::mat4(1.0f);
    
    glm::mat4 mv = _view * _model;
    glm::mat3 norm = glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));

    _renderProgram.setUniform("ModelViewMatrix", mv);
    _renderProgram.setUniform("NormalMatrix", norm);
    _renderProgram.setUniform("MVP", _projection * mv);
    
    // Draw the particles
    glPointSize(1.0f);
    _renderProgram.setUniform("Color", glm::vec4(0.0f, 0.0f, 0.0f, 0.2f));
    glBindVertexArray(_particlesVAO);
    glDrawArrays(GL_POINTS, 0, _particlesAmount);

    // Draw the attractors
    glPointSize(5.0f);
    glBindBuffer(GL_ARRAY_BUFFER, _attractorsPosBuf);
    glBufferSubData(GL_ARRAY_BUFFER, 0, _attractorsPos.size() * sizeof(GLfloat), &_attractorsPos[0]);
    
    _renderProgram.setUniform("Color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glBindVertexArray(_attractorsVAO);
    glDrawArrays(GL_POINTS, 0, _attractorsAmount);

    glfwSwapBuffers(_window->glWindow_);
    glfwPollEvents();
}
