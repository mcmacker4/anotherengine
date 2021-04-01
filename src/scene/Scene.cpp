#include "Scene.h"

static GLfloat triangle_data[9] {
    -0.5, -0.5, 0.0,
    0.5, -0.5, 0.0,
    0.0, 0.5, 0.0
};

Scene::Scene()
    : vao(gl::VAO::empty()),
      program(gl::ShaderProgram::loadFromFile("shaders", "main")) {}

void Scene::init() {
    gl::VBO vertices = gl::VBO::vertex_buffer(
        triangle_data, 9 * sizeof(GLfloat), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    vao.addAttribute(0, 3, GL_FLOAT, std::move(vertices));
}

void Scene::update(double delta) {}

void Scene::render() {
    program.bind();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Scene::cleanup() {}
