/*
 *  TextBox.cpp
 *
 *  Created on: 24 Jan 2025
 *      Author: mchlp
 */


#include <vector>

#include "TextBox.h"

TextBox::TextBox(
		Face& parent,
		glm::vec4 pixels,
		glm::vec4 percentage,
		glm::vec3 color,
		float margin
) :
	Face(parent, pixels, percentage),
	m_margin(margin),
	m_color(color)
{}

void TextBox::draw(IPainter* pPainter)
{
	if (m_isSelected)
        pPainter->drawPanel(glm::vec4(m_dimensions.x - 1, m_dimensions.y - 1, m_dimensions.z + 2, m_dimensions.w + 2), m_color, m_margin);
	pPainter->drawPanel(m_dimensions, m_color, m_margin);
	pPainter->drawText("test", glm::vec2(m_dimensions.x + m_margin, m_dimensions.y + m_margin), 1.0f, m_color);  // todo temp test line
	Face::draw(pPainter);
}
