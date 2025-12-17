
#include <functional>
#include <glm/glm.hpp>

#include "Face.h"

class Slider : public Face
{
public:
	Slider() = delete;
	Slider(glm::vec3 color, float margin=50.0f, float min=0.0f, float max=1.0f);
	~Slider() = default;

	void draw(IPainter* pPainter) override;

	bool onSelect(bool down, int modifiers) override;

	bool onCursorDragged(glm::vec2 offset) override;
    bool onScroll(glm::vec2 offset) override;

    void updateValue();

	float getValue() { return m_value; }

	void setCallbackUpdate(std::function<void(float)> cb) {m_callbackUpdate = cb;}
protected:
	glm::vec3 m_color;
	float m_margin;
    bool m_held;
    float m_offset, m_min, m_max;

	float m_value;

	std::function<void(float)> m_callbackUpdate;
private:
    void setOffset(float offset);
};