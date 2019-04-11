#version 430

layout(binding = 0) uniform sampler2D src_texture;

in vec2 tex_coord;
out vec4 color;

void main()
{
   float v = texture(src_texture, vec2(.25*tex_coord.x, 0.)).r;
   float h = .1*sqrt(v);

   if (tex_coord.y > h)
       discard;

    color = vec4(1., 0., 0., 1.);
}
