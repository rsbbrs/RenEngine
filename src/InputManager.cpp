#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "Types.h"
#include "InputManager.h"
#include "GraphicsManager.h"

using namespace RenEngine;

void InputManager::imStartup()
{
    // Doesn't do anything right now.
}

void InputManager::imShutdown()
{
    // Doesn't do anything right now.

}

void InputManager::update()
{
    glfwPollEvents();
}

bool InputManager::keyPressed(GraphicsManager& gm, input_codes key)
{
    glfwGetKey(gm.window, key);
}