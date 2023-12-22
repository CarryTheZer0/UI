/*
 * Painter.cpp
 *
 *  Created on: 22 Jul 2021
 *      Author: mchlp
 */

// Painter.cpp

#include "Painter.h"
#include "UIRenderer.h"
#include "PaintHelpers.h"

Painter::Painter(UIRenderer* pRenderer, const char* name) :
	m_pRenderer(pRenderer)
{}

void Painter::drawPanel(glm::vec4 dimensions, glm::vec3 color, float margin)
{
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;

	float windowWidth = 1024.0f;
	float windowHeight = 768.0f;

	float ratio = dimensions.w / dimensions.z;  // height / width

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f + 2 * dimensions.x / windowWidth, -1.0f + 2 * dimensions.y / windowHeight, 0.0f));
	model = glm::scale(model, glm::vec3( dimensions.z / windowWidth, dimensions.z / windowHeight, 1.0f ));
	model = glm::translate(model, glm::vec3(1.0f, ratio, 0.0f));

	int nextIndex = 0;
	nextIndex = drawRoundedRectangle(vertices, triangles, ratio, (margin * 2) / dimensions.z, color, nextIndex);

	m_pRenderer->drawTriangles(vertices, triangles, model);
}

void Painter::drawMenu()
{
	// drawPanel();
}

void Painter::drawButton()
{
	// drawPanel();
}
