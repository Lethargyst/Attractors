#include "Geometry2D.hpp"

float Line2d::length() const
{
    return Distance(start_, end_);
}

float Line2d::lengthSq() const
{
    return DistanceSq(start_, end_);
}

glm::vec2 Rectangle2d::getMin() const
{
    return origin_;
}

glm::vec2 Rectangle2d::getMax() const
{
    return origin_ + size_;
}

Rectangle2d fromMinMax(const glm::vec2& min, const glm::vec2& max)
{
    return Rectangle2d(min, max - min);
}

float Distance(const glm::vec2& l, const glm::vec2& r)
{
    glm::vec2 tmp = l - r;
    return tmp.length();
}

float DistanceSq(const glm::vec2& l, const glm::vec2& r) 
{
    glm::vec2 tmp = l - r;
    return tmp.x * tmp.x + tmp.y * tmp.y;
}
