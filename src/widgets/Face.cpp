/*
 * Face.cpp
 *
 *  Created on: 22 Jul 2021
 *      Author: mchlp
 */

#include <ranges>

#include "Face.h"

Face::Face(float width, float height) :
	m_id(-1),
	m_pParent(nullptr),
	m_isSelected(false)
{
	m_dimensions = glm::vec4(0.0f, 0.0f, width, height);
}

Face::~Face()
{
	m_children.clear();
}

void Face::draw(IPainter* pPainter)
{
	for (auto face = m_children.begin(); face != m_children.end(); ++face)
	{
		face->second->draw(pPainter);
	}
}

void Face::onCursorButton(glm::vec2 pos, bool down, unsigned int button)
{
	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		face->second->onCursorButton(pos, down, button);
	}
}

void Face::onCursorMoved(glm::vec2 pos)
{
	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		face->second->onCursorMoved(pos);
	}
	m_isSelected = isInBounds(pos);
}

void Face::onCursorDragged(glm::vec2 offset)
{
	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		face->second->onCursorDragged(offset);
	}
}

bool Face::onScroll(glm::vec2 offset)
{
	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		if (face->second->onScroll(offset))
			return true;
	}

	return false;
}

void Face::addChild(std::shared_ptr<Face> pChild)
{
	pChild->setId(m_nextID);
	m_children.emplace(std::make_pair(m_nextID, pChild));
	m_nextID++;
	pChild->setParent(this);
	pChild->setRect({ 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 100.0f, 100.0f });
}

void Face::removeChild(unsigned int id)
{
	m_children.erase(id);
}

void Face::removeChild(std::shared_ptr<Face> face)
{
	m_children.erase(face->getId());
}

void Face::setParent(Face* pParent)
{
	m_pParent = pParent;
}

glm::vec4 Face::getRect()
{
	return m_dimensions;
}

void Face::setRect(glm::vec4 pixels, glm::vec4 percentage)
{
	glm::vec4 dimensions = m_pParent->getRect();

	pixels.x += dimensions.x;
	pixels.y += dimensions.y;
	percentage.x *= dimensions.z;
	percentage.y *= dimensions.w;
	percentage.z *= dimensions.z;
	percentage.w *= dimensions.w;

	m_dimensions = { pixels.x + percentage.x / 100, pixels.y + percentage.y / 100, pixels.z + percentage.z / 100, pixels.w + percentage.w / 100 };
}

bool Face::isInBounds(glm::vec2 pos)
{
	if (pos.x > m_dimensions.x && pos.y > m_dimensions.y &&
		pos.x < m_dimensions.x + m_dimensions.z && pos.y < m_dimensions.y + m_dimensions.w)
		return true;
	else
		return false;
}
