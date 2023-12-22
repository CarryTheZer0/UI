/*
 * testDrawTriangle.cpp
 * 
 *  30 July 2023
 *  Mike
 */

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "glm/gtc/matrix_transform.hpp"

#include "UIRenderer.h"
#include "Shader.h"

/*
 *  Draw a triangle and a square
 */
int main()
{
    glewExperimental=true;
    if (!glfwInit() )
    {
        fprintf( stderr, "Failed to initialise GLFW\n" );
        return -1;
    }

    GLFWwindow* pWindow;
	pWindow = glfwCreateWindow( 1024, 768, "Test 01", NULL, NULL);
    glfwMakeContextCurrent(pWindow);

    glewExperimental=true;
    if (glewInit() != GLEW_OK) {
        fprintf( stderr, "Failed to initialize GLEW\n" );
        return -1;
    }

    Shader s = Shader();
    s.loadShaderFromFile("../src/graphics/shaders/SimpleVertexShader.glsl", "../src/graphics/shaders/SimpleFragmentShader.glsl");
    UIRenderer renderer = UIRenderer(s);

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), 1024.0f / 768.0f, 0.1f, 100.0f);
	
	// Or, for an ortho camera :
	// glm::mat4 projection = glm::ortho(-10.0f, 10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3( 10.0f, 10.0f, 1.0f ));

	glm::mat4 view = glm::lookAt(
		glm::vec3(0,0,1), // location
		glm::vec3(0,0,0), // target
		glm::vec3(0,1,0)  // orientation (up direction)
    );

	renderer.setProjection(projection);
    renderer.setView(view);
    renderer.setModel(model);
    
	glfwWindowHint(GLFW_SAMPLES, 4);  // 4x antialiasin
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // OpenGL 3.3g
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // We don't want the old OpenGL

    bool running = true;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const float dt = 0.016;
    float currentTime = glfwGetTime();
    float step = 0.0f;
    float accumulator = 0.0f;

    while(running) {
        glfwPollEvents();

        float newTime = glfwGetTime();
		float frameTime = newTime - currentTime;
		currentTime = newTime;

        accumulator += frameTime;

		while (accumulator >= dt)
		{
            // do processing on a fixed time
			accumulator -= dt;

            if (glfwWindowShouldClose(pWindow))
            {
                running = false;
            }

            step += 0.01f;

            glm::mat4 view = glm::lookAt(
                glm::vec3(cos(step) * 30.0f,0,sin(step) * 30.0f), // location
                glm::vec3(0,0,0), // target
                glm::vec3(0,1,0)  // orientation (up direction)
            );
			renderer.setView(view);

            model = glm::rotate(model, 0.001f, glm::vec3(0.0f, 0.0f, 1.0f));
		}

		// render as often as possible
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);  // grey background
		glClear(GL_COLOR_BUFFER_BIT);

        // draw a simnple triangle
        renderer.drawTriangle(glm::vec2(-0.5f, 0.3f),        // vertex 0
                              glm::vec2(-0.82f, -0.3f),      // vertex 1
                              glm::vec2(-0.18f, -0.3f),      // vertex 2
                              model,
                              glm::vec2(),                   // no camera translation
                              glm::vec3(0.0f, 1.0f, 0.0f));  // green (rgb = 010)  
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;

        // draw a sqaure using index buffer
        glm::vec3 red = glm::vec3(1.0f, 0.0f, 0.0f);                // red (rgb = 100)
        vertices.emplace_back(Vertex(glm::vec2(0.5f, 0.3f), red));  // vertex 0
        vertices.emplace_back(Vertex(glm::vec2(0.8f, 0.0f), red));  // vertex 1
        vertices.emplace_back(Vertex(glm::vec2(0.5f, -0.3f), red)); // vertex 2
        vertices.emplace_back(Vertex(glm::vec2(0.2f, 0.0f), red));  // vertex 3

        triangles.emplace_back(Triangle(0, 2, 1));  // top triangle
        triangles.emplace_back(Triangle(0, 2, 3));  // bottom triangle

        renderer.drawTriangles(vertices, triangles, model);
        renderer.draw();

        glfwSwapBuffers(pWindow);
    }

	glfwTerminate();
}