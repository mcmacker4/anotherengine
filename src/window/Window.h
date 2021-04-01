#ifndef MINECPP_WINDOW_H
#define MINECPP_WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Window {

    GLFWwindow* handle;
    int width, height;

public:
    explicit Window();

    Window(const Window& w) = delete;

    Window(Window&& w) = delete;

    ~Window();

    void swapBuffers();

    void setTitle(const std::string& title);

    void setVisible(bool visible);

    bool shouldClose();

private:
    void updateSize(int width, int height);

public:
    friend void windowSizeCallback(GLFWwindow* handle, int width, int height);

};


#endif //MINECPP_WINDOW_H
