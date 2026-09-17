/*
 *  Popup.h
 *
 *  Created on: 17 Dec 2025
 *      Author: mchlp
 */

#include "Face.h"

class Popup : public Face
{
public:
    Popup() = delete;
	Popup(
        std::shared_ptr<Face> content,
		glm::vec4 pixels=glm::vec4(), 
		glm::vec4 percentage=glm::vec4(),
		glm::vec3 color=glm::vec3(1.0f),
		float margin=50.0f
    );

    void draw(IPainter* pPainter) override;

    bool onCursorMoved(glm::vec2 position) override;
private:
    glm::vec3 m_color;
    float m_margin;
    bool m_isActive;

    std::shared_ptr<Face> m_content;
};