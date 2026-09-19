/*
 *  TextBox.cpp
 *
 *  Created on: 24 Jan 2025
 *      Author: mchlp
 */


#include <vector>

#include "TextBox.h"

TextBox::TextBox(
		glm::vec4 pixels,
		glm::vec4 percentage,
		glm::vec3 color,
		float margin
) :
	Face(pixels, percentage),
	m_margin(margin),
	m_color(color),
	m_text("")
{}

bool TextBox::onTextInput(char character)
{
	if (Face::onTextInput(character)) return true;

	if (isFocused())
	{
		m_text.append(1, character);
		return true;
	}
	return false;
}

void TextBox::draw(IPainter* pPainter)
{
	if (isFocused())
        pPainter->drawPanel(glm::vec4(m_dimensions.x - 1, m_dimensions.y - 1, m_dimensions.z + 2, m_dimensions.w + 2), m_color, m_margin);
	pPainter->drawPanel(m_dimensions, m_color, m_margin);
	pPainter->drawText(m_text, glm::vec2(m_dimensions.x + m_margin, m_dimensions.y + m_margin), 1.0f, m_color);  // todo temp test line
	Face::draw(pPainter);
}
