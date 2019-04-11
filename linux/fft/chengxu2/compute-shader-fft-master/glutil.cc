#include <fstream>
#include <streambuf>
#include <sstream>

#include <GL/glew.h>

#include "panic.h"
#include "glutil.h"

namespace gl {

//
//   s h a d e r
//

shader::shader(GLenum type)
    : id_ { GL_CHECK_R(glCreateShader(type)) }
{ }

void
shader::set_source(const std::string& source)
{
    const char *sources[] = { source.c_str() };
    GL_CHECK(glShaderSource(id_, 1, sources, nullptr));

    GL_CHECK(glCompileShader(id_));

    int rv;
    GL_CHECK(glGetShaderiv(id_, GL_COMPILE_STATUS, &rv));
    if (!rv) {
        GLchar buf[8192];
        GLsizei buf_length;
        glGetShaderInfoLog(id_, sizeof(buf) - 1, &buf_length, buf);

        panic("failed to compile shader:\n%.*s", buf_length, buf);
    }
}

void
shader::load_source(const std::string& filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    set_source(buffer.str());
}

//
//   p r o g r a m
//

program::program()
    : id_ { GL_CHECK_R(glCreateProgram()) }
{ }

void
program::attach(const shader& s)
{
    GL_CHECK(glAttachShader(id_, s.id_));
}

void
program::link()
{
    GL_CHECK(glLinkProgram(id_));

    int rv;
    GL_CHECK(glGetProgramiv(id_, GL_LINK_STATUS, &rv));
    if (!rv)
        panic("failed to link program");
}

void
program::use()
{
    GL_CHECK(glUseProgram(id_));
}

program::uniform
program::get_uniform(const std::string& name)
{
    GLint location = GL_CHECK_R(glGetUniformLocation(id_, name.c_str()));
    if (location < 0)
        panic("invalid uniform %s", name);
    return uniform(location);
}

program::uniform::uniform(GLint location)
    : location_ { location }
{ }

void
program::uniform::set_f(GLfloat v0)
{
    GL_CHECK(glUniform1f(location_, v0));
}

void
program::uniform::set_f(GLfloat v0, GLfloat v1)
{
    GL_CHECK(glUniform2f(location_, v0, v1));
}

void
program::uniform::set_f(GLfloat v0, GLfloat v1, GLfloat v2)
{
    GL_CHECK(glUniform3f(location_, v0, v1, v2));
}

void
program::uniform::set_f(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    GL_CHECK(glUniform4f(location_, v0, v1, v2, v3));
}

void
program::uniform::set_i(GLint v0)
{
    GL_CHECK(glUniform1i(location_, v0));
}

void
program::uniform::set_i(GLint v0, GLint v1)
{
    GL_CHECK(glUniform2i(location_, v0, v1));
}

void
program::uniform::set_i(GLint v0, GLint v1, GLint v2)
{
    GL_CHECK(glUniform3i(location_, v0, v1, v2));
}

void
program::uniform::set_i(GLint v0, GLint v1, GLint v2, GLint v3)
{
    GL_CHECK(glUniform4i(location_, v0, v1, v2, v3));
}

//
//   b u f f e r
//

buffer::buffer(GLenum target)
    : target_ { target }
{
    GL_CHECK(glGenBuffers(1, &id_));
}

void
buffer::bind()
{
    GL_CHECK(glBindBuffer(target_, id_));
}

void
buffer::bind_base(int index)
{
    GL_CHECK(glBindBufferBase(target_, index, id_));
}

void
buffer::set_data(GLsizeiptr size, const GLvoid *data)
{
    bind();
    GL_CHECK(glBufferData(target_, size, data, GL_STREAM_DRAW));
}

void
buffer::get_sub_data(GLintptr offset, GLsizeiptr size, GLvoid *data)
{
    bind();
    GL_CHECK(glGetBufferSubData(target_, offset, size, data));
}

} // gl
