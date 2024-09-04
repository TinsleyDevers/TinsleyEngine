//////////////////////////////////////////////////////////////////////
// Created by Tinsley Devers
// https://tinsley.dev
// https://github.com/TinsleyDevers
//////////////////////////////////////////////////////////////////////
// First created on 2024.09.04
// Last edited on 2024.09.04
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main()
{
    glfwInit();

    // Set the version of OpenGL to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window to be used for OpenGL
    GLFWwindow* window = glfwCreateWindow(800, 800, "TinsleyEngine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window the current context
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    } 
    
    // Set the viewport size and color
    glViewport(0, 0, 800, 800);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // End the program
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}   