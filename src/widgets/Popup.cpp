/*
 *  Popup.cpp
 *
 *  Created on: 17 Dec 2025
 *      Author: mchlp
 */

#include "Popup.h"

Popup::Popup(
		Face& parent,
        Face& content,
		glm::vec4 pixels,
		glm::vec4 percentage,
		glm::vec3 color,
		float margin
) :
	Face(parent, pixels, percentage),
    m_content(content),
	m_color(color),
	m_margin(margin),
    m_isActive(false)
{}

void Popup::draw(IPainter* pPainter)
{
    if (m_isSelected)
        pPainter->drawPanel(glm::vec4(m_dimensions.x - 1, m_dimensions.y - 1, m_dimensions.z + 2, m_dimensions.w + 2), m_color, m_margin);
	pPainter->drawPanel(m_dimensions, m_color, m_margin);
	Face::draw(pPainter);
}

bool Popup::onCursorMoved(glm::vec2 position)
{
    bool wasSelected = (Face::onCursorMoved(position));

    if (m_isSelected && !m_isActive)
    {
        addChild(m_content);
        m_isActive = true;
    }
    else if (!m_isSelected && !m_content.isSelected())
    {
        if (m_isActive) removeChild(m_content);
        m_isActive = false;
    }
    
    return wasSelected;
}

void Popup::setRect(glm::vec4 pixels, glm::vec4 percentage)
{
    Face::setRect(pixels, percentage);
    m_content.setRect(pixels, percentage);
}
