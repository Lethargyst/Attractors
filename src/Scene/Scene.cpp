
#include "Scene.hpp"

Scene& Scene::initialize(Window* window, GLuint partsAmount) 
{
    static Scene sceneObj(window, partsAmount);
    sceneObj.prepareShaderPrograms();
    sceneObj.initBuffers(partsAmount);
    
    glClearColor(0.9f, 0.9f, 0.98f, 1.0f);

    glm::vec2 res = window->getResolution();
    sceneObj._projection = glm::perspective(glm::radians(50.0f), (float)res.x / res.y, 1.0f, 100.0f);
    
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

void Scene::initBuffers(GLuint particlesAmount)
{
    std::vector<GLfloat> positions(particlesAmount * 4);
    std::vector<GLfloat> velocities(particlesAmount * 4, 0.0f);

    for (std::size_t i = 0; i < positions.size(); ++i)
        positions[i] = (Random::getNormalizedFloat() * 2 - 1.0f) * 3;

    GLuint bufs[2];
    glGenBuffers(2, bufs);   
    GLuint posBuf = bufs[0];
    GLuint velBuf = bufs[1];

    GLuint bufSize = particlesAmount * 4 * sizeof(GLfloat);
 
    // prepare compute shader buffers
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, posBuf);
    glBufferData(GL_SHADER_STORAGE_BUFFER, bufSize, &positions[0], GL_DYNAMIC_COPY);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, velBuf);
    glBufferData(GL_SHADER_STORAGE_BUFFER, bufSize, &velocities[0], GL_DYNAMIC_DRAW);

    //prepare particles VAO
    glGenVertexArrays(1, &_particlesVAO);
    glBindVertexArray(_particlesVAO);

    glBindBuffer(GL_ARRAY_BUFFER, posBuf);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    
    //prepare attractors buffers
    glGenBuffers(1, &_attrVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _attrVBO);
    
    GLfloat attrdata[] = {_attr1.x, _attr1.y, _attr1.z, _attr1.w, 
                          _attr2.x, _attr2.y, _attr2.z, _attr2.w};

    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), attrdata, GL_DYNAMIC_DRAW);
    
    glGenVertexArrays(1, &_attrVAO);
    glBindVertexArray(_attrVAO);

    glBindBuffer(GL_ARRAY_BUFFER, _attrVBO);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Scene::render()
{
    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(_angle), glm::vec3(0,0,1));
    glm::vec3 att1 = glm::vec3(rot * _attr1);
    glm::vec3 att2 = glm::vec3(rot * _attr1);
    
    // Execute the compute shader
    _computeProgram.use();
    _computeProgram.setUniform("BlackHolePos1", _attr1);
    _computeProgram.setUniform("BlackHolePos2", _attr2);
    glDispatchCompute(_particlesAmount / 1000, 1, 1);
    glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT );

    // Draw the scene
    _renderProgram.use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _view = glm::lookAt(glm::vec3(2,0,20), glm::vec3(0,0,0), glm::vec3(0,1,0));
    _model = glm::mat4(1.0f);
    
    glm::mat4 mv = _view * _model;
    glm::mat3 norm = glm::mat3( glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]) );

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
    glBindBuffer(GL_ARRAY_BUFFER, _attrVBO);
    GLfloat attrData[] = {_attr1.x, _attr1.y, _attr1.z, 1.0f, 
                          _attr2.x, _attr2.y, _attr2.z, 1.0f};
    glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof(GLfloat), attrData);
    
    _renderProgram.setUniform("Color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glBindVertexArray(_attrVAO);
    glDrawArrays(GL_POINTS, 0, 2);

    glfwSwapBuffers(_window->glWindow_);
    glfwPollEvents();
}
