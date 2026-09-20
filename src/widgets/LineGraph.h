/*
 *  LineGraph.h
 *
 *  Created on: 19 May 2026
 *      Author: mchlp
 */

#ifndef UI_LINE_GRAPH_H_
#define UI_LINE_GRAPH_H_

#include <algorithm>

#include "Face.h"
#include "IPainter.h"

class LineGraph : public Face
{
public:
	LineGraph() = delete;
	LineGraph(
		glm::vec4 pixels=glm::vec4(), 
		glm::vec4 percentage=glm::vec4(),
		float min=0.0f,
		float max=1.0f,
		glm::vec3 color=glm::vec3(1.0f)
	);

	void draw(IPainter* pPainter) override;

    void addDataPoint(float dataPoint) { m_data.push_back(dataPoint); }
    void setData(std::vector<float> &data);
protected:
	glm::vec3 m_color;
    float m_min, m_max;

    std::vector<float> m_data;
};

#endif /* UI_LINE_GRAPH_H_ */
