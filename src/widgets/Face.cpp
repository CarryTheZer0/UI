/*
 * Face.cpp
 *
 *  Created on: 22 Jul 2021
 *      Author: mchlp
 */

#include <algorithm>
#include <ranges>

#include "Face.h"

Face::Face(glm::vec4 pixels, glm::vec4 percentage) :
	m_pixels(pixels),
	m_percentage(percentage),
	m_focus(0),
	m_isSelected(false)
{}

Face::Face(float width, float height, float x_offset, float y_offset) :
	m_isSelected(false),
	m_focus(0),
	m_dimensions(x_offset, y_offset, width, height),
	m_parentDimensions(),
	m_pixels(x_offset, y_offset, width, height),
	m_percentage()
{}

Face::~Face()
{
	m_children.clear();
}

void Face::draw(IPainter* pPainter)
{
	for (auto face = m_children.begin(); face != m_children.end(); ++face)
	{
		(*face)->draw(pPainter);
	}
}

bool Face::onSelect(bool down, int modifiers)
{
	bool wasPressed = false;
	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		wasPressed = (*face)->onSelect(down, modifiers);
	}

	return wasPressed;
}

bool Face::onCursorMoved(glm::vec2 position)
{
	bool wasSelected = false;
	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		wasSelected = (*face)->onCursorMoved(position) || wasSelected;
	}

	if (isInBounds(position) && !wasSelected)
	{
		m_isSelected = true;
		wasSelected = true;
	}
	else
	{
		m_isSelected = false;
	}
	
	return wasSelected;
}

bool Face::onCursorDragged(glm::vec2 offset)
{
	bool wasDragged = false;
	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		wasDragged = (*face)->onCursorDragged(offset);
	}

	return wasDragged;
}

bool Face::onScroll(glm::vec2 offset)
{
	bool wasScrolled = false;
	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		wasScrolled = (*face)->onScroll(offset);
	}

	return wasScrolled;
}

bool Face::cycleFocus()
{
	bool wasShifted = false;

	if (m_isSelected)
	{
		m_isSelected = false;
		if (m_children.size())
		{
			m_children[0]->select();
			wasShifted = true;
		}
	}
	else
	{
		if (m_children.size())
		{
			wasShifted = m_children[m_focus]->cycleFocus();
		}
	}

	if (!wasShifted)
	{
		m_isSelected = false;
		if (m_children.size() > 1)
		{
			for (auto& child : m_children)
				child->deselect();

			m_focus++;
			if (m_focus < m_children.size())
			{
				m_children[m_focus]->select();
				wasShifted = true;
			}
			else
			{
				m_focus = 0;
			}
		}
		else if (m_children.size() == 1)
		{
			m_isSelected = true;
		}
	}

	return wasShifted;
}

bool Face::shiftFocusLevel(bool down)
{
	return false;
}

bool Face::shiftFocus(glm::vec2 direction)
{
	return false;
}

void Face::addChild(std::shared_ptr<Face> child)
{
	child->m_parentDimensions = m_dimensions;
	child->setRect();
	m_children.push_back(child);
}

void Face::removeChild(std::shared_ptr<Face> face)
{
	const auto position = std::find_if(m_children.begin(), m_children.end(), [face](const std::shared_ptr<Face> otherFace) {
        return face.get() == otherFace.get();
    });
	
	m_children.erase(position);
	m_focus--;  // todo
	if (m_focus < 0) m_focus = 0;
}

glm::vec4 Face::getRect()
{
	return m_dimensions;
}

void Face::setRect()
{
	m_dimensions = m_parentDimensions;

	m_dimensions.x += (m_percentage.x / 100.0f) * m_dimensions.z;
	m_dimensions.y += (m_percentage.y / 100.0f) * m_dimensions.w;
	m_dimensions.z *= m_percentage.z / 100.0f;
	m_dimensions.w *= m_percentage.w / 100.0f;
	
	m_dimensions.x += m_pixels.x;
	m_dimensions.y += m_pixels.y;
	m_dimensions.z += m_pixels.z;
	m_dimensions.w += m_pixels.w;

	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		(*face)->m_parentDimensions = m_dimensions;
		(*face)->setRect();
	}
}

glm::vec2 Face::getCentre()
{
	return glm::vec2(m_dimensions.x + m_dimensions.z / 2, m_dimensions.y + m_dimensions.w / 2);
}

void Face::move(glm::vec2 transform)
{
	// do move
	m_dimensions.x += transform.x;
	m_dimensions.y += transform.y;
	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		(*face)->move(transform);
	}
}

bool Face::isInBounds(glm::vec2 position)
{
	if (position.x > m_dimensions.x && position.y > m_dimensions.y &&
		position.x < m_dimensions.x + m_dimensions.z && position.y < m_dimensions.y + m_dimensions.w)
		return true;
	else
		return false;
}
