
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "InputHandler.h"
#include "Face.h"

namespace temp_UI {
    InputHandler::InputHandler(Face* pUiRoot) :
        m_pUiRoot(pUiRoot)
    {}

    void InputHandler::keyCallback(int key, int action, int modifiers)
    {
        if (action && key == GLFW_KEY_TAB) m_pUiRoot->cycleFocus();

        onInput(key, action, modifiers);
    }

    void InputHandler::mouseCallback(int button, int action, int modifiers)
    {
        m_pUiRoot->onCursorMoved(glm::vec2(m_mouseX, m_mouseY));
        onInput(button, action, modifiers);
    }

    void InputHandler::mouseMoveCallback(double xPos, double yPos)
    {
        float xMove = xPos - m_mouseX;
        float yMove = yPos - m_mouseY;

        m_mouseX = xPos;
        m_mouseY = yPos;
        m_pUiRoot->onCursorMoved(glm::vec2(m_mouseX, m_mouseY));
        if (m_pressed[GLFW_MOUSE_BUTTON_1])
            m_pUiRoot->onCursorDragged(glm::vec2(xMove, yMove));
    }

    void InputHandler::scrollCallback(float x, float y)
    {
        m_pUiRoot->onScroll(glm::vec2(x, y));
    }

    void InputHandler::onInput(int id, int action, int modifiers)
    {
        if (!m_pressed.count(id)) m_pressed[id] = false;

        if (action == GLFW_PRESS)
        {
            if (!m_pressed[id])
                m_pUiRoot->onSelect(true, 0);
            m_pressed[id] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            m_pUiRoot->onSelect(false, 0);
            m_pressed[id] = false;
        }
    }
}
