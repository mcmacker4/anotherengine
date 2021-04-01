#ifndef MINECPP_SRC_ENGINE_H
#define MINECPP_SRC_ENGINE_H

#include "window/Window.h"
#include "scene/Scene.h"
#include "util/Timer.h"

class Engine {

    Window* window;
    Timer timer;

    Scene* scene;

    static Engine* engine;

private:
    Engine();
    ~Engine();

public:
    void start();

private:
    void init();
    void update();
    void render();
    void cleanup();

public:
    static Engine& instance();

private:
    static void createInstance();
    static void destroyInstance();

    friend int main();

};

#endif // MINECPP_SRC_ENGINE_H
