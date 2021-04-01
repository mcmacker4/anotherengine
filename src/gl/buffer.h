#ifndef MINECPP_SRC_GL_OBJECTS_H
#define MINECPP_SRC_GL_OBJECTS_H

#include <glad/glad.h>
#include <unordered_map>

namespace gl {

class VBO {
    GLuint handle;

    explicit VBO(GLuint handle) : handle(handle) {}

  public:
    VBO(const VBO&) = delete;
    ~VBO();
    VBO(VBO&&) noexcept;

    void bind(GLuint target) const;

    VBO& operator=(VBO&& rhs) noexcept;

    static VBO vertex_buffer(const void* data, unsigned int bytes, GLuint target, GLenum usage);

    friend class VAO;
};



class VAO {
    GLuint handle;

    std::unordered_map<GLint, VBO> attributes;

    explicit VAO(GLuint handle) : handle(handle), attributes() {}

  public:
    VAO(const VAO&) = delete;
    ~VAO();
    VAO(VAO&& other) noexcept;

    VAO& operator=(VAO&& other) noexcept;

    void bind() const;

    void addAttribute(GLint index, GLint size, GLenum type, VBO&& vbo);

    static VAO empty();
};




}

#endif // MINECPP_SRC_GL_OBJECTS_H
