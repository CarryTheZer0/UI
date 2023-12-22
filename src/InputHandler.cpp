
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "InputHandler.h"
#include "Face.h"

InputHandler::InputHandler(Face* pFace) :
    m_pFace(pFace),
    m_pressed(false)
{}

void InputHandler::keyCallback(int key, int scancode, int action, int mods)
{
    // if (action == GLFW_PRESS)
    //     onKeyPressed(key);
    // else if (action == GLFW_RELEASE)
    // 	onKeyReleased(key);
}

void InputHandler::mouseCallback(int button, int action, int mods)
{
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_1)
    {
        if (!m_pressed)
            m_pFace->onCursorButton(glm::vec2(m_mouseX, m_mouseY), true, 0);
        m_pressed = true;
    }
    else if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_1)
    {
        m_pFace->onCursorButton(glm::vec2(m_mouseX, m_mouseY), false, 0);
    	m_pressed = false;
    }
}

void InputHandler::mouseMoveCallback(double xPos, double yPos)
{
    float xMove = xPos - m_mouseX;
    float yMove = yPos - m_mouseY;

	m_mouseX = xPos;
	m_mouseY = yPos;
	m_pFace->onCursorMoved(glm::vec2(m_mouseX, m_mouseY));
    if (m_pressed)
        m_pFace->onCursorDragged(glm::vec2(xMove, yMove));
}

void InputHandler::scrollCallback(float x, float y)
{
    m_pFace->onScroll(glm::vec2(x, y));
}