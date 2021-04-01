#ifndef ANOTHERENGINE_SHADER_H
#define ANOTHERENGINE_SHADER_H

#include <glad/glad.h>
#include <string>

namespace gl {

class Shader {
    GLuint handle;

    explicit Shader(GLuint handle) : handle(handle) {}

  public:
    Shader(const Shader&) = delete;
    Shader(Shader&& other) noexcept;

    static Shader fromSource(const std::string& src, GLenum type);

    friend class ShaderProgram;
};


class ShaderProgram {
    GLuint handle;

    explicit ShaderProgram(GLuint handle) : handle(handle) {}

  public:
    ShaderProgram(const Shader&) = delete;
    ShaderProgram(ShaderProgram&& other) noexcept;

    void bind() const;

    static void unbind();

    ShaderProgram& operator=(ShaderProgram&&) noexcept;

    static ShaderProgram fromVertexFragment(Shader& vertex, Shader& fragment);

    static ShaderProgram loadFromFile(const std::string& directory, const std::string& name);

};

}

#endif // ANOTHERENGINE_SHADER_H
