#include "buffer.h"

#include <iostream>

namespace gl {

/*
 *  Vertex Buffer Object
 *  Wrapper class for OpenGL object.
 *
 */

VBO::VBO(VBO&& other) noexcept {
    this->handle = other.handle;
    other.handle = 0;
}

VBO::~VBO() {
#ifndef NDEBUG
    if (this->handle != 0) {
        std::cout << "Delete VBO" << std::endl;
    }
#endif
    glDeleteBuffers(1, &this->handle);
}

void VBO::bind(GLuint target) const { glBindBuffer(target, handle); }

VBO VBO::vertex_buffer(const void* data, unsigned int bytes, GLuint target,
                       GLenum usage) {
    GLuint hnd;
    glGenBuffers(1, &hnd);
    glBindBuffer(target, hnd);

    glBufferData(target, bytes, data, usage);

    return VBO(hnd);
}

VBO& VBO::operator=(VBO&& rhs) noexcept {
    this->handle = rhs.handle;
    rhs.handle = 0;
    return *this;
}

/*
 *  Vertex Array Object
 *  Wrapper class for OpenGL object.
 *
 */

VAO::VAO(VAO&& other) noexcept {
    this->handle = other.handle;
    other.handle = 0;
}

VAO::~VAO() {
#ifndef NDEBUG
    if (this->handle != 0) {
        std::cout << "Delete VAO" << std::endl;
    }
#endif
    glDeleteVertexArrays(1, &this->handle);
}

VAO& VAO::operator=(VAO&& other) noexcept {
    handle = other.handle;
    other.handle = 0;
    return *this;
}

void VAO::bind() const { glBindVertexArray(handle); }

void VAO::addAttribute(GLint index, GLint size, GLenum type, VBO&& vbo) {
    this->bind();
    vbo.bind(GL_ARRAY_BUFFER);
    glVertexAttribPointer(index, size, type, 0, 0, nullptr);
    glEnableVertexAttribArray(index);

    attributes.emplace(index, std::move(vbo));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VAO VAO::empty() {
    GLuint hnd;
    glGenVertexArrays(1, &hnd);
    return VAO(hnd);
}

} // namespace gl