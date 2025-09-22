/*
 *  TextBox.cpp
 *
 *  Created on: 24 Jan 2025
 *      Author: mchlp
 */


#include <vector>

#include "TextBox.h"

TextBox::TextBox(glm::vec3 color, float margin) :
	Face(),
	m_margin(margin),
	m_color(color)
{}

void TextBox::draw(IPainter* pPainter)
{
	pPainter->drawPanel(m_dimensions, m_color, m_margin);
	pPainter->drawText("test", glm::vec2(m_dimensions.x + m_margin, m_dimensions.y + m_margin), 1.0f, m_color);  // todo temp test line
	Face::draw(pPainter);
}
