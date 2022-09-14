#define GLFW_INCLUDE_NONE
#define SOKOL_IMPL
#define SOKOL_GLCORE33

#include <GLFW/glfw3.h>
#include "sokol_gfx.h"
#include <GraphicsManager.h>
#include <vector>

using namespace RenEngine;

// Private implemenation class.
class PrivateImpl
{
    public:
        // Pointer to main window.
        GLFWwindow* window;

        // A vertex buffer containing a textured square.
        std::vector<float> vertices;
        
        // Vertex buffer for 2D objects.
        sg_buffer_desc buffer_desc{};
        sg_buffer vertex_buffer;

        // Pipeline to describe GPU state for drawing.
        sg_pipeline_desc pipeline_desc{};

};

// Constructor creates a new Private Implemenation automatically.
GraphicsManager::GraphicsManager()
: pImpl(new PrivateImpl())
{}

// Creates the window to be displayed with the specific
// configuration parameters.
void GraphicsManager::gmStartup(Configuration windowParam)
{
    // Window creation magic by GLFW.
    glfwInit();

    // We'll use sokol_gfx's OpenGL backend
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    pImpl->window = glfwCreateWindow( windowParam.window.width, 
                                           windowParam.window.height, 
                                           windowParam.window.name, 
                                           windowParam.window.fullscreen ? glfwGetPrimaryMonitor() : 0, 0);

    glfwSetWindowAspectRatio( pImpl->window, windowParam.window.width, windowParam.window.height );

    if( !pImpl->window )
    {
        std::cerr << "Failed to create a window." << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent( pImpl->window );
    
    glfwSwapInterval(1);

    // Sokol startup
    sg_setup(sg_desc{});

    pImpl->vertices = {
        // positions      // texcoords
        -1.0f,  -1.0f,    0.0f,  0.0f,
        1.0f,  -1.0f,    1.0f,  0.0f,
        -1.0f,   1.0f,    0.0f,  1.0f,
        1.0f,   1.0f,    1.0f,  1.0f,
    };

    pImpl->buffer_desc.data = SG_RANGE(pImpl->vertices);
    pImpl->vertex_buffer = sg_make_buffer(pImpl->buffer_desc);
}

void GraphicsManager::gmShutdown()
{
    delete pImpl;
    glfwTerminate();
    sg_shutdown();
}

// Returns the value of the close flag, which
// is set to 1 whenever the close button is 
// pressed, otherwise returns 0.
bool GraphicsManager::closeWindow()
{
    return !glfwWindowShouldClose(pImpl->window);
}

// Used to access the window by the input manager.
void* GraphicsManager::getWindow()
{
    return pImpl->window;
}