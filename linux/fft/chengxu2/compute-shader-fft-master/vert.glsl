#version 430

layout(location = 0) in vec2 pos;

out vec2 tex_coord;

void main()
{
    tex_coord = .5f + .5f*pos;
    gl_Position = vec4(pos.x, pos.y, 0., 1.);
}
