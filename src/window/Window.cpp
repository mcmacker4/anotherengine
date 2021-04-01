#include "Window.h"

#include <iostream>

static void keyCallback(GLFWwindow* handle, int key, int scancode, int action,
                        int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
        glfwSetWindowShouldClose(handle, GLFW_TRUE);
    }
}

void windowSizeCallback(GLFWwindow* handle, int width, int height) {
    auto* window = static_cast<Window*>(glfwGetWindowUserPointer(handle));
    window->updateSize(width, height);
}

Window::Window() {
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

#ifndef NDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    this->width = 1024;
    this->height = 576;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

    this->handle = glfwCreateWindow(1024, 576, "", nullptr, nullptr);
    if (handle == nullptr) {
        std::cout << "Could not create GLFW window" << std::endl;
        exit(-1);
    }

    glfwSetWindowPos(this->handle, (vidmode->width - width) / 2,
                     (vidmode->height - height) / 2);

    glfwMakeContextCurrent(handle);
    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) ==
        0) {
        std::cerr << "Could not initialize OpenGL GLAD." << std::endl;
        exit(-1);
    }

    glfwSetWindowUserPointer(handle, this);
    glfwSetWindowSizeCallback(handle, windowSizeCallback);
    glfwSetKeyCallback(handle, keyCallback);
}

Window::~Window() { glfwDestroyWindow(handle); }

void Window::swapBuffers() { glfwSwapBuffers(handle); }

void Window::setTitle(const std::string& title) {
    glfwSetWindowTitle(handle, title.c_str());
}

void Window::setVisible(bool visible) {
    if (visible) {
        glfwShowWindow(handle);
    } else {
        glfwHideWindow(handle);
    }
}

void Window::updateSize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(this->handle) == GLFW_TRUE;
}