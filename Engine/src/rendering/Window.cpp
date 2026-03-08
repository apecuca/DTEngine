#include "Window.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

DTEngine::Window* DTEngine::Window::instance;

using namespace DTEngine;

Window::~Window()
{
    //
}

Window::Window(int _width, int _height, std::string _name)
:
width(_width), height(_height)
{
    if (instance != nullptr)
        throw std::string("Duplicated window instance");
    
    instance = this;

    winPtr = glfwCreateWindow(_width, _height, _name.c_str(), NULL, NULL);

    if (!winPtr) {
        glfwTerminate();
        throw std::string("Failed to initialize Window");
    }
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
    glClearColor(0.17f, 0.29f, 0.45f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(winPtr);
}

void Window::ReadInputs()
{
    glfwPollEvents();
}

bool Window::IsRunning()
{
    return !glfwWindowShouldClose(winPtr);
}

void Window::callback_framebufferSize(GLFWwindow* window, int newWidth, int newHeight)
{
	instance->width = newWidth;
	instance->height = newHeight;

	glViewport(0, 0, instance->width, instance->height);
}