#pragma once

#include <string>
#include <GL/gl.h>

#include "panic.h"

#define GL_CHECK(expr) \
    [&] { \
        expr; \
        auto e = glGetError(); \
        if (e != GL_NO_ERROR) \
            panic("%s:%d: GL error: %x", __FILE__, __LINE__, e); \
    }()

#define GL_CHECK_R(expr) \
    [&] { \
        auto r = expr; \
        auto e = glGetError(); \
        if (e != GL_NO_ERROR) \
            panic("%s:%d: GL error: %x", __FILE__, __LINE__, e); \
        return r; \
    }()

namespace gl {

class noncopyable
{
protected:
    noncopyable() = default;
    ~noncopyable() = default;

    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;
};

class shader : private noncopyable
{
public:
    shader(GLenum type);

    void set_source(const std::string& source);
    void load_source(const std::string& filename);

private:
    friend class program;
    GLuint id_;
};

class program : private noncopyable
{
public:
    program();

    void attach(const shader& s);
    void link();

    void use();

    class uniform
    {
    public:
        uniform(GLint location);

        void set_f(GLfloat v0);
        void set_f(GLfloat v0, GLfloat v1);
        void set_f(GLfloat v0, GLfloat v1, GLfloat v2);
        void set_f(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

        void set_i(GLint v0);
        void set_i(GLint v0, GLint v1);
        void set_i(GLint v0, GLint v1, GLint v2);
        void set_i(GLint v0, GLint v1, GLint v2, GLint v3);

    private:
        GLint location_;
    };

    uniform get_uniform(const std::string& name);

private:
    GLuint id_;
};

class buffer : private noncopyable
{
public:
    buffer(GLenum target);

    void bind();
    void bind_base(int index);

    void set_data(GLsizeiptr size, const GLvoid *data);
    void get_sub_data(GLintptr offset, GLsizeiptr size, GLvoid *data);

private:
    GLuint id_;
    GLenum target_;
};

} // gl
