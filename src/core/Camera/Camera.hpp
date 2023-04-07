#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Renderer/Window.hpp"
#include <glm/glm.hpp>

using namespace glm;
class Camera
{
public:
    Camera() {}
    Camera(vec3 pos, vec3 front, vec3 up, float speed);
    ~Camera() {};

    void initialize(vec3 pos, vec3 front, vec3 up, float speed);
    void processInput(const Window* window);

    void setPosition(const vec3& pos) { _pos.x = pos.x; _pos.y = pos.y; _pos.z = pos.z; };
    void setFrontVec(const vec3& front) { _front.x = front.x; _front.y = front.y; _front.z = front.z; };
    void setRightVec(const vec3& right) { _right.x = right.x; _right.y = right.y; _right.z = right.z; };
    void setUpVec(const vec3& up) { _up.x = up.x; _up.y = up.y; _up.z = up.z; };
    void setSpeed(float speed) { _speed = speed; }

    vec3 getPosition() const { return _pos; };
    vec3 getFrontVec() const { return _front; };
    vec3 getRightVec() const { return _right; };
    vec3 getUpVec() const { return _up; };
    
    vec3 _pos, _front, _right, _left, _up, _down;
    float _speed;
};

#endif
