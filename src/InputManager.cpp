#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "InputManager.h"
#include "GraphicsManager.h"

using namespace RenEngine;

void InputManager::startup()
{
    // Doesn't do anything right now.
}

void InputManager::shutdown()
{
    // Doesn't do anything right now.

}

void InputManager::update()
{
    glfwPollEvents();
}

// Uses graphics manager window pointer directly, via the private
// function getWindow. Had to cast the returned window because
// it's passing it as a void pointer to hide the GLFW headers in
// the .cpp file.
bool InputManager::keyPressed(GraphicsManager& gm, input_code key)
{
    return (glfwGetKey((GLFWwindow*)gm.getWindow(), key) == 1) ? true : false;
}