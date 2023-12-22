/*
 * triangles.h
 *
 *  28 July 2023
 *  Mike
 */

#ifndef UI_TRIANGLES_H_
#define UI_TRIANGLES_H_

#include <glm/glm.hpp>

struct Vertex
{
    Vertex(float x, float y) :
        x(x), y(y), r(1.0f), g(1.0f), b(1.0f)
    {}

    Vertex(float x, float y, float r, float g, float b) :
        x(x), y(y), r(r), g(g), b(b)
    {}

    Vertex(float x, float y, glm::vec3 color) :
        x(x), y(y), r(color.x), g(color.y), b(color.z)
    {}

    Vertex(glm::vec2 pos, glm::vec3 color) :
        x(pos.x), y(pos.y), r(color.x), g(color.y), b(color.z)
    {}

    float x; float y; float r; float g; float b;
};

struct Triangle
{
    Triangle(uint32_t i1, uint32_t i2, uint32_t i3) :
        i1(i1), i2(i2), i3(i3)
    {}

	uint32_t i1; uint32_t i2; uint32_t i3;
};

#endif /* UI_TRIANGLES_H */