/*
 *  DebugRenderer.cpp
 *
 *  Created on: 18 Jan 2025
 *      Author: mchlp
 */

#include <iostream>  // todo remove

#include "DebugRenderer.h"

#include <ft2build.h>
#include FT_FREETYPE_H

struct line
{
	float x1; float y1; float r1; float g1; float b1;
	float x2; float y2; float r2; float g2; float b2;
};

DebugRenderer::DebugRenderer(Shader &lineShader, Shader &textShader, float width, float height) :
	m_windowWidth(width),
    m_windowHeight(height),
    m_linesOffset(0),
	m_lineShader(lineShader),
	m_textShader(textShader),
	m_linesBatchSize(1024),  // todo set this
	m_textBatchSize(1024)
{
    initDebugRenderer();
	initTextRenderer();
	initFont();
}

DebugRenderer::~DebugRenderer()
{
    glDeleteVertexArrays(1, &m_linesVAO);
}

void DebugRenderer::drawLine(glm::vec2 a, glm::vec2 b, glm::vec3 color)
{
    m_lineShader.use();

    a *= glm::vec2(2.0f / m_windowWidth, 2.0f / m_windowHeight);
    b *= glm::vec2(2.0f / m_windowWidth, 2.0f / m_windowHeight);
    a -= glm::vec2(1.0f, 1.0f);
    b -= glm::vec2(1.0f, 1.0f);

    // generate vertex data
    float vertices[] = {
    	a.x, a.y, color.x, color.y, color.z, // first vertex
    	b.x, b.y, color.x, color.y, color.z  // second vertex
    };

	if (m_linesOffset >= m_linesBatchSize)
	{
		drawLines();
		m_linesOffset = 0;
	}

    // write to vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_linesVBO);
	glBufferSubData(GL_ARRAY_BUFFER, m_linesOffset * sizeof(line), sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_linesOffset++;

    // translate camera
	// glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(camera.x, camera.y, 0.0f));
	// set uniforms
	m_lineShader.setMvpMatrix("view", glm::mat4(1.0f));
}

void DebugRenderer::drawCircle(glm::vec2 centre, float radius)
{
	m_lineShader.use();

	drawLine(glm::vec2(centre.x, centre.y + radius), glm::vec2(centre.x + (0.71f * radius), centre.y + (0.71f * radius)), glm::vec3());
	drawLine(glm::vec2(centre.x + (0.71f * radius), centre.y + (0.71f * radius)), glm::vec2(centre.x + radius, centre.y), glm::vec3());
	drawLine(glm::vec2(centre.x + radius, centre.y), glm::vec2(centre.x + (0.71f * radius), centre.y - (0.71f * radius)), glm::vec3());
	drawLine(glm::vec2(centre.x + (0.71f * radius), centre.y - (0.71f * radius)), glm::vec2(centre.x, centre.y - radius), glm::vec3());
	drawLine(glm::vec2(centre.x, centre.y - radius), glm::vec2(centre.x - (0.71f * radius), centre.y - (0.71f * radius)), glm::vec3());
	drawLine(glm::vec2(centre.x - (0.71f * radius), centre.y - (0.71f * radius)), glm::vec2(centre.x - radius, centre.y), glm::vec3());
	drawLine(glm::vec2(centre.x - radius, centre.y), glm::vec2(centre.x - (0.71f * radius), centre.y + (0.71f * radius)), glm::vec3());
	drawLine(glm::vec2(centre.x - (0.71f * radius), centre.y + (0.71f * radius)), glm::vec2(centre.x, centre.y + radius), glm::vec3());
}

void DebugRenderer::drawLines()
{
	// draw lines
	m_lineShader.use();
	glBindVertexArray(m_linesVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_linesVBO);
	glDrawArrays(GL_LINES, 0, m_linesOffset * 2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	m_linesOffset = 0;
}

void DebugRenderer::drawString(std::string text, float x, float y, float scale, glm::vec3 color)
{
	int textureUnits;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);
	int maxTexUnits = 32; // todo temp line

	m_textShader.use();
	int samplers[maxTexUnits];
	for (int i = 0; i < maxTexUnits; i++)
    	samplers[i] = i;
	glUniform1iv(glGetUniformLocation(m_textShader.getID(), "text"), maxTexUnits, samplers);

	glUniform3f(glGetUniformLocation(m_textShader.getID(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_textVAO);

	for (char c : text)
	{
		// draw current batch if texture units are full
		if (m_texCount >= textureUnits || m_texCount >= maxTexUnits)
		{
			drawQuads();
			m_texCount = 0;
			m_texIDs.clear();
		}

		if (m_textOffset >= m_textBatchSize)
		{
			drawQuads();
			m_textOffset = 0;
		}

		Character ch = m_characters[c];

		// identify required texture unit
	    int textureSlot;
	    if(!(m_texIDs.count(ch.textureID)))
	    {
	    	// Add texture to map if not present
	    	m_texIDs.insert(std::pair<unsigned int, int>(ch.textureID, m_texCount));
	    	textureSlot = m_texCount;
	    	m_texCount++;
	    }
	    else
	    {
	    	// Get texture unit if already present
	        textureSlot = m_texIDs[ch.textureID];
	    }

		float xPos = x + ch.bearing.x * scale;
		float yPos = y + ch.bearing.y * scale;

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;
		
		w *= 2.0f / m_windowWidth;
		h *= 2.0f / m_windowHeight;

		xPos *= 2.0f / m_windowWidth;
		yPos *= 2.0f / m_windowHeight;

		xPos -= 1.0f;
		yPos -= 1.0f;

		// generate vertex data
		float vertices[] = {
			// pos         	 	// texPos   // texID
			xPos, yPos,   		0.0f, 0.0f, (float)textureSlot,
			xPos, yPos - h, 	0.0f, 1.0f, (float)textureSlot,
			xPos + w, yPos - h, 1.0f, 1.0f, (float)textureSlot,
			xPos + w, yPos, 	1.0f, 0.0f, (float)textureSlot,
		};

		// generate index data
		uint32_t indices[] = {
	    		(m_textOffset * 4) + 0, (m_textOffset * 4) + 1, (m_textOffset * 4) + 2,
				(m_textOffset * 4) + 2, (m_textOffset * 4) + 3, (m_textOffset * 4) + 0
		};

		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		// write to vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_textVBO);
		glBufferSubData(GL_ARRAY_BUFFER, m_textOffset * sizeof(vertices), sizeof(vertices), vertices);

		// write to index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_textIBO);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, m_textOffset * sizeof(indices), sizeof(indices), indices);

		x += (ch.advance >> 6) * scale;

		m_textOffset++;

		m_textShader.setMvpMatrix("view", glm::mat4(1.0f));
	}

	drawQuads();

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void DebugRenderer::drawQuads()
{
	// draw two triangles per quad
	m_textShader.use();
	glBindVertexArray(m_textVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_textIBO);
	glDrawElements(GL_TRIANGLES, m_textOffset * 6, GL_UNSIGNED_INT, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	m_textOffset = 0;
}

void DebugRenderer::initDebugRenderer()
{
	glGenVertexArrays(1, &m_linesVAO);
	glGenBuffers(1, &m_linesVBO);

	GLfloat lineSeg[] =
	{
	    0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // first vertex
	    2.0f, 2.0f, 1.0f, 1.0f, 1.0f // second vertex
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_linesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineSeg) * m_linesBatchSize, nullptr, GL_DYNAMIC_DRAW);

	glBindVertexArray(m_linesVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)8);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void DebugRenderer::initTextRenderer()
{
    glGenVertexArrays(1, &m_textVAO);
    glGenBuffers(1, &m_textVBO);
    glGenBuffers(1, &m_textIBO);

    float vertices[] = {
            // pos      // texPos   //texIndex
            0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    		1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    		1.0f, 1.0f, 1.0f, 1.0f, 1.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * m_textBatchSize, nullptr, GL_DYNAMIC_DRAW);

    uint32_t indices[] = {
    		0, 1, 2, 2, 3, 0
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_textIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * m_textBatchSize, nullptr, GL_DYNAMIC_DRAW);

    glBindVertexArray(m_textVAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)8);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)16);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void DebugRenderer::initFont()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
		std::cout << "error" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, "C:/Users/mchlp/Documents/vsCode/UI/resources/arial.ttf", 0, &face))
    {
		std::cout << "error" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
		std::cout << "error" << std::endl;
        return;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
			std::cout << "error" << std::endl;
            continue;
        }

        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x
        };
        m_characters.insert(std::pair<char, Character>(c, character));
    }
}

void DebugRenderer::draw()
{
	drawLines();
	drawQuads();
}
