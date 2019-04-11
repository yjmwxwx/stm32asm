#version 430

#define SIZE 8
#define PI 3.14159265358979323844

layout(local_size_x = SIZE) in;

layout(std430) buffer;

layout(binding = 0) readonly buffer Input {
    vec2 input_data[SIZE];
};

layout(binding = 1) writeonly buffer Output {
    vec2 output_data[SIZE];
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
    int i = int(gl_LocalInvocationID.x);

    int base = (i/ns)*(ns/2);
    int offs = i%(ns/2);

    int i0 = base + offs;
    int i1 = i0 + SIZE/2;
    
    vec2 v0 = values[i0][source];
    vec2 v1 = values[i1][source];
    
    float a = -2.*PI*float(i)/ns;

    float t_re = cos(a);
    float t_im = sin(a);

    values[i][source ^ 1] = v0 + vec2(dot(vec2(t_re, -t_im), v1), dot(vec2(t_im, t_re), v1));
}

void main()
{
    const uint i = gl_LocalInvocationID.x;

    values[i][0] = input_data[i];
    synchronize();

    int source = 0;

    for (int n = 2; n <= SIZE; n *= 2) {
        fft_pass(n, source);
        source ^= 1;

        synchronize();
    }

    output_data[i] = values[i][source];
}
