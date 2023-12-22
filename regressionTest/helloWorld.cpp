/*
 * helloWorld.cpp
 *
 *  27 July 2023
 *  Mike
 */

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <glm/gtx/string_cast.hpp>

#include "UIRenderer.h"
#include "InputHandler.h"
#include "Shader.h"
#include "Painter.h"

#include "Panel.h"
#include "Slider.h"
#include "Button.h"

/*
 *  General purpose testing script
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
    
	glfwWindowHint(GLFW_SAMPLES, 4);  // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // OpenGL 3.3g
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // We don't want the old OpenGL

    bool running = true;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 view = glm::lookAt(
        glm::vec3(0,0,1),  // location
        glm::vec3(0,0,0),  // target
        glm::vec3(0,1,0)   // orientation (up direction)
    );
    renderer.setView(view);

    // ortho camera :
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f); // In world coordinates
    // glm::mat4 projection = glm::perspective(glm::radians(60.0f), 1024.0f / 768.0f, 0.1f, 100.0f);

    renderer.setProjection(projection); 

    Painter painter = Painter(&renderer, "myPainter");
    Face root = Face(1024.0f, 768.0f);

    Panel panel = Panel(glm::vec3(1.0f, 1.0f, 0.0f));
    root.addChild(&panel);
    panel.setRect(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 100.0f, 100.0f));

    Button button1 = Button(glm::vec3(0.0f, 1.0f, 0.0f), 30.0f);
    panel.addChild(&button1);
    button1.setRect(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec4(10.0f, 10.0f, 20.0f, 20.0f));
    std::function<void()> myfunc = [](){std::cout << "pressed" << std::endl;};
    button1.setCallback(myfunc);

    Button button2 = Button(glm::vec3(0.0f, 1.0f, 0.0f), 30.0f);
    panel.addChild(&button2);
    button2.setRect(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec4(40.0f, 10.0f, 20.0f, 20.0f));
    button2.setCallback(myfunc);

    Slider slider = Slider(glm::vec3(0.0f, 1.0f, 0.0f), 30.0f);
    panel.addChild(&slider);
    slider.setRect(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec4(10.0f, 50.0f, 40.0f, 30.0f));

    InputHandler input = InputHandler(&root);

    glfwSetWindowUserPointer( pWindow, &input );

    glfwSetCursorPosCallback( pWindow, []( GLFWwindow* window, double x, double y)
    {
        InputHandler* input = static_cast<InputHandler*>( glfwGetWindowUserPointer( window ) );

        // x = -1.0f + 2 * x / 1024.0f;
        // y = -1.0f + 2 * (768.0f - y) / 768.0f;
        y = (768.0f - y);

        glm::mat4 view = glm::lookAt(
            glm::vec3(0,0,1),  // location
            glm::vec3(0,0,0),  // target
            glm::vec3(0,1,0)   // orientation (up direction)
        );

        // ortho camera :
        glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f); // In world coordinates

        glm::vec4 pos = glm::inverse(projection) * glm::inverse(view) * glm::vec4(x, y, 0.0f, 1.0f);

        input->mouseMoveCallback(x, y);
    });

    glfwSetMouseButtonCallback( pWindow, []( GLFWwindow* window, int button, int action, int mods)
    {
        InputHandler* input = static_cast<InputHandler*>( glfwGetWindowUserPointer( window ) );
        input->mouseCallback(button, action, mods);
    });

    glfwSetScrollCallback( pWindow, [](GLFWwindow* window, double x, double y)
    {
        InputHandler* input = static_cast<InputHandler*>( glfwGetWindowUserPointer( window ) );
        input->scrollCallback(x, y);
    });

    while(running) {
        glfwPollEvents();

		// render
		glClearColor(0.18f, 0.38f, 0.37f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        root.draw(&painter);
        renderer.draw();

        if (glfwWindowShouldClose(pWindow)) {
            running = false;
        }
        glfwSwapBuffers(pWindow);
    }

	glfwTerminate();
}