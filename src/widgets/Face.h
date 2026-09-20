/*
 *  Face.h
 *
 *  Created on: 22 Jul 2021
 *      Author: mchlp
 */

#ifndef UI_FACE_H_
#define UI_FACE_H_

#include <glm/glm.hpp>

#include <vector>
#include <memory>
#include <functional>

#include "IPainter.h"

enum UiInput 
{
	UI_NEWLINE = 0,
	UI_BACKSPACE = 1
};

class Face
{
public:
	Face() = delete;
	Face(
		glm::vec4 pixels=glm::vec4(), 
		glm::vec4 percentage=glm::vec4()
	);

	Face(float width, float height, float x_offset=0.0f, float y_offset=0.0f);

	virtual ~Face();

	virtual void draw(IPainter* pPainter);

	/// @return true if the widget was selected
	virtual void onSelect(bool down, int modifiers) {}
	virtual void onCursorDragged(glm::vec2 offset) {}
	virtual void onScroll(glm::vec2 offset) {}
	virtual void onTextInput(char character) {}

	virtual void onFocused() {}
	virtual void onUnfocused() {}

	void select(bool down, int modifiers);
	void drag(glm::vec2 offset);
	void scroll(glm::vec2 offset);
	void textInput(char character);

	bool cursorMoved(glm::vec2 position);
	bool cycleFocus();
	bool shiftFocusLevel(bool down);
	bool shiftFocus(glm::vec2 direction);

	template <class FaceType, class... ValueTypes>
	FaceType& addChild(
		glm::vec4 pixels=glm::vec4(), 
		glm::vec4 percentage=glm::vec4(),
		ValueTypes... args
	) { 
		m_children.push_back(std::make_unique<FaceType>(pixels, percentage, args...));
		FaceType& newFace = *dynamic_cast<FaceType*>(m_children.back().get());
		newFace.m_parentDimensions = m_dimensions;
		newFace.setRect();
		return newFace; 
	}

	void removeChild(Face& faceA)
	{
		auto position = std::find_if(m_children.begin(), m_children.end(), [&](std::unique_ptr<Face>& faceB){ return &faceA == faceB.get(); });
		if((*position)->isFocused()) cycleFocus();
		m_children.erase(position);
	}
	
	glm::vec4 getRect() { return m_dimensions; }
	glm::vec2 getCentre() { return glm::vec2(m_dimensions.x + m_dimensions.z / 2, m_dimensions.y + m_dimensions.w / 2); }
	void move(glm::vec2 transform);

	bool isFocused() { return m_isFocused; }
	bool isFrozen() { return m_isFrozen; }
	bool isActive() { return m_isActive; }

	void setActive(bool active) {
		m_isActive = active;
		m_isFocused = m_isFocused && active;
	}
protected:
	glm::vec4 m_parentDimensions;
	glm::vec4 m_pixels;
	glm::vec4 m_percentage;
	glm::vec4 m_dimensions;

	bool m_holdFocus;

	std::vector<std::unique_ptr<Face>> m_children;

	void setRect(); 

	bool isInBounds(glm::vec2 position);
private:
	bool m_isFocused;
	bool m_isActive;
	bool m_isFrozen;
	int m_focusedChild;

	bool tryToShiftFocus();

	void focus() { m_isFocused = true; onFocused(); } 
	void unfocus() { m_isFocused = false; onUnfocused(); }
};

#endif /* UI_FACE_H_ */
