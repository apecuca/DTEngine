#include "Window.hpp"

#include <Engine/Utils.hpp>
#include "core/InternalWorksManager.hpp"
#include "rendering/Rendering.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

DTEngine::Window* DTEngine::Window::instance;

using namespace DTEngine;

Window::~Window()
{
    instance = nullptr;
}

Window::Window(int _width, int _height, std::string _name)
:
width(_width), height(_height), fov(defaultFov)
{
    if (instance != nullptr)
        throw std::string("Duplicated window instance");
    
    instance = this;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    // Same size as the screen results in black background
    width = mode->width + 1;
    height = mode->height + 1;

    winPtr = glfwCreateWindow(width, height, _name.c_str(), NULL, NULL);

    if (!winPtr) {
        glfwTerminate();
        throw std::string("Failed to initialize Window");
    }

    int xpos, ypos;
    glfwGetMonitorPos(monitor, &xpos, &ypos);
    glfwSetWindowPos(winPtr, xpos, ypos);
}

void Window::ConfigWindow()
{
    // Set viewport size
	glViewport(0, 0, width, height);

    // Set callbacks
	glfwSetFramebufferSizeCallback(winPtr, callback_framebufferSize);
}

void Window::Clear()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    //glClearColor(0.17f, 0.29f, 0.45f, 1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(winPtr);
}

void Window::ReadInputs()
{
    glfwPollEvents();

    glfwGetCursorPos(winPtr, &mousex, &mousey);

    auto* rendering = InternalWorksManager::GetInstance()->GetRendering();
    int objId = rendering->GetObjectUnderMouse(mousex, mousey);
    glfwSetWindowAttrib(winPtr, GLFW_MOUSE_PASSTHROUGH, objId == 0 ? GLFW_TRUE : GLFW_FALSE);
}

bool Window::IsRunning()
{
    return !glfwWindowShouldClose(winPtr);
}

void Window::callback_framebufferSize(GLFWwindow* window, int newWidth, int newHeight)
{
	instance->width = newWidth + 1;
	instance->height = newHeight + 1;

	glViewport(0, 0, instance->width, instance->height);
}

Vector2 Window::GetSize()
{
    return Vector2(width, height);
}