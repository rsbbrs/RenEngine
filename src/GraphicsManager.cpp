#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GraphicsManager.h>

using namespace RenEngine;

// Private implemenation class.
class PrivateImpl
{
    public:
        GLFWwindow* window;
};

// Constructor creates a new Private Implemenation automatically.
GraphicsManager::GraphicsManager()
: pimpl(new PrivateImpl())
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

    pimpl->window = glfwCreateWindow( windowParam.window.width, 
                                           windowParam.window.height, 
                                           windowParam.window.name, 
                                           windowParam.window.fullscreen ? glfwGetPrimaryMonitor() : 0, 0);

    glfwSetWindowAspectRatio( pimpl->window, windowParam.window.width, windowParam.window.height );

    if( !pimpl->window )
    {
        std::cerr << "Failed to create a window." << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent( pimpl->window );
    
    glfwSwapInterval(1);
}

void GraphicsManager::gmShutdown()
{
    delete pimpl;
    glfwTerminate();
}

// Returns the value of the close flag, which
// is set to 1 whenever the close button is 
// pressed, otherwise returns 0.
bool GraphicsManager::closeWindow()
{
    return !glfwWindowShouldClose(pimpl->window);
}

// Used to access the window by the input manager.
void* GraphicsManager::getWindow()
{
    return pimpl->window;
}