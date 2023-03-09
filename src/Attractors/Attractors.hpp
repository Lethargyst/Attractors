#ifndef ATTRACTORS_HPP_
#define ATTRACTORS_HPP_

#include <glm/vec4.hpp>

struct Attractors
{
    Attractors(glm::vec4 pos, float gravity) : _pos(pos), _gravity(gravity) {}
    
    glm::vec4 _pos;
    float _gravity;
};

#endif
