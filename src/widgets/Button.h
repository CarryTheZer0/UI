/*
 * Button.h
 *
 *  Created on: 23 Jul 2021
 *      Author: mchlp
 */

#ifndef UI_BUTTON_H_
#define UI_BUTTON_H_

#include <functional>
#include "Face.h"

class Button : public Face
{
public:
	enum ButtonState {
		Selected, Held
	};

	Button() = delete;
	Button(
		Face& parent,
		glm::vec4 pixels=glm::vec4(), 
		glm::vec4 percentage=glm::vec4(),
		glm::vec3 color=glm::vec3(1.0f),
		float margin=50.0f
	);

	void draw(IPainter* pPainter) override;

	bool onSelect(bool down, int modifiers) override;
	
	void setCallbackDown(std::function<void()> cb) {m_callbackDown = cb;}
	void setCallbackUp(std::function<void()> cb) {m_callbackUp = cb;}
protected:
	glm::vec3 m_color;
	float m_margin;
	bool m_isHeld;

	std::function<void()> m_callbackDown;
	std::function<void()> m_callbackUp;
};

#endif /* UI_BUTTON_H_ */
