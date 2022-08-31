#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "Types.h"
#include "GraphicsManager.h"
#include <iostream>

using namespace RenEngine;

void GraphicsManager::gmStartup(Window windowParam)
{
    // Window creation magic by GLFW.
    glfwInit();
    // We'll use sokol_gfx's OpenGL backend
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    GLFWwindow* window = glfwCreateWindow( windowParam.width, 
                                           windowParam.height, 
                                           windowParam.name, 
                                           windowParam.fullscreen ? glfwGetPrimaryMonitor() : 0, 0 );
    glfwSetWindowAspectRatio( window, windowParam.width, windowParam.height );
    if( !window )
    {
        std::cerr << "Failed to create a window." << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent( window );
    glfwSwapInterval(1);
}