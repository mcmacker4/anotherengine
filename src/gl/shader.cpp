#include "shader.h"

#include <iostream>
#include <fstream>

namespace gl {

/*
 *  Shader
 *  Wrapper class for OpenGL object.
 *
 */

Shader::Shader(Shader&& other) noexcept {
    this->handle = other.handle;
    other.handle = 0;
}

Shader Shader::fromSource(const std::string& src, GLenum type) {
    GLuint hnd = glCreateShader(type);

    const char* srcPtr = src.c_str();
    GLint len = src.length();
    glShaderSource(hnd, 1, &srcPtr, &len);

    glCompileShader(hnd);
    GLint status;
    glGetShaderiv(hnd, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        GLchar buffer[512];
        glGetShaderInfoLog(hnd, 512, nullptr, buffer);
        std::cerr << buffer << std::endl;
        exit(1);
    }

    return Shader(hnd);
}

/*
 *  Shader Program
 *  Wrapper class for OpenGL object.
 *
 */

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept {
    this->handle = other.handle;
    other.handle = 0;
}

void ShaderProgram::bind() const {
    glUseProgram(this->handle);
}

void ShaderProgram::unbind() {
    glUseProgram(0);
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& rhs) noexcept {
    handle = rhs.handle;
    rhs.handle = 0;
    return *this;
}

ShaderProgram ShaderProgram::fromVertexFragment(Shader& vertex,
                                                Shader& fragment) {
    GLuint hnd = glCreateProgram();
    glAttachShader(hnd, vertex.handle);
    glAttachShader(hnd, fragment.handle);

    glLinkProgram(hnd);

    GLint status;
    glGetProgramiv(hnd, GL_LINK_STATUS, &status);

    if (status != GL_TRUE) {
        GLchar buffer[512];
        glGetProgramInfoLog(hnd, 512, nullptr, buffer);
        std::cerr << buffer << std::endl;
        exit(1);
    }

    glValidateProgram(hnd);
    glGetProgramiv(hnd, GL_VALIDATE_STATUS, &status);

    if (status != GL_TRUE) {
        GLchar buffer[512];
        glGetProgramInfoLog(hnd, 512, nullptr, buffer);
        std::cerr << buffer << std::endl;
        exit(1);
    }

    return ShaderProgram(hnd);
}

inline std::string readToString(const std::string& path) {
    std::ifstream stream(path);
    if (!stream.is_open()) {
        std::cerr << "Could not open file: "  << path << std::endl;
        exit(1);
    }
    return std::string(std::istreambuf_iterator<char>(stream),
                       std::istreambuf_iterator<char>());
}

ShaderProgram ShaderProgram::loadFromFile(const std::string& directory,
                                          const std::string& name) {
    auto fullname = directory + "/" + name;
    auto vertSrc = readToString(fullname + ".vert");
    auto fragSrc = readToString(fullname + ".frag");
    auto vert = Shader::fromSource(vertSrc, GL_VERTEX_SHADER);
    auto frag = Shader::fromSource(fragSrc, GL_FRAGMENT_SHADER);
    return fromVertexFragment(vert, frag);
}
}
