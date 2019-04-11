#version 430

// based on the algorithm described in http://research.microsoft.com/pubs/70576/tr-2008-62.pdf

#define SIZE 512

#define PI 3.14159265358979323844

layout(local_size_x = SIZE) in;

layout(std430) buffer;

layout(binding = 0, r32f) writeonly uniform image2D dest_texture;

layout(binding = 1) readonly buffer Input {
    float input_data[SIZE];
};

shared vec2 values[SIZE][2];

void synchronize()
{
    memoryBarrierShared();
    barrier();
}

void
fft_pass(int ns, int source)
{
    uint i = gl_LocalInvocationID.x;

    uint base = (i/ns)*(ns/2);
    uint offs = i%(ns/2);

    uint i0 = base + offs;
    uint i1 = i0 + SIZE/2;
    
    vec2 v0 = values[i0][source];
    vec2 v1 = values[i1][source];
    
    float a = -2.*PI*float(i)/ns;

    float t_re = cos(a);
    float t_im = sin(a);

    values[i][source ^ 1] = v0 + vec2(dot(vec2(t_re, -t_im), v1), dot(vec2(t_im, t_re), v1));
}

void main()
{
    uint i = gl_LocalInvocationID.x;

    values[i][0] = vec2(input_data[i], 0.);
    synchronize();

    int source = 0;

    for (int n = 2; n <= SIZE; n *= 2) {
        fft_pass(n, source);
        source ^= 1;
        synchronize();
    }

    float v = length(values[i][source]);

    imageStore(dest_texture, ivec2(i, 0), vec4(v, 0., 0., 0.));
}
