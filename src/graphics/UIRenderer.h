/*
 * UIRenderer.h
 *
 *  27 July 2023
 *  Mike
 */

#ifndef UI_RENDERER_H
#define UI_RENDERER_H

#include <vector>

#include  <glm/glm.hpp>

#include "Shader.h"
#include "Triangles.h"

class UIRenderer
{
public:
	UIRenderer(Shader &shader);
    ~UIRenderer() = default;
    
    void draw();
    void drawTriangle(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::mat4 model, 
                      glm::vec2 camera=glm::vec2(0.0f, 0.0f), 
                      glm::vec3 color=glm::vec3(1.0f, 1.0f, 1.0f));
    void drawTriangles(std::vector<Vertex> vertices, std::vector<Triangle> triangles, 
                       glm::mat4 model);

    void setModel(glm::mat4 m);
    void setView(glm::mat4 v);
    void setProjection(glm::mat4 p);
private:
    Shader m_shader;

    unsigned int m_triangleVAO;
    unsigned int m_triangleVBO;
    unsigned int m_triangleIBO;

    int m_vertexOffset;
    int m_indexOffset;

    glm::mat4 m_model;
    glm::mat4 m_view;
    glm::mat4 m_projection;
    glm::mat4 m_mvp;

    void writeVertex(Vertex vertex, glm::mat4 model);
    void writeTriangle(Triangle triangle);
    void initRenderData();
};

#endif /* UI_RENDERER_H */