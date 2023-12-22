/*
 * Face.cpp
 *
 *  Created on: 22 Jul 2021
 *      Author: mchlp
 */

#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "Face.h"
#include "Window.h"

Face::Face(float width, float height) :
	m_pParent(nullptr),
	m_isSelected(false)
{
	m_dimensions = glm::vec4(0.0f, 0.0f, width, height);
}

Face::~Face()
{
	for (Face* f : m_children)
	{
		delete f;
	}
}

void Face::draw(IPainter* pPainter)
{
	for (Face* pFace : m_children)
	{
		pFace->draw(pPainter);
	}
}

void Face::onCursorButton(glm::vec2 pos, bool down, unsigned int button)
{
	for (Face* pFace : m_children)
	{
		pFace->onCursorButton(pos, down, button);
	}
}

void Face::onCursorMoved(glm::vec2 pos)
{
	for (Face* pFace : m_children)
	{
		pFace->onCursorMoved(pos);
	}
	m_isSelected = isInBounds(pos);
}

void Face::onCursorDragged(glm::vec2 offset)
{
	for (Face* pFace : m_children)
	{
		pFace->onCursorDragged(offset);
	}
}

void Face::onScroll(glm::vec2 offset)
{
	std::cout << offset.x << " " << offset.y << std::endl;
	for (Face* pFace : m_children)
	{
		pFace->onScroll(offset);
	}
}

void Face::addChild(Face* pChild)
{
	m_children.emplace_back(pChild);
	pChild->setParent(this);
	pChild->setRect({ 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 100.0f, 100.0f });
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
