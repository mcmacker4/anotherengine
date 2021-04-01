#ifndef MINECPP_SCENE_H
#define MINECPP_SCENE_H

#include "../gl/buffer.h"
#include "../gl/shader.h"

class Scene {

    gl::VAO vao;
    gl::ShaderProgram program;

public:
    Scene();

    void init();
    void update(double delta);
    void render();
    void cleanup();

};


#endif //MINECPP_SCENE_H
