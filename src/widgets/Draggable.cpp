/*
 *  Draggable.cpp
 *
 *  Created on: 13 Sep 2026
 *      Author: mchlp
 */

#include "Draggable.h"

Draggable::Draggable(
    glm::vec4 pixels,
    glm::vec4 percentage,
    bool clampToParent
) :
    Face(pixels, percentage),
    m_clampToParent(clampToParent),
    m_isHeld(false)
{}

void Draggable::onSelect(bool down, int modifiers)
{
    if (!down)
    {
        m_isHeld = false;
    }
    else if (isFocused())
    {
        m_isHeld = true;
    }
}

void Draggable::onCursorDragged(glm::vec2 offset)
{
    if (m_isHeld)
    {
        if (m_clampToParent) 
        {
            if (m_dimensions.x + offset.x < m_parentDimensions.x) offset.x = m_parentDimensions.x - m_dimensions.x;
            if (m_dimensions.y + offset.y < m_parentDimensions.y) offset.y = m_parentDimensions.y - m_dimensions.y;
            
            if (m_dimensions.x + m_dimensions.z + offset.x > m_parentDimensions.x + m_parentDimensions.z) offset.x = (m_parentDimensions.x + m_parentDimensions.z) - (m_dimensions.x + m_dimensions.z);
            if (m_dimensions.y + m_dimensions.w + offset.y > m_parentDimensions.y + m_parentDimensions.w) offset.y = (m_parentDimensions.y + m_parentDimensions.w) - (m_dimensions.y + m_dimensions.w);
        }
        move(offset);
    }
}

void Draggable::draw(IPainter* pPainter)
{
    if (isFocused())
        pPainter->drawPanel(glm::vec4(m_dimensions.x - 1, m_dimensions.y - 1, m_dimensions.z + 2, m_dimensions.w + 2), glm::vec3(1.0f), 0);
	pPainter->drawPanel(m_dimensions, glm::vec3(1.0f), 0);
	Face::draw(pPainter);
}
