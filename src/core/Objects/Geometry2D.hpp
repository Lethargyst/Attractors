#ifndef GEOMETRY_2D_HPP_
#define GEOMETRY_2D_HPP_

#include <glm/vec2.hpp>

enum ShapeType {
    POINT2D,
    LINE2D,
    CIRCLE2D,
    RECTANGLE2D
};

typedef glm::vec2 Point2d;

struct Shape
{
    Shape() {}
};

struct Line2d 
{
    Line2d() {}
    Line2d(const Point2d& start, const Point2d& end) : start_(start), end_(end) {}
    Line2d(const Line2d& other) : start_(other.start_), end_(other.end_) {}
    
    float length() const;
    float lengthSq() const;

    Point2d start_, end_;
};

struct Rectangle2d : Shape
{
    Rectangle2d(const Point2d& origin, const glm::vec2& size) : origin_(origin), size_(size) {} 
    Rectangle2d(const Rectangle2d& other) : origin_(other.origin_), size_(other.size_) {}
    Rectangle2d(float x0, float y0, 
                float x1, float y1) : origin_(Point2d(x0, y0)), size_(glm::vec2(x1, y1)) {}
    Rectangle2d() {}

    glm::vec2 getMin() const;
    glm::vec2 getMax() const;

    Point2d origin_;
    glm::vec2 size_;
    float rotation = 0.0f;
};

struct Circle : Shape
{
    Circle(const Point2d& pos, const float radius) : pos_(pos), radius_(radius) {}
    Circle(const Circle& other) : pos_(other.pos_), radius_(other.radius_) {}
    Circle() {}
    
    Point2d pos_;
    float radius_;
};

Rectangle2d fromMinMax(const glm::vec2& min, const glm::vec2& max);

float Distance(const glm::vec2& l, const glm::vec2& r);
float DistanceSq(const glm::vec2& l, const glm::vec2& r);

#endif
