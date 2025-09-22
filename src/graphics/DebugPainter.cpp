/*
 *  DebugPainter.cpp
 *
 *  Created on: 18 Jan 2025
 *      Author: mchlp
 */

#include "DebugPainter.h"
#include "DebugRenderer.h"

DebugPainter::DebugPainter(DebugRenderer* pRenderer, const char* name) : 
	m_pRenderer(pRenderer)
{}

void DebugPainter::drawPanel(glm::vec4 dimensions, glm::vec3 color, float margin)
{
    m_pRenderer->drawLine(glm::vec2(dimensions.x, dimensions.y), glm::vec2(dimensions.x + dimensions.z, dimensions.y), color);
    m_pRenderer->drawLine(glm::vec2(dimensions.x, dimensions.y + dimensions.w), glm::vec2(dimensions.x + dimensions.z, dimensions.y + dimensions.w), color);
    m_pRenderer->drawLine(glm::vec2(dimensions.x, dimensions.y), glm::vec2(dimensions.x, dimensions.y + dimensions.w), color);
    m_pRenderer->drawLine(glm::vec2(dimensions.x + dimensions.z, dimensions.y), glm::vec2(dimensions.x + dimensions.z, dimensions.y + dimensions.w), color);
}

void DebugPainter::drawMenu() 
{

}

void DebugPainter::drawButton()
{

}

void DebugPainter::drawText(std::string text, glm::vec2 posistion, float scale, glm::vec3 color)
{
    m_pRenderer->drawString(text, posistion.x, posistion.y, scale, color);
}