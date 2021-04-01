#include "Engine.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Engine* Engine::engine = nullptr;

#ifndef NDEBUG
static void APIENTRY openglDebugCallback(GLenum source, GLenum type,
                                         GLuint id, GLenum severity,
                                         GLsizei length, const GLchar* message,
                                         const void* userParam) {
    std::cout << "[GL DEBUG] " << message << std::endl;
}
#endif

Engine::Engine() {

    if (glfwInit() != GLFW_TRUE) {
        std::cerr << "Could not initialize GLFW." << std::endl;
        exit(-1);
    }

    Engine::window = new Window();

    glClearColor(0.3, 0.6, 0.9, 1.0);

#ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(openglDebugCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif

    Engine::window->setTitle(std::string("MineCpp"));
    Engine::window->setVisible(true);

    timer = Timer();

    scene = new Scene();

}

Engine::~Engine() {
    delete scene;
    delete window;
    glfwTerminate();
}

void Engine::start() {

    init();

    while (!Engine::window->shouldClose()) {
        Engine::window->swapBuffers();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        update();
        render();

        glfwPollEvents();
    }

    cleanup();

}

void Engine::init() {
    scene->init();
}

void Engine::update() {
    timer.update();
    scene->update(timer.delta());
}

void Engine::render() {
    scene->render();
}

void Engine::cleanup() {
    scene->cleanup();
}

Engine& Engine::instance() {
    return *Engine::engine;
}

void Engine::createInstance() {
    Engine::engine = new Engine();
}

void Engine::destroyInstance() {
    delete Engine::engine;
}

int main() {
    Engine::createInstance();
    Engine::instance().start();
    Engine::destroyInstance();
}