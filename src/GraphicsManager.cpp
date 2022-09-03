#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "Types.h"
#include "GraphicsManager.h"
#include <iostream>

using namespace RenEngine;

void GraphicsManager::gmStartup(Configuration windowParam)
{
    // Window creation magic by GLFW.
    glfwInit();

    // We'll use sokol_gfx's OpenGL backend
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    window = glfwCreateWindow( windowParam.window.width, 
                                           windowParam.window.height, 
                                           windowParam.window.name, 
                                           windowParam.window.fullscreen ? glfwGetPrimaryMonitor() : 0, 0);

    glfwSetWindowAspectRatio( window, windowParam.window.width, windowParam.window.height );

    if( !window )
    {
        std::cerr << "Failed to create a window." << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent( window );
    
    glfwSwapInterval(1);
}

void GraphicsManager::gmShutdown()
{
    glfwTerminate();
}