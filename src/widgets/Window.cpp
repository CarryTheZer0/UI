// /*
//  * Window.cpp
//  *
//  *  Created on: 22 Jul 2021
//  *      Author: mchlp
//  */

// #include "Window.h"

// Window::Window(const char* name, int width, int height) :
// 	Face(name, nullptr)
// {
// 	m_dimensions.z = width;
// 	m_dimensions.w = height;
// }

// void Window::callEvent(const char* eventName)
// {
// 	m_eventCalls[eventName](eventName);
// }

// void Window::addEvent(const char* name, std::function<void(const char*)> func)
// {
// 	m_eventCalls.insert({ name, func });
// }

// void Window::addAnchor(const char* name, Face* face)
// {
// 	m_anchorPoints.insert({ name, face });
// }
