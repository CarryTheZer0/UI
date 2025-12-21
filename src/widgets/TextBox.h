/*
 *  TextBox.h
 *
 *  Created on: 24 Jan 2025
 *      Author: mchlp
 */

#ifndef UI_TEXTBOX_H_
#define UI_TEXTBOX_H_

#include "Face.h"
#include "IPainter.h"

class TextBox : public Face
{
public:
	TextBox() = delete;
	TextBox(
		Face& parent,
		glm::vec4 pixels=glm::vec4(), 
		glm::vec4 percentage=glm::vec4(),
		glm::vec3 color=glm::vec3(1.0f),
		float margin=50.0f
	);

	void draw(IPainter* pPainter) override;

	float getMargin() { return this->m_margin; }
protected:
	float m_margin;
	glm::vec3 m_color;
};

#endif /* UI_TEXTBOX_H_ */
