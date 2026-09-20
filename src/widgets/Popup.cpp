/*
 *  Popup.cpp
 *
 *  Created on: 17 Dec 2025
 *      Author: mchlp
 */

#include "Popup.h"

Popup::Popup(
    glm::vec4 pixels, 
    glm::vec4 percentage,
    glm::vec3 color,
    float margin
) :
	Face(pixels, percentage),
    m_color(color),
    m_margin(margin)
{}

void Popup::draw(IPainter* pPainter)
{
    if (isFocused())
        pPainter->drawPanel(glm::vec4(m_dimensions.x - 1, m_dimensions.y - 1, m_dimensions.z + 2, m_dimensions.w + 2), m_color, m_margin);
	pPainter->drawPanel(m_dimensions, m_color, m_margin);
	Face::draw(pPainter);
}

void Popup::onFocused()
{
    for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
        (*face)->setActive(true);
}

void Popup::onUnfocused()
{
    for (auto face = m_children.rbegin(); face != m_children.rend(); ++face) 
        if ((*face)->isFocused()) return;
    
    for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
        (*face)->setActive(false);
}
