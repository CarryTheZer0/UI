/*
 * UIRenderer.cpp
 *
 *  27 July 2023
 *  Mike
 */

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "UIRenderer.h"


UIRenderer::UIRenderer(Shader &shader) :
    m_vertexOffset(0),
	m_indexOffset(0),
    m_shader(shader),
	m_model(glm::mat4(1.0f)),
	m_view(glm::mat4(1.0f)),
	m_projection(glm::mat4(1.0f)),
	m_mvp(glm::mat4(1.0f))
{
    this->initRenderData();
}

void UIRenderer::draw()
{
    // draw lines
	m_shader.use();

	glBindVertexArray(m_triangleVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_triangleIBO);
	glDrawElements(GL_TRIANGLES, m_indexOffset * 3, GL_UNSIGNED_INT, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	m_vertexOffset = 0;
	m_indexOffset = 0;
}

void UIRenderer::drawTriangle(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::mat4 model, 
							  glm::vec2 camera, glm::vec3 color)
{
    m_shader.use();

	// index data
	this->writeTriangle({ 0, 1, 2 });

    // vertex data
	this->writeVertex({ a.x, a.y, color.x, color.y, color.z }, model);
	this->writeVertex({ b.x, b.y, color.x, color.y, color.z }, model);
	this->writeVertex({ c.x, c.y, color.x, color.y, color.z }, model);
}

void UIRenderer::drawTriangles(std::vector<Vertex> vertices, std::vector<Triangle> triangles, glm::mat4 model)
{
    m_shader.use();

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	// index data
	for(auto triangle: triangles)
	{
		this->writeTriangle(triangle);
	}

    // vertex data
    for(auto vertex: vertices)
    {
		this->writeVertex(vertex, model);
    }
}

void UIRenderer::setModel(glm::mat4 m)
{
	m_model = m;
}

void UIRenderer::setView(glm::mat4 v)
{
	m_view = v;
}

void UIRenderer::setProjection(glm::mat4 p)
{
	m_projection = p;
}

void UIRenderer::writeVertex(Vertex vertex, glm::mat4 model)
{
	glm::vec4 position = m_projection * m_view * model * glm::vec4(vertex.x, vertex.y, 0.0f, 1.0f);

	float vertexList[] = { position.x, position.y, position.z, position.w, vertex.r, vertex.g, vertex.b };

    // write to vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);
	glBufferSubData(GL_ARRAY_BUFFER, m_vertexOffset * sizeof(vertexList), sizeof(vertexList), vertexList);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_vertexOffset++;
}

void UIRenderer::writeTriangle(Triangle triangle)
{
	uint32_t indexArray[] = { triangle.i1 + m_vertexOffset, triangle.i2 + m_vertexOffset, triangle.i3 + m_vertexOffset };

	// write to index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_triangleIBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, m_indexOffset * sizeof(indexArray), sizeof(indexArray), indexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	m_indexOffset++;
}

void UIRenderer::initRenderData()
{
	glGenVertexArrays(1, &m_triangleVAO);
	glGenBuffers(1, &m_triangleVBO);
	glGenBuffers(1, &m_triangleIBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3000, nullptr, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_triangleIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Triangle) * 1000, nullptr, GL_DYNAMIC_DRAW);

	glBindVertexArray(m_triangleVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)(4 * sizeof(GL_FLOAT)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}