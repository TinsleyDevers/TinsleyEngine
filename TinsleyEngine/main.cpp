//////////////////////////////////////////////////////////////////////
// Created by Tinsley Devers
// https://tinsley.dev
// https://github.com/TinsleyDevers
//////////////////////////////////////////////////////////////////////
// First created on 2024.09.04
// Last edited on 2024.09.09
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
// Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.51f, 0.49f, 1.0f, 1.0f);\n" // Set the color of the triangle
"}\n\0";


int main()
{
    glfwInit();

    // Set the version of OpenGL to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Set the profile of OpenGL to use
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Verticies of the triangle
    GLfloat verticies[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Bottom left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Bottom right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Top corner
    };

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
    

    // Create the vertex shaders 
    GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
    // Attach the shader source code to the shader
    glShaderSource(vertexshader, 1, &vertexShaderSource, NULL);
    // Compile the shader
    glCompileShader(vertexshader);

    // Create the fragment shader
    GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach the fragment shader source code to the shader
    glShaderSource(fragmentshader, 1, &fragmentShaderSource, NULL);
    // Compile the shader
    glCompileShader(fragmentshader);

    // Create the shader program
    GLuint shaderprogram = glCreateProgram();
    // Attach the vertexshader to the program
    glAttachShader(shaderprogram, vertexshader);
    // Attach the fragmentshader to the program
    glAttachShader(shaderprogram, fragmentshader);
    // Wrap-up/Link all the shaders together into the shader program
    glLinkProgram(shaderprogram);

    // Delete the shaders as they're linked into the program now and no longer necessery
    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);

    // Create the vertex buffer object
    GLuint VAO, VBO;

    // Generate the VAO and VBO with the vertex data
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the VAO and VBO into an Array Object
    glBindVertexArray(VAO);

    // Bind the VBO by specifying the type of buffer as GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce the verticies into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    // Configure the vertex attributes so OpenGL knows how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
    // Enable the vertex attributes so OpenGL knows to use them
    glEnableVertexAttribArray(0);

    // Bind both the VAO and VBO to 0 so they can't be modified
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Main Loop
    // Ref: https://en.wikipedia.org/wiki/Rotation_matrix
    // Ref: https://en.wikipedia.org/wiki/Matrix_(mathematics)
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.092f, 0.046f, 0.134f, 1.0f); // Set the background color
        glClear(GL_COLOR_BUFFER_BIT);

        // Tell OpenGL to use the shader program
        glUseProgram(shaderprogram);
        // Bind the VAO so OpenGL knows to use it
        glBindVertexArray(VAO); 
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Delete all the objects created
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderprogram);

    // End the program
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}   