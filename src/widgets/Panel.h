/*
 * Panel.h
 *
 *  Created on: 22 Jul 2021
 *      Author: mchlp
 */

#ifndef UI_PANEL_H_
#define UI_PANEL_H_

#include "Face.h"
#include "IPainter.h"

class Panel : public Face
{
public:
	Panel(glm::vec3 color, float margin=50.0f);
	~Panel() = default;

	void draw(IPainter* pPainter) override;

	float getMargin() { return this->m_margin; }
protected:
	float m_margin;
	glm::vec3 m_color;
};

#endif /* UI_PANEL_H_ */
